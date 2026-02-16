/*
 * LCC (Layout Command Control / OpenLCB) Node for ESP32
 * Uses ESP32 Built-in CAN Controller (TWAI)
 * 
 * Hardware:
 * - ESP32 DevKit (any variant)
 * - SN65HVD230 or TJA1050 CAN transceiver
 * 
 * Wiring:
 * ESP32 GPIO5  → CAN Transceiver CTX (TX)
 * ESP32 GPIO4  → CAN Transceiver CRX (RX)
 * ESP32 3.3V   → Transceiver VCC
 * ESP32 GND    → Transceiver GND
 * 
 * Transceiver CANH/CANL → CAN Bus (RJ45 pins 3/4)
 * 
 * Features:
 * - Node initialization and identification
 * - Event producers (button)
 * - Event consumers (LED)
 * - Serial debug output
 */

#include <driver/twai.h>

// ============================================================================
// CONFIGURATION - CUSTOMIZE THESE VALUES
// ============================================================================

// Your unique Node ID (48 bits total)
#define NODE_ID_HIGH    0x02        // Manufacturer ID (keep as 0x02 for DIY)
#define NODE_ID_MID     0x01        // Product line
#define NODE_ID_LOW     0x87654321  // Serial number - CHANGE THIS!

// Event IDs - based on your Node ID
#define EVENT_BUTTON_PRESSED   0x0201876543210001ULL
#define EVENT_BUTTON_RELEASED  0x0201876543210002ULL
#define EVENT_LED_ON           0x0201876543210010ULL
#define EVENT_LED_OFF          0x0201876543210011ULL

// Pin definitions (can be changed)
#define CAN_TX_PIN      GPIO_NUM_5   // CAN TX
#define CAN_RX_PIN      GPIO_NUM_4   // CAN RX
#define LED_PIN         GPIO_NUM_2   // Built-in LED
#define BUTTON_PIN      GPIO_NUM_0   // Boot button

// ============================================================================
// LCC MESSAGE TYPE IDENTIFIERS (MTI)
// ============================================================================

#define MTI_INITIALIZATION_COMPLETE     0x0100
#define MTI_VERIFY_NODE_ID_GLOBAL       0x0490
#define MTI_VERIFY_NODE_ID_ADDRESSED    0x0488
#define MTI_VERIFIED_NODE_ID            0x0170
#define MTI_PRODUCER_IDENTIFIED_VALID   0x0544
#define MTI_PRODUCER_IDENTIFIED_INVALID 0x0545

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

uint64_t nodeID;
uint16_t nodeAlias;

// Button debouncing
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// ============================================================================
// SETUP
// ============================================================================

void setup() {
  // Initialize Serial
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== ESP32 LCC Node Starting ===");
  
  // Construct Node ID
  nodeID = ((uint64_t)NODE_ID_HIGH << 40) |
           ((uint64_t)NODE_ID_MID << 32) |
           ((uint64_t)NODE_ID_LOW);
  
  Serial.print("Node ID: 0x");
  Serial.println((uint32_t)(nodeID >> 32), HEX);
  Serial.println((uint32_t)(nodeID & 0xFFFFFFFF), HEX);
  
  // Generate alias (simplified)
  nodeAlias = (uint16_t)((nodeID >> 24) & 0x0FFF);
  if (nodeAlias == 0) nodeAlias = 0x234;
  
  Serial.print("Node Alias: 0x");
  Serial.println(nodeAlias, HEX);
  
  // Initialize pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
  
  // Initialize CAN (TWAI)
  Serial.print("Initializing CAN... ");
  if (initCAN()) {
    Serial.println("OK");
  } else {
    Serial.println("FAILED!");
    errorBlink();
  }
  
  // Send Initialization Complete
  delay(100);
  sendInitializationComplete();
  
  // Blink LED to show ready
  for(int i = 0; i < 6; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
  
  Serial.println("=== ESP32 LCC Node Ready ===\n");
}

// ============================================================================
// MAIN LOOP
// ============================================================================

void loop() {
  // Process incoming CAN messages
  processCANMessages();
  
  // Check button state
  checkButton();
  
  // Small delay
  delay(10);
}

// ============================================================================
// CAN FUNCTIONS
// ============================================================================

/**
 * Initialize CAN (TWAI) controller
 */
bool initCAN() {
  // Configure CAN timing for 125 kbps
  // ESP32 APB clock is typically 80 MHz
  twai_timing_config_t timing_config = TWAI_TIMING_CONFIG_125KBITS();
  
  // Configure CAN filter to accept all messages
  twai_filter_config_t filter_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
  
  // Configure CAN controller
  twai_general_config_t general_config = TWAI_GENERAL_CONFIG_DEFAULT(
    CAN_TX_PIN, 
    CAN_RX_PIN, 
    TWAI_MODE_NORMAL
  );
  
  general_config.tx_queue_len = 10;
  general_config.rx_queue_len = 10;
  
  // Install TWAI driver
  if (twai_driver_install(&general_config, &timing_config, &filter_config) != ESP_OK) {
    return false;
  }
  
  // Start TWAI driver
  if (twai_start() != ESP_OK) {
    return false;
  }
  
  return true;
}

/**
 * Send a CAN frame
 */
void sendCANFrame(uint32_t id, uint8_t* data, uint8_t len) {
  twai_message_t message;
  
  message.identifier = id;
  message.extd = 1;  // Extended frame (29-bit)
  message.rtr = 0;   // Data frame
  message.data_length_code = len;
  
  for (int i = 0; i < len && i < 8; i++) {
    message.data[i] = data[i];
  }
  
  // Transmit message
  if (twai_transmit(&message, pdMS_TO_TICKS(100)) != ESP_OK) {
    Serial.println("CAN TX failed");
  }
}

/**
 * Process incoming CAN messages
 */
void processCANMessages() {
  twai_message_t message;
  
  // Check for received messages
  if (twai_receive(&message, pdMS_TO_TICKS(0)) == ESP_OK) {
    // Only process extended frames
    if (message.extd) {
      uint32_t canID = message.identifier;
      uint16_t mti = (canID >> 12) & 0x0FFF;
      uint16_t srcAlias = canID & 0x0FFF;
      
      // Handle different message types
      switch (mti) {
        case MTI_VERIFY_NODE_ID_GLOBAL:
          Serial.println("Received: Verify Node ID (Global)");
          sendVerifiedNodeID();
          break;
          
        case MTI_VERIFY_NODE_ID_ADDRESSED:
          if (message.data_length_code >= 6) {
            uint64_t targetID = ((uint64_t)message.data[0] << 40) |
                               ((uint64_t)message.data[1] << 32) |
                               ((uint64_t)message.data[2] << 24) |
                               ((uint64_t)message.data[3] << 16) |
                               ((uint64_t)message.data[4] << 8) |
                               message.data[5];
            
            if (targetID == nodeID) {
              Serial.println("Received: Verify Node ID (Addressed to us)");
              sendVerifiedNodeID();
            }
          }
          break;
          
        case MTI_PRODUCER_IDENTIFIED_VALID:
          if (message.data_length_code == 8) {
            uint64_t eventID = ((uint64_t)message.data[0] << 56) |
                              ((uint64_t)message.data[1] << 48) |
                              ((uint64_t)message.data[2] << 40) |
                              ((uint64_t)message.data[3] << 32) |
                              ((uint64_t)message.data[4] << 24) |
                              ((uint64_t)message.data[5] << 16) |
                              ((uint64_t)message.data[6] << 8) |
                              message.data[7];
            
            handleEvent(eventID);
          }
          break;
      }
    }
  }
}

// ============================================================================
// LCC PROTOCOL FUNCTIONS
// ============================================================================

/**
 * Send Initialization Complete message
 */
void sendInitializationComplete() {
  uint8_t data[6];
  
  data[0] = (nodeID >> 40) & 0xFF;
  data[1] = (nodeID >> 32) & 0xFF;
  data[2] = (nodeID >> 24) & 0xFF;
  data[3] = (nodeID >> 16) & 0xFF;
  data[4] = (nodeID >> 8) & 0xFF;
  data[5] = nodeID & 0xFF;
  
  uint32_t canID = ((uint32_t)MTI_INITIALIZATION_COMPLETE << 12) | nodeAlias;
  
  sendCANFrame(canID, data, 6);
  
  Serial.println("Sent: Initialization Complete");
}

/**
 * Send Verified Node ID message
 */
void sendVerifiedNodeID() {
  uint8_t data[6];
  
  data[0] = (nodeID >> 40) & 0xFF;
  data[1] = (nodeID >> 32) & 0xFF;
  data[2] = (nodeID >> 24) & 0xFF;
  data[3] = (nodeID >> 16) & 0xFF;
  data[4] = (nodeID >> 8) & 0xFF;
  data[5] = nodeID & 0xFF;
  
  uint32_t canID = ((uint32_t)MTI_VERIFIED_NODE_ID << 12) | nodeAlias;
  
  sendCANFrame(canID, data, 6);
  
  Serial.println("Sent: Verified Node ID");
}

/**
 * Send an event (producer)
 */
void sendEvent(uint64_t eventID, bool valid) {
  uint8_t data[8];
  
  data[0] = (eventID >> 56) & 0xFF;
  data[1] = (eventID >> 48) & 0xFF;
  data[2] = (eventID >> 40) & 0xFF;
  data[3] = (eventID >> 32) & 0xFF;
  data[4] = (eventID >> 24) & 0xFF;
  data[5] = (eventID >> 16) & 0xFF;
  data[6] = (eventID >> 8) & 0xFF;
  data[7] = eventID & 0xFF;
  
  uint16_t mti = valid ? MTI_PRODUCER_IDENTIFIED_VALID : MTI_PRODUCER_IDENTIFIED_INVALID;
  uint32_t canID = ((uint32_t)mti << 12) | nodeAlias;
  
  sendCANFrame(canID, data, 8);
  
  Serial.print("Sent Event: 0x");
  Serial.println((uint32_t)(eventID & 0xFFFFFFFF), HEX);
}

/**
 * Handle consumed events (LED control)
 */
void handleEvent(uint64_t eventID) {
  Serial.print("Received Event: 0x");
  Serial.println((uint32_t)(eventID & 0xFFFFFFFF), HEX);
  
  if (eventID == EVENT_LED_ON) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON");
  }
  else if (eventID == EVENT_LED_OFF) {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF");
  }
}

// ============================================================================
// INPUT HANDLING
// ============================================================================

/**
 * Check button and send events
 */
void checkButton() {
  bool reading = digitalRead(BUTTON_PIN);
  
  // Debounce
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    static bool buttonState = HIGH;
    
    if (reading != buttonState) {
      buttonState = reading;
      
      if (buttonState == LOW) {
        // Button pressed
        Serial.println("Button PRESSED");
        sendEvent(EVENT_BUTTON_PRESSED, true);
      } else {
        // Button released
        Serial.println("Button RELEASED");
        sendEvent(EVENT_BUTTON_RELEASED, true);
      }
    }
  }
  
  lastButtonState = reading;
}

// ============================================================================
// ERROR HANDLING
// ============================================================================

/**
 * Error handler - blink LED rapidly forever
 */
void errorBlink() {
  while(1) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

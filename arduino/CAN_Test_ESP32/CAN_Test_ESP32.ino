/*
 * ESP32 Built-in CAN Test
 * Tests the ESP32 TWAI (CAN) controller
 * 
 * Wiring:
 * ESP32 GPIO5  → CAN Transceiver CTX
 * ESP32 GPIO4  → CAN Transceiver CRX
 * ESP32 3.3V   → Transceiver VCC
 * ESP32 GND    → Transceiver GND
 * 
 * Expected behavior:
 * - LED blinks fast (10 times) = Test PASSED
 * - LED blinks slow continuously = Test FAILED
 */

#include <driver/twai.h>

#define CAN_TX_PIN  GPIO_NUM_5
#define CAN_RX_PIN  GPIO_NUM_4
#define LED_PIN     GPIO_NUM_2

bool allTestsPassed = false;

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  Serial.println("\n=== ESP32 CAN Test ===");
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Initial blink
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
  
  delay(500);
  
  // Run tests
  allTestsPassed = runTests();
  
  if (allTestsPassed) {
    Serial.println("\n✓ ALL TESTS PASSED!");
    
    // Success: Fast blinks
    for(int i = 0; i < 10; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
  } else {
    Serial.println("\n✗ TESTS FAILED");
  }
}

void loop() {
  // Indicate test result
  static unsigned long lastBlink = 0;
  unsigned long interval = allTestsPassed ? 500 : 1000;
  
  if (millis() - lastBlink > interval) {
    lastBlink = millis();
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
}

bool runTests() {
  bool passed = true;
  
  // Test 1: Initialize CAN
  Serial.print("Test 1: Initialize CAN... ");
  
  twai_timing_config_t timing_config = TWAI_TIMING_CONFIG_125KBITS();
  twai_filter_config_t filter_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
  twai_general_config_t general_config = TWAI_GENERAL_CONFIG_DEFAULT(
    CAN_TX_PIN, 
    CAN_RX_PIN, 
    TWAI_MODE_NORMAL
  );
  
  if (twai_driver_install(&general_config, &timing_config, &filter_config) != ESP_OK) {
    Serial.println("FAILED (driver install)");
    return false;
  }
  
  if (twai_start() != ESP_OK) {
    Serial.println("FAILED (start)");
    return false;
  }
  
  Serial.println("PASSED");
  delay(100);
  
  // Test 2: Switch to loopback mode
  Serial.print("Test 2: Loopback mode... ");
  
  twai_stop();
  twai_driver_uninstall();
  
  general_config.mode = TWAI_MODE_NO_ACK;  // Loopback-like mode
  
  if (twai_driver_install(&general_config, &timing_config, &filter_config) != ESP_OK) {
    Serial.println("FAILED (reinstall)");
    return false;
  }
  
  if (twai_start() != ESP_OK) {
    Serial.println("FAILED (restart)");
    return false;
  }
  
  Serial.println("PASSED");
  delay(100);
  
  // Test 3: Send and receive message
  Serial.print("Test 3: Send/Receive test... ");
  
  twai_message_t tx_msg;
  tx_msg.identifier = 0x123;
  tx_msg.extd = 1;
  tx_msg.rtr = 0;
  tx_msg.data_length_code = 4;
  tx_msg.data[0] = 0xAA;
  tx_msg.data[1] = 0xBB;
  tx_msg.data[2] = 0xCC;
  tx_msg.data[3] = 0xDD;
  
  if (twai_transmit(&tx_msg, pdMS_TO_TICKS(1000)) != ESP_OK) {
    Serial.println("FAILED (transmit)");
    passed = false;
  } else {
    Serial.println("PASSED");
  }
  
  delay(100);
  
  // Test 4: Check CAN state
  Serial.print("Test 4: CAN state check... ");
  
  twai_status_info_t status_info;
  if (twai_get_status_info(&status_info) == ESP_OK) {
    Serial.print("PASSED (State: ");
    switch(status_info.state) {
      case TWAI_STATE_RUNNING: Serial.print("RUNNING"); break;
      case TWAI_STATE_BUS_OFF: Serial.print("BUS_OFF"); break;
      case TWAI_STATE_RECOVERING: Serial.print("RECOVERING"); break;
      default: Serial.print("UNKNOWN");
    }
    Serial.println(")");
  } else {
    Serial.println("FAILED");
    passed = false;
  }
  
  delay(100);
  
  // Test 5: Cleanup
  Serial.print("Test 5: Cleanup... ");
  
  twai_stop();
  twai_driver_uninstall();
  
  Serial.println("PASSED");
  
  return passed;
}

# ESP32 LCC Node - Quick Setup Guide

## Why Choose ESP32 for LCC?

✅ **Cheaper:** $8 total vs $18 for STM32
✅ **Simpler:** Built-in CAN controller (no MCP2515!)
✅ **More powerful:** Dual-core, WiFi, Bluetooth
✅ **Future-proof:** Can add WiFi config, OTA updates, MQTT bridge

---

## What You Need (~$10 total)

1. **ESP32 DevKit** - $6-8
   - Any ESP32 board works
   - Search: "ESP32 development board"
   
2. **SN65HVD230 CAN Transceiver** - $1-2
   - 3.3V transceiver module
   - Search: "SN65HVD230"
   
3. **RJ45 Breakout Board** - $2-3
   - Screw terminal type
   - Search: "RJ45 screw terminal adapter"

**Already have from STM32 project?** Just need ESP32 + transceiver!

---

## 5-Minute Setup

### Step 1: Install Arduino IDE

If you haven't already:
1. Download from arduino.cc
2. Install and launch

### Step 2: Add ESP32 Board Support

1. **File → Preferences**
2. **Additional Board Manager URLs**, add:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. **Tools → Board → Boards Manager**
4. Search: **ESP32**
5. Install: **esp32 by Espressif Systems**
6. Wait for installation (takes 2-3 minutes)

### Step 3: Wire Hardware

**Super simple - only 4 wires!**

```
ESP32 → SN65HVD230 → RJ45
─────────────────────────
3.3V  → VCC
GND   → GND          → Pin 1,2
GPIO5 → CTX
GPIO4 → CRX
        CANH         → Pin 3
        CANL         → Pin 4
```

**Detailed wiring:** See [ESP32_WIRING.md](ESP32_WIRING.md)

### Step 4: Upload Test Sketch

1. **File → Open** → `CAN_Test_ESP32.ino`
2. **Tools → Board** → ESP32 Dev Module
3. **Tools → Port** → Select your port (COM# or /dev/tty*)
4. Click **Upload** (→)
5. **Tools → Serial Monitor** (set to 115200)
6. Should see: **"✓ ALL TESTS PASSED!"**

### Step 5: Upload LCC Node

1. **File → Open** → `LCC_Node_ESP32.ino`
2. **Edit Node ID** (lines 23-25) - make it unique!
   ```cpp
   #define NODE_ID_LOW     0x87654321  // CHANGE THIS!
   ```
3. Click **Upload**
4. Done! Your LCC node is running! 🎉

---

## Testing Your Node

### Open Serial Monitor

**Tools → Serial Monitor** (115200 baud)

You should see:
```
=== ESP32 LCC Node Starting ===
Node ID: 0x201
87654321
Node Alias: 0x765
Initializing CAN... OK
Sent: Initialization Complete
=== ESP32 LCC Node Ready ===
```

### Test Button

Press **BOOT button** on ESP32 → Should see:
```
Button PRESSED
Sent Event: 0x43210001
Button RELEASED
Sent Event: 0x43210002
```

### Connect to Network

1. Plug RJ45 cable into CAN bus
2. Add 120Ω terminator if this is end node
3. Test with another LCC node!

---

## Pin Reference

### Default Pins (Can be changed in code):

| Function | Pin | Notes |
|----------|-----|-------|
| CAN TX | GPIO5 | To transceiver CTX |
| CAN RX | GPIO4 | To transceiver CRX |
| LED | GPIO2 | Built-in LED |
| Button | GPIO0 | BOOT button |

### Changing Pins:

Just edit in the sketch:
```cpp
#define CAN_TX_PIN  GPIO_NUM_21  // Any GPIO
#define CAN_RX_PIN  GPIO_NUM_22  // Any GPIO
```

---

## Comparison with STM32 Version

### What's Different?

| Feature | ESP32 | STM32F303RE |
|---------|-------|-------------|
| **CAN Hardware** | Built-in | External (MCP2515) |
| **Wiring** | 4 wires | 8+ wires (SPI) |
| **Cost** | ~$8 | ~$18 |
| **Programming** | Arduino IDE | Arduino or STM32Cube |
| **WiFi/BT** | ✅ Yes | ❌ No |
| **Speed** | 240 MHz | 72 MHz |
| **Complexity** | Simpler | More complex |

### What's the Same?

- ✅ LCC protocol implementation
- ✅ RJ45 connectors
- ✅ Bus power capable
- ✅ Daisy-chain support
- ✅ Event producers/consumers

---

## Troubleshooting

### "Board not found" in Boards Manager

**Solution:**
1. Check Board Manager URL is correct
2. Restart Arduino IDE
3. Try again

### "Port not found" or can't upload

**Solution:**
1. Install CP210x or CH340 USB driver
2. Try different USB cable
3. Hold BOOT button while uploading

### "CAN initialization failed"

**Check:**
- SN65HVD230 has 3.3V power
- GPIO5 and GPIO4 wired correctly
- Selected "ESP32 Dev Module" as board

### No CAN messages received

**Check:**
- CANH/CANL connected to bus
- 120Ω termination on both ends
- Baud rate is 125kbps
- Other nodes on bus

---

## Next Steps

### 1. Basic Usage
- ✅ You're here - node works!
- Connect to LCC network
- Test button → LED communication

### 2. Customize
- Change Node ID
- Add more events
- Connect sensors/outputs

### 3. Advanced Features
- WiFi configuration interface
- MQTT bridge
- OTA firmware updates
- Mobile app control

### 4. Hardware
- Add second RJ45 for daisy-chain
- Add bus power
- Design custom PCB
- 3D print enclosure

---

## Bonus: WiFi Features (Coming Soon!)

ESP32's WiFi enables cool features:

### Web Configuration Interface
```
http://lcc-node.local
- Configure Node ID
- Set event mappings
- View statistics
```

### MQTT Bridge
```
LCC Events ←→ MQTT Topics
Integrate with Home Assistant!
```

### OTA Updates
```
Upload new firmware over WiFi
No need to disconnect from bus!
```

---

## Example Projects

### 1. Basic Communication
- **Node 1:** Button → Sends event
- **Node 2:** Receives event → Lights LED

### 2. Turnout Control
- Control servo motors
- Feedback sensors
- WiFi status monitoring

### 3. Block Detector
- IR sensors detect trains
- Publish occupancy events
- WiFi dashboard shows layout

### 4. WiFi-LCC Bridge
- MQTT broker connection
- Control layout from phone
- Home automation integration

---

## Resources

### Documentation
- [ESP32_WIRING.md](ESP32_WIRING.md) - Detailed wiring
- [ESP32_ADVANCED.md](ESP32_ADVANCED.md) - Advanced features
- [COMPARISON.md](COMPARISON.md) - ESP32 vs STM32

### Hardware
- [Transceiver Guide](TRANSCEIVER_GUIDE.md)
- [RJ45 Setup](RJ45_SETUP.md)
- [Bus Power](BUS_POWER.md)

### Software
- [Arduino Examples](examples/)
- [LCC Protocol](LCC_PROTOCOL.md)
- [WiFi Features](WIFI_FEATURES.md)

---

## Get Help

- **GitHub Issues:** Report bugs
- **GitHub Discussions:** Ask questions
- **LCC Community:** OpenLCB forums

---

## Summary Checklist

- [ ] Arduino IDE installed
- [ ] ESP32 board support added
- [ ] Hardware wired (4 connections)
- [ ] Test sketch uploaded and passed
- [ ] LCC node sketch uploaded
- [ ] Node ID customized
- [ ] Connected to CAN bus
- [ ] Tested with another node
- [ ] **Ready to build your layout!** 🚂

---

**Questions?** Check [ESP32_WIRING.md](ESP32_WIRING.md) or open an issue!

**Cost:** ~$8-10 total
**Time:** 15 minutes setup
**Difficulty:** ⭐⭐☆☆☆ (Easy!)

🚀 **Happy building!** 🚀

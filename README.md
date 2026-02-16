## ⚠️ CRITICAL: NMRA S-9.7.1.1 Compliant

This project uses the **official NMRA S-9.7.1.1 standard** pinout.

**Required:** Pins 3 and 6 must be connected together inside your node!

See [NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md](docs/NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md)


# ESP32 LCC Node with Built-in CAN

A complete implementation of an LCC (Layout Command Control / OpenLCB) node using ESP32 with its built-in CAN controller (TWAI).

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-ESP32-red.svg)
![Arduino](https://img.shields.io/badge/Arduino-compatible-orange.svg)

## 📋 Overview

This project provides everything you need to build professional LCC nodes using ESP32:

- ✅ **Uses built-in CAN** - No MCP2515 needed!
- ✅ **Much cheaper** - ESP32 boards as low as $5
- ✅ **More powerful** - Dual-core, WiFi, Bluetooth
- ✅ **Easy programming** - Arduino IDE support
- ✅ **Professional** - RJ45 connectors, bus power, daisy-chain

## 🚀 Why ESP32 for LCC?

### Advantages over STM32:

| Feature | ESP32 | STM32F303RE |
|---------|-------|-------------|
| **Built-in CAN** | ✅ Yes (TWAI) | ❌ No |
| **Price** | ~$5-10 | ~$15 |
| **External IC needed** | Only transceiver (~$1) | MCP2515 (~$3) |
| **WiFi/Bluetooth** | ✅ Built-in | ❌ No |
| **Programming** | Arduino IDE | More complex |
| **Speed** | 240 MHz dual-core | 72 MHz |
| **Total cost** | ~$6-11 | ~$18-20 |

### ESP32 Built-in CAN (TWAI)

ESP32 has a **CAN 2.0B controller built into the chip!**
- No external controller needed
- Just add a CAN transceiver (SN65HVD230 or TJA1050)
- Cheaper and simpler hardware

## 🔌 Hardware Requirements

### Minimal Setup (~$6 total):

| Item | Price | Notes |
|------|-------|-------|
| ESP32 DevKit | $5-8 | Any ESP32 board |
| SN65HVD230 CAN Transceiver | $1-2 | 3.3V transceiver |
| RJ45 Breakout | $2-3 | For connections |
| **Total** | **~$8-13** | vs $18+ for STM32 |

### Professional Setup:

Add for production nodes:
- Second RJ45 for daisy-chain (+$3)
- Voltage regulators for bus power (+$5)
- Enclosure (+$5)

## 📦 Quick Start

### 1. Install Arduino IDE

Download from: https://www.arduino.cc/en/software

### 2. Add ESP32 Board Support

1. Arduino IDE → File → Preferences
2. Additional Board Manager URLs:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Tools → Board → Boards Manager
4. Search "ESP32"
5. Install "esp32 by Espressif Systems"

### 3. Wire Your Hardware

**ESP32 → CAN Transceiver (SN65HVD230):**

```
ESP32 GPIO5  → CTX (CAN TX)
ESP32 GPIO4  → CRX (CAN RX)
ESP32 3.3V   → VCC
ESP32 GND    → GND

CAN Transceiver:
CANH → RJ45 Pin 3
CANL → RJ45 Pin 4
```

### 4. Upload Sketch

1. Open: `arduino/LCC_Node_ESP32/LCC_Node_ESP32.ino`
2. Select Board: Tools → Board → ESP32 Dev Module
3. Select Port: Tools → Port → (your COM port)
4. Upload!

## 📁 Project Structure

```
ESP32-LCC-Node/
├── arduino/
│   ├── LCC_Node_ESP32/          # Main LCC node
│   └── CAN_Test_ESP32/          # Hardware test
│
├── docs/
│   ├── ESP32_SETUP_GUIDE.md     # Complete setup
│   ├── ESP32_WIRING.md          # Hardware connections
│   ├── RJ45_CONNECTION.md       # RJ45 setup
│   ├── BUS_POWER.md             # Power from bus
│   └── LCC_PROTOCOL.md          # Protocol reference
│
├── hardware/
│   └── schematics/              # Circuit diagrams
│
├── README.md
└── LICENSE
```

## 🎯 Features

### LCC Protocol Support

- ✅ Node initialization and identification
- ✅ Verify Node ID (global and addressed)
- ✅ Event producers (buttons, sensors)
- ✅ Event consumers (LEDs, relays)
- ✅ CAN bus at 125 kbps (LCC standard)
- ⏳ Simple Node Information Protocol (planned)
- ⏳ Configuration via WiFi (ESP32 exclusive!)

### Hardware Features

- Built-in CAN controller (no external chip!)
- RJ45 connectors
- Dual RJ45 for daisy-chaining
- Bus power support (12V → 3.3V)
- Optional WiFi configuration interface
- Optional Bluetooth for mobile app control

## 🔧 Pin Mapping

### Default ESP32 Pins:

| Function | GPIO | Notes |
|----------|------|-------|
| CAN TX | GPIO5 | To transceiver CTX |
| CAN RX | GPIO4 | To transceiver CRX |
| LED | GPIO2 | Built-in LED |
| Button | GPIO0 | Boot button (pull-up) |

**Can be changed in code!** ESP32 has flexible pin mapping.

## 💡 Bonus Features (ESP32 Exclusive!)

### 1. WiFi Configuration Interface

Access your node via web browser:
- Configure Node ID
- Set event mappings
- View status and statistics
- Update firmware OTA

### 2. Bluetooth App Control

Control your layout from phone:
- Send events
- Monitor node status
- Configure settings

### 3. MQTT Bridge

Connect LCC to MQTT for home automation:
- Integrate with Home Assistant
- Control from Alexa/Google Home
- Log events to database

## 📊 ESP32 vs STM32 Comparison

### Cost Breakdown:

**ESP32 Solution:**
```
ESP32 Board:     $6
CAN Transceiver: $1
RJ45 Breakout:   $3
Total:          $10
```

**STM32 Solution:**
```
STM32 Nucleo:   $15
MCP2515:         $3
RJ45 Breakout:   $3
Total:          $21
```

**Savings: $11 per node!**

### Performance:

| Metric | ESP32 | STM32F303RE |
|--------|-------|-------------|
| CPU Speed | 240 MHz (dual) | 72 MHz |
| RAM | 520 KB | 64 KB |
| Flash | 4 MB | 512 KB |
| WiFi | ✅ | ❌ |
| Bluetooth | ✅ | ❌ |

## 🛠️ Advanced Features

### Multi-Protocol Support

Since ESP32 has WiFi + CAN:
- Bridge between LCC and WiFi devices
- Remote node monitoring
- Cloud logging
- Mobile app integration

### OTA Updates

Update firmware over WiFi:
- No need to physically access node
- Update entire network remotely
- Rollback capability

## 📚 Documentation

### Getting Started
- [ESP32 Setup Guide](docs/ESP32_SETUP_GUIDE.md)
- [Hardware Wiring](docs/ESP32_WIRING.md)
- [Quick Reference](docs/ESP32_QUICK_REFERENCE.md)

### Hardware
- [CAN Transceiver Guide](docs/CAN_TRANSCEIVER.md)
- [RJ45 Connections](docs/RJ45_CONNECTION.md)
- [Bus Power Setup](docs/BUS_POWER.md)

### Software
- [Arduino Examples](docs/EXAMPLES.md)
- [LCC Protocol](docs/LCC_PROTOCOL.md)
- [WiFi Configuration](docs/WIFI_CONFIG.md)

## 🎨 Example Projects

1. **Basic LCC Node** - Button → LED communication
2. **Turnout Controller** - Control servos via LCC
3. **Block Detector** - IR sensors to LCC events
4. **WiFi Bridge** - LCC ↔ MQTT gateway
5. **Mobile Dashboard** - Monitor layout from phone

## 🤝 Contributing

Contributions welcome! This is a sister project to STM32-LCC-Node.

## 📜 License

MIT License - see [LICENSE](LICENSE) file

## 🙏 Acknowledgments

- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
- [OpenLCB.org](https://openlcb.org) - LCC standards
- [STM32-LCC-Node](https://github.com/yourusername/STM32-LCC-Node) - Inspiration

## 🗺️ Roadmap

- [x] Basic LCC node implementation
- [x] Built-in CAN support
- [ ] WiFi configuration interface
- [ ] MQTT bridge
- [ ] Mobile app (Bluetooth)
- [ ] OTA updates
- [ ] Custom PCB design
- [ ] 3D printed enclosure

---

**Made with ❤️ for the model railroad community**

🚂 **Cheaper, Faster, Better!** 🚂

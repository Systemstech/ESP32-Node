# 🚀 ESP32 LCC Node - START HERE!

## Why ESP32 is Better Than STM32 for LCC

✅ **$10 cheaper** per node ($8 vs $18)
✅ **Simpler wiring** - Built-in CAN controller (no MCP2515!)
✅ **More powerful** - 240MHz dual-core, 520KB RAM
✅ **WiFi + Bluetooth** included - Future expansion possibilities
✅ **Easier programming** - Native Arduino support

---

## What's Included

```
ESP32-LCC-Node/
├── arduino/
│   ├── LCC_Node_ESP32/          # Main LCC node sketch
│   └── CAN_Test_ESP32/          # Hardware test sketch
│
├── docs/
│   ├── ESP32_QUICK_START.md     # ← READ THIS FIRST!
│   ├── ESP32_WIRING.md          # Detailed wiring guide
│   ├── RJ45_CONNECTION_GUIDE.md # RJ45 setup
│   ├── DUAL_RJ45_PASSTHROUGH.md # Daisy-chain setup
│   ├── BUS_POWERED_NODE.md      # Power from bus
│   └── LCC_PROTOCOL_REFERENCE.md# Protocol details
│
├── hardware/
│   └── schematics/              # Circuit diagrams (future)
│
├── README.md                     # Full project documentation
├── LICENSE                       # MIT License
├── .gitignore                    # Git ignore file
└── GITHUB_INSTRUCTIONS.md        # How to push to GitHub
```

---

## 🎯 Quick Start (15 Minutes!)

### 1. What You Need (~$10 total)

| Item | Price | Where |
|------|-------|-------|
| ESP32 DevKit | $6-8 | Amazon/AliExpress |
| SN65HVD230 CAN Transceiver | $1-2 | AliExpress |
| RJ45 Breakout Board | $2-3 | Amazon |

**Already have STM32 parts?** Just need ESP32 + transceiver!

### 2. Install Arduino IDE

1. Download from: https://www.arduino.cc/
2. Install and launch
3. File → Preferences → Additional Board Manager URLs:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Tools → Board → Boards Manager → Search "ESP32" → Install

### 3. Wire Hardware (Only 4 Wires!)

```
ESP32 3.3V → Transceiver VCC
ESP32 GND  → Transceiver GND → RJ45 Pins 1,2
ESP32 GPIO5 → Transceiver CTX
ESP32 GPIO4 → Transceiver CRX
              Transceiver CANH → RJ45 Pin 3
              Transceiver CANL → RJ45 Pin 4
```

**Detailed guide:** [docs/ESP32_WIRING.md](docs/ESP32_WIRING.md)

### 4. Upload Test Sketch

1. Open `arduino/CAN_Test_ESP32/CAN_Test_ESP32.ino`
2. Tools → Board → ESP32 Dev Module
3. Tools → Port → (select your port)
4. Upload
5. LED blinks 10× fast = SUCCESS! ✅

### 5. Upload LCC Node

1. Open `arduino/LCC_Node_ESP32/LCC_Node_ESP32.ino`
2. **Change Node ID** (line 25):
   ```cpp
   #define NODE_ID_LOW     0x87654321  // YOUR UNIQUE ID
   ```
3. Upload
4. Done! 🎉

---

## 📚 Documentation

### Getting Started
- **[ESP32_QUICK_START.md](docs/ESP32_QUICK_START.md)** ← Start here!
- [ESP32_WIRING.md](docs/ESP32_WIRING.md) - Hardware connections
- [README.md](README.md) - Full project overview

### Hardware Setup
- [RJ45_CONNECTION_GUIDE.md](docs/RJ45_CONNECTION_GUIDE.md) - Professional connectors
- [DUAL_RJ45_PASSTHROUGH.md](docs/DUAL_RJ45_PASSTHROUGH.md) - Daisy-chain wiring
- [BUS_POWERED_NODE.md](docs/BUS_POWERED_NODE.md) - Power from LCC bus

### Software
- [LCC_PROTOCOL_REFERENCE.md](docs/LCC_PROTOCOL_REFERENCE.md) - Protocol details
- [GITHUB_INSTRUCTIONS.md](GITHUB_INSTRUCTIONS.md) - Push to GitHub

---

## 🔧 Key Differences from STM32 Version

| Feature | ESP32 (This Project) | STM32 (Other Project) |
|---------|----------------------|----------------------|
| CAN Controller | ✅ Built-in (TWAI) | ❌ External (MCP2515) |
| Wiring | 4 wires | 8+ wires |
| Code Library | ESP32 TWAI | MCP2515 Library |
| Total Cost | ~$8 | ~$18 |
| WiFi/BT | ✅ Included | ❌ No |
| Programming | Arduino IDE | Arduino or STM32Cube |

**Everything else is the same!** Same LCC protocol, same RJ45 setup, same features.

---

## 💡 Bonus Features (ESP32 Exclusive!)

Because ESP32 has WiFi and more power:

### Coming Soon:
- 🌐 **WiFi Configuration Interface** - Configure via web browser
- 📱 **Bluetooth App** - Control from phone
- ☁️ **MQTT Bridge** - Integrate with Home Assistant
- 🔄 **OTA Updates** - Update firmware over WiFi
- 📊 **Web Dashboard** - Monitor layout status

---

## 🚀 Next Steps

### After Basic Node Works:

1. **Add More I/O**
   - Connect sensors (IR, reed switches)
   - Add outputs (LEDs, relays, servos)
   - Create event mappings

2. **Build Network**
   - Add second RJ45 (daisy-chain)
   - Connect multiple nodes
   - Test communication

3. **Go Professional**
   - Add bus power
   - Design custom PCB
   - 3D print enclosure

4. **Add WiFi Features** (Future)
   - Web configuration
   - Mobile app control
   - Cloud integration

---

## 📦 Pushing to GitHub

Want to share your work or contribute?

1. Read: **[GITHUB_INSTRUCTIONS.md](GITHUB_INSTRUCTIONS.md)**
2. Create repository: `ESP32-LCC-Node`
3. Push your code
4. Share with the community!

---

## 🆘 Need Help?

### Common Issues:

**"Can't upload to ESP32"**
- Hold BOOT button while clicking Upload
- Install CH340/CP210x USB driver
- Try different USB cable

**"CAN initialization failed"**
- Check wiring (GPIO5=TX, GPIO4=RX)
- Verify transceiver has 3.3V power
- Select "ESP32 Dev Module" as board

**"No messages on bus"**
- Check CANH/CANL connections
- Add 120Ω termination resistors
- Verify baud rate (125kbps)

**More help:** See [docs/ESP32_QUICK_START.md](docs/ESP32_QUICK_START.md)

---

## ⭐ Why This Project is Awesome

- ✅ **Cheapest LCC solution** - $10 vs $20+ for commercial
- ✅ **Future-proof** - WiFi/BT for expansion
- ✅ **Open source** - Modify and improve
- ✅ **Well documented** - Complete guides included
- ✅ **Easy to build** - Beginner-friendly
- ✅ **Professional results** - RJ45, bus power, daisy-chain

---

## 🎁 Sister Project

Also check out **STM32-LCC-Node** if you:
- Already have STM32 boards
- Need USB Device capability
- Want to learn STM32CubeIDE
- Prefer more traditional embedded development

Both projects share the same LCC protocol implementation!

---

## 📜 License

MIT License - Use freely, contribute back!

---

## 🙏 Credits

- ESP32 Arduino Core by Espressif
- OpenLCB.org for LCC standards
- Model railroad community for inspiration

---

# 🚂 Ready to build your LCC network! 🚂

**Start with:** [docs/ESP32_QUICK_START.md](docs/ESP32_QUICK_START.md)

**Questions?** Open an issue or check the docs!

**Happy building!** 🎉

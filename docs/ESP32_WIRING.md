# ESP32 LCC Node - Hardware Wiring Guide

## ESP32 Built-in CAN Advantage

**No MCP2515 needed!** ESP32 has a CAN controller (called TWAI) built into the chip.

You only need:
- ✅ ESP32 board ($5-10)
- ✅ CAN transceiver ($1-2)
- ✅ RJ45 connector ($2-3)

**Total: ~$8-15** vs $18-20 for STM32 solution!

---

## Hardware Options

### Option 1: SN65HVD230 (Recommended for 3.3V)

**Best for ESP32** - Native 3.3V, cheap, reliable

**Pinout:**
```
SN65HVD230 Module
┌──────────┐
│   VCC ●  │ → ESP32 3.3V
│   GND ●  │ → ESP32 GND
│   CTX ●  │ → ESP32 GPIO5 (CAN TX)
│   CRX ●  │ → ESP32 GPIO4 (CAN RX)
│  CANH ●  │ → CAN Bus High
│  CANL ●  │ → CAN Bus Low
└──────────┘
```

**Cost:** ~$1-2 on AliExpress/Amazon

### Option 2: TJA1050 (5V but works)

**Also works** - More common, slightly different voltage

**Pinout:**
```
TJA1050 Module
┌──────────┐
│   VCC ●  │ → ESP32 3.3V or 5V
│   GND ●  │ → ESP32 GND
│    TX ●  │ → ESP32 GPIO5 (CAN TX)
│    RX ●  │ → ESP32 GPIO4 (CAN RX)
│  CANH ●  │ → CAN Bus High
│  CANL ●  │ → CAN Bus Low
└──────────┘
```

**Note:** Some TJA1050 modules work at 3.3V, some need 5V. Check your module!

---

## Complete Wiring Diagram

### Minimal Setup (USB Power, Single RJ45)

```
         ESP32 DevKit              SN65HVD230           RJ45
         
     ┌──────────────┐           ┌───────────┐        ┌──────┐
     │              │           │           │        │      │
  3.3V─┤ 3.3V       │───────────┤ VCC       │        │      │
  GND ─┤ GND        │───────────┤ GND       │────────┤ Pin 1│
     │              │           │           │   ┌────┤ Pin 2│
  GPIO5┤ GPIO5      │───────────┤ CTX       │   │    │      │
  GPIO4┤ GPIO4      │───────────┤ CRX       │   │    │      │
     │              │           │           │   │    │      │
     │              │           │ CANH      ├───┼────┤ Pin 3│
     │              │           │ CANL      ├───┼────┤ Pin 4│
     │              │           │           │   │    │      │
  GPIO2┤ LED (GPIO2)│           └───────────┘   │    │      │
  GPIO0┤ BTN (GPIO0)│                           │    │      │
     │              │                           │    │      │
     │         USB  │ ← Power & Programming     │    │      │
     └──────────────┘                           │    │      │
                                               GND   └──────┘
```

### Full Setup (Bus Powered, Dual RJ45)

```
           RJ45 IN                              RJ45 OUT
            │                                      │
     Pin 7,8 (12V) ────┐                          │
     Pin 1,2 (GND) ────┼──────────┐               │
     Pin 3,4 (CAN) ────┼─────┐    │               │
            │          │     │    │               │
            │     ┌────▼─────▼────▼───┐           │
            │     │  Voltage Reg      │           │
            │     │  12V → 5V → 3.3V  │           │
            │     └────┬──────────────┘           │
            │          │ 3.3V                     │
            │          │                          │
            │     ┌────▼─────────┐                │
            │     │   ESP32      │                │
            │     │   DevKit     │                │
            │     │              │                │
            │     │ GPIO5  GPIO4 │                │
            │     └───┬──────┬───┘                │
            │         │      │                    │
            │    ┌────▼──────▼───┐                │
            │    │  SN65HVD230   │                │
            │    │ CAN Transceiver│               │
            │    └────┬──────┬───┘                │
            │         │      │                    │
            └─────────┴──────┴────────────────────┘
                  CANH  CANL    (pass-through)
```

---

## Pin Connections Reference

### ESP32 Default Pins:

| Function | ESP32 Pin | Transceiver Pin | Notes |
|----------|-----------|-----------------|-------|
| CAN TX | GPIO5 | CTX or TX | Configurable |
| CAN RX | GPIO4 | CRX or RX | Configurable |
| Power | 3.3V | VCC | From ESP32 |
| Ground | GND | GND | Common ground |

### RJ45 to CAN:

| RJ45 Pin | Signal | Wire Color | Goes To |
|----------|--------|------------|---------|
| Pin 1 | GND | White/Blue | Ground |
| Pin 2 | GND | Blue | Ground |
| Pin 3 | CAN_H | White/Orange | Transceiver CANH |
| Pin 4 | CAN_L | Orange | Transceiver CANL |
| Pin 7 | 12V+ | White/Brown | Voltage reg (optional) |
| Pin 8 | 12V+ | Brown | Voltage reg (optional) |

---

## ESP32 Board Variants

### ESP32 DevKit V1 (Most Common)

**30-pin board:**
```
           ┌────────────┐
    3.3V ──┤●          ●├── GND
     GND ──┤●          ●├── GPIO23
    GPIO15─┤●          ●├── GPIO22
    GPIO2 ─┤●  [USB]   ●├── GPIO1 (TX)
    GPIO0 ─┤●          ●├── GPIO3 (RX)
    GPIO4 ─┤● CAN RX   ●├── GPIO21
    GPIO16─┤●          ●├── GND
    GPIO17─┤●          ●├── GPIO19
    GPIO5 ─┤● CAN TX   ●├── GPIO18
    GPIO18─┤●   ESP32  ●├── GPIO5
    GPIO19─┤●  DevKit  ●├── GPIO17
    GND   ─┤●          ●├── GPIO16
    GPIO21─┤●          ●├── GPIO4
    GPIO22─┤●          ●├── GPIO0
    GPIO23─┤●          ●├── GPIO2
           └────────────┘
```

### ESP32-WROOM-32 (Bare Module)

Need to add your own USB, regulator, etc. Not recommended for beginners.

### ESP32-S3 / ESP32-C3

Also have CAN (TWAI) support! Same wiring.

---

## Breadboard Layout

```
Power Rails:
+ (Red)   → 3.3V from ESP32
- (Black) → GND

Row Layout:
A-E:  ESP32 DevKit (30 pins)
F-J:  (empty space)
K-O:  SN65HVD230 transceiver module
P-T:  RJ45 breakout board
U-Y:  Voltage regulator (if bus powered)

Jumper Wires:
ESP32 3.3V → + rail → Transceiver VCC
ESP32 GND → - rail → Transceiver GND & RJ45 GND
ESP32 GPIO5 → Transceiver CTX
ESP32 GPIO4 → Transceiver CRX
Transceiver CANH → RJ45 Pin 3
Transceiver CANL → RJ45 Pin 4
```

---

## Testing Your Wiring

### Step 1: Power Test

1. Connect USB to ESP32
2. Measure voltage:
   - ESP32 3.3V pin: Should be ~3.3V
   - Transceiver VCC: Should be ~3.3V
   - Between CANH and CANL: ~0V (idle)

### Step 2: Upload Test Sketch

1. Open: `CAN_Test_ESP32.ino`
2. Select Board: ESP32 Dev Module
3. Select Port: (your COM/tty port)
4. Upload
5. Open Serial Monitor (115200 baud)
6. Should see "ALL TESTS PASSED"

### Step 3: Connect to CAN Bus

1. Connect CANH/CANL to bus
2. Add 120Ω terminator if end node
3. Upload LCC node sketch
4. Test with another node!

---

## Customizing Pins

You can change CAN pins in code:

```cpp
// Change these to any valid GPIO
#define CAN_TX_PIN  GPIO_NUM_21  // New TX pin
#define CAN_RX_PIN  GPIO_NUM_22  // New RX pin
```

**Valid GPIO for CAN:**
- Any GPIO except: 6, 7, 8, 9, 10, 11 (used for flash)
- Recommended: 4, 5, 16, 17, 21, 22

---

## Power Supply Options

### Option 1: USB Power (Development)

- Connect USB cable to ESP32
- Powers ESP32 and transceiver
- Simple, no additional components

### Option 2: 5V External

- 5V → ESP32 5V pin (or VIN)
- ESP32 regulates to 3.3V internally
- Good for permanent installation

### Option 3: Bus Power (12V from RJ45)

```
RJ45 12V → Buck Converter → 5V → ESP32 VIN pin
                         → 3.3V → Transceiver VCC

Components needed:
- LM2596 (12V → 5V)
- Or use AMS1117-5.0 if 12V regulated down first
```

**See:** [BUS_POWER.md](BUS_POWER.md) for details

---

## Shopping List

### Minimal Setup (~$10):

| Item | Quantity | Search Term | Price |
|------|----------|-------------|-------|
| ESP32 DevKit | 1 | "ESP32 development board" | $6-8 |
| SN65HVD230 | 1 | "SN65HVD230 CAN transceiver" | $1-2 |
| RJ45 Breakout | 1 | "RJ45 screw terminal" | $2-3 |
| Jumper wires | 10 | "dupont jumper wires" | $2 |

### Professional Setup (~$20):

Add:
- Second RJ45 breakout (+$3)
- LM2596 buck converter (+$2)
- Fuse & protection (+$2)
- Enclosure (+$5)

---

## Common Issues

### "CAN initialization failed"

**Check:**
- GPIO5 and GPIO4 wired correctly
- Transceiver has power (3.3V)
- Using correct board in Arduino IDE

### "No messages received"

**Check:**
- CANH/CANL connected to bus
- 120Ω termination at both ends
- Other nodes on bus are powered on
- Baud rate is 125kbps

### "ESP32 won't program"

**Solution:**
- Hold BOOT button while clicking upload
- Release after "Connecting..." appears
- Check USB cable (must be data cable, not charge-only)

### "3.3V or 5V for transceiver?"

**Answer:**
- SN65HVD230: Always 3.3V
- TJA1050: Check your module datasheet
- When in doubt: Use 3.3V from ESP32

---

## Comparison: ESP32 vs STM32

| Feature | ESP32 | STM32F303RE |
|---------|-------|-------------|
| CAN Controller | ✅ Built-in (TWAI) | ❌ External (MCP2515) |
| Transceiver needed | ✅ Yes (~$1) | ✅ Yes (~$1) |
| External CAN chip | ❌ No | ✅ Yes (MCP2515 ~$3) |
| Total pins used | 2 (TX, RX) | 5 (SPI + CS) |
| Code complexity | Simple | More complex |
| **Total hardware cost** | **~$8** | **~$18** |

---

## Next Steps

1. ✅ Wire ESP32 to transceiver
2. ✅ Connect to RJ45 breakout
3. ✅ Upload test sketch
4. ✅ Upload LCC node sketch
5. ✅ Connect to CAN bus
6. ✅ Test with another node!

---

**Questions?** Check the troubleshooting section or open an issue! 🚀

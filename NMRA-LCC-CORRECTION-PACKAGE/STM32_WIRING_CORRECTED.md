# STM32 LCC Node - NMRA Standard Wiring Guide

## ⚠️ CRITICAL: NMRA LCC Standard Pinout

This guide uses the **official NMRA LCC S-9.7.4.1 standard** RJ45 pinout:

```
Pin 1: CAN_H
Pin 2: CAN_L
Pin 7: Ground (-)
Pin 8: Positive (+12V)
```

**This is required for compatibility with all NMRA-compliant LCC equipment!**

---

## Complete Wiring Diagram - NMRA Compliant

### Minimal Setup (USB Power, Single RJ45)

```
    STM32F303RE           MCP2515            RJ45 (NMRA LCC)
    
  ┌──────────┐         ┌─────────┐         ┌──────┐
  │          │         │         │         │      │
3.3V──┤ 3.3V  │─────────┤ VCC     │         │      │
GND ──┤ GND   │────┬────┤ GND     │─────────┤ Pin 7│ GND (-)
  │          │    │    │         │         │ Pin 8│ +12V (USB powered)
PA4 ──┤ PA4   │────┼────┤ CS      │         │      │
PA5 ──┤ PA5   │────┼────┤ SCK     │         │      │
PA6 ──┤ PA6   │────┼────┤ MISO    │         │      │
PA7 ──┤ PA7   │────┼────┤ MOSI    │         │      │
  │          │    │    │         │         │      │
  │          │    │    │ CANH    ├─────────┤ Pin 1│ CAN_H
  │          │    │    │ CANL    ├─────────┤ Pin 2│ CAN_L
  │          │    │    │         │         │      │
PA5 ──┤ LED   │    │    └─────────┘         └──────┘
PC13──┤ BTN   │    │
  │          │    │
  │    USB   │    │ ← Power & Programming
  └──────────┘    │
                  │
                 GND
```

### Bus-Powered Setup (NMRA Standard)

```
        RJ45 IN                                    RJ45 OUT
        (NMRA LCC)                                (NMRA LCC)
         
  Pin 8 (+12V) ────┬──────────────────────────┬─── Pin 8
  Pin 7 (GND)  ────┼──────────┬───────────────┼─── Pin 7
  Pin 1 (CAN_H)────┼──────┐   │               ├─── Pin 1
  Pin 2 (CAN_L)────┼──────┼───┼───────────────┼─── Pin 2
                   │      │   │               │
              ┌────▼──────▼───▼────┐          │
              │  Voltage Reg       │          │
              │  12V → 5V → 3.3V   │          │
              └────┬───────────────┘          │
                   │ 3.3V                     │
                   │                          │
              ┌────▼────────┐                 │
              │  STM32      │                 │
              │  F303RE     │                 │
              │             │                 │
              │ PA4-PA7     │                 │
              └───┬─────────┘                 │
                  │ SPI                       │
             ┌────▼────────┐                  │
             │  MCP2515    │                  │
             │  + TJA1050  │                  │
             └────┬────┬───┘                  │
                  │    │                      │
               CANH  CANL                     │
                  │    │                      │
                  └────┴──────────────────────┘
               (pass-through to next node)
```

---

## RJ45 Breakout Wiring - NMRA Standard

### Screw Terminal Connections:

```
RJ45 Breakout          MCP2515              STM32F303RE
──────────────────────────────────────────────────────────
Terminal 1 (CAN_H) ──→ CANH (TJA1050)
Terminal 2 (CAN_L) ──→ CANL (TJA1050)
Terminal 7 (GND)   ──→ GND ──────────────→ GND
Terminal 8 (+12V)  ──→ [Voltage Reg] ────→ 3.3V

                       CS   ←───────────── PA4
                       SCK  ←───────────── PA5
                       MISO ────────────→ PA6
                       MOSI ←───────────── PA7
                       VCC  ←───────────── 3.3V
                       GND  ────────────→ GND
```

### With Dual RJ45 (Pass-Through):

```
Breakout-IN                              Breakout-OUT
Terminal 1 (CAN_H) ─────┬──── CANH ──────┬─── Terminal 1
Terminal 2 (CAN_L) ─────┼──── CANL ──────┼─── Terminal 2
Terminal 7 (GND)   ─────┼──── GND  ──────┼─── Terminal 7
Terminal 8 (+12V)  ─────┴──── +12V ──────┴─── Terminal 8
                        │
                        ├──→ To MCP2515
                        └──→ To voltage regulator
```

---

## Shopping List - NMRA Compliant

| Item | Quantity | Notes | Price |
|------|----------|-------|-------|
| STM32F303RE Nucleo | 1 | Official STM board | $15 |
| **MCP2515 Module** | 1 | **With TJA1050 transceiver** | $3 |
| RJ45 Breakout | 1-2 | Screw terminal type | $2-3 each |
| **Standard Ethernet Cable** | As needed | **Cat5e/Cat6 (T568B)** | $3-5 |
| 120Ω Resistor | 1-2 | For termination | $0.50 |
| Jumper wires | 10+ | Dupont style | $2 |

**Important:** Use **standard Ethernet cables** - they have correct wiring for NMRA LCC!

---

## Pin Connections Reference

### STM32 → MCP2515 (SPI):

| STM32 Pin | Function | MCP2515 Pin | Notes |
|-----------|----------|-------------|-------|
| 3.3V | Power | VCC | From Nucleo |
| GND | Ground | GND | Common ground |
| PA4 | CS | CS | Chip Select |
| PA5 | SCK | SCK | SPI Clock |
| PA6 | MISO | SO | SPI Data Out |
| PA7 | MOSI | SI | SPI Data In |

### MCP2515 → RJ45 (NMRA Standard):

| MCP2515/TJA1050 Pin | RJ45 Pin | NMRA Signal | Wire Color (T568B) |
|---------------------|----------|-------------|--------------------|
| CANH | **Pin 1** | **CAN_H** | White/Orange |
| CANL | **Pin 2** | **CAN_L** | Orange |
| GND | **Pin 7** | **Ground (-)** | White/Brown |
| - | **Pin 8** | **+12V** | Brown |

---

## Breadboard Layout - NMRA Compliant

```
Power Rails:
+ (Red)   → 3.3V from STM32
- (Black) → GND (connects to RJ45 Pin 7)

Row Layout:
A-J:   STM32 Nucleo board (spans both sides)
K-O:   MCP2515 module
P-T:   RJ45 breakout board
U-Y:   Voltage regulator (if bus powered)

Critical Connections:
STM32 PA4     → MCP2515 CS
STM32 PA5     → MCP2515 SCK
STM32 PA6     → MCP2515 MISO
STM32 PA7     → MCP2515 MOSI
STM32 3.3V    → MCP2515 VCC → + rail
STM32 GND     → MCP2515 GND → - rail → RJ45 Pin 7

MCP2515 CANH  → RJ45 Pin 1 (CAN_H)
MCP2515 CANL  → RJ45 Pin 2 (CAN_L)

RJ45 Pin 8 (+12V) → Voltage reg (if bus powered)
RJ45 Pin 7 (GND)  → - rail
```

---

## Testing - NMRA Compliance

### Step 1: Verify Pinout

Before connecting to any LCC network:

```
1. Check RJ45 Pin 1 connects to MCP2515 CANH ✓
2. Check RJ45 Pin 2 connects to MCP2515 CANL ✓
3. Check RJ45 Pin 7 connects to GND ✓
4. Check RJ45 Pin 8 connects to +12V input ✓
```

### Step 2: Voltage Test

With bus powered (or 12V supply on pins 7-8):

```
Measure Pin 8 to Pin 7: Should be +12V (±2V) ✓
Measure Pin 1 to Pin 7: ~2.5V idle (CAN_H)
Measure Pin 2 to Pin 7: ~2.5V idle (CAN_L)
```

### Step 3: Upload Test Sketch

1. Open `MCP2515_Test_Arduino.ino`
2. Upload to STM32 via Arduino IDE
3. Serial Monitor should show test results
4. LED blinks 10× fast = Hardware OK! ✓

### Step 4: Connect to LCC Network

1. Connect standard Ethernet cable
2. Add 120Ω terminator if end node
3. Upload LCC node sketch
4. Should communicate with other LCC nodes! ✓

---

## Common Mistakes - AVOID THESE!

### ❌ WRONG: Using Generic CAN Pinout

**Don't use:**
```
Pin 3: CAN_H  ← DeviceNet/CANopen standard
Pin 4: CAN_L  ← NOT LCC standard!
```

### ✅ CORRECT: NMRA LCC Pinout

**Always use:**
```
Pin 1: CAN_H  ← NMRA LCC standard
Pin 2: CAN_L  ← Required for LCC!
```

---

## Nucleo Board Pin Locations

### CN7 Header (Left side, looking at board):
```
Pin 1:  NC
Pin 2:  IOREF
...
Pin 8:  GND        ← Use this for GND
Pin 15: PA5 (SCK)  ← SPI Clock to MCP2515
Pin 16: PA6 (MISO) ← SPI Data from MCP2515
Pin 17: PA7 (MOSI) ← SPI Data to MCP2515
Pin 18: 3.3V       ← Use this for power
```

### CN10 Header (Right side):
```
Pin 25: PA4        ← CS to MCP2515
```

---

## Why This Matters

### Using Wrong Pinout:

- ❌ Won't work with commercial LCC equipment
- ❌ Won't work with other DIY LCC nodes
- ❌ Can't connect to existing LCC networks
- ❌ May damage equipment!

### Using NMRA Standard:

- ✅ Works with all LCC equipment
- ✅ Compatible with RR-CirKits, Digitrax, MERG
- ✅ Works with JMRI
- ✅ Future-proof
- ✅ Safe and reliable

---

## Standard Ethernet Cables Work!

**Good news:** Regular Cat5e/Cat6 Ethernet cables use T568B wiring:

```
Pin 1: White/Orange → CAN_H  ✓
Pin 2: Orange       → CAN_L  ✓
Pin 7: White/Brown  → GND    ✓
Pin 8: Brown        → +12V   ✓
```

**Just use standard Ethernet cables!** Already correct for NMRA LCC!

---

## Termination - NMRA Standard

### 120Ω Between Pins 1 and 2:

At **both ends** of bus only:

```
RJ45 Pin 1 (CAN_H) ──┬────┐
                     │    │
                    120Ω  │
                     │    │
RJ45 Pin 2 (CAN_L) ──┴────┘
```

**Middle nodes:** NO termination! Pass-through only.

---

## Arduino Code Update

**No changes needed!** The MCP2515 library works the same.

Only hardware wiring changed:
- RJ45 pins are different
- Code is identical

---

## Summary - Critical Points

1. ✅ **Pin 1 = CAN_H** (not pin 3!)
2. ✅ **Pin 2 = CAN_L** (not pin 4!)  
3. ✅ **Pin 7 = GND** (not pins 1-2!)
4. ✅ **Pin 8 = +12V** (not pin 7!)
5. ✅ Use **standard Ethernet cables**
6. ✅ Test before connecting to network
7. ✅ Terminate both ends only

**Follow this guide for NMRA LCC compatibility!** ✅

---

**Questions?** Check [NMRA_LCC_RJ45_STANDARD.md](NMRA_LCC_RJ45_STANDARD.md) for complete specification!

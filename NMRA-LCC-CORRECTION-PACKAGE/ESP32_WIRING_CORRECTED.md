# ESP32 LCC Node - NMRA Standard Wiring Guide

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
         ESP32 DevKit         SN65HVD230        RJ45 (NMRA LCC Standard)
         
     ┌──────────────┐      ┌───────────┐       ┌──────┐
     │              │      │           │       │      │
  3.3V─┤ 3.3V       │──────┤ VCC       │       │      │
  GND ─┤ GND        │──┬───┤ GND       │───────┤ Pin 7│ Ground (-)
     │              │  │   │           │       │ Pin 8│ +12V (not used - USB powered)
  GPIO5┤ GPIO5      │  │   │ CTX       │       │      │
  GPIO4┤ GPIO4      │──┼───┤ CRX       │       │      │
     │              │  │   │           │       │      │
     │              │  │   │ CANH      ├───────┤ Pin 1│ CAN_H
     │              │  │   │ CANL      ├───────┤ Pin 2│ CAN_L
     │              │  │   │           │       │      │
  GPIO2┤ LED        │  │   └───────────┘       └──────┘
  GPIO0┤ BTN        │  │
     │              │  │
     │         USB  │  │ ← Power & Programming
     └──────────────┘  │
                       │
                      GND
```

### Bus-Powered Setup (NMRA Standard)

```
           RJ45 IN                               RJ45 OUT
           (NMRA LCC)                           (NMRA LCC)
            
     Pin 8 (+12V) ────┬────────────────────────┬─── Pin 8
     Pin 7 (GND)  ────┼─────────┬──────────────┼─── Pin 7
     Pin 1 (CAN_H)────┼─────┐   │              ├─── Pin 1
     Pin 2 (CAN_L)────┼─────┼───┼──────────────┼─── Pin 2
                      │     │   │              │
                 ┌────▼─────▼───▼───┐          │
                 │  Voltage Reg     │          │
                 │  12V → 5V → 3.3V │          │
                 └────┬─────────────┘          │
                      │ 3.3V                   │
                      │                        │
                 ┌────▼──────────┐             │
                 │   ESP32       │             │
                 │   DevKit      │             │
                 │               │             │
                 │ GPIO5  GPIO4  │             │
                 └───┬──────┬────┘             │
                     │      │                  │
                ┌────▼──────▼───┐              │
                │  SN65HVD230   │              │
                │ CAN Transceiver│             │
                └────┬──────┬───┘              │
                     │      │                  │
                  CANH  CANL                   │
                     │      │                  │
                     └──────┴──────────────────┘
                  (pass-through to next node)
```

---

## RJ45 Breakout Wiring - NMRA Standard

### Screw Terminal Connections:

```
RJ45 Breakout          SN65HVD230           ESP32
─────────────────────────────────────────────────────
Terminal 1 (CAN_H) ──→ CANH
Terminal 2 (CAN_L) ──→ CANL
Terminal 7 (GND)   ──→ GND ──────────────→ GND
Terminal 8 (+12V)  ──→ [Voltage Reg] ────→ 3.3V

                       CTX  ←───────────── GPIO5
                       CRX  ────────────→ GPIO4
                       VCC  ←───────────── 3.3V
                       GND  ────────────→ GND
```

### With Dual RJ45 (Pass-Through):

```
Breakout-IN                            Breakout-OUT
Terminal 1 (CAN_H) ─────┬──── CANH ────┬─── Terminal 1
Terminal 2 (CAN_L) ─────┼──── CANL ────┼─── Terminal 2
Terminal 7 (GND)   ─────┼──── GND  ────┼─── Terminal 7
Terminal 8 (+12V)  ─────┴──── +12V ────┴─── Terminal 8
                        │
                        ├──→ To transceiver
                        └──→ To voltage regulator
```

---

## Shopping List - NMRA Compliant

| Item | Quantity | Notes | Price |
|------|----------|-------|-------|
| ESP32 DevKit | 1 | Any ESP32 board | $6-8 |
| **SN65HVD230** | 1 | **3.3V CAN transceiver** | $1-2 |
| RJ45 Breakout | 1-2 | Screw terminal type | $2-3 each |
| **Standard Ethernet Cable** | As needed | **Cat5e/Cat6 (T568B)** | $3-5 |
| 120Ω Resistor | 1-2 | For termination | $0.50 |

**Important:** Use **standard Ethernet cables** with T568B wiring - they already have the correct wire pairs on pins 1-2 and 7-8!

---

## Pin Connections Reference

### ESP32 → CAN Transceiver:

| ESP32 Pin | Function | Transceiver Pin | Notes |
|-----------|----------|-----------------|-------|
| 3.3V | Power | VCC | Direct connection |
| GND | Ground | GND | Common ground |
| GPIO5 | CAN TX | CTX | Configurable |
| GPIO4 | CAN RX | CRX | Configurable |

### Transceiver → RJ45 (NMRA Standard):

| Transceiver Pin | RJ45 Pin | NMRA Signal | Wire Color (T568B) |
|-----------------|----------|-------------|--------------------|
| CANH | **Pin 1** | **CAN_H** | White/Orange |
| CANL | **Pin 2** | **CAN_L** | Orange |
| GND | **Pin 7** | **Ground (-)** | White/Brown |
| - | **Pin 8** | **+12V** | Brown |

---

## Breadboard Layout - NMRA Compliant

```
Power Rails:
+ (Red)   → 3.3V from ESP32
- (Black) → GND (connects to RJ45 Pin 7)

Row Layout:
A-E:  ESP32 DevKit
K-O:  SN65HVD230 transceiver
P-T:  RJ45 breakout board
U-Y:  Voltage regulator (if bus powered)

Critical Connections:
ESP32 GPIO5    → Transceiver CTX
ESP32 GPIO4    → Transceiver CRX
ESP32 3.3V     → Transceiver VCC → + rail
ESP32 GND      → Transceiver GND → - rail → RJ45 Pin 7

Transceiver CANH → RJ45 Pin 1 (CAN_H)
Transceiver CANL → RJ45 Pin 2 (CAN_L)

RJ45 Pin 8 (+12V) → Voltage reg (if bus powered)
RJ45 Pin 7 (GND)  → - rail
```

---

## Testing - NMRA Compliance

### Step 1: Verify Pinout

Before connecting to any LCC network:

```
1. Check RJ45 Pin 1 connects to transceiver CANH ✓
2. Check RJ45 Pin 2 connects to transceiver CANL ✓
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

1. Open `CAN_Test_ESP32.ino`
2. Upload to ESP32
3. Serial Monitor should show "ALL TESTS PASSED"
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

### ❌ WRONG: Incorrect Power Pins

**Don't use:**
```
Pin 1-2: GND  ← Wrong!
Pin 7-8: CAN  ← Wrong!
```

### ✅ CORRECT: NMRA Power Pins

**Always use:**
```
Pin 7: GND    ← NMRA standard
Pin 8: +12V   ← Required for LCC!
```

---

## Why This Matters

### Compatibility Issues:

Using **wrong pinout** means:
- ❌ Won't work with commercial LCC equipment
- ❌ Won't work with other DIY LCC nodes
- ❌ Can't connect to existing LCC networks
- ❌ May damage equipment!

Using **NMRA standard** means:
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

**Just use standard Ethernet cables!** The wiring is already correct for LCC!

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

**Location:** Inside RJ45 connector or external plug

**Middle nodes:** NO termination! Pass-through only.

---

## References

- **NMRA Standard S-9.7.4.1:** "LCC Physical Layer"
- **NMRA TN-9.7.4.1:** "RJ45 Connector Pinout"
- **OpenLCB.org:** Official LCC specifications
- **This project:** Fully NMRA-compliant implementation

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

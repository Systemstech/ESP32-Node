# NMRA LCC RJ45 Pinout - Official S-9.7.1.1 Standard

## Official NMRA Standard S-9.7.1.1 (Adopted January 24, 2025)

This document provides the **official NMRA Layout Command Control (LCC) CAN Physical Layer** pinout specification.

---

## Official RJ45 Pinout

```
Pin | Signal Name  | T568B Wire Color | Function
----|--------------|------------------|---------------------------
1   | CAN_H        | White/Orange     | CAN Bus High
2   | CAN_L        | Orange           | CAN Bus Low
3   | CAN_GND      | White/Green      | CAN Ground Reference
4   | ALT_L        | Blue             | Alternate Use (e.g., DCC)
5   | ALT_H        | White/Blue       | Alternate Use (e.g., DCC)
6   | CAN_SHIELD   | Green            | CAN Shield
7   | PWR_NEG      | White/Brown      | Power Negative (Ground)
8   | PWR_POS      | Brown            | Power Positive (9-15VDC)
```

### Visual Pinout Diagram

Looking at RJ45 jack from front (tab down):

```
     ┌─────────────┐
     │  ┌───────┐  │
     │  │ 8 7 6 │  │ ← Contacts visible
     │  │ 5 4 3 │  │
     │  │ 2 1   │  │
     │  └───────┘  │
     │             │
     │    [TAB]    │ ← Locking tab
     └─────────────┘

Pin 1: CAN_H        (White/Orange) - CAN Bus High
Pin 2: CAN_L        (Orange)       - CAN Bus Low
Pin 3: CAN_GND      (White/Green)  - CAN Ground
Pin 4: ALT_L        (Blue)         - Alternate (DCC low)
Pin 5: ALT_H        (White/Blue)   - Alternate (DCC high)
Pin 6: CAN_SHIELD   (Green)        - Shield
Pin 7: PWR_NEG      (White/Brown)  - Power Ground
Pin 8: PWR_POS      (Brown)        - Power +9-15VDC
```

---

## Ground Connections - CRITICAL!

### Three Separate Ground/Reference Signals:

The NMRA standard defines THREE different ground-related pins:

1. **Pin 3: CAN_GND** - CAN signal ground reference
2. **Pin 6: CAN_SHIELD** - Shield connection
3. **Pin 7: PWR_NEG** - Power supply ground/negative

### Mandatory Ground Connections in Your Node:

Per NMRA S-9.7.1.1 section 4 (lines 45-47):

**REQUIRED:**
- **Pins 3 and 6 SHALL be connected together** in your node
- This connection must be rated for at least 1A

**OPTIONAL:**
- Pin 7 (PWR_NEG) MAY be connected to pins 3 & 6
- If your node requires this connection for proper operation, then connect it

### Practical Ground Wiring:

```
Inside Your Node:

CAN_GND (Pin 3) ──┬──── Connected together (REQUIRED)
                  │
CAN_SHIELD (Pin 6)┘      These MUST be connected!
                         Rated for 1A minimum
                  
PWR_NEG (Pin 7) ─────── May or may not connect to above
                        (depends on your design)
```

**Example 1 - All Grounds Common (Most Common):**
```
Pin 3 ──┬──→ System GND
Pin 6 ──┤
Pin 7 ──┘
```

**Example 2 - Isolated Power:**
```
Pin 3 ──┬──→ CAN/Signal GND
Pin 6 ──┘

Pin 7 ────→ Power GND (isolated via regulator)
```

---

## Wiring to Your LCC Node

### CAN Transceiver Connections:

```
RJ45 Pin 1 (CAN_H)    ──→ Transceiver CANH
RJ45 Pin 2 (CAN_L)    ──→ Transceiver CANL
RJ45 Pin 3 (CAN_GND)  ──→ Transceiver GND
RJ45 Pin 6 (CAN_SHIELD)──→ Connect to Pin 3
```

### Power Connections (if using bus power):

```
RJ45 Pin 8 (PWR_POS) ──→ Voltage Regulator Input (9-15VDC)
RJ45 Pin 7 (PWR_NEG) ──→ Power Ground
```

### Alternate Use Pins (if using DCC signal):

```
RJ45 Pin 4 (ALT_L) ──→ DCC Negative/Low
RJ45 Pin 5 (ALT_H) ──→ DCC Positive/High
```

---

## Complete ESP32 Node Wiring (NMRA Compliant)

```
RJ45 Breakout         SN65HVD230           ESP32 DevKit
──────────────────────────────────────────────────────────

Pin 1 (CAN_H)    ──→  CANH
Pin 2 (CAN_L)    ──→  CANL
Pin 3 (CAN_GND)  ──┬→ GND  ──────────────→ ESP32 GND
Pin 6 (CAN_SHIELD)─┘                      
Pin 7 (PWR_NEG)  ───────────┐             
                             ├──→ GND ───→ ESP32 GND
Pin 8 (PWR_POS)  ─→ [Reg] ──┘  3.3V ────→ ESP32 3.3V
                              
                      VCC  ←─────────────── 3.3V
                      CTX  ←─────────────── GPIO5
                      CRX  ─────────────→ GPIO4
```

---

## Complete STM32 Node Wiring (NMRA Compliant)

```
RJ45 Breakout         MCP2515              STM32F303RE
──────────────────────────────────────────────────────────

Pin 1 (CAN_H)    ──→  CANH (TJA1050)
Pin 2 (CAN_L)    ──→  CANL (TJA1050)
Pin 3 (CAN_GND)  ──┬→ GND  ──────────────→ STM32 GND
Pin 6 (CAN_SHIELD)─┘
Pin 7 (PWR_NEG)  ───────────┐
                             ├──→ GND ───→ STM32 GND
Pin 8 (PWR_POS)  ─→ [Reg] ──┘  3.3V ────→ STM32 3.3V

                      VCC  ←─────────────── 3.3V
                      CS   ←─────────────── PA4
                      SCK  ←─────────────── PA5
                      MISO ─────────────→ PA6
                      MOSI ←─────────────── PA7
```

---

## Cable Requirements (NMRA S-9.7.1.1)

### Mandatory Pairs:

Per NMRA standard, cables SHALL:
- **Carry pins 1 & 2 as a twisted pair** (CAN_H / CAN_L)
- **Carry pins 3 & 6 as a twisted pair** (CAN_GND / CAN_SHIELD)

### Optional Pairs:

Cables MAY carry:
- **Pins 4 & 5 as a twisted pair** (ALT_L / ALT_H for DCC)
- **Pins 7 & 8 as a twisted pair** (PWR_NEG / PWR_POS)

### Standard Ethernet Cables:

**Good news!** Standard Cat5e/Cat6 cables (T568B wiring) work perfectly:

```
T568B Standard:
Pin 1: White/Orange → CAN_H      } Pair 2
Pin 2: Orange       → CAN_L      }

Pin 3: White/Green  → CAN_GND    } Pair 3
Pin 6: Green        → CAN_SHIELD }

Pin 4: Blue         → ALT_L      } Pair 1
Pin 5: White/Blue   → ALT_H      }

Pin 7: White/Brown  → PWR_NEG    } Pair 4
Pin 8: Brown        → PWR_POS    }
```

**All required pairs are already twisted pairs in standard Ethernet cable!** ✅

---

## Power Specifications

### Supplying Power (Section 7):

If your node provides power:
- **Voltage:** 9-15VDC (minimum 9V, maximum 15V)
- **Current:** Up to 500mA maximum per node
- **Label:** Must be permanently labeled with max current
- **Pins:** PWR_POS (Pin 8) positive, PWR_NEG (Pin 7) negative

### Consuming Power (Section 8):

If your node draws power:
- **Voltage range:** Must operate from 7.5-15VDC
- **Maximum draw:** 500mA per node
- **Label:** Must be permanently labeled with max current
- **Pins:** PWR_POS (Pin 8) positive, PWR_NEG (Pin 7) negative

---

## CAN Bus Requirements

### Data Rate:
- **125 kbps** (per NMRA S-9.7.1.1 section 5)
- **CAN 2.0B protocol**

### Termination:
- **120Ω resistor between pins 1 and 2** at BOTH ENDS only
- Middle nodes: NO termination
- Termination may be switchable (jumper/DIP switch)

### Bus Length:
- **Maximum 300 meters** at 125kbps
- Nodes must support this length with proper bit timing

---

## Dual RJ45 Pass-Through (Daisy-Chain)

### All Pins Connect in Parallel:

```
RJ45-A (IN)              Your Node              RJ45-B (OUT)

Pin 1 ─────┬─────────→ To CANH ←─────────┬───── Pin 1
Pin 2 ─────┼─────────→ To CANL ←─────────┼───── Pin 2
Pin 3 ─────┼─────────→ To GND  ←─────────┼───── Pin 3
Pin 4 ─────┼─────────→ ALT_L (optional)──┼───── Pin 4
Pin 5 ─────┼─────────→ ALT_H (optional)──┼───── Pin 5
Pin 6 ─────┼─────────→ To GND  ←─────────┼───── Pin 6
Pin 7 ─────┼─────────→ To GND  ←─────────┼───── Pin 7
Pin 8 ─────┴─────────→ To +12V ←─────────┴───── Pin 8
```

Per NMRA S-9.7.1.1 section 4 (lines 38-43):
- All 8 conductors SHALL be present on all connections
- Pins 1, 2, 3, 6, 7 SHALL be connected in parallel
- Pin 8 SHALL be connected in parallel if not providing power
- All wiring SHALL be rated for at least 1A

---

## Alternate Use: DCC Signal (Pins 4 & 5)

Per NMRA S-9.7.1.1 section 6.1:

### DCC on ALT_L / ALT_H:

Pins 4 and 5 may be used for **NMRA S-9.1.2 DCC Power Station Interface**:

```
Pin 4 (ALT_L): DCC "negative" (first half of bit)
Pin 5 (ALT_H): DCC "positive" (first half of bit)
```

### Important DCC Requirements:

- **Voltage:** Up to 27V AC (peak) or DC (either polarity)
- **Isolation:** DCC consumer SHALL support arbitrary common mode voltages
- **No connection:** ALT_L/ALT_H shall NOT connect to CAN_GND with <4kΩ impedance
- **Labeling:** Nodes that source or consume DCC SHALL be permanently labeled
- **Pass-through:** All nodes pass ALT_L/ALT_H regardless of use

---

## Testing Your NMRA-Compliant Node

### Step 1: Verify Connections

With multimeter (power off):
- [ ] Pin 1 connects to transceiver CANH
- [ ] Pin 2 connects to transceiver CANL
- [ ] Pin 3 connects to transceiver GND
- [ ] Pin 6 connects to Pin 3 (required!)
- [ ] Pin 7 connects to power ground
- [ ] Pin 8 connects to voltage regulator input

### Step 2: Verify Ground Connections

- [ ] Continuity between Pin 3 and Pin 6 (required!)
- [ ] Continuity between Pin 3 and transceiver GND
- [ ] Pin 7 connection to Pin 3 (if applicable)

### Step 3: Voltage Test (Bus Powered)

With 12V on bus:
- [ ] Pin 8 to Pin 7: +12V (±3V)
- [ ] Pin 3 to Pin 7: 0V (if connected) or isolated
- [ ] Pin 1 to Pin 3: ~2.5V (CAN_H idle)
- [ ] Pin 2 to Pin 3: ~2.5V (CAN_L idle)

### Step 4: Upload and Test

- [ ] Upload test sketch
- [ ] Verify CAN communication
- [ ] Check current draw (<500mA)
- [ ] Test with other LCC nodes

---

## Quick Reference Table

| Pin | Signal | Required? | Your Connection | Notes |
|-----|--------|-----------|-----------------|-------|
| 1 | CAN_H | Yes | Transceiver CANH | CAN bus high |
| 2 | CAN_L | Yes | Transceiver CANL | CAN bus low |
| 3 | CAN_GND | Yes | GND + Pin 6 | Must connect to Pin 6! |
| 4 | ALT_L | Optional | DCC low or pass-through | Optional DCC |
| 5 | ALT_H | Optional | DCC high or pass-through | Optional DCC |
| 6 | CAN_SHIELD | Yes | Pin 3 + GND | Must connect to Pin 3! |
| 7 | PWR_NEG | If bus powered | Power GND | May connect to Pin 3 |
| 8 | PWR_POS | If bus powered | +9-15VDC input | Through regulator |

---

## Key Differences from Previous Documentation

### What Changed:

❌ **OLD (WRONG):**
- Pin 3: CAN_H
- Pin 4: CAN_L
- Pin 1-2: Some kind of ground
- Pin 7-8: Some kind of power

✅ **NOW (CORRECT per NMRA):**
- Pin 1: CAN_H
- Pin 2: CAN_L
- Pin 3: CAN_GND (must connect to Pin 6!)
- Pin 6: CAN_SHIELD (must connect to Pin 3!)
- Pin 7: PWR_NEG
- Pin 8: PWR_POS

### Critical New Requirements:

1. **Pins 3 and 6 MUST be connected** together in your node
2. **Three separate ground signals** (CAN_GND, CAN_SHIELD, PWR_NEG)
3. **All 8 pins defined** (not just power and CAN)
4. **Specific pair requirements** for cables
5. **DCC signal specifications** on pins 4-5

---

## References

- **NMRA Standard S-9.7.1.1** - "LCC CAN Physical Layer" (July 22, 2024, Adopted Jan 24, 2025)
- **OpenLCB.org** - Official LCC/OpenLCB specifications
- **TIA-968-A** - RJ45 connector specification
- **ISO 11898** - CAN bus specification

---

## Summary

**For NMRA LCC Compliance:**

1. ✅ Use pins 1-2 for CAN (not 3-4!)
2. ✅ Connect pins 3 and 6 together (required!)
3. ✅ Use pins 7-8 for power (not 1-2 and 7-8!)
4. ✅ Use standard Cat5e/Cat6 Ethernet cables
5. ✅ Terminate 120Ω between pins 1-2 at ends only
6. ✅ Support 9-15VDC power on pin 8
7. ✅ Label power capability permanently

**This is the official NMRA standard - follow this for guaranteed compatibility!** ✅

# Dual RJ45 Pass-Through for LCC Nodes

## Why Two RJ45 Jacks?

With two jacks, you can daisy-chain nodes easily:

```
Bus ──→ [Node 1] ──→ [Node 2] ──→ [Node 3] ──→ [Node 4]
        IN | OUT     IN | OUT     IN | OUT     IN | OUT
```

**Benefits:**
- ✅ Easy to add/remove nodes
- ✅ No need to cut cables
- ✅ Professional appearance
- ✅ Standard industrial practice

---

## Wiring Two RJ45 Jacks

### Basic Concept: Parallel Connection

Both RJ45 jacks connect to the **same internal signals**:

```
     RJ45 Jack #1        Your Node        RJ45 Jack #2
     (INPUT)                              (OUTPUT)
     
Pin 1 ────────┬────────→ GND ←────────┬──────── Pin 1
Pin 2 ────────┘                        └──────── Pin 2

Pin 3 ────────┬────────→ CAN_H ←──────┬──────── Pin 3
Pin 4 ────────┘────────→ CAN_L ←──────┘──────── Pin 4

Pin 7 ────────┬────────→ 12V+ ←───────┬──────── Pin 7
Pin 8 ────────┘                        └──────── Pin 8
```

### Internal Schematic:

```
RJ45-A                                            RJ45-B
(IN)                                              (OUT)

Pin 1 ───┬────────────────────────────────────┬─── Pin 1
Pin 2 ───┘                                     └─── Pin 2
         │                                     │
         └──→ Common GND ←────────────────────┘
         
Pin 3 ───┬────────┬───→ To MCP2515 CANH       
Pin 4 ───┘        │         
         │        └───→ To MCP2515 CANL
         └──────────────────────────────────────┬─── Pin 3
                                                └─── Pin 4

Pin 7 ───┬────────┬───→ To Power Regulator
Pin 8 ───┘        │
         │        └───→ To Power Regulator
         └──────────────────────────────────────┬─── Pin 7
                                                └─── Pin 8
```

---

## Shopping List - Dual RJ45 Version

| Item | Quantity | Purpose | Price |
|------|----------|---------|-------|
| RJ45 Jack (PCB mount) | 2 | IN and OUT | $2-4 |
| OR RJ45 Breakout Board | 2 | Easier prototyping | $6-10 |
| Wire (22-24 AWG) | ~2 feet | Connecting jacks together | $2 |
| LM2596 Module | 1 | 12V → 5V | $2-3 |
| AMS1117-3.3 Module | 1 | 5V → 3.3V | $1-2 |
| Fuse 500mA | 1 | Protection | $1 |

**Total: ~$15-25**

---

## Method 1: Using Two RJ45 Breakout Boards (Easiest!)

### What to Buy:

Search: **"RJ45 breakout board screw terminal"** × 2

### Wiring Between Two Breakouts:

```
Breakout #1 (IN)              Breakout #2 (OUT)
Terminal 1 ───────────────────── Terminal 1  } GND
Terminal 2 ───────────────────── Terminal 2  } GND

Terminal 3 ─────┬─── To CANH ───┬─── Terminal 3  } CAN_H
Terminal 4 ─────┤   To CANL ────┤─── Terminal 4  } CAN_L
                │               │
                │   MCP2515     │
                └───────────────┘

Terminal 7 ─────┬─── To 12V ────┬─── Terminal 7  } 12V+
Terminal 8 ─────┘   Regulator   └─── Terminal 8  } 12V+
```

### Physical Layout:

```
┌─────────────┐                           ┌─────────────┐
│  RJ45 IN    │                           │  RJ45 OUT   │
│  Breakout   │                           │  Breakout   │
│             │                           │             │
│ ○○○○○○○○    │                           │ ○○○○○○○○    │
│ 12345678    │                           │ 12345678    │
└──┬──┬──┬──┬─┘                           └──┬──┬──┬──┬─┘
   │  │  │  │                                │  │  │  │
   1  3  4  7                                1  3  4  7
   │  │  │  │                                │  │  │  │
   └──┼──┼──┼────────────────────────────────┘  │  │  │
      │  │  │                                    │  │  │
      │  │  └────────────────────────────────────┘  │  │
      │  └───────────────────────────────────────────┘  │
      │                                                  │
      ▼                                                  ▼
   To Node                                           To Node
   (GND, CAN, 12V)                                  (GND, CAN, 12V)
```

### Step-by-Step Wiring:

1. **Connect GND (pins 1-2) in parallel:**
   ```
   Breakout-IN Terminal 1 → Breakout-OUT Terminal 1
   Breakout-IN Terminal 2 → Breakout-OUT Terminal 2
   Both → Common GND rail
   ```

2. **Connect CAN_H (pin 3) in parallel:**
   ```
   Breakout-IN Terminal 3 → MCP2515 CANH
   Breakout-OUT Terminal 3 → MCP2515 CANH (same point)
   ```

3. **Connect CAN_L (pin 4) in parallel:**
   ```
   Breakout-IN Terminal 4 → MCP2515 CANL
   Breakout-OUT Terminal 4 → MCP2515 CANL (same point)
   ```

4. **Connect 12V (pins 7-8) in parallel:**
   ```
   Breakout-IN Terminal 7,8 → Regulator input
   Breakout-OUT Terminal 7,8 → Regulator input (same point)
   ```

---

## Method 2: Using PCB-Mount RJ45 Jacks

### What to Buy:

Search: **"RJ45 jack PCB mount through-hole"**
- Example: Wurth 615008144221
- Or any 8P8C modular jack

### PCB Layout:

```
┌────────────────────────────────────────┐
│         Dual RJ45 Node PCB             │
│                                        │
│  ┌──────┐            ┌──────┐         │
│  │ RJ45 │            │ RJ45 │         │
│  │  IN  │            │ OUT  │         │
│  └──┬───┘            └───┬──┘         │
│     │                    │            │
│     │   ┌────────────┐   │            │
│     └───┤ Common Bus ├───┘            │
│         │ Connection │                │
│         └─────┬──────┘                │
│               │                       │
│         ┌─────┴──────┐                │
│         │   Node     │                │
│         │ Electronics│                │
│         └────────────┘                │
└────────────────────────────────────────┘
```

### Schematic:

```
         RJ45-A (IN)              RJ45-B (OUT)
         
Pin 1 ──┬────────────────────────────┬── Pin 1
Pin 2 ──┘         GND                 └── Pin 2
        │
        ├──→ To MCP2515 GND
        └──→ To Regulator GND
        
Pin 3 ──┬────────────────────────────┬── Pin 3
        │         CAN_H               │
        └──→ To MCP2515 CANH
        
Pin 4 ──┬────────────────────────────┬── Pin 4
        │         CAN_L               │
        └──→ To MCP2515 CANL
        
Pin 7 ──┬────────────────────────────┬── Pin 7
Pin 8 ──┘         12V+                └── Pin 8
        │
        └──→ To Regulator 12V input
```

---

## Method 3: Using a PCB Trace (Most Professional)

### Design Your Own PCB:

**KiCad / EasyEDA Layout:**

```
Layer: Top Copper

   RJ45-A        Traces         RJ45-B
   ┌────┐                       ┌────┐
   │ 1  ├────────═══════────────┤ 1  │  (GND)
   │ 2  ├────────═══════────────┤ 2  │  (GND)
   │ 3  ├────────═══════────────┤ 3  │  (CAN_H)
   │ 4  ├────────═══════────────┤ 4  │  (CAN_L)
   │ 5  │                       │ 5  │
   │ 6  │                       │ 6  │
   │ 7  ├────────═══════────────┤ 7  │  (12V+)
   │ 8  ├────────═══════────────┤ 8  │  (12V+)
   └────┘                       └────┘
       │                         │
       └──→ Taps to node circuits
```

**PCB Design Tips:**
1. Route CAN_H and CAN_L as **differential pair**
2. Keep traces **short and equal length**
3. Add **ground plane** underneath
4. Place **120Ω terminator** with jumper between the jacks
5. Add **TVS diodes** for protection

---

## Termination Resistor Placement

### Where to Put 120Ω Resistor?

**Only on END nodes!** Middle nodes should NOT have termination.

### Switchable Terminator:

Add a jumper between the two RJ45 jacks:

```
        Jumper Position
        ┌─────────┐
        │  ON OFF │
        └────┬────┘
             │
RJ45-A   ┌───▼────┐   RJ45-B
Pin 3 ───┤        ├─── Pin 3
         │  120Ω  │
Pin 4 ───┤        ├─── Pin 4
         └────────┘
```

**Jumper ON:** This is an END node (terminator active)
**Jumper OFF:** This is a MIDDLE node (pass-through only)

### DIP Switch Version:

```
         ┌─────────┐
         │ ┌─┐ ┌─┐ │
CAN_H ───┤ │1│ │2│ ├─── CAN_H
         │ └─┘ └─┘ │
         │  120Ω   │
         │         │
CAN_L ───┤         ├─── CAN_L
         └─────────┘
         
Switch 1&2 ON: Terminator active
Switch 1&2 OFF: Pass-through only
```

---

## Complete Wiring Diagram - Dual RJ45 with Bus Power

```
┌─────────────────────────────────────────────────────────┐
│                    LCC NODE ASSEMBLY                     │
│                                                          │
│  ┌──────┐                              ┌──────┐         │
│  │ RJ45 │                              │ RJ45 │         │
│  │  IN  │                              │ OUT  │         │
│  └──┬───┘                              └───┬──┘         │
│     │                                      │            │
│  Pin 1,2 ─────┬──────────────────────┬── Pin 1,2       │
│               │       GND            │                  │
│  Pin 3,4 ─────┼──┬────────────────┬──┼── Pin 3,4       │
│               │  │    CAN Bus     │  │                  │
│  Pin 7,8 ─────┼──┼────────────────┼──┼── Pin 7,8       │
│               │  │     12V+       │  │                  │
│               │  │                │  │                  │
│               │  │  ┌─────────┐  │  │                  │
│               │  │  │Terminator│ │  │                  │
│               │  │  │ (jumper) │ │  │                  │
│               │  └──┤  120Ω   ├──┘  │                  │
│               │     └─────────┘     │                  │
│               │                     │                  │
│               ▼                     ▼                  │
│          ┌─────────┐          ┌──────────┐            │
│    GND───│  FUSE   │    CAN_H─┤ MCP2515  │            │
│          └────┬────┘    CAN_L─┤  Module  │            │
│               │                └──────────┘            │
│          ┌────▼────┐                                   │
│    12V───│ LM2596  │                                   │
│          │ 12V→5V  │                                   │
│          └────┬────┘                                   │
│               │ 5V                                     │
│          ┌────▼────┐                                   │
│          │AMS1117  │          ┌──────────┐            │
│          │ 5V→3.3V │    3.3V──│  STM32   │            │
│          └────┬────┘    GND───│  F303RE  │            │
│               │ 3.3V          └──────────┘            │
│               │                                        │
│               └───→ To boards                          │
└─────────────────────────────────────────────────────────┘
```

---

## Breadboard Prototype with Two RJ45 Breakouts

### Physical Setup:

```
Component Layout on Breadboard:

Row A-E:   RJ45 Breakout #1 (IN)
Row F-J:   RJ45 Breakout #2 (OUT)
Row K:     Wire jumpers connecting pins 1,2,3,4,7,8
Row L-O:   Fuse, TVS diodes
Row P-T:   LM2596 module
Row U-Y:   AMS1117 module
Row Z+:    STM32 Nucleo board
```

### Jumper Wire List:

| From | To | Signal | Color |
|------|-----|--------|-------|
| RJ45-IN Pin 1 | RJ45-OUT Pin 1 | GND | Black |
| RJ45-IN Pin 2 | RJ45-OUT Pin 2 | GND | Black |
| RJ45-IN Pin 3 | RJ45-OUT Pin 3 | CAN_H | Orange |
| RJ45-IN Pin 4 | RJ45-OUT Pin 4 | CAN_L | Blue |
| RJ45-IN Pin 7 | RJ45-OUT Pin 7 | 12V+ | Red |
| RJ45-IN Pin 8 | RJ45-OUT Pin 8 | 12V+ | Red |
| All Pin 1,2 | GND rail | GND | Black |
| All Pin 7,8 | 12V rail | 12V+ | Red |

---

## Testing Dual RJ45 Pass-Through

### Test 1: Continuity Test (Power OFF)

1. Plug cable into RJ45-IN
2. Use multimeter on RJ45-OUT pins
3. Verify continuity:
   - Pin 1 (IN) to Pin 1 (OUT): ✓
   - Pin 3 (IN) to Pin 3 (OUT): ✓
   - Pin 4 (IN) to Pin 4 (OUT): ✓
   - Pin 7 (IN) to Pin 7 (OUT): ✓

### Test 2: Three-Node Chain

```
Power Supply ──→ [Node A] ──→ [Node B] ──→ [Node C]
                   IN OUT      IN OUT      IN OUT
```

**Procedure:**
1. Connect power to Node A input
2. Measure voltage at Node B input: Should be 12V
3. Measure voltage at Node C input: Should be 12V
4. All nodes should power on

### Test 3: Communication Test

1. Upload sketch to all three nodes
2. Press button on Node A
3. Verify LED lights on Node B and C
4. Confirms CAN signals passing through

---

## Common Mistakes to Avoid

### ❌ Wrong: Star Topology

```
        Node B
          ↑
          │
Node A ───┼─── Node C
          │
          ↓
        Node D
```

**Don't do this!** CAN must be linear bus.

### ✓ Correct: Linear Daisy Chain

```
Node A ──→ Node B ──→ Node C ──→ Node D
```

### ❌ Wrong: Termination on Every Node

```
[Node A]     [Node B]     [Node C]
[120Ω ON]    [120Ω ON]    [120Ω ON]  ← ALL WRONG!
```

### ✓ Correct: Termination Only on Ends

```
[Node A]     [Node B]     [Node C]
[120Ω ON]    [120Ω OFF]   [120Ω ON]  ← CORRECT!
```

---

## Enclosure Mounting

### Panel-Mount RJ45 Jacks:

For a professional enclosure:

```
┌────────────────────────┐
│   Enclosure Front      │
│                        │
│  [RJ45-IN]  [RJ45-OUT] │ ← Panel mount jacks
│                        │
│  [LED Status]          │
│                        │
└────────────────────────┘
```

**Buy:** "RJ45 panel mount jack" or "RJ45 bulkhead connector"

### Mounting Holes:

- RJ45 jacks typically need 15mm × 15mm square cutout
- Or use RJ45 keystone jack with keystone mounting plate

---

## Cable Length Considerations

### Maximum Chain Length:

```
Node 1 ──3m── Node 2 ──5m── Node 3 ──2m── Node 4
        Total: 10m
```

**At 125 kbps:** Maximum total bus length = 500m
**At 250 kbps:** Maximum total bus length = 250m
**At 500 kbps:** Maximum total bus length = 100m

**Rule of thumb:** Keep individual cable segments under 10m each.

---

## Power Distribution

### Voltage Drop Calculation:

With multiple nodes, voltage drops along the cable:

```
12V ──→ [Node 1] ─11.8V─→ [Node 2] ─11.6V─→ [Node 3]
```

**Each node draws current, causing drop.**

**Solutions:**
1. Use thicker wire (Cat6 > Cat5e)
2. Limit number of nodes per segment (5-10 max)
3. Add power injection points every 10 nodes
4. Use higher bus voltage (15V or 24V)

---

## Shopping Links Reference

### Dual RJ45 Setup:

**Search Terms:**
- "RJ45 breakout screw terminal" → Buy 2
- "RJ45 panel mount jack" → Buy 2  
- "RJ45 keystone jack" → Buy 2
- "Ethernet cable bulk" → For making custom lengths

**Estimated Cost:**
- 2× RJ45 Breakouts: $6-10
- Wire & connectors: $5
- Regulators: $5
- **Total: $15-20** (vs $5-10 for single RJ45)

---

## Summary

**For proper daisy-chain LCC network:**
- ✅ Each node needs TWO RJ45 jacks
- ✅ Wire them in parallel (pass-through)
- ✅ Add switchable terminator between jacks
- ✅ Only terminate END nodes
- ✅ Test with 3-node chain

**Start simple:**
1. Build first with USB power, single RJ45
2. Test CAN communication
3. Add second RJ45 for pass-through
4. Add bus power
5. Build multiple nodes!

---

Need help with specific wiring or have questions? Let me know! 🚀

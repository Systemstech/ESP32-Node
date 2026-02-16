# Connecting STM32F303 + MCP2515 via RJ45

## Why Use RJ45 for CAN Bus?

✅ **Standard connector** - easy to find cables
✅ **Robust connection** - reliable, hard to disconnect accidentally
✅ **Multiple wires** - can carry CAN + power in one cable
✅ **Daisy-chaining** - easy to connect multiple nodes
✅ **Professional appearance**
✅ **Shielded cables available** - better noise immunity

---

## Standard CAN Bus Pinouts for RJ45

There are several industry standards. Here are the most common:

### Option 1: CANopen/DeviceNet Standard (Recommended)

This is the most widely used standard for CAN over RJ45:

```
RJ45 Pin    Signal      Wire Color (Standard)
───────────────────────────────────────────────
Pin 1       CAN_GND     White/Blue
Pin 2       CAN_GND     Blue
Pin 3       CAN_H       White/Orange
Pin 4       CAN_L       Orange
Pin 5       CAN_GND     White/Green
Pin 6       (not used)  Green
Pin 7       V+          White/Brown
Pin 8       V+          Brown
```

**Power:** Pins 7-8 can carry 12V or 24V for powering nodes

### Option 2: Simplified CAN-Only (Minimal)

If you only want CAN signals (external power supply):

```
RJ45 Pin    Signal      Notes
────────────────────────────────
Pin 1       GND         Ground reference
Pin 2       GND         Ground reference
Pin 3       CAN_H       CAN High
Pin 4       CAN_H       CAN High (redundant)
Pin 5       CAN_L       CAN Low
Pin 6       CAN_L       CAN Low (redundant)
Pin 7       (not used)
Pin 8       (not used)
```

### Option 3: LCC/OpenLCB Common Practice

Many LCC builders use this simplified pinout:

```
RJ45 Pin    Signal      
──────────────────────
Pin 1       CAN_H
Pin 2       CAN_H       
Pin 3       (not used)
Pin 4       GND
Pin 5       GND
Pin 6       (not used)
Pin 7       CAN_L
Pin 8       CAN_L
```

---

## Hardware Setup Options

### Option A: Direct Wiring (Prototyping)

**What you need:**
- RJ45 breakout board or jack
- Jumper wires

**Wiring Example (DeviceNet Standard):**

```
RJ45 Breakout → MCP2515 Module
─────────────────────────────────
Pin 3 (CAN_H) → MCP2515 CANH
Pin 4 (CAN_L) → MCP2515 CANL
Pin 1 (GND)   → MCP2515 GND & STM32 GND
Pin 7 (V+)    → Power regulator input (if using)

MCP2515 → STM32F303RE (same as before)
───────────────────────────────────────
VCC → 3.3V
GND → GND
CS  → PA4
SI  → PA7
SO  → PA6
SCK → PA5
```

**Diagram:**
```
          RJ45 Jack                MCP2515           STM32F303RE
         ┌─────────┐              ┌────────┐        ┌──────────┐
Pin 3 ───┤ CAN_H   ├──────────────┤ CANH   │        │          │
Pin 4 ───┤ CAN_L   ├──────────────┤ CANL   │        │          │
Pin 1 ───┤ GND     ├──────────────┤ GND    ├────────┤ GND      │
         │         │              │        │        │          │
         │         │              │ VCC    ├────────┤ 3.3V     │
         │         │              │ CS     ├────────┤ PA4      │
         │         │              │ SI     ├────────┤ PA7      │
         │         │              │ SO     ├────────┤ PA6      │
         │         │              │ SCK    ├────────┤ PA5      │
         └─────────┘              └────────┘        └──────────┘
```

---

### Option B: RJ45 with Power (Bus Powered)

If you want to power your node from the RJ45 cable:

**Components Needed:**
- RJ45 jack with magnetics (optional, for protection)
- Voltage regulator (if bus voltage is 12V/24V)
  - LM2596 buck converter (12V → 5V)
  - AMS1117-3.3 (5V → 3.3V)
  - Or combined 12V → 3.3V regulator

**Wiring:**
```
RJ45 Pin 7,8 (V+) → Voltage Regulator Input (12V/24V)
RJ45 Pin 1,2 (GND) → Ground
Regulator Output → 3.3V for STM32 & MCP2515
```

**Example Circuit:**
```
RJ45                 Regulator              STM32 + MCP2515
                     
Pin 7,8 ─────┬───→ 12V Input
Pin 1,2 ─────┼───→ GND          ┌──────────┐
             │                  │ LM2596   │
             │                  │ 12V→5V   │
Pin 3 ───────┼──────────────────┤          ├──→ 5V
Pin 4 ───────┼──────────────────┤          │   ↓
             │                  └──────────┘   AMS1117
             │                                 5V→3.3V
             │                                    ↓
             └───────────────────────────────→ 3.3V to boards
```

---

### Option C: Custom PCB (Professional)

For a permanent solution, design a small PCB with:

**PCB Layout:**
```
┌─────────────────────────────────────────┐
│  LCC Node PCB                           │
│                                         │
│  ┌───────┐      ┌────────┐             │
│  │ RJ45  │      │ STM32  │             │
│  │ Jack  │──────│ F303RE │             │
│  └───────┘      └────────┘             │
│                                         │
│  ┌────────┐     ┌──────────┐           │
│  │Voltage │     │ MCP2515  │           │
│  │Regulator─────│  Module  │           │
│  └────────┘     └──────────┘           │
│                                         │
│  [Terminal Blocks for I/O]             │
└─────────────────────────────────────────┘
```

**Features to include:**
- RJ45 jack with magnetics (EMI protection)
- TVS diodes on CAN lines (surge protection)
- 120Ω termination resistor with jumper
- Power supply section
- Screw terminals for sensors/outputs

---

## Cable Types

### Standard Ethernet Cables

**Can you use regular Ethernet cables?**
- ✅ **YES for short runs** (<10m)
- ✅ **Twisted pairs are good** for CAN
- ⚠️ **Not ideal for long runs** (impedance not optimized for CAN)

**Ethernet Cable Types:**
- **Cat5e / Cat6**: Works fine for CAN
- **Stranded vs Solid**: Stranded is more flexible
- **Shielded (STP)**: Better for noisy environments

### Proper CAN Bus Cables

For best performance, use actual CAN bus cable:

**DeviceNet Cable:**
- Specifically designed for CAN
- Correct impedance (120Ω)
- Available with RJ45 connectors
- Example: Belden 3082A

**DIY Cable:**
- Use twisted pair wire (24 AWG)
- Crimp RJ45 connectors
- Follow standard pinout

---

## Termination Resistor

### What is it?
A 120Ω resistor between CAN_H and CAN_L at **each end** of the bus.

### Where to add it?

**Option 1: Inside RJ45 Connector**
Some RJ45 jacks have space for a resistor
```
     ┌─────────────┐
     │   RJ45      │
     │             │
CAN_H┤○──┬────────○┤ Pin 3
     │   │         │
     │  120Ω       │
     │   │         │
CAN_L┤○──┴────────○┤ Pin 4
     └─────────────┘
```

**Option 2: External Terminator Plug**
Create a small RJ45 plug with just a resistor
```
     ┌─────────────┐
     │  Terminator │
     │    Plug     │
     │             │
Pin 3├──┬─────┬───┤ Pin 3
     │  │     │    │
     │ 120Ω  │    │
     │  │     │    │
Pin 4├──┴─────┴───┤ Pin 4
     └─────────────┘
```

**Option 3: Switchable On-Board**
Add a jumper or DIP switch on your PCB
```
        ┌────────┐
CAN_H ──┤        ├── CANH to transceiver
        │ Jumper │
        │  120Ω  │
        │        │
CAN_L ──┤        ├── CANL to transceiver
        └────────┘
```

---

## Network Topology

### Linear Bus (Correct)

```
Node 1        Node 2        Node 3        Node 4
[TERM]                                    [TERM]
  │             │             │             │
  ├─────────────┼─────────────┼─────────────┤
  RJ45          RJ45          RJ45          RJ45
  Cable         Cable         Cable         Cable
```

- Termination at BOTH ends only
- Maximum total length: 500m @ 125kbps

### Daisy Chain Connection

**Each node has 2 RJ45 jacks:**
```
Node 1         Node 2         Node 3
┌─────┐       ┌─────┐       ┌─────┐
│ ○ ○ │───────│ ○ ○ │───────│ ○ ○ │
└─────┘       └─────┘       └─────┘
[IN][OUT]     [IN][OUT]     [IN][OUT]
```

Internally, both jacks connect to same CAN_H/CAN_L

---

## Practical Shopping List

### For Prototyping:

| Item | Quantity | Example | Price |
|------|----------|---------|-------|
| RJ45 Breakout Board | 1 | SparkFun BOB-00716 | $5 |
| RJ45 Ethernet Cable | 1-2m | Cat5e/Cat6 | $3 |
| 120Ω Resistor | 2 | 1/4W through-hole | $0.50 |

### For Permanent Installation:

| Item | Quantity | Example | Price |
|------|----------|---------|-------|
| RJ45 Jack (PCB mount) | 1-2 | Wurth 615008144221 | $2 |
| RJ45 Plugs | 10 | Standard Cat5e | $5 |
| CAN Bus Cable | Per meter | DeviceNet cable | $1-2/m |
| TVS Diode | 2 | SMAJ24CA | $1 |
| Voltage Regulator | 1 | LM2596 module | $3 |

---

## PCB Design Tips

### Schematic Symbols

```
      RJ45 Jack
   ┌─────────────┐
 1 │○ GND        │
 2 │○ GND        │
 3 │○ CAN_H      │──→ To MCP2515 CANH
 4 │○ CAN_L      │──→ To MCP2515 CANL
 5 │○            │
 6 │○            │
 7 │○ V+ (12V)   │──→ To regulator
 8 │○ V+ (12V)   │──→ To regulator
   └─────────────┘
```

### PCB Layout Considerations:

1. **Keep CAN traces short** from RJ45 to transceiver
2. **Route CAN_H and CAN_L as differential pair**
3. **Add ground plane** underneath
4. **TVS diodes close to connector**
5. **Termination resistor accessible** (via jumper)

---

## Testing Your RJ45 Connection

### Step 1: Continuity Test
Use multimeter to verify:
- Pin 3 connects to CANH
- Pin 4 connects to CANL
- Pin 1 connects to GND

### Step 2: Cable Test
- Plug in RJ45 cable
- Measure continuity end-to-end
- Check for shorts between pins

### Step 3: Network Test
- Connect two nodes
- Add terminators at each end
- Upload test sketch
- Check CAN communication

---

## Ready-Made Solutions

### Commercial RJ45 CAN Modules

**Option 1: Buy RJ45 CAN Breakout**
- Search: "RJ45 CAN bus breakout"
- ~$10-15
- Has RJ45 jack + screw terminals

**Option 2: Industrial CAN Node**
- Search: "DeviceNet connector module"
- Professional quality
- More expensive ($20-50)

---

## Example: Simple RJ45 Node

### Bill of Materials:

```
Part              Qty    Notes
─────────────────────────────────────────
STM32F303RE       1      Nucleo board
MCP2515 Module    1      With TJA1050
RJ45 Breakout     1      8-pin screw terminals
120Ω Resistor     1      If end node
Jumper wires      10     Dupont cables
Enclosure         1      Optional
```

### Wiring:

```python
# RJ45 Breakout Screw Terminals
Terminal 3 (CAN_H) → MCP2515 CANH
Terminal 4 (CAN_L) → MCP2515 CANL  
Terminal 1 (GND)   → MCP2515 GND → STM32 GND
Terminal 2 (GND)   → MCP2515 GND → STM32 GND

# Between terminals 3 & 4: Add 120Ω if end node

# MCP2515 to STM32 (same as always)
MCP2515 VCC → STM32 3.3V
MCP2515 CS  → STM32 PA4
MCP2515 SI  → STM32 PA7
MCP2515 SO  → STM32 PA6
MCP2515 SCK → STM32 PA5
```

---

## Safety & Best Practices

### Do's:
✅ Use shielded cable in noisy environments
✅ Keep CAN wires twisted together
✅ Add TVS diodes for protection
✅ Terminate properly (120Ω at ends only)
✅ Keep total bus length under 500m @ 125kbps

### Don'ts:
❌ Don't create star topology (linear only)
❌ Don't forget terminators
❌ Don't mix different cable types
❌ Don't exceed voltage ratings
❌ Don't create ground loops

---

## Next Steps

1. **Start Simple:** Use RJ45 breakout board
2. **Test:** Verify connectivity with test sketch
3. **Connect Nodes:** Link two nodes via RJ45 cable
4. **Expand:** Add more nodes to network
5. **Design PCB:** Create custom board if needed

---

Need help with any specific aspect? Let me know! 🚀

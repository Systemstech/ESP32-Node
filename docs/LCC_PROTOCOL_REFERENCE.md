# LCC Protocol Quick Reference

## LCC/OpenLCB Overview

Layout Command Control (LCC) / OpenLCB is a comprehensive standard for model railroad control and general automation. It uses CAN bus for physical communication.

## Key Concepts

### Node ID
- **Format**: 48-bit unique identifier (6 bytes)
- **Structure**: `0x02 01 XX XX XX XX` where XX is unique per device
- **Purpose**: Globally unique identifier for each node

### Alias
- **Format**: 12-bit short identifier
- **Purpose**: Used in CAN frames to save bandwidth
- **Allocation**: Generated from Node ID using specific algorithm

### Event ID
- **Format**: 64-bit identifier (8 bytes)
- **Purpose**: Identifies state changes (button press, sensor trigger, etc.)
- **Structure**: Often `Node ID` + `Event Index`

## CAN Frame Format

LCC uses CAN 2.0B Extended Frames (29-bit identifier):

```
┌─────────────────────────────────────┐
│  CAN Identifier (29 bits)           │
├──────────┬────────────┬─────────────┤
│ Variable │    MTI     │   Alias     │
│ (17 bits)│  (12 bits) │  (12 bits)  │
└──────────┴────────────┴─────────────┘
│         Data (0-8 bytes)            │
└─────────────────────────────────────┘
```

## Common Message Types (MTI)

### Node Initialization

| MTI    | Name                        | Direction | Data            |
|--------|-----------------------------|-----------|-----------------|
| 0x0100 | Initialization Complete     | Outgoing  | Node ID (6 bytes)|
| 0x0490 | Verify Node ID Global       | Incoming  | None or Node ID |
| 0x0488 | Verify Node ID Addressed    | Incoming  | Node ID (6 bytes)|
| 0x0170 | Verified Node ID            | Outgoing  | Node ID (6 bytes)|

### Node Information

| MTI    | Name                        | Direction | Data            |
|--------|-----------------------------|-----------|-----------------|
| 0x0828 | Protocol Support Inquiry    | Incoming  | None            |
| 0x0668 | Protocol Support Reply      | Outgoing  | Protocol Bits   |
| 0x0DE8 | Simple Node Ident Request   | Incoming  | None            |
| 0x0A08 | Simple Node Ident Reply     | Outgoing  | Node Info       |

### Event Messages

| MTI    | Name                        | Direction | Data            |
|--------|-----------------------------|-----------|-----------------|
| 0x0594 | Producer Identified Valid   | Outgoing  | Event ID (8 bytes)|
| 0x0595 | Producer Identified Invalid | Outgoing  | Event ID (8 bytes)|
| 0x04C7 | Consumer Identified Valid   | Outgoing  | Event ID (8 bytes)|
| 0x04C6 | Consumer Identified Invalid | Outgoing  | Event ID (8 bytes)|
| 0x05B4 | Producer/Consumer Report    | Both      | Event ID (8 bytes)|

### Error Handling

| MTI    | Name                        | Direction | Data            |
|--------|-----------------------------|-----------|-----------------|
| 0x0068 | Optional Interaction Rejected| Outgoing | Error Code      |
| 0x1068 | Terminate Due to Error      | Outgoing  | Error Info      |

## Initialization Sequence

```
Power On
   │
   ├──> Generate Alias from Node ID
   │
   ├──> Check for Alias Conflicts (CIM sequence)
   │    └──> Send 4 Check ID (CID) frames
   │         Wait for objections
   │
   ├──> Reserve Alias (RID frame)
   │
   ├──> Send AMD (Alias Map Definition)
   │    Data: Node ID (6 bytes)
   │
   ├──> Send Initialization Complete (0x0100)
   │    Data: Node ID (6 bytes)
   │
   └──> Ready to communicate
```

## Example Message Sequences

### Example 1: Node Announces Itself

```
TX: MTI 0x0100, Alias 0x7A3
    Data: 02 01 99 AA BB CC
    (Initialization Complete with Node ID)
```

### Example 2: Another Node Queries Your ID

```
RX: MTI 0x0490, Alias 0x5B1
    Data: (empty - global query)

TX: MTI 0x0170, Alias 0x7A3
    Data: 02 01 99 AA BB CC
    (Verified Node ID)
```

### Example 3: Button Press Event

```
TX: MTI 0x0594, Alias 0x7A3
    Data: 02 01 99 AA BB CC 00 01
    (Producer Identified Valid for Event 0x020199AABBCC0001)
```

### Example 4: LED Control Event

```
RX: MTI 0x0594, Alias 0x5B1
    Data: 02 01 99 AA BB CC 00 10
    (Another node produced Event 0x020199AABBCC0010)

Action: Turn on LED (if we consume this event)
```

## Event ID Convention

Common practice for event IDs:

```
┌──────────────────────────────────────────┐
│  Node ID (48 bits)  │  Event Index (16 bits) │
├─────────────────────┼──────────────────────┤
│  02 01 99 AA BB CC  │     00 01            │
└─────────────────────┴──────────────────────┘
```

**Examples:**
- `0x020199AABBCC0001` - Button 1 Pressed
- `0x020199AABBCC0002` - Button 1 Released
- `0x020199AABBCC0010` - LED 1 On
- `0x020199AABBCC0011` - LED 1 Off

## Protocol Support Bits

Indicate which protocols your node supports:

| Bit | Protocol                     |
|-----|------------------------------|
| 0   | Simple Node Information      |
| 1   | Configuration Description    |
| 2   | Datagram                     |
| 3   | Stream                       |
| 4   | Memory Configuration         |
| 5   | Reservation                  |
| 6   | Event Exchange               |
| 7   | Identification               |

## Common Use Cases

### Use Case 1: Simple Button and LED

**Node 1 (Button):**
- Produces: `EVENT_BUTTON_PRESSED` when button pushed
- Produces: `EVENT_BUTTON_RELEASED` when button released

**Node 2 (LED):**
- Consumes: `EVENT_BUTTON_PRESSED` → Turn LED on
- Consumes: `EVENT_BUTTON_RELEASED` → Turn LED off

### Use Case 2: Occupancy Detector

**Detector Node:**
- Produces: `EVENT_BLOCK_OCCUPIED` when train detected
- Produces: `EVENT_BLOCK_CLEAR` when train leaves

**Panel Node:**
- Consumes: `EVENT_BLOCK_OCCUPIED` → Show red indicator
- Consumes: `EVENT_BLOCK_CLEAR` → Show green indicator

### Use Case 3: Turnout Control

**Control Panel Node:**
- Produces: `EVENT_TURNOUT_1_THROW` when button pressed
- Produces: `EVENT_TURNOUT_1_CLOSE` when button pressed

**Turnout Driver Node:**
- Consumes: `EVENT_TURNOUT_1_THROW` → Drive servo/motor
- Consumes: `EVENT_TURNOUT_1_CLOSE` → Drive servo/motor

## Debugging Tips

### Monitor CAN Traffic

Use a CAN analyzer to see all bus traffic:

```
Time    ID          Data                    Decoded
────────────────────────────────────────────────────────
0.000   0x1007A3    02 01 99 AA BB CC       Init Complete
0.100   0x490581    [empty]                 Verify Node ID
0.101   0x1707A3    02 01 99 AA BB CC       Verified
0.500   0x5947A3    02 01 99 AA BB CC 00 01 Event Produced
```

### Common Issues

**No ACK on transmission:**
- No other nodes on bus
- Incorrect termination
- Wrong baud rate

**Bus Off errors:**
- Electrical problem on bus
- Conflicting bit timing
- Cable too long for baud rate

**Alias conflicts:**
- Two nodes with same Node ID
- Incorrect alias allocation algorithm

## Testing with JMRI

JMRI (Java Model Railroad Interface) can test LCC nodes:

1. Configure JMRI for LCC/OpenLCB
2. Set CAN adapter (GridConnect, USB-CAN, etc.)
3. Use "Monitor LCC Traffic" tool
4. Use "Send LCC Message" tool
5. Configure events in JMRI Event Table

## Configuration Tools

- **JMRI**: Full-featured, Java-based
- **LCC Buffer**: Simple traffic monitor
- **Custom Python scripts**: Using python-can library

## Further Reading

- [OpenLCB.org](https://openlcb.org) - Official standards
- [LCC Documentation](https://openlcb.org/openlcb-and-lcc-documents/)
- [CAN Bus Basics](https://www.ti.com/lit/an/sloa101b/sloa101b.pdf)

## Example Python Test Script

```python
import can

# Setup CAN interface
bus = can.interface.Bus(channel='can0', bustype='socketcan', bitrate=125000)

# Listen for LCC messages
for msg in bus:
    mti = (msg.arbitration_id >> 12) & 0xFFF
    alias = msg.arbitration_id & 0xFFF
    print(f"MTI: 0x{mti:04X}, Alias: 0x{alias:03X}, Data: {msg.data.hex()}")
```

---

This quick reference covers the essential LCC protocol elements for getting started with your STM32 node!

# Bus-Powered LCC Node - STM32F303RE + MCP2515

## Yes, You Can Power From the Bus! 🔌

Most LCC networks provide **12V or 15V DC** on the RJ45 cable pins 7-8. You just need to regulate it down to **3.3V** for your STM32 and MCP2515.

---

## Power Requirements

### What You Need to Supply:

| Component | Voltage | Current (Typical) | Current (Max) |
|-----------|---------|-------------------|---------------|
| STM32F303RE | 3.3V | ~50mA | 150mA |
| MCP2515 + TJA1050 | 3.3V | ~30mA | 100mA |
| **Total** | **3.3V** | **~80mA** | **~250mA** |

**Add safety margin:** Design for **500mA** to handle inrush current and future additions.

---

## Standard LCC Bus Voltage

### Common Voltages on LCC Networks:

- **12V DC** - Most common
- **15V DC** - Also used
- **24V DC** - Industrial systems
- **5V DC** - Some DIY setups

**For this guide, we'll assume 12V input.**

---

## Voltage Regulator Options

### Option 1: Linear Regulator (Simplest)

**AMS1117-3.3 LDO Regulator**

**Pros:**
- ✅ Very simple (3 pins)
- ✅ Cheap ($0.50)
- ✅ Low noise
- ✅ Few external components

**Cons:**
- ❌ Wastes power as heat
- ❌ Gets hot with 12V input
- ❌ Limited current (~800mA max)

**Wiring:**
```
12V (from RJ45) ──→ [IN]  AMS1117-3.3  [OUT] ──→ 3.3V to boards
                           [GND]
                            │
                            ↓
                           GND
```

**Heat Dissipation:**
- Power loss = (12V - 3.3V) × 0.25A = **2.2W** 🔥
- **Gets very hot!** Needs heatsink or better solution

### Option 2: Buck Converter (Recommended!)

**LM2596 Step-Down Module**

**Pros:**
- ✅ Efficient (85-90%)
- ✅ Low heat
- ✅ Can handle 3A+
- ✅ Adjustable output

**Cons:**
- ❌ Slightly more expensive ($2-3)
- ❌ Can generate switching noise

**Wiring:**
```
12V (from RJ45) ──→ [IN+]  LM2596 Module  [OUT+] ──→ 3.3V to boards
GND             ──→ [IN-]                 [OUT-] ──→ GND
```

**Power loss:** Only ~0.3W (stays cool!)

### Option 3: Two-Stage (Best Performance)

**12V → 5V (Buck) → 3.3V (LDO)**

**Why?**
- Buck converter for efficiency
- LDO for clean, low-noise 3.3V

**Components:**
- LM2596 module (12V → 5V)
- AMS1117-3.3 (5V → 3.3V)

**Wiring:**
```
12V ──→ [LM2596] ──→ 5V ──→ [AMS1117-3.3] ──→ 3.3V
                      │                      │
                     GND                    GND
```

**Benefits:**
- ✅ Efficient (buck converter)
- ✅ Clean power (LDO filter)
- ✅ AMS1117 barely gets warm (5V-3.3V = 1.7V drop)

---

## Complete Circuit Diagram

### Full Bus-Powered Node:

```
     RJ45 Jack          Voltage            STM32F303RE
                       Regulation          & MCP2515
                       
Pin 7 ───┬─────→ 12V ───┐
Pin 8 ───┘              │
                   ┌────▼────┐
                   │ LM2596  │
                   │ Buck    │
                   │12V→5V   │
Pin 1 ───┬─────→ GND   │    ├───→ 5V
Pin 2 ───┘         └────┼────┘    │
                        │         │
Pin 3 ────────────────────────────┼───→ CANH
Pin 4 ────────────────────────────┼───→ CANL
                                  │
                            ┌─────▼─────┐
                            │ AMS1117   │
                            │  5V→3.3V  │
                            └─────┬─────┘
                                  │
                                 3.3V
                                  │
                    ┌─────────────┴──────────────┐
                    │                            │
                ┌───▼────┐                  ┌────▼─────┐
                │ STM32  │                  │ MCP2515  │
                │F303RE  │◄────SPI──────────┤ Module   │
                └────────┘                  └──────────┘
```

---

## Shopping List - Bus Powered Version

### Additional Components Needed:

| Item | Quantity | Purpose | Price |
|------|----------|---------|-------|
| LM2596 Buck Module | 1 | 12V → 5V | $2-3 |
| AMS1117-3.3 Module | 1 | 5V → 3.3V | $1-2 |
| OR AMS1117-3.3 IC | 1 | 5V → 3.3V | $0.50 |
| 10µF Capacitor | 2 | Power filtering | $0.50 |
| 100µF Capacitor | 2 | Bulk storage | $1 |
| Fuse or PTC | 1 | Overcurrent protection | $0.50 |

**Total additional cost: ~$5-8**

### Pre-Made Modules (Easier):

Search for these on Amazon/eBay/AliExpress:

1. **"LM2596 DC-DC Buck Converter"** - $2-3
   - Has screw terminals
   - Adjustable output
   - Already has capacitors

2. **"AMS1117-3.3V Module"** - $1-2
   - Complete with capacitors
   - Just solder in

3. **"12V to 3.3V DC-DC Converter"** - $3-5
   - Single module does everything
   - Look for "MP2307" or "LM2596S"

---

## Wiring with Pre-Made Modules

### Using LM2596 + AMS1117 Modules:

```
RJ45 Breakout Board
─────────────────────
Terminal 7,8 (12V) ───┐
                      │
                ┌─────▼──────┐
                │  LM2596    │
                │  Module    │
                │            │
Terminal 1,2 ───┤ IN- GND    │
                └─────┬──────┘
                      │ 5V OUT
                      │
                ┌─────▼──────┐
                │ AMS1117    │
                │ -3.3 Module│
                │            │
                └─────┬──────┘
                      │ 3.3V OUT
                      │
                ┌─────┴──────┐
                │            │
           To STM32      To MCP2515
           3.3V pin      VCC pin
```

**Step-by-step:**

1. **Connect 12V input:**
   - RJ45 pin 7 → LM2596 IN+
   - RJ45 pin 8 → LM2596 IN+ (parallel)
   
2. **Connect ground:**
   - RJ45 pin 1 → LM2596 IN-
   - RJ45 pin 2 → LM2596 IN- (parallel)
   
3. **Adjust LM2596 output:**
   - Turn potentiometer to get 5V out
   - Use multimeter to check
   
4. **Connect to AMS1117:**
   - LM2596 OUT+ → AMS1117 IN
   - LM2596 OUT- → AMS1117 GND
   
5. **Get 3.3V:**
   - AMS1117 OUT → STM32 3.3V pin
   - AMS1117 OUT → MCP2515 VCC
   - AMS1117 GND → Common ground

---

## Protection Circuit (Recommended)

### Add These for Safety:

```
12V from RJ45 ──→ [FUSE] ──→ [TVS Diode] ──→ Buck Converter
                    500mA        to GND
```

**Components:**

1. **Fuse or PTC Resettable Fuse**
   - Rating: 500mA or 1A
   - Protects against shorts
   - Example: "Polyfuse 500mA"
   
2. **TVS Diode**
   - Rating: 15V or 18V
   - Protects against voltage spikes
   - Example: SMAJ15CA or 1.5KE15CA

3. **Reverse Polarity Protection**
   - Add diode in series (1N4007)
   - Or use MOSFET circuit
   - Prevents damage if bus wired wrong

### Complete Protected Circuit:

```
     RJ45
      │
Pin 7,8 (12V+) ──→ [FUSE] ──→ [DIODE] ──→ [TVS] ──→ Buck Converter
                    500mA     1N4007    to GND
                                                       
Pin 1,2 (GND)  ────────────────────────────────────→ GND
```

---

## Physical Layout

### Suggested Board Layout:

```
┌──────────────────────────────────────────┐
│  LCC Bus-Powered Node PCB                │
│                                          │
│  ┌──────┐     ┌────────┐                │
│  │ RJ45 │     │ FUSE   │                │
│  │ Jack │─────│ TVS    │                │
│  └──────┘     └────┬───┘                │
│                    │                     │
│               ┌────▼────┐                │
│               │ LM2596  │                │
│               │ 12V→5V  │                │
│               └────┬────┘                │
│                    │                     │
│               ┌────▼────┐                │
│               │AMS1117  │                │
│               │ 5V→3.3V │                │
│               └────┬────┘                │
│                    │ 3.3V                │
│        ┌───────────┴──────────┐          │
│        │                      │          │
│   ┌────▼────┐           ┌─────▼─────┐   │
│   │ STM32   │           │  MCP2515  │   │
│   │ F303RE  │◄──SPI─────┤  Module   │   │
│   └─────────┘           └───────────┘   │
│                                          │
│   [Screw Terminals for I/O]             │
└──────────────────────────────────────────┘
```

---

## Power Budget

### Check Your Total Current:

**Base System:**
- STM32F303RE: 50mA
- MCP2515 + TJA1050: 30mA
- **Subtotal: 80mA**

**Add Your Peripherals:**
- LED indicators (3x): 60mA (20mA each)
- Servo motor: 500mA (!)
- Relay coil: 70mA
- Sensors: 10-50mA each

**Example Total:** 80 + 60 = 140mA (well under budget)

**Important:** If adding servos or relays, consider separate 5V supply!

---

## Testing Bus Power

### Step 1: Before Connecting Boards

1. **Connect RJ45 to bus** (or 12V power supply)
2. **Measure voltages:**
   - At LM2596 output: Should be ~5V
   - At AMS1117 output: Should be ~3.3V
3. **Check for heat:**
   - LM2596: Should be barely warm
   - AMS1117: May be slightly warm

### Step 2: Load Test

1. **Connect STM32 and MCP2515**
2. **Power on bus**
3. **Measure voltages under load:**
   - Should still be stable 3.3V
4. **Check current draw:**
   - Use multimeter in series
   - Should be <250mA total

### Step 3: Long-Term Test

1. **Run for 30 minutes**
2. **Check temperature:**
   - Regulators should not be too hot to touch
   - If burning hot, improve heatsinking or use more efficient regulator

---

## Breadboard Prototype

### Quick Test Setup:

```
Components needed:
- RJ45 breakout board
- LM2596 module  
- AMS1117-3.3 module
- Jumper wires
- Breadboard

Steps:
1. Insert modules into breadboard
2. Wire 12V from RJ45 to LM2596 IN
3. Wire LM2596 OUT to AMS1117 IN
4. Connect all grounds together
5. Power STM32 from AMS1117 OUT
6. Test!
```

**Photo Guide:**
```
Breadboard Layout:

[RJ45 Breakout] ── Red wire ──→ [LM2596 IN+]
                ── Black wire ─→ [LM2596 IN-]
                
                                [LM2596 OUT+] ── Red ──→ [AMS1117 IN]
                                [LM2596 OUT-] ── Black ─→ [AMS1117 GND]
                
                                                         [AMS1117 OUT] ──→ STM32 3.3V
                                                         [AMS1117 GND] ──→ STM32 GND
```

---

## Arduino Code Modification

### Monitor Input Voltage:

You can monitor the bus voltage using STM32's ADC:

```cpp
// Add voltage divider to measure 12V input
// 12V ──[10kΩ]──┬──[3.3kΩ]── GND
//               │
//              PA0 (ADC)

void setup() {
  pinMode(PA0, INPUT_ANALOG);
}

void loop() {
  int rawValue = analogRead(PA0);
  float voltage = (rawValue / 4096.0) * 3.3;
  float busVoltage = voltage * ((10 + 3.3) / 3.3);
  
  Serial.print("Bus Voltage: ");
  Serial.print(busVoltage);
  Serial.println(" V");
  
  // Warn if voltage too low
  if (busVoltage < 11.0) {
    Serial.println("WARNING: Bus voltage low!");
  }
  
  delay(1000);
}
```

---

## Common Issues & Solutions

### Issue 1: Voltage Drops Under Load

**Symptom:** 3.3V drops to 3.0V when powered on

**Solutions:**
- Add larger capacitors (470µF or 1000µF)
- Use thicker wire from RJ45 to regulator
- Check LM2596 is set to proper 5V output
- Upgrade to higher current regulator

### Issue 2: Regulators Getting Hot

**Symptom:** LM2596 or AMS1117 very hot

**Solutions:**
- Add heatsink to LM2596
- Ensure good airflow
- Reduce load current
- Use switching regulator instead of LDO

### Issue 3: Noise in CAN Communication

**Symptom:** CAN errors when switching regulator active

**Solutions:**
- Add ferrite bead on 3.3V line
- Use separate ground planes for power and CAN
- Add 100nF ceramic caps near ICs
- Use shielded cable for CAN

### Issue 4: Node Resets Randomly

**Symptom:** STM32 resets during operation

**Solutions:**
- Increase input capacitance (add 470µF)
- Add 10µF tantalum cap near STM32
- Check all ground connections solid
- Measure 3.3V rail with oscilloscope for dips

---

## Enclosure Considerations

### Heat Management:

If putting in enclosure:
- Drill ventilation holes
- Mount regulators on aluminum case (heatsink)
- Use thermal paste
- Consider adding small fan for high-current applications

### Strain Relief:

- Use cable glands for RJ45 cable entry
- Secure cable inside enclosure
- Don't rely on RJ45 jack for mechanical support

---

## Summary: Should You Use Bus Power?

### ✅ Use Bus Power If:
- Building permanent installation
- Want clean, professional setup
- Have multiple nodes (easier wiring)
- Bus provides stable 12V/15V
- Current draw <500mA

### ❌ Use USB Power If:
- Prototyping/testing
- Need >1A current (servos, motors)
- Bus voltage unreliable
- Simpler debugging

---

## Next Steps

1. **Decide on power source:**
   - Bus powered = cleaner but more complex
   - USB powered = simpler for testing

2. **Buy regulator modules** (~$5)

3. **Build on breadboard first**

4. **Test thoroughly**

5. **Design permanent PCB** (optional)

---

**Want help designing a bus-powered PCB or choosing specific modules?** Let me know! 🚀

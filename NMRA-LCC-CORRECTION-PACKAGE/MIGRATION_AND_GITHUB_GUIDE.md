# NMRA S-9.7.1.1 Correction Package - Ready for GitHub

## 📦 What's In This Package

This package contains **corrected documentation** based on the official **NMRA S-9.7.1.1 standard** (adopted January 24, 2025).

### ✅ What's Corrected:

1. **RJ45 Pinout** - Now uses official NMRA standard
2. **Ground Connections** - Added required Pin 3 ↔ Pin 6 connection
3. **All 8 pins defined** - Including optional DCC on pins 4-5
4. **Cable pairing requirements** - Documented which wires must be twisted pairs
5. **Power specifications** - Voltage ranges and current limits

---

## 🎯 Quick Summary of Changes

### Official NMRA Pinout:

```
Pin 1: CAN_H        - CAN Bus High  
Pin 2: CAN_L        - CAN Bus Low
Pin 3: CAN_GND      - CAN Ground (MUST connect to Pin 6!)
Pin 4: ALT_L        - Alternate (optional DCC)
Pin 5: ALT_H        - Alternate (optional DCC)
Pin 6: CAN_SHIELD   - Shield (MUST connect to Pin 3!)
Pin 7: PWR_NEG      - Power Negative
Pin 8: PWR_POS      - Power Positive (+9-15VDC)
```

### 🔴 CRITICAL Requirement:

**Pins 3 and 6 MUST be connected together inside your node!**

```
Per NMRA S-9.7.1.1 Section 4:
"Nodes shall connect conductors 3 and 6.  
This connection shall be rated to carry at least 1A."
```

---

## 📂 Files in This Package

### For Both Platforms:

- **NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md** - Complete official standard reference
- **OFFICIAL_STANDARD_COMPARISON.md** - What changed and why
- **THIS FILE** - Migration guide

### For ESP32:

- **ESP32_WIRING_CORRECTED.md** - Complete ESP32 wiring with NMRA pinout
- **ESP32_QUICK_START_CORRECTED.md** - Updated quick start
- Arduino sketches (LCC_Node_ESP32.ino, CAN_Test_ESP32.ino)

### For STM32:

- **STM32_WIRING_CORRECTED.md** - Complete STM32 wiring with NMRA pinout
- **STM32_QUICK_START_CORRECTED.md** - Updated quick start
- Arduino sketches (LCC_Node_Arduino.ino, MCP2515_Test_Arduino.ino)
- STM32Cube files (mcp2515.c/h, lcc_node files)

---

## 🔧 How to Apply These Corrections

### If You Haven't Built Yet:

**Easy!** Just use the corrected wiring guides:
1. Follow **ESP32_WIRING_CORRECTED.md** or **STM32_WIRING_CORRECTED.md**
2. Pay special attention to Pin 3 ↔ Pin 6 connection
3. Build and test!

### If You Already Built with Old Pinout:

**STOP!** Don't connect to LCC network yet!

**Hardware changes required:**

```
OLD Wiring (WRONG):          NEW Wiring (CORRECT):
────────────────────         ─────────────────────
Pin 3 → CAN_H                Pin 1 → CAN_H
Pin 4 → CAN_L                Pin 2 → CAN_L
Pin 1 → GND                  Pin 3 → CAN_GND  ┐
Pin 2 → GND                  Pin 6 → CAN_SHIELD┘ Connect these!
                             Pin 7 → PWR_NEG
                             Pin 8 → PWR_POS
```

**Arduino code:** No changes needed! Only hardware wiring changes.

---

## 📋 Wiring Checklists

### ESP32 Node Checklist:

```
RJ45 Connection:
- [ ] Pin 1 → SN65HVD230 CANH
- [ ] Pin 2 → SN65HVD230 CANL
- [ ] Pin 3 → SN65HVD230 GND + Pin 6
- [ ] Pin 6 → SN65HVD230 GND + Pin 3
- [ ] Pin 7 → Power GND (if bus powered)
- [ ] Pin 8 → Voltage regulator (if bus powered)

ESP32 Connection:
- [ ] GPIO5 → SN65HVD230 CTX
- [ ] GPIO4 → SN65HVD230 CRX
- [ ] 3.3V → SN65HVD230 VCC
- [ ] GND → SN65HVD230 GND
```

### STM32 Node Checklist:

```
RJ45 Connection:
- [ ] Pin 1 → MCP2515/TJA1050 CANH
- [ ] Pin 2 → MCP2515/TJA1050 CANL
- [ ] Pin 3 → MCP2515 GND + Pin 6
- [ ] Pin 6 → MCP2515 GND + Pin 3
- [ ] Pin 7 → Power GND (if bus powered)
- [ ] Pin 8 → Voltage regulator (if bus powered)

STM32 Connection:
- [ ] PA4 → MCP2515 CS
- [ ] PA5 → MCP2515 SCK
- [ ] PA6 → MCP2515 MISO
- [ ] PA7 → MCP2515 MOSI
- [ ] 3.3V → MCP2515 VCC
- [ ] GND → MCP2515 GND
```

---

## 🧪 Testing After Correction

### 1. Multimeter Tests (Power OFF):

```
Continuity Check:
Pin 1 to CANH:           Should beep ✓
Pin 2 to CANL:           Should beep ✓
Pin 3 to Pin 6:          Should beep ✓ (CRITICAL!)
Pin 3 to transceiver GND: Should beep ✓
Pin 6 to transceiver GND: Should beep ✓
```

### 2. Voltage Tests (Power ON):

```
With 12V bus power:
Pin 8 to Pin 7:  ~12V ✓
Pin 1 to Pin 3:  ~2.5V (CAN_H idle) ✓
Pin 2 to Pin 3:  ~2.5V (CAN_L idle) ✓
```

### 3. Upload Test Sketch:

- ESP32: `CAN_Test_ESP32.ino`
- STM32: `MCP2515_Test_Arduino.ino`

LED should blink 10× fast = Success! ✓

### 4. Connect to LCC Network:

- Add 120Ω terminator (if end node)
- Upload LCC node sketch
- Test with another LCC node

---

## 📚 Documentation Files

### Complete References:

1. **NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md**
   - Complete official standard
   - All pin definitions
   - Power specifications
   - Cable requirements

2. **OFFICIAL_STANDARD_COMPARISON.md**
   - What was wrong in old docs
   - What's correct now
   - Why it matters

3. **ESP32_WIRING_CORRECTED.md**
   - Step-by-step ESP32 wiring
   - Breadboard layout
   - Testing procedures

4. **STM32_WIRING_CORRECTED.md**
   - Step-by-step STM32 wiring
   - Breadboard layout
   - Testing procedures

---

## 🎯 For GitHub

### Commit Message Template:

```
CRITICAL: Update to NMRA S-9.7.1.1 Official Standard

- Corrected RJ45 pinout to match NMRA S-9.7.1.1
- Added required Pin 3 ↔ Pin 6 connection
- Documented all 8 pins including optional DCC
- Updated all wiring diagrams
- Added cable pairing requirements

Breaking change: Hardware wiring changes required!
Nodes built with old pinout will NOT work with LCC networks.

Based on official NMRA S-9.7.1.1 adopted January 24, 2025.
```

### README Updates:

Add prominent warning at top:

```markdown
## ⚠️ IMPORTANT: NMRA S-9.7.1.1 Compliance

This project now uses the **official NMRA S-9.7.1.1 standard** pinout.

**Critical requirement:** Pins 3 and 6 must be connected together!

See [NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md](docs/NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md)
```

---

## 📦 Project Structure for GitHub

### Recommended Structure:

```
Your-LCC-Project/
├── arduino/
│   ├── LCC_Node_*/
│   └── Test_*/
├── docs/
│   ├── NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md     ← Add this!
│   ├── OFFICIAL_STANDARD_COMPARISON.md        ← Add this!
│   ├── WIRING.md                              ← Update this!
│   └── QUICK_START.md                         ← Update this!
├── hardware/
├── README.md                                   ← Update with warning!
├── LICENSE
└── .gitignore
```

---

## ✅ Final Checklist Before Push

- [ ] All wiring docs updated with NMRA pinout
- [ ] Pin 3 ↔ Pin 6 connection documented
- [ ] README has prominent warning
- [ ] NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md included
- [ ] OFFICIAL_STANDARD_COMPARISON.md included
- [ ] Arduino sketches present (no changes needed)
- [ ] Testing procedures updated
- [ ] License file present (MIT)
- [ ] .gitignore present
- [ ] Commit message prepared

---

## 🎉 You're Ready!

Once you've:
1. ✅ Updated all documentation
2. ✅ Tested the corrected wiring
3. ✅ Added the new reference files
4. ✅ Updated README with warning

**You're ready to push to GitHub!**

```bash
git add .
git commit -m "CRITICAL: Update to NMRA S-9.7.1.1 official standard"
git push origin main
```

---

## 💬 Announcing the Update

### GitHub Release Notes:

```
## v2.0.0 - NMRA S-9.7.1.1 Compliance

### ⚠️ BREAKING CHANGE

Hardware wiring has changed to comply with official NMRA S-9.7.1.1 standard.

**If you built a node with v1.x, you MUST rewire before connecting to LCC networks!**

### What Changed:
- CAN_H now on Pin 1 (was Pin 3)
- CAN_L now on Pin 2 (was Pin 4)
- Added Pin 3 ↔ Pin 6 connection (required!)
- All 8 pins now defined per NMRA standard

### Migration:
See OFFICIAL_STANDARD_COMPARISON.md for complete details.

### Compatibility:
✅ Now compatible with all NMRA-compliant LCC equipment
✅ Works with RR-CirKits, Digitrax, MERG CBUS
✅ Works with JMRI
✅ Standard Ethernet cables (Cat5e/Cat6) work perfectly
```

---

## 🆘 Need Help?

### Resources:

- **NMRA S-9.7.1.1 Standard:** Official document (provided in package)
- **OpenLCB.org:** Additional technical information
- **GitHub Issues:** Report problems or ask questions
- **LCC Forums:** Community support

---

**This correction is CRITICAL for NMRA LCC compatibility!**

Thank you for using NMRA-compliant standards! 🚂✨

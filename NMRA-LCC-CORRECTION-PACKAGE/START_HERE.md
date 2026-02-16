# NMRA S-9.7.1.1 LCC Correction Package

## 🎯 Purpose

This package contains **corrected documentation** for building NMRA-compliant LCC nodes based on the official **NMRA S-9.7.1.1 standard** (adopted January 24, 2025).

---

## ⚠️ CRITICAL UPDATE

**Previous documentation had INCORRECT RJ45 pinout!**

This package provides the **official NMRA standard** pinout and wiring.

---

## 📦 What's Included

### 1. **START_HERE.md** (This File)
   - Overview of corrections
   - Quick reference

### 2. **NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md**
   - Complete official NMRA standard
   - All 8 pin definitions
   - Power specifications
   - Cable requirements
   - **READ THIS FIRST!**

### 3. **OFFICIAL_STANDARD_COMPARISON.md**
   - What was wrong in old documentation
   - What's correct now
   - Why it matters for compatibility

### 4. **MIGRATION_AND_GITHUB_GUIDE.md**
   - How to apply corrections to existing projects
   - GitHub commit templates
   - Testing procedures
   - Release notes templates

### 5. **ESP32_WIRING_CORRECTED.md**
   - Complete ESP32 wiring with NMRA pinout
   - Step-by-step instructions
   - Breadboard layout
   - Testing checklist

### 6. **STM32_WIRING_CORRECTED.md**
   - Complete STM32 wiring with NMRA pinout
   - Step-by-step instructions
   - Breadboard layout
   - Testing checklist

### 7. **PINOUT_CORRECTION_README.md**
   - Detailed explanation of all changes
   - Before/after comparison

---

## 🚀 Quick Start

### If You Haven't Built Anything Yet:

1. Read **NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md**
2. Follow **ESP32_WIRING_CORRECTED.md** or **STM32_WIRING_CORRECTED.md**
3. Build your node!

### If You Already Have a Project:

1. Read **OFFICIAL_STANDARD_COMPARISON.md** to understand what changed
2. Read **MIGRATION_AND_GITHUB_GUIDE.md** for how to update
3. Rewire your hardware if needed
4. Update your documentation
5. Push to GitHub!

---

## 🔴 The Most Critical Change

**Pins 3 and 6 MUST be connected together!**

```
Official NMRA Requirement (S-9.7.1.1 Section 4):

"Nodes shall connect conductors 3 and 6.
This connection shall be rated to carry at least 1A."

Implementation:
RJ45 Pin 3 (CAN_GND) ──┬──→ System GND
RJ45 Pin 6 (CAN_SHIELD)┘
```

**This was NOT in previous documentation!**

---

## 📊 Official NMRA Pinout

```
Pin | Signal      | Function
----|-------------|----------------------------------
1   | CAN_H       | CAN Bus High
2   | CAN_L       | CAN Bus Low  
3   | CAN_GND     | CAN Ground (connect to Pin 6!)
4   | ALT_L       | Alternate (optional DCC)
5   | ALT_H       | Alternate (optional DCC)
6   | CAN_SHIELD  | Shield (connect to Pin 3!)
7   | PWR_NEG     | Power Negative/Ground
8   | PWR_POS     | Power Positive (+9-15VDC)
```

---

## ✅ What This Fixes

### Ensures Compatibility With:

- ✅ All NMRA-compliant LCC equipment
- ✅ RR-CirKits LCC products
- ✅ Digitrax LCC bridges
- ✅ MERG CBUS (compatible)
- ✅ JMRI LCC support
- ✅ All commercial LCC nodes
- ✅ Other DIY LCC nodes using correct pinout

### Prevents:

- ❌ Non-functional nodes on LCC networks
- ❌ Incompatibility with commercial equipment
- ❌ Potential equipment damage
- ❌ Wasted time and money

---

## 🎯 For Your GitHub Project

### Add These Files to Your Project:

```
your-lcc-project/
├── docs/
│   ├── NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md    ← Add this!
│   ├── OFFICIAL_STANDARD_COMPARISON.md       ← Add this!
│   └── (your other docs - update wiring!)
└── README.md                                  ← Update with warning!
```

### Update Your README:

Add prominent warning at top:

```markdown
## ⚠️ IMPORTANT: NMRA S-9.7.1.1 Compliant

This project uses the **official NMRA S-9.7.1.1 standard** pinout.

**Critical:** Pins 3 and 6 must be connected together inside your node!

See [NMRA Standard](docs/NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md) for complete spec.
```

---

## 📝 Recommended Reading Order

1. **This file (START_HERE.md)** ← You are here
2. **NMRA_OFFICIAL_S-9.7.1.1_PINOUT.md** - Complete standard
3. **OFFICIAL_STANDARD_COMPARISON.md** - What changed
4. **Your platform wiring guide** (ESP32 or STM32)
5. **MIGRATION_AND_GITHUB_GUIDE.md** - How to update projects

---

## 🔧 Hardware Changes Required

### If You Built with Old Pinout:

```
Change RJ45 connections:

OLD (Wrong):              NEW (Correct):
Pin 3 → CAN_H            Pin 1 → CAN_H
Pin 4 → CAN_L            Pin 2 → CAN_L
Pin 1-2 → GND            Pin 3 → CAN_GND  ┐
                         Pin 6 → CAN_SHIELD┘ Connect!
                         Pin 7 → PWR_NEG
                         Pin 8 → PWR_POS
```

**Arduino code:** No changes needed!

---

## 💡 Good News: Standard Cables Work!

Standard Cat5e/Cat6 Ethernet cables (T568B) are perfect:

```
Pin 1: White/Orange → CAN_H      ✓
Pin 2: Orange       → CAN_L      ✓
Pin 3: White/Green  → CAN_GND    ✓
Pin 6: Green        → CAN_SHIELD ✓
Pin 7: White/Brown  → PWR_NEG    ✓
Pin 8: Brown        → PWR_POS    ✓

All required pairs are already twisted! ✓
```

---

## 📚 References

- **NMRA S-9.7.1.1** "LCC CAN Physical Layer" (July 22, 2024, Adopted Jan 24, 2025)
- **OpenLCB.org** - Official LCC/OpenLCB website
- **TIA-968-A** - RJ45 connector specification
- **ISO 11898** - CAN bus specification

---

## 🆘 Questions?

1. Read the included documentation
2. Check **MIGRATION_AND_GITHUB_GUIDE.md** for specifics
3. Visit OpenLCB.org for additional information
4. Open GitHub issues on your project

---

## ✨ Summary

**This package provides:**
- ✅ Official NMRA S-9.7.1.1 pinout
- ✅ Corrected wiring guides for ESP32 and STM32
- ✅ Migration instructions
- ✅ GitHub integration guide
- ✅ Complete testing procedures

**Use this to:**
- ✅ Build NMRA-compliant nodes
- ✅ Update existing projects
- ✅ Ensure compatibility with all LCC equipment

---

**Thank you for using the official NMRA standard!** 🚂✨

This ensures your nodes will work with **ALL** LCC equipment and networks!

# COSAR UNIFIED FIRMWARE - Implementation Guide

## Overview

This is a **complete rewrite** of your six separate Arduino sketches into **ONE unified program** with:
- **Multiple Modes** - Switch between Color ID, Navigation, Medicine/Danger
- **Button Control** - No recompiling needed - just press buttons!
- **Auto-Calibration** - One-button calibration
- **Volume Control** - Adjust volume with buttons
- **EEPROM Storage** - Saves your preferences
- **Better Color Detection** - HSV-based algorithm

---

## What You Need

### Hardware Required:
1. **Arduino Uno** or compatible
2. **TCS3200 Color Sensor** (already have)
3. **DFPlayer Mini** module (already have)
4. **4 Push Buttons** (NEW - $1-2 each)
   - Button 1: Mode Switch
   - Button 2: Calibration
   - Button 3: Volume Up
   - Button 4: Volume Down
5. **4 x 10kΩ Resistors** (for button pull-ups)
6. **Speaker/Headphones** (already have)

### Software:
- Arduino IDE (free download)
- DFPlayer Mini library (already using)

---

## Hardware Wiring

### Pin Assignments (Same as Before + 4 New Buttons):

```
TCS3200 Color Sensor:
  S0 → Pin 2
  S1 → Pin 3
  S2 → Pin 4
  S3 → Pin 5
  OUT → Pin 6
  VCC → 5V
  GND → GND

Push Buttons (NEW):
  Button 1 (Mode) → Pin 8 → GND (with pull-up)
  Button 2 (Calibrate) → Pin 9 → GND (with pull-up)
  Button 3 (Vol+) → Pin A0 → GND (with pull-up)
  Button 4 (Vol-) → Pin A1 → GND (with pull-up)

DFPlayer Mini:
  RX → Pin 10
  TX → Pin 11
  Speaker + → Speaker+
  Speaker - → Speaker-
  VCC → 5V
  GND → GND

LED Indicator:
  LED → Pin 7 → GND (through 220Ω resistor)
```

### Button Wiring Detail:

```
         ___
        |   |  ← Button (Momentary Push)
        |___|
         | |
         | └─────────→ GND
         │
         ├─────────→ Pin (8, 9, A0, or A1)
         │
         ├─ 10kΩ Resistor ─→ 5V (Pull-up Resistor)
         │
        GND

OR use INPUT_PULLUP (no external resistor needed)
```

---

## Installation Steps

### Step 1: Backup Your Current Code
```
Save all your current .ino files somewhere safe first!
```

### Step 2: Download the New Firmware
- Get `COSAR_UNIFIED_FIRMWARE.ino` from outputs

### Step 3: Open in Arduino IDE
```
1. Open Arduino IDE
2. Click File → Open
3. Select COSAR_UNIFIED_FIRMWARE.ino
```

### Step 4: Install Required Libraries
```
Sketch → Include Library → Manage Libraries

Search for and install:
- "DFRobotDFPlayerMini" by DFRobot
- (SoftwareSerial is built-in)
- (EEPROM is built-in)
```

### Step 5: Select Board and Port
```
Tools → Board → Arduino Uno
Tools → Port → COM3 (or your port)
```

### Step 6: Upload
```
Click Upload (→ button) or Ctrl+U
Wait for "Upload Complete"
```

### Step 7: Add Buttons to Hardware
```
Solder 4 buttons to pins 8, 9, A0, A1 as shown above
OR use breadboard for testing first
```

### Step 8: Prepare Audio Files
Create these MP3 files and place on microSD card:

**Color Names (MODE 1):**
- 001.mp3 = Black
- 002.mp3 = White/Gray
- 003.mp3 = Red
- 004.mp3 = Orange
- 005.mp3 = Yellow
- 006.mp3 = Green
- 007.mp3 = Cyan
- 008.mp3 = Blue
- 009.mp3 = Purple
- 010.mp3 = Magenta
- 011.mp3 = Pink

**Navigation (MODE 2):**
- 020.mp3 = Obstacle
- 021.mp3 = Clear path
- 022.mp3 = Straight
- 023.mp3 = Right
- 024.mp3 = Left
- 025.mp3 = Destination
- 026.mp3 = Location
- 027.mp3 = Special location

**Medicine/Danger (MODE 3):**
- 030.mp3 = Dark/Blocked
- 031.mp3 = Clear
- 032.mp3 = Danger (Red alert)
- 033.mp3 = Pharmacy (Green)
- 034.mp3 = Emergency (Blue zone)
- 035.mp3 = Clinic (Yellow zone)
- 036.mp3 = Medical center (Purple)

**Mode Announcements:**
- 101.mp3 = "Color Identification Mode"
- 102.mp3 = "Navigation Mode"
- 103.mp3 = "Medicine Detection Mode"
- 104.mp3 = "Starting Calibration"
- 105.mp3 = "Calibration Complete"

---

## 🎮 How to Use

### Button Functions:

| Button | Pin | Function |
|--------|-----|----------|
| **MODE** | 8 | Press to cycle: Color ID → Navigation → Medicine → (back to Color ID) |
| **CALIBRATE** | 9 | Press to start 5-second calibration |
| **VOL+** | A0 | Press to increase volume (0-30) |
| **VOL-** | A1 | Press to decrease volume (0-30) |

### Quick Start:

**1. Power On**
- LED blinks once
- Serial prints startup info
- Current mode is announced

**2. Calibrate (Optional but Recommended)**
- Press CALIBRATE button
- LED blinks rapidly
- Move colorful objects over sensor for 5 seconds
- Wait for LED to flash 3 times = done!

**3. Start Using**
- Object detects automatically
- Color is identified and announced
- No waiting, no recompiling!

**4. Switch Modes**
- Press MODE button
- LED flashes (number = mode)
- New mode is announced
- Start detecting in new mode

**5. Adjust Volume**
- Press VOL+ or VOL-
- LED flashes briefly
- Serial shows new volume

---

## Serial Monitor Output

Open Serial Monitor (Ctrl+Shift+M) at 9600 baud to see:

```
=== COSAR UNIFIED FIRMWARE ===
DFPlayer initialized successfully
========================================
Current Mode: COLOR IDENTIFICATION
Volume: 20
========================================
Raw Freq - R: 245 G: 189 B: 156 | HSV: 25.5° 36.7% 96.1%
Detected: ORANGE
Raw Freq - R: 89 G: 234 B: 95 | HSV: 122.3° 61.8% 91.8%
Detected: GREEN
```

---

## Customization

### Change Color Thresholds:
Edit the `detectColorIdentification()` function:
```cpp
} else if (hue >= 0 && hue < 15) {  // ← Adjust these numbers
    Serial.println("Detected: RED");
    dfPlayer.play(3);
```

### Change Audio File Numbers:
If your MP3 files have different numbers:
```cpp
dfPlayer.play(10); // ← Change the number
```

### Adjust Calibration Duration:
```cpp
const unsigned long CALIBRATION_DURATION = 5000; // ← milliseconds
```

### Change Debounce Delay:
```cpp
const unsigned long DEBOUNCE_DELAY = 300; // ← milliseconds
```

---

## 🐛 Troubleshooting

### Problem: Buttons don't work
**Solution:**
- Check button wiring (should be Pin → GND)
- Verify pins in code match your wiring
- Test with Serial.println() statements

### Problem: Color detection is wrong
**Solution:**
- Run calibration by pressing BUTTON_CALIBRATE
- Move different colored objects over sensor
- Let it calibrate for full 5 seconds

### Problem: No audio output
**Solution:**
- Check DFPlayer is powered
- Verify microSD card is inserted
- Check MP3 files are named correctly (001.mp3, not 1.mp3)
- Test with dfPlayer.play(1) in Serial Monitor

### Problem: Mode doesn't change
**Solution:**
- Press MODE button firmly
- Wait 300ms between presses (debounce)
- Check Button 8 is properly connected

### Problem: Volume buttons don't work
**Solution:**
- Verify A0 and A1 pins are connected
- Check resistors if not using INPUT_PULLUP
- Try increasing DEBOUNCE_DELAY

---

## Saving Your Settings

The system automatically saves:
- Current mode
- Volume setting
- Calibration values

Stored in EEPROM, so they persist after power off!

---

## Understanding the Code

### Main Sections:

1. **PIN DEFINITIONS** - Where everything connects
2. **CONSTANTS** - Mode enum, EEPROM addresses
3. **GLOBAL VARIABLES** - Data storage
4. **SETUP** - Initialize everything
5. **LOOP** - Main program loop
6. **BUTTON HANDLING** - Debounce and detect presses
7. **MODE SWITCHING** - Change modes with feedback
8. **COLOR SENSOR READING** - Get RGB frequencies
9. **CALIBRATION** - Auto-calibration routine
10. **COLOR PROCESSING** - HSV conversion
11. **MODE-SPECIFIC DETECTION** - 3 different detection modes
12. **EEPROM STORAGE** - Save/load settings

### Key Improvement: HSV

Old code used simple RGB thresholds:
```cpp
if (red < 15 && green > 14 && blue > 11) { // ← Hard to fine-tune
```

New code uses **HSV (Hue, Saturation, Value)**:
```cpp
if (hue >= 0 && hue < 30) { // ← Much more reliable
```

**Why HSV is better:**
- **Hue** (0-360°) = Color (independent of lighting)
- **Saturation** (0-100%) = Color intensity
- **Value** (0-100%) = Brightness

---

## Comparison: Old vs New

| Feature | Old Code | New Code |
|---------|----------|----------|
| Number of sketches | 6 | 1 |
| Modes | Hard to switch | Easy button switching |
| Recompile needed | YES | NO |
| Volume control | No | YES (buttons) |
| Calibration | Manual | Auto 1-button |
| Color detection | RGB threshold | HSV-based |
| Settings saved | No | YES (EEPROM) |
| Code size | 372 lines | 450 lines (better) |

---

## Advanced Features

### Adding More Modes:
```cpp
// In enum Mode section:
enum Mode {
  MODE_COLOR_ID = 0,
  MODE_NAVIGATION = 1,
  MODE_MEDICINE = 2,
  MODE_CALIBRATION = 3,
  MODE_YOUR_NEW_MODE = 4  // ← Add here
};

// In processColor() switch:
case MODE_YOUR_NEW_MODE:
  detectYourNewMode(hue, saturation, value);
  break;

// Create new detection function:
void detectYourNewMode(float hue, float saturation, float value) {
  if (hue >= 0 && hue < 30) {
    Serial.println("Your detection here");
    dfPlayer.play(40); // ← Your audio file
  }
}
```

### Adding More Buttons:
```cpp
#define BUTTON_NEW = A2;  // ← Add pin

// In handleButtonPresses():
if (digitalRead(BUTTON_NEW) == LOW) {
  lastButtonPress = millis();
  // Your action here
}
```

---

## Resources

- **Arduino Reference:** https://www.arduino.cc/reference/en/
- **DFPlayer Mini Guide:** https://www.dfrobot.com/product-1121.html
- **TCS3200 Datasheet:** Search "TCS3200 color sensor datasheet"
- **HSV Color Space:** https://en.wikipedia.org/wiki/HSL_and_HSV

---

## Final Checklist

- ☐ Downloaded COSAR_UNIFIED_FIRMWARE.ino
- ☐ Installed DFRobotDFPlayerMini library
- ☐ Selected correct board (Arduino Uno)
- ☐ Selected correct COM port
- ☐ Uploaded code (no errors)
- ☐ Wired 4 push buttons
- ☐ Tested MODE button (LED flashes)
- ☐ Tested CALIBRATE button (LED blinks rapidly)
- ☐ Tested VOL+/VOL- buttons (LED flashes)
- ☐ Created MP3 files for audio
- ☐ Inserted microSD card in DFPlayer
- ☐ Opened Serial Monitor to verify output
- ☐ Tested color detection
- ☐ Tested mode switching


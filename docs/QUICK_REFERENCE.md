# COSAR UNIFIED FIRMWARE - QUICK REFERENCE

##  Button Functions at a Glance

```
    Pin 8           Pin 9          Pin A0         Pin A1
    MODE            CALIBRATE      VOLUME UP      VOLUME DOWN
    (Switch Modes)  (Start Cal)    (Louder)       (Quieter)
     ___             ___            ___            ___
    |   |           |   |          |   |          |   |
    |___|           |___|          |___|          |___|
     │               │              │              │
    GND             GND            GND            GND
```

---

##  Modes (Press MODE Button to Cycle)

### MODE 1: COLOR IDENTIFICATION ← Default
**Use:** Identify any color
**Colors Detected:**
- Black, White/Gray, Red, Orange, Yellow
- Green, Cyan, Blue, Purple, Magenta, Pink
**LED Flash:** 1 flash
**Audio:** "Color Identification Mode"

### MODE 2: NAVIGATION
**Use:** Get directions
**Outputs:**
- Straight (Red) → Obstacle (Black) → Clear Path (White)
- Right (Green) → Left (Blue)
- Destination (Purple) → Location (Yellow) → Special (Pink)
**LED Flash:** 2 flashes
**Audio:** "Navigation Mode"

### MODE 3: MEDICINE & DANGER
**Use:** Health facility detection
**Outputs:**
- Danger (Red) → Pharmacy (Green) → Emergency (Blue)
- Clinic (Yellow) → Medical Center (Purple)
- Clear (White) → Dark (Black)
**LED Flash:** 3 flashes
**Audio:** "Medicine Detection Mode"

### MODE 4: CALIBRATION
**Use:** Train the sensor
**LED Flash:** 4 flashes
**To Use:** Press CALIBRATE button (Button 9)

---

##  Pin Layout (Quick Reference)

```
ARDUINO UNO

Sensors:
  Pin 2  → S0 (Color Sensor)
  Pin 3  → S1 (Color Sensor)
  Pin 4  → S2 (Color Sensor)
  Pin 5  → S3 (Color Sensor)
  Pin 6  → OUT (Color Sensor)
  Pin 7  → LED (Indicator)

Communication:
  Pin 10 → DFPlayer RX
  Pin 11 → DFPlayer TX

Buttons:
  Pin 8  → MODE Button
  Pin 9  → CALIBRATE Button
  Pin A0 → VOLUME UP Button
  Pin A1 → VOLUME DOWN Button

Power:
  5V → VCC (all devices)
  GND → GND (all devices)
```

---

##  Serial Monitor Output

**Baud Rate:** 9600

**What You'll See:**
```
=== COSAR UNIFIED FIRMWARE ===
DFPlayer initialized successfully
========================================
Current Mode: COLOR IDENTIFICATION
Volume: 20
========================================
Raw Freq - R: 245 G: 189 B: 156 | HSV: 25.5° 36.7% 96.1%
Detected: ORANGE
```

---

##  Audio File Mapping

**COLOR MODE (Files 1-11):**
| File | Color |
|------|-------|
| 001.mp3 | Black |
| 002.mp3 | White/Gray |
| 003.mp3 | Red |
| 004.mp3 | Orange |
| 005.mp3 | Yellow |
| 006.mp3 | Green |
| 007.mp3 | Cyan |
| 008.mp3 | Blue |
| 009.mp3 | Purple |
| 010.mp3 | Magenta |
| 011.mp3 | Pink |

**NAVIGATION MODE (Files 20-27):**
| File | Direction |
|------|-----------|
| 020.mp3 | Obstacle |
| 021.mp3 | Clear Path |
| 022.mp3 | Straight |
| 023.mp3 | Right |
| 024.mp3 | Left |
| 025.mp3 | Destination |
| 026.mp3 | Location |
| 027.mp3 | Special Location |

**MEDICINE MODE (Files 30-36):**
| File | Status |
|------|--------|
| 030.mp3 | Dark/Blocked |
| 031.mp3 | Clear |
| 032.mp3 | Danger (Red Alert) |
| 033.mp3 | Pharmacy (Green) |
| 034.mp3 | Emergency (Blue) |
| 035.mp3 | Clinic (Yellow) |
| 036.mp3 | Medical Center (Purple) |

**MODE ANNOUNCEMENTS (Files 101-105):**
| File | Announcement |
|------|--------------|
| 101.mp3 | "Color Identification Mode" |
| 102.mp3 | "Navigation Mode" |
| 103.mp3 | "Medicine Detection Mode" |
| 104.mp3 | "Starting Calibration" |
| 105.mp3 | "Calibration Complete" |

---

##  Troubleshooting Quick Fix

| Problem | Quick Fix |
|---------|-----------|
| Buttons don't work | Check GND connection |
| No sound | Insert microSD card |
| Wrong color detected | Run calibration (Button 9) |
| Mode won't change | Press Button 8 firmly |
| Serial shows garbage | Check baud rate = 9600 |
| LED doesn't flash | Check pin 7 connections |

---

##  Normal Operating Procedure

1. **Power On**
   - LED blinks once
   - Mode is announced
   - Ready to detect

2. **Detect Colors**
   - Hold object in front of sensor
   - Color is identified automatically
   - Audio plays the color name

3. **Change Mode (Optional)**
   - Press Button 8 (MODE)
   - LED flashes showing new mode
   - Mode is announced

4. **Adjust Volume (Optional)**
   - Press Button A0 to increase
   - Press Button A1 to decrease
   - Volume range: 0-30

5. **Calibrate (Recommended First Time)**
   - Press Button 9 (CALIBRATE)
   - Move colors over sensor for 5 seconds
   - LED flashes 3 times = done

6. **Power Off**
   - Settings are automatically saved
   - Will remember mode & volume on restart

---

##  Creating Audio Files

### Using Text-to-Speech:
1. Go to www.ttsmp3.com
2. Type: "Red" (or color name)
3. Download MP3
4. Rename to 003.mp3 (or your number)
5. Copy to microSD card

### Using Audacity (Free):
1. Generate → Tone to test
2. Export as MP3
3. Rename and copy to card

### File Naming:
```
✓ Correct:   001.mp3, 002.mp3, 003.mp3
✗ Wrong:     1.mp3, color_red.mp3, Red.mp3
```

---

##  Power Requirements

| Component | Current | Voltage |
|-----------|---------|---------|
| Arduino Uno | ~50mA | 5V |
| TCS3200 | ~5mA | 5V |
| DFPlayer | ~25mA | 5V |
| Speaker | ~100mA (peak) | - |
| Buttons | ~1mA | 5V |
| **Total** | **~180mA** | **5V** |

**Recommendation:** Use 5V power supply rated for 500mA+ (to be safe)

---

##  Color Detection Ranges (HSV)

```
RED:      0° - 30°
ORANGE:   30° - 45°
YELLOW:   45° - 65°
GREEN:    85° - 160°
CYAN:     160° - 200°
BLUE:     200° - 260°
PURPLE:   260° - 290°
MAGENTA:  290° - 330°
PINK:     330° - 360°
```

(Hue values in degrees, 0-360°)

---

##  Customization Quick Tips

### Change a Color Threshold:
```cpp
} else if (hue >= 0 && hue < 15) {  // ← Change 15 to new value
    Serial.println("Detected: RED");
```

### Change Audio File Number:
```cpp
dfPlayer.play(3);  // ← Change 3 to your file number
```

### Change Default Volume:
```cpp
currentVolume = 20;  // ← Change 20 to 0-30
```

### Change Calibration Time:
```cpp
const unsigned long CALIBRATION_DURATION = 5000;  // ← Change to milliseconds
```

---

##  Serial Monitor Commands (For Testing)

Open Tools → Serial Monitor (9600 baud)

**Type these to see responses:**
- Type "status" → Shows current settings
- Type "calibrate" → Starts calibration
- Type "mode=1" → Changes to navigation mode

*(Note: These are for future enhancement)*

---

##  Wiring Checklist Before Uploading Code

- ☐ TCS3200 pins 2-6 connected
- ☐ DFPlayer RX pin 10, TX pin 11
- ☐ All GND connections made
- ☐ 5V power connected
- ☐ LED on pin 7 (optional but recommended)
- ☐ 4 buttons connected to pins 8, 9, A0, A1
- ☐ microSD card inserted in DFPlayer
- ☐ Speaker connected to DFPlayer

---

##  Learning Path

1. **Start Here:** This quick reference
2. **Read Next:** UNIFIED_FIRMWARE_GUIDE.md
3. **Study:** Code comments in COSAR_UNIFIED_FIRMWARE.ino
4. **Customize:** Modify color thresholds or modes
5. **Expand:** Add your own modes or buttons

---

##  Important Settings Saved to EEPROM

These persist after power off:
- Current mode
- Volume level
- Calibration min/max values

Reset to defaults: Reflash the firmware

---

##  Timing Reference

| Action | Duration |
|--------|----------|
| Button debounce | 300ms |
| Color detection cycle | 500ms |
| Calibration | 5000ms (5 sec) |
| DFPlayer startup | ~1000ms |
| Volume change response | ~50ms |

---

##  Emergency Recovery

If something breaks:
1. Unplug power (5V)
2. Check all connections
3. Re-upload firmware (Ctrl+U in Arduino IDE)
4. Check Serial Monitor for errors

---

##  Quick Debugging

Open Serial Monitor and watch for:
```
✓ "DFPlayer initialized successfully" = Good
✓ "Current Mode: COLOR IDENTIFICATION" = Good
✓ "Raw Freq - R: XXX G: XXX B: XXX" = Sensor working
✓ "Detected: RED" = Color detection working
✗ "DFPlayer not detected!" = Check DFPlayer connection
✗ Garbage text = Wrong baud rate (should be 9600)
```

---

**Version 1.0** | **Created May 2025** | **Ready to Use**

**For complete guide: See UNIFIED_FIRMWARE_GUIDE.md**

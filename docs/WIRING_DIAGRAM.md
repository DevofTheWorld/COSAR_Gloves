# COSAR Unified Firmware - Wiring & Circuit Diagram

## Complete System Diagram

```
┌──────────────────────────────────────────────────────────────────────┐
│                         COSAR System Overview                         │
└──────────────────────────────────────────────────────────────────────┘

                            ┌─────────────┐
                            │ Arduino Uno │
                            └──────┬──────┘
                                   │
        ┌──────────────┬───────────┼───────────┬──────────────┐
        │              │           │           │              │
        ▼              ▼           ▼           ▼              ▼
    ┌────────┐    ┌────────┐  ┌────────┐  ┌────────┐   ┌──────────┐
    │TCS3200 │    │DFPlayer│  │  LED   │  │Buttons │   │ Calibrat.│
    │ Sensor │    │ Module │  │(Pin 7) │  │(Pins)  │   │ Cap.     │
    └────────┘    └────────┘  └────────┘  └────────┘   └──────────┘
```

---

## TCS3200 Color Sensor Connections

### Wiring Table:
```
TCS3200 Pin    →    Arduino Pin    Function
─────────────────────────────────────────────
VCC            →    5V             Power
GND            →    GND            Ground
S0             →    Pin 2          Scaling (Frequency scaling)
S1             →    Pin 3          Scaling (Frequency scaling)
S2             →    Pin 4          Color Select (Red)
S3             →    Pin 5          Color Select (Green)
OUT            →    Pin 6          Output Frequency
LED/ANODE      →    5V (Optional)  Illumination LED
```

### Pinout Diagram:
```
TCS3200 Module (Top View):

        ┌─────────────────┐
        │   TCS3200       │
        │   Color Sensor  │
        │                 │
┌───────┴─────────────────┴───────┐
│ 1(S2) 2(S3) 3(OUT) 4(GND) 5(VCC)│
│ 8(S0) 7(S1) 6(LED) Sensor Pin   │
└──────────────────────────────────┘
```

### Breadboard Layout:
```
     GND    5V    Pin2   Pin3   Pin4   Pin5   Pin6   GND   5V
      │      │      │      │      │      │      │      │      │
    ──┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──
      │                                                          │
     [5V Bus]                                              [GND Bus]
      │                                                          │
      ├─ TCS3200 VCC                                             │
      │                                                          │
      │ TCS3200 S0 ─→ Pin 2                                     │
      │ TCS3200 S1 ─→ Pin 3                                     │
      │ TCS3200 S2 ─→ Pin 4                                     │
      │ TCS3200 S3 ─→ Pin 5                                     │
      │ TCS3200 OUT ─→ Pin 6                                    │
      │ TCS3200 GND ─────────────────────────────────────────────┤
      │
     [All power connections should be thick red wire]
```

---

## 2DFPlayer Mini Connections

### Wiring Table:
```
DFPlayer Pin    →    Arduino Pin    Function
──────────────────────────────────────────────
VCC             →    5V             Power
GND             →    GND            Ground
RX              →    Pin 10         Receive Data
TX              →    Pin 11         Transmit Data
SPK1 (Speaker+) →    Speaker+       Speaker Output
SPK2 (Speaker-) →    Speaker-       Speaker Output
IO1             →    Not used       Optional
AD               →    Not used       Aux in
```

### Module Layout:
```
DFPlayer Mini (Front View):

    ┌──────────────────────┐
    │   DFPlayer Mini      │
    │                      │
    │  microSD Slot        │
    │  [═══════]           │
    │                      │
┌───┴──────────────────────┴───┐
│Pin1(RX) Pin2(TX) ...pins... │ (Bottom)
│GND      VCC     SPK1 SPK2    │
└────────────────────────────────┘
```

### Pin Assignment (DFPlayer):
```
Pin 1: RX (Receive) ──→ Arduino Pin 10
Pin 2: TX (Transmit) ──→ Arduino Pin 11
Pin 3: BUSY (Optional feedback)
Pin 4: GND ──→ GND
Pin 5: RX Capacitor (-) 
Pin 6: RX Capacitor (+) to 5V through 10Ω
Pin 7: SPK2 (Speaker-) ──→ Speaker-
Pin 8: SPK1 (Speaker+) ──→ Speaker+
Pin 9: VCC ──→ 5V with 100μF capacitor to GND
Pin 10: AD (Aux in - optional)
Pin 11: IO1 (Digital out - optional)
Pin 12: Ground (back pin)
```

---

## Push Button Connections

### Button Wiring Diagram:

```
METHOD 1: With External Pull-up Resistor
────────────────────────────────────────

     5V
      │
      ├─ 10kΩ Resistor ─┐
                        │
                    ┌───┴───┐       ┌─────────┐
                    │       ├───────┤ Arduino │
                  ┌─┴─┐     │       │  Pin    │
                  │ O │     │       └─────────┘
    Button (Push) │   │     │
                  └─┬─┘     │
                    │       │
                   GND ─────┴─── GND


METHOD 2: Using INPUT_PULLUP (Recommended - No Resistor Needed)
───────────────────────────────────────────────────────────────

        ┌─────────┐
        │ Arduino │
        │   Pin   │
        │(w/built-│
        │in 20k-  │ ← INPUT_PULLUP enabled
        │upR)     │
        └────┬────┘
             │
          ┌──┴──┐
          │     │ ← Push Button (Momentary)
          └──┬──┘
             │
            GND
```

### Button Pin Assignment:

```
Function            Pin     WireColor   Function in Code
─────────────────────────────────────────────────────────
MODE Switch         8       Blue        BUTTON_MODE
CALIBRATE           9       Green       BUTTON_CALIBRATE
VOLUME UP          A0       Yellow      BUTTON_VOLUME_UP
VOLUME DOWN        A1       Orange      BUTTON_VOLUME_DOWN
```

### Recommended Breadboard Layout (4 Buttons):

```
                    5V (Red Bus)
                    │    │    │    │
                    ├────┴────┼────┤
                    │    │    │    │
              ┌─────┘    │    │    │
              │     ┌────┘    │    │
              │     │     ┌───┘    │
              │     │     │    ┌───┘
          ┌───┴──┐ ┌┴───┐ ┌──┴─┐ ┌──┴─┐
    Blue  │      │ │ Gre│ │ Yel│ │ Ora│ Buttons
    (Mode)│      │ │ (Cal
          └───┬──┘ └─┬──┘ └──┬─┘ └──┬─┘
             GND    GND     GND     GND
              │      │       │       │
              └──────┴───────┴───────┴─ GND (Black Bus)
```

### Full Button Schematic:

```
Pin 8 (MODE)       Pin 9 (CAL)        Pin A0 (VOL+)      Pin A1 (VOL-)
│                  │                  │                  │
├─────────────────┐├─────────────────┐├─────────────────┐├─────────────────┐
│                 ││                 ││                 ││                 │
│ 10kΩ (optional) │ 10kΩ (optional) │ 10kΩ (optional) │ 10kΩ (optional) │
│                 ││                 ││                 ││                 │
└────┬────────────┘└────┬────────────┘└────┬────────────┘└────┬────────────┘
     │                  │                  │                  │
     │ ┌──────────────┐ │ ┌──────────────┐ │ ┌──────────────┐ │
     │ │ Button (Push)│ │ │ Button (Push)│ │ │ Button (Push)│ │
     │ └──────┬───────┘ │ └──────┬───────┘ │ └──────┬───────┘ │
     │        │         │        │         │        │         │
     └────┬───┘         └────┬───┘         └────┬───┘         │
          │                  │                  │              │
         GND                GND                GND            GND
          │                  │                  │              │
          └──────────────────┴──────────────────┴──────────────┘
                             │
                          GND Bus
```

---

##  LED Indicator

### Wiring:
```
5V
│
├─ 220Ω Resistor ─┐
                  │
                  ├─→ LED (+) Long Leg
                  │
                  ├─→ LED (-) Short Leg
                  │
                  │
                 GND

Arduino Connection:
Pin 7 ─→ 220Ω Resistor ─→ LED (+)
GND ─→ LED (-)
```

### LED States:
- **Off** = Idle
- **Single Blink** = Power on
- **Single Flash** = Button pressed
- **Rapid Blinks** = Calibrating
- **3 Flashes** = Calibration complete
- **N Flashes** = Mode switched (N = mode number)

---

## Complete System Wiring (All Together)

### Top-Level Block Diagram:

```
                      ┌──────────────┐
                      │  Power Supply│
                      │   (5V, 500mA)│
                      └───┬──────┬───┘
                          │      │
                          5V    GND
                          │      │
           ┌──────────────┼──────┼──────────────┐
           │              │      │              │
           ▼              ▼      ▼              ▼
      ┌────────────┐  ┌────────────┐  ┌─────────────┐
      │ Arduino    │  │ TCS3200    │  │ DFPlayer    │
      │ Uno        │  │ Sensor     │  │ Module      │
      └─┬──────┬──┘  └────────────┘  └─────────────┘
        │      │           │               │
    Pins│      │      Pins 2-6        Pins 10-11
        │      │           │               │
        │      └───────────┴───────────────┘
        │
        ├─ Pin 7 ──→ LED + 220Ω
        ├─ Pin 8 ──→ BUTTON (MODE)
        ├─ Pin 9 ──→ BUTTON (CALIBRATE)
        ├─ Pin A0 ──→ BUTTON (VOL+)
        └─ Pin A1 ──→ BUTTON (VOL-)

        All → GND
```

---

##  Breadboard Wiring Example

### Layout (Arduino in center):

```
                        ┌─ 5V Bus ─┐
                        │          │
┌──────────────────────┬┴──────────┴┬──────────────────────┐
│                      │ Arduino UNO│                      │
│    ┌─────────────────┤            ├─────────────────────┐│
│    │                 │            │                     ││
│    │                 │  • • •     │                     ││
│    │                 │  • • •     │                     ││
│    │                 └────┬───────┘                     ││
│    │                      │                             ││
│    │              GND Bus (Black)                       ││
│    │                      │                             ││
│    │                     5V (Red)                       ││
│    │                      │                             ││
│    ▼                      │                             ▼
┌─────────────┐             │                    ┌──────────────┐
│  TCS3200    │             │                    │  DFPlayer    │
│             │             │                    │              │
│ VCC ────────┼────────────►5V                   │ VCC ─────────┼──►5V
│ GND ────────┼────────────►GND                  │ GND ─────────┼──►GND
│ S0(P2) ─────┼────────►Pin 2                    │ RX(P10) ─────┼──►Pin 10
│ S1(P3) ─────┼────────►Pin 3                    │ TX(P11) ─────┼──►Pin 11
│ S2(P4) ─────┼────────►Pin 4                    │ SPK1 ────────┼──►Speaker+
│ S3(P5) ─────┼────────►Pin 5                    │ SPK2 ────────┼──►Speaker-
│ OUT(P6) ────┼────────►Pin 6                    │              │
└─────────────┘         │                        └──────────────┘
                        │
                   ┌────┴────┐
                   │  Buttons │
                   │          │
                   │ P8 ──────┼──►Mode
                   │ P9 ──────┼──►Calibrate
                   │ PA0 ─────┼──►Vol+
                   │ PA1 ─────┼──►Vol-
                   │ All GND ─┼──►GND
                   └──────────┘
```

---

##  Soldering Guide (For Permanent Setup)

### Soldering Order:
1. **Power connections first** (5V and GND)
2. **Sensor connections** (TCS3200 pins)
3. **DFPlayer connections** (RX/TX)
4. **Button connections** (with resistors)
5. **LED indicator** (with resistor)
6. **Test before sealing**

### Soldering Tips:
```
✓ Use 30W soldering iron
✓ Use lead-free solder
✓ Heat both pad and wire for 3 seconds
✓ Use just enough solder to coat
✓ Let cool naturally - don't blow on it
✓ Trim excess wire with flush cutter
✓ Use heat shrink tubing for insulation
```

### Heat Shrink Cable Organization:
```
Red   = 5V Power
Black = GND
Blue  = Data/Signal
Yellow= Optional

Use labels:
  [5V]
  [GND]
  [Pin 2] [S0]
  [Pin 3] [S1]
  [Pin 4] [S2]
  etc.
```

---

##  Cable Color Convention

```
Function          Cable Color    Standard
─────────────────────────────────────────
5V Power          Red            Common
Ground            Black          Common
Signal/Data       Blue/White     Common
Sensor Signals    Green/Yellow   Custom
Button Input      Orange         Custom
```

---

##  Troubleshooting Wiring

### Symptom: Nothing works
**Check:** 5V and GND connections first!

### Symptom: Sensor not detected
**Check:** Pins 2-6 connections to Arduino

### Symptom: No sound
**Check:** DFPlayer pins 10-11 and speaker connection

### Symptom: Buttons unresponsive
**Check:** Pins 8, 9, A0, A1 and GND connections

### Symptom: LED doesn't blink
**Check:** Pin 7 and 220Ω resistor

### Quick Test with Multimeter:
```
1. Measure voltage: Should be 5V between VCC and GND
2. Test continuity: Each wire should have no breaks
3. Check shorts: No conductivity between 5V and GND (except through resistor)
4. Verify pins: Use multimeter to confirm pin numbers
```

---

## Final Wiring Checklist

POWER:
- ☐ 5V connected to Arduino, TCS3200, DFPlayer
- ☐ GND connected everywhere
- ☐ No shorts between 5V and GND

SENSORS:
- ☐ TCS3200 pins 2-6 connected
- ☐ All sensor GNDs connected

COMMUNICATION:
- ☐ DFPlayer RX to Pin 10
- ☐ DFPlayer TX to Pin 11
- ☐ TxRx rates match (9600)

BUTTONS:
- ☐ Pin 8 (Mode) wired
- ☐ Pin 9 (Calibrate) wired
- ☐ Pin A0 (Vol+) wired
- ☐ Pin A1 (Vol-) wired
- ☐ All buttons to GND

FEEDBACK:
- ☐ LED on pin 7
- ☐ 220Ω resistor in series
- ☐ Speaker connected

TESTING:
- ☐ No visible damage
- ☐ All solder joints shiny
- ☐ No loose wires
- ☐ Multimeter checks pass





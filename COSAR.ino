#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <EEPROM.h>


// COSAR UNIFIED FIRMWARE - Multi-Mode Color Detection System
// Version: 1.0
// Features: Color Identification, Navigation, Medicine/Danger Detection
// Mode Switching: Via Push Buttons (No Recompiling Required)


// ============== PIN DEFINITIONS ==============
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define SENSOR_OUT 6
#define LED_PIN 7

// Button pins for mode switching
#define BUTTON_MODE 8      // Switch between modes
#define BUTTON_CALIBRATE 9 // Trigger calibration
#define BUTTON_VOLUME_UP A0   // Increase volume
#define BUTTON_VOLUME_DOWN A1 // Decrease volume

// ============== CONSTANTS ==============
// Operating Modes
enum Mode {
  MODE_COLOR_ID = 0,      // Identify general colors
  MODE_NAVIGATION = 1,    // Navigation directions
  MODE_MEDICINE = 2,      // Medicine/Danger detection
  MODE_CALIBRATION = 3    // Calibration mode
};

// EEPROM addresses for storing settings
#define EEPROM_MODE_ADDR 0
#define EEPROM_VOLUME_ADDR 1
#define EEPROM_MIN_RED_ADDR 2
#define EEPROM_MAX_RED_ADDR 6
#define EEPROM_MIN_GREEN_ADDR 10
#define EEPROM_MAX_GREEN_ADDR 14
#define EEPROM_MIN_BLUE_ADDR 18
#define EEPROM_MAX_BLUE_ADDR 22

// ============== GLOBAL VARIABLES ==============
SoftwareSerial dfSerial(10, 11); // RX, TX for DFPlayer
DFRobotDFPlayerMini dfPlayer;

// Mode variables
Mode currentMode = MODE_COLOR_ID;
int currentVolume = 20;

// Calibration variables
int minRed = 1000, minGreen = 1000, minBlue = 1000;
int maxRed = 0, maxGreen = 0, maxBlue = 0;
bool isCalibrating = false;
unsigned long calibrationStart = 0;
const unsigned long CALIBRATION_DURATION = 5000; // 5 seconds

// Color frequency readings
int redFrequency = 0, greenFrequency = 0, blueFrequency = 0;

// Button debouncing
unsigned long lastButtonPress = 0;
const unsigned long DEBOUNCE_DELAY = 300;

// SETUP FUNCTION
void setup() {
  // Initialize pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SENSOR_OUT, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Button pins
  pinMode(BUTTON_MODE, INPUT_PULLUP);
  pinMode(BUTTON_CALIBRATE, INPUT_PULLUP);
  pinMode(BUTTON_VOLUME_UP, INPUT_PULLUP);
  pinMode(BUTTON_VOLUME_DOWN, INPUT_PULLUP);

  // Initialize serial communication
  Serial.begin(9600);
  dfSerial.begin(9600);
  delay(1000);

  // Initialize DFPlayer
  if (!dfPlayer.begin(dfSerial)) {
    Serial.println("DFPlayer not detected!");
    blinkError();
    while (1);
  }

  Serial.println("=== COSAR UNIFIED FIRMWARE ===");
  Serial.println("DFPlayer initialized successfully");

  // Set sensor scaling (20%)
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Load settings from EEPROM
  loadSettings();

  // Set initial volume
  dfPlayer.volume(currentVolume);

  // Print startup info
  printStartupInfo();
  
  // Quick test
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
}


// MAIN LOOP

void loop() {
  // Check for button presses
  handleButtonPresses();

  // Read color from sensor
  readColorSensor();

  // Process based on current mode
  if (isCalibrating) {
    handleCalibration();
  } else {
    processColor();
  }

  delay(500); // Adjustment delay
}


// BUTTON HANDLING
void handleButtonPresses() {
  if (millis() - lastButtonPress < DEBOUNCE_DELAY) {
    return; // Debounce
  }

  // Mode button (switch between modes)
  if (digitalRead(BUTTON_MODE) == LOW) {
    lastButtonPress = millis();
    switchMode();
    delay(50);
  }

  // Calibration button
  if (digitalRead(BUTTON_CALIBRATE) == LOW) {
    lastButtonPress = millis();
    startCalibration();
    delay(50);
  }

  // Volume up button
  if (digitalRead(BUTTON_VOLUME_UP) == LOW) {
    lastButtonPress = millis();
    if (currentVolume < 30) {
      currentVolume++;
      dfPlayer.volume(currentVolume);
      Serial.print("Volume: ");
      Serial.println(currentVolume);
      digitalWrite(LED_PIN, HIGH);
      delay(50);
      digitalWrite(LED_PIN, LOW);
    }
  }

  // Volume down button
  if (digitalRead(BUTTON_VOLUME_DOWN) == LOW) {
    lastButtonPress = millis();
    if (currentVolume > 0) {
      currentVolume--;
      dfPlayer.volume(currentVolume);
      Serial.print("Volume: ");
      Serial.println(currentVolume);
      digitalWrite(LED_PIN, HIGH);
      delay(50);
      digitalWrite(LED_PIN, LOW);
    }
  }
}


// MODE SWITCHING
void switchMode() {
  currentMode = (Mode)((currentMode + 1) % 4);
  saveSettings();
  
  // Flash LED to indicate mode change
  for (int i = 0; i < currentMode + 1; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }

  printStartupInfo();
}

void printStartupInfo() {
  Serial.print("Current Mode: ");
  
  switch (currentMode) {
    case MODE_COLOR_ID:
      Serial.println("COLOR IDENTIFICATION");
      dfPlayer.play(101); // Play mode announcement
      break;
    case MODE_NAVIGATION:
      Serial.println("NAVIGATION");
      dfPlayer.play(102);
      break;
    case MODE_MEDICINE:
      Serial.println("MEDICINE/DANGER DETECTION");
      dfPlayer.play(103);
      break;
    case MODE_CALIBRATION:
      Serial.println("CALIBRATION");
      break;
  }
  
  Serial.print("Volume: ");
  Serial.println(currentVolume);
}


// COLOR SENSOR READING
void readColorSensor() {
  redFrequency = getFrequency(LOW, LOW);      // Red
  greenFrequency = getFrequency(HIGH, HIGH);  // Green
  blueFrequency = getFrequency(LOW, HIGH);    // Blue
}

int getFrequency(bool s2State, bool s3State) {
  digitalWrite(S2, s2State);
  digitalWrite(S3, s3State);
  delay(10);
  return pulseIn(SENSOR_OUT, LOW, 100000); // 100ms timeout
}

// CALIBRATION
void startCalibration() {
  isCalibrating = true;
  calibrationStart = millis();
  minRed = 1000; minGreen = 1000; minBlue = 1000;
  maxRed = 0; maxGreen = 0; maxBlue = 0;
  
  Serial.println("Calibration started. Move object over sensor...");
  dfPlayer.play(104); // Play calibration announcement
  
  // Blink LED rapidly during calibration
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

void handleCalibration() {
  // Update min/max values
  minRed = min(minRed, redFrequency);
  maxRed = max(maxRed, redFrequency);
  minGreen = min(minGreen, greenFrequency);
  maxGreen = max(maxGreen, greenFrequency);
  minBlue = min(minBlue, blueFrequency);
  maxBlue = max(maxBlue, blueFrequency);

  // Print current values
  Serial.print("R: "); Serial.print(minRed); Serial.print("-"); Serial.print(maxRed);
  Serial.print(" | G: "); Serial.print(minGreen); Serial.print("-"); Serial.print(maxGreen);
  Serial.print(" | B: "); Serial.print(minBlue); Serial.print("-"); Serial.println(maxBlue);

  // Check if calibration time is complete
  if (millis() - calibrationStart > CALIBRATION_DURATION) {
    isCalibrating = false;
    saveCalibration();
    Serial.println("Calibration complete!");
    dfPlayer.play(105); // Play completion announcement
    
    // Flash LED to indicate completion
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      delay(200);
    }
  }
}

// COLOR PROCESSING & DETECTION
void processColor() {
  // Normalize RGB values (0-255)
  int red = map(constrain(redFrequency, minRed, maxRed), minRed, maxRed, 0, 255);
  int green = map(constrain(greenFrequency, minGreen, maxGreen), minGreen, maxGreen, 0, 255);
  int blue = map(constrain(blueFrequency, minBlue, maxBlue), minBlue, maxBlue, 0, 255);

  // Convert to HSV for better color detection
  float hue, saturation, value;
  rgbToHsv(red, green, blue, hue, saturation, value);

  // Debug output
  Serial.print("Raw Freq - R: "); Serial.print(redFrequency);
  Serial.print(" G: "); Serial.print(greenFrequency);
  Serial.print(" B: "); Serial.print(blueFrequency);
  Serial.print(" | HSV: "); Serial.print(hue, 1);
  Serial.print("° "); Serial.print(saturation * 100, 1);
  Serial.print("% "); Serial.print(value * 100, 1);
  Serial.println("%");

  // Detect and announce color based on mode
  switch (currentMode) {
    case MODE_COLOR_ID:
      detectColorIdentification(hue, saturation, value);
      break;
    case MODE_NAVIGATION:
      detectNavigation(hue, saturation, value);
      break;
    case MODE_MEDICINE:
      detectMedicineAndDanger(hue, saturation, value);
      break;
    default:
      break;
  }
}


// RGB TO HSV CONVERSION
void rgbToHsv(int r, int g, int b, float &hue, float &saturation, float &value) {
  float rf = r / 255.0, gf = g / 255.0, bf = b / 255.0;
  float maxVal = max(rf, max(gf, bf));
  float minVal = min(rf, min(gf, bf));
  float delta = maxVal - minVal;

  // Calculate Hue
  hue = 0;
  if (delta > 0) {
    if (maxVal == rf) {
      hue = fmod(((gf - bf) / delta), 6) * 60;
    } else if (maxVal == gf) {
      hue = ((bf - rf) / delta + 2) * 60;
    } else {
      hue = ((rf - gf) / delta + 4) * 60;
    }
    if (hue < 0) hue += 360;
  }

  // Calculate Saturation
  saturation = (maxVal == 0) ? 0 : (delta / maxVal);

  // Calculate Value
  value = maxVal;
}


// MODE 1: COLOR IDENTIFICATION
void detectColorIdentification(float hue, float saturation, float value) {
  if (value < 0.15) {
    Serial.println("Detected: BLACK");
    dfPlayer.play(1);
  } else if (saturation < 0.15) {
    Serial.println("Detected: WHITE/GRAY");
    dfPlayer.play(2);
  } else if (hue >= 0 && hue < 15) {
    Serial.println("Detected: RED");
    dfPlayer.play(3);
  } else if (hue >= 15 && hue < 45) {
    Serial.println("Detected: ORANGE");
    dfPlayer.play(4);
  } else if (hue >= 45 && hue < 65) {
    Serial.println("Detected: YELLOW");
    dfPlayer.play(5);
  } else if (hue >= 65 && hue < 160) {
    Serial.println("Detected: GREEN");
    dfPlayer.play(6);
  } else if (hue >= 160 && hue < 200) {
    Serial.println("Detected: CYAN");
    dfPlayer.play(7);
  } else if (hue >= 200 && hue < 260) {
    Serial.println("Detected: BLUE");
    dfPlayer.play(8);
  } else if (hue >= 260 && hue < 290) {
    Serial.println("Detected: PURPLE");
    dfPlayer.play(9);
  } else if (hue >= 290 && hue < 330) {
    Serial.println("Detected: MAGENTA");
    dfPlayer.play(10);
  } else if (hue >= 330 && hue < 360) {
    Serial.println("Detected: PINK");
    dfPlayer.play(11);
  } else {
    Serial.println("Detected: UNKNOWN");
  }
}


// MODE 2: NAVIGATION
void detectNavigation(float hue, float saturation, float value) {
  if (value < 0.15) {
    Serial.println("Navigation: OBSTACLE");
    dfPlayer.play(20);
  } else if (saturation < 0.15) {
    Serial.println("Navigation: CLEAR PATH (White)");
    dfPlayer.play(21);
  } else if (hue >= 0 && hue < 30) {
    Serial.println("Navigation: STRAIGHT (Red)");
    dfPlayer.play(22);
  } else if (hue >= 85 && hue < 160) {
    Serial.println("Navigation: RIGHT (Green)");
    dfPlayer.play(23);
  } else if (hue >= 200 && hue < 260) {
    Serial.println("Navigation: LEFT (Blue)");
    dfPlayer.play(24);
  } else if (hue >= 260 && hue < 330) {
    Serial.println("Navigation: DESTINATION (Purple)");
    dfPlayer.play(25);
  } else if (hue >= 45 && hue < 65) {
    Serial.println("Navigation: LOCATION (Yellow)");
    dfPlayer.play(26);
  } else if (hue >= 330 && hue < 360) {
    Serial.println("Navigation: SPECIAL LOCATION (Pink)");
    dfPlayer.play(27);
  } else {
    Serial.println("Navigation: UNCERTAIN");
  }
}


// MODE 3: MEDICINE & DANGER DETECTION

void detectMedicineAndDanger(float hue, float saturation, float value) {
  if (value < 0.15) {
    Serial.println("Status: DARK/BLOCKED");
    dfPlayer.play(30);
  } else if (saturation < 0.15) {
    Serial.println("Status: CLEAR");
    dfPlayer.play(31);
  } else if (hue >= 0 && hue < 30) {
    Serial.println("Status: DANGER - RED ALERT");
    dfPlayer.play(32);
  } else if (hue >= 85 && hue < 160) {
    Serial.println("Status: MEDICINE - PHARMACY");
    dfPlayer.play(33);
  } else if (hue >= 200 && hue < 260) {
    Serial.println("Status: EMERGENCY - BLUE ZONE");
    dfPlayer.play(34);
  } else if (hue >= 45 && hue < 65) {
    Serial.println("Status: CLINIC - YELLOW ZONE");
    dfPlayer.play(35);
  } else if (hue >= 260 && hue < 330) {
    Serial.println("Status: MEDICAL CENTER");
    dfPlayer.play(36);
  } else {
    Serial.println("Status: UNKNOWN");
  }
}


// EEPROM STORAGE

void saveSettings() {
  EEPROM.write(EEPROM_MODE_ADDR, currentMode);
  EEPROM.write(EEPROM_VOLUME_ADDR, currentVolume);
}

void loadSettings() {
  currentMode = (Mode)EEPROM.read(EEPROM_MODE_ADDR);
  currentVolume = EEPROM.read(EEPROM_VOLUME_ADDR);
  
  // Validate loaded values
  if (currentMode > 3) currentMode = MODE_COLOR_ID;
  if (currentVolume == 255 || currentVolume > 30) currentVolume = 20;
}

void saveCalibration() {
  // Simplified calibration storage
  EEPROM.put(EEPROM_MIN_RED_ADDR, minRed);
  EEPROM.put(EEPROM_MAX_RED_ADDR, maxRed);
  EEPROM.put(EEPROM_MIN_GREEN_ADDR, minGreen);
  EEPROM.put(EEPROM_MAX_GREEN_ADDR, maxGreen);
  EEPROM.put(EEPROM_MIN_BLUE_ADDR, minBlue);
  EEPROM.put(EEPROM_MAX_BLUE_ADDR, maxBlue);
}

void loadCalibration() {
  EEPROM.get(EEPROM_MIN_RED_ADDR, minRed);
  EEPROM.get(EEPROM_MAX_RED_ADDR, maxRed);
  EEPROM.get(EEPROM_MIN_GREEN_ADDR, minGreen);
  EEPROM.get(EEPROM_MAX_GREEN_ADDR, maxGreen);
  EEPROM.get(EEPROM_MIN_BLUE_ADDR, minBlue);
  EEPROM.get(EEPROM_MAX_BLUE_ADDR, maxBlue);
}

// UTILITY FUNCTIONS

void blinkError() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}


// END OF FIRMWARE


/*
BUTTON SETUP GUIDE:
===================

Connect push buttons to these pins with:
- One end to the pin
- Other end to GND
- 10kΩ pull-up resistor (or use INPUT_PULLUP)

Pin 8  (BUTTON_MODE):        Switch between modes
Pin 9  (BUTTON_CALIBRATE):   Start calibration
Pin A0 (BUTTON_VOLUME_UP):   Increase volume
Pin A1 (BUTTON_VOLUME_DOWN): Decrease volume

MODE SWITCHING:
Press Button 8 to cycle through:
1. COLOR IDENTIFICATION - Identify colors
2. NAVIGATION - Direction and location guidance
3. MEDICINE/DANGER - Health facility detection
4. Back to MODE 1

QUICK START:
1. Upload this code to Arduino
2. Connect buttons as shown above
3. Connect color sensor (TCS3200) to pins 2-6
4. Connect DFPlayer to pins 10-11
5. Place speaker/headphones on DFPlayer output
6. Press buttons to switch modes and control


CALIBRATION:
Press Button 9 to calibrate:
- Move colorful object over sensor for 5 seconds
- Device will auto-save calibration
- LED will flash when complete

AUDIO FILES NEEDED:
Place these MP3 files on microSD card:

001-011: Color names (Black, White, Red, Orange, Yellow, Green, Cyan, Blue, Purple, Magenta, Pink)
020-027: Navigation (Obstacle, Clear, Straight, Right, Left, Destination, Location, Special)
030-036: Medicine/Danger (Dark, Clear, Danger, Pharmacy, Emergency, Clinic, Center)
101-103: Mode announcements
104-105: Calibration messages
*/

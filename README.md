# COSAR: Color Sensing Gloves with Audio Readouts

> Arduino-based assistive technology for visually impaired individuals | Limay Senior High School STEM Capstone 2024-2025

---

## About This Project

COSAR represents a comprehensive research and development initiative to create wearable assistive technology that leverages color detection to enhance independence and spatial awareness for visually impaired individuals. By converting visual color information into real-time audio feedback, COSAR enables users to navigate their environment and interpret color-coded information independently.

**Status:** Research Complete • Firmware Production-Ready • Open for Further Development

---

## The Team

**Research & Development Team**
- Matt Joseph M. Managaytay — Team Lead & Developer
- Anthony A. Lumantao — Hardware Engineering
- Ysha Mae V. De Guzman — Research & Testing
- Eugene Kimberly B. Visbal — Data Analysis
- Russel Vien A. Gracela — Field Testing
- Larianne Joael D. Basbas — Documentation

**Academic Supervision**
- Research Adviser: Mrs. Cecille B. Delgado
- Research Coordinator: Mrs. Rowena V. Cabrera, EdD

**Institution:** Limay Senior High School, Duale, Limay, Bataan | STEM 12-B Program

---

## Research Overview

### Primary Objectives

This study developed and evaluated an Arduino-based color sensing system specifically designed to:

**Capability Development**
- Create wearable gloves capable of real-time color detection
- Implement audio feedback mechanism for color interpretation
- Design ergonomic form factor suitable for extended wear

**Effectiveness Evaluation**
- Measure color detection accuracy under various conditions
- Assess audio feedback clarity and user comprehension
- Evaluate impact on user independence and navigation ability

**Accessibility Assessment**
- Analyze material costs and long-term maintenance requirements
- Evaluate component durability and lifespan
- Determine affordability and accessibility for target users
- Test performance across varying environmental conditions

### Research Methodology

**Research Type:** Quantitative Research (True-Experimental Study Design)

**Participant Profile**
- Sample Size: 6 visually impaired students (Grades 11-12)
- Academic Level: Academic Track
- Visual Impairment Distribution:
  - 3 with Myopia (nearsightedness)
  - 3 with Hyperopia (farsightedness)

**Data Collection & Analysis**
- Structured questionnaires
- Observational assessment methods
- Descriptive statistics
- Weighted mean analysis
- Independent t-tests for significance testing

---

## Key Results

### Performance Metrics

**Color Detection System**
- Detection Accuracy: 66.66%
- Audio Feedback Clarity: 100%
- Real-time Processing: Continuous

**User Experience**
- Comfort & Wearability Rating: 66.66%
- Navigation Success Rate: 100%
- Component Durability: 66.66%
- Maintenance Cost Efficiency: 66.66%

**Accessibility Factors**
- Initial Material Affordability: 34% positive
- Long-term Durability: 66.66% positive
- Battery Life Performance: 33.33% extended
- Color Range Detection: 66-100% across spectrum
- Environmental Lighting Compatibility: 33.33%

### Statistical Significance

The study demonstrated statistically significant results:

- **Myopia Group Mean:** 2.50 | **Hyperopia Group Mean:** 2.25
- **T-statistic:** 2.35336
- **P-value:** 0.03910 (p < 0.05)
- **Finding:** Alternative hypothesis accepted — COSAR demonstrates significant accuracy and durability performance

---

## Hardware Architecture

### Core Components

**Processing Unit**
- Microcontroller: Arduino Uno
- Operating Voltage: 5V
- Memory: 2KB RAM, 32KB Flash

**Sensor System**
- Color Detection: TCS3200 RGB Color Sensor
- Detection Method: Optical frequency measurement
- Color Channels: Red, Green, Blue, Clear
- Detection Range: 8-bit per channel (256 levels)

**Audio Interface**
- Audio Module: DFPlayer Mini MP3 Player
- Storage: microSD Card (up to 32GB)
- Output: 3.5mm Speaker Jack
- Volume Range: 0-30 levels

**Power Management**
- Primary Supply: 5V Rechargeable Battery Pack
- Capacity: 2000-2500 mAh
- Estimated Runtime: 4-6 hours
- Charging Time: 2-3 hours

**User Interface**
- Control Method: 4 Push Buttons
  - Mode Selection
  - Calibration Trigger
  - Volume Up/Down
- Visual Feedback: LED Indicator
- Status Output: Serial Debug Monitor

---

## Technical Implementation

### The Unified Firmware

This repository includes a production-ready Arduino firmware that consolidates multiple operational modes into a single, button-controlled system. No code recompilation required.

**Operating Modes**

**Mode 1: Color Identification**
Detects and announces 11 distinct colors (Black, White, Red, Orange, Yellow, Green, Cyan, Blue, Purple, Magenta, Pink) with real-time audio feedback.

**Mode 2: Navigation Assistance**
Provides directional guidance through color-coded environments. Identifies 8 navigation states (Obstacle, Clear Path, Straight, Right, Left, Destination, Location, Special Location) for independent wayfinding.

**Mode 3: Health Facility Detection**
Identifies medical and emergency facilities through color recognition. Detects 7 facility types (Dark/Blocked, Clear, Danger, Pharmacy, Emergency, Clinic, Medical Center) for healthcare navigation.

**Mode 4: Calibration**
Automated environmental calibration with 5-second initialization period and EEPROM storage for persistent settings.

### Software Features

- HSV-based color detection algorithm (superior to RGB threshold methods)
- Automatic sensor calibration with one-button activation
- Volume control (0-30 adjustable levels)
- Settings persistence through EEPROM storage
- 300ms button debounce for reliable input
- Real-time frequency analysis from TCS3200 sensor
- Serial debug output for troubleshooting

---

## Getting Started

### Prerequisites

**Hardware**
- Arduino Uno microcontroller
- TCS3200 color sensor module
- DFPlayer Mini audio module
- Small speaker or headphones
- microSD card (256MB minimum)
- 4 push buttons
- Rechargeable battery pack (5V)
- Wearable glove (modified for sensor integration)

**Software**
- Arduino IDE (latest version)
- DFRobotDFPlayerMini library
- USB cable for Arduino programming

### Installation

**1. Prepare Development Environment**

Install the required library through Arduino IDE:
```
Sketch → Include Library → Manage Libraries
Search: "DFRobotDFPlayerMini"
Install: DFRobotDFPlayerMini by DFRobot
```

**2. Upload Firmware**

- Open `COSAR_UNIFIED_FIRMWARE.ino`
- Select Board: Arduino Uno
- Select Port: Your COM port
- Click Upload

**3. Prepare Audio Feedback**

Generate 40 MP3 files for audio responses:
- Use text-to-speech service (www.ttsmp3.com) or record personally
- Name files sequentially: 001.mp3 through 105.mp3
- Copy files to microSD card root directory
- Insert card into DFPlayer module

**4. Hardware Assembly**

Connect components per wiring specifications:
- Sensor pins: 2-6
- Button pins: 8, 9, A0, A1
- Serial communication: 10-11
- LED indicator: Pin 7
- Power: 5V and GND

See `WIRING_DIAGRAM.md` for complete pinout details.

---

## Documentation

This repository includes comprehensive documentation covering all aspects of the project.

**For Users & Implementers**
- [UNIFIED_FIRMWARE_GUIDE.md](UNIFIED_FIRMWARE_GUIDE.md) — Complete setup and operation manual
- [WIRING_DIAGRAM.md](WIRING_DIAGRAM.md) — Hardware connection specifications with diagrams
- [QUICK_REFERENCE.md](QUICK_REFERENCE.md) — Quick lookup guide for button functions and troubleshooting

**For Developers & Researchers**
- [CODE_VERIFICATION_REPORT.md](CODE_VERIFICATION_REPORT.md) — Code quality assurance and verification
- [TROUBLESHOOTING_AND_FAQ.md](TROUBLESHOOTING_AND_FAQ.md) — Problem resolution guide with diagnostic procedures
- [IMPLEMENTATION_CHECKLIST.md](IMPLEMENTATION_CHECKLIST.md) — Phase-by-phase implementation tracking

**Research Documentation**
- [docs/abstract.md](docs/abstract.md) — Research abstract and key findings
- [docs/methodology.md](docs/methodology.md) — Detailed research methodology and procedures
- [docs/findings.md](docs/findings.md) — Complete statistical analysis and results

---

## Project Structure

```
cosar-gloves/
│
├── COSAR_UNIFIED_FIRMWARE.ino        # Production firmware (upload to Arduino)
├── README.md                          # This file
│
├── docs/                              # Technical documentation
│   ├── UNIFIED_FIRMWARE_GUIDE.md     # Setup & operation guide
│   ├── WIRING_DIAGRAM.md             # Hardware specifications
│   ├── QUICK_REFERENCE.md            # Quick lookup
│   ├── TROUBLESHOOTING_AND_FAQ.md    # Problem solving
│   └── CODE_VERIFICATION_REPORT.md   # Code quality
│
├── research/                          # Research documentation
│   └── COSAR-Research-Study.docx     # Original research paper
│
└── .gitignore                        # Git configuration
```

---

## Key Findings & Conclusions

### What We Learned

**System Effectiveness**
COSAR successfully demonstrates the feasibility of color-based assistive technology. The system achieved 100% success in navigation tasks and provides clear, audible feedback across all tested conditions. Audio clarity rated at 100% with user comprehension exceeding 90%.

**User Impact**
Participants reported improved confidence in independent navigation. The device enhanced spatial awareness and enabled independent interpretation of color-coded information without external assistance.

**Accessibility Challenges**
Battery life and lighting sensitivity remain the primary limitations. Current system provides 4-6 hours of operation, sufficient for school-day use but requiring optimization for extended deployment. Lighting conditions affect detection accuracy by up to 33%, indicating need for adaptive calibration.

**Cost-Benefit Analysis**
Bill of materials costs approximately $50-75 USD, representing an accessible price point for educational settings. Component durability testing shows 66.66% rating for long-term reliability, suggesting 2-3 year useful lifespan with proper maintenance.

### Recommendations for Future Development

**Near-term Improvements**
- Implement higher-capacity battery (12+ hour target)
- Add adaptive light-sensitivity calibration
- Develop ergonomic glove design for all-day wear
- Expand audio library for additional detection modes

**Medium-term Expansion**
- Conduct testing with larger, more diverse participant groups
- Integrate obstacle detection sensor
- Add GPS-based location feedback
- Implement machine learning for improved color classification

**Long-term Vision**
- Develop commercial prototype for wider adoption
- Create comprehensive user training program
- Establish maintenance and support procedures
- Explore integration with other assistive technologies

---

## Research References

This research builds upon established theories in assistive technology and multisensory integration:

**Primary Theoretical Framework**
- Cross-Modal Plasticity Theory (Bach-y-Rita, 1960s; Park & Finde, 2023)
- Multisensory Integration Theory (Stein, Stanford, & Rowland, 2021)
- Affordance in Assistive Technology (Baines et al., 2023)

**Related Work**
The study synthesizes insights from research on wearable assistive devices, color perception in non-visual contexts, and accessibility for visually impaired individuals in educational environments.

---

## How to Contribute

This project welcomes contributions and improvements from the research and development community.

**Development Contributions**
- Fork this repository
- Create a feature branch for your improvements
- Implement enhancements with clear documentation
- Test thoroughly with target user group
- Submit pull request with detailed description

**Research Contributions**
- Conduct expanded testing with larger participant groups
- Document findings and share results
- Propose new operational modes or features
- Contribute to accessibility improvements

**Documentation Contributions**
- Improve existing guides and tutorials
- Translate documentation to additional languages
- Create video tutorials or visual guides
- Contribute to code documentation

---

## License & Usage

This project is made available for academic research and educational purposes. All research documentation, code, and findings are provided as-is for non-commercial use.

**For Academic Use:** Citation appreciated. Reference as "COSAR: Color Sensing Gloves Research Project, Limay Senior High School STEM Capstone 2024-2025"

**For Commercial Development:** Contact research team for licensing discussions and collaboration opportunities.

---

## Contact & Support

**Research Team Contact**
- Matt Joseph M. Managaytay (Lead) — anoishida01@gmail.com
- Anthony A. Lumantao — anthonylumantao.dev@gmail.com
- Ysha Mae V. De Guzman — yshamae7197@gmail.com
- Eugene Kimberly B. Visbal — eugenevisbal688@gmail.com
- Russel Vien A. Gracela — russelgracela74@gmail.com
- Larianne Joael D. Basbas — lariannediego@gmail.com

**Questions & Support**
Comprehensive documentation is provided in this repository. For questions not addressed in the guides, please review the relevant documentation file or contact the research team directly.

---

## Project Timeline

- **March 2025** — Research study completed and documented
- **April 2025** — Results approved and validated
- **May 2025** — Firmware optimized and unified
- **Current** — Open for further development and community contributions

---

## Technology Stack

- **Language:** C++ (Arduino)
- **Microcontroller:** Arduino Uno (ATmega328P)
- **Primary Libraries:** SoftwareSerial, DFRobotDFPlayerMini, EEPROM
- **Hardware:** TCS3200, DFPlayer Mini, Arduino-compatible components
- **Development Environment:** Arduino IDE
- **Version Control:** Git/GitHub

---

## Status & Roadmap

**Current Status:** Production-Ready Firmware | Research Complete | Documentation Complete

**Immediate Next Steps**
- Community testing and feedback
- Integration with expanded audio library
- Real-world deployment in educational settings
- Accessibility improvements based on user feedback

**Long-term Goals**
- Commercial prototype development
- Expanded research with larger participant groups
- Feature integration (obstacle detection, GPS, ML-based recognition)
- Community-driven improvements and extensions

---

**Last Updated:** May 2025  
**Repository Status:** Active Development  
**Contribution Status:** Open to Collaboration

---

## Acknowledgments

This research would not have been possible without the dedicated support of our adviser Mrs. Cecille B. Delgado, coordinator Mrs. Rowena V. Cabrera, and the institutional support of Limay Senior High School. Special thanks to our research participants and the broader STEM community for valuable feedback throughout the project.

---

**[Read the Full Research Paper](research/COSAR-Research-Study.docx)** | **[View Technical Specifications](research/src/hardware-specifications.md)** | **[See Implementation Guide](docs/UNIFIED_FIRMWARE_GUIDE.md)**

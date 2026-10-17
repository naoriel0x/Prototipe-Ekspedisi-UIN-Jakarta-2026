<div align="center">

<img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white"/>
<img src="https://img.shields.io/badge/PlatformIO-FF7F00?style=for-the-badge&logo=platformio&logoColor=white"/>
<img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white"/>
<img src="https://img.shields.io/badge/VS%20Code-007ACC?style=for-the-badge&logo=visualstudiocode&logoColor=white"/>

# 🔍 LogamDetektor

### Pulse Induction Metal Detector — Arduino Nano

> A physics-meets-electronics prototype that detects metal objects using electromagnetic pulse induction, adaptive calibration, and real-time feedback.

<img src="https://img.shields.io/badge/Status-Active%20Development-brightgreen?style=flat-square"/>
<img src="https://img.shields.io/badge/Board-Arduino%20Nano-00979D?style=flat-square&logo=arduino&logoColor=white"/>
<img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white"/>
<img src="https://img.shields.io/badge/AI%20Integration-Coming%20Soon-blueviolet?style=flat-square"/>

</div>

---

## ⚡ How It Works

```
┌─────────────────────────────────────────────────────────────┐
│                                                             │
│   Pulse Coil ──► Electromagnetic Pulse ──► Sensor Coil      │
│                                                │            │
│                                         Induction Response  │
│                                                │            │
│                                         Arduino Nano (ADC)  │
│                                                │            │
│                              ┌─────────────────┴──────┐     │
│                              │  Adaptive Calibration  │     │
│                              └─────────────────┬──────┘     │
│                                                │            │
│                         ┌──────────────────────┤            │
│                         │                      │            │
│                    ✅ NORMAL               🚨 METAL!       │
│                    Green LED              Red LED           │
│                                           + Buzzer          │
└─────────────────────────────────────────────────────────────┘
```

---

## 🧰 Hardware

<div align="center">

| Component | Role | Pin |
|:---:|:---:|:---:|
| 🔵 Arduino Nano | Microcontroller | — |
| 🌀 Sensor Coil | Induction input | `A5` |
| ⚡ Pulse Coil | EM pulse output | `A0` |
| 🔴 Red LED | Metal detected indicator | `D8` |
| 🟢 Green LED | Normal state indicator | `D10` |
| 🔊 Buzzer SFM-27 | Audio alert | `D6` |
| 🔧 Transistor BC547 | Buzzer driver | — |

</div>

---

## ✨ Features

- 🎯 **Pulse Induction detection** — reliable on most conductive metals
- 📊 **50-iteration auto-calibration** on startup
- 🧠 **Adaptive threshold** — self-adjusts to environmental noise
- 💡 **Dual LED feedback** — red for detection, green for standby
- 🔇 **Anti-false-positive** — buzzer only cuts off after 10 consecutive clean readings
- 🖥️ **Real-time Serial Monitor** output with labeled status

---

## 🚀 Getting Started

**1. Clone the repository**
```bash
git clone https://github.com/naoriel0x/Prototipe-Ekspedisi-UIN-Jakarta-2026.git
cd Prototipe-Ekspedisi-UIN-Jakarta-2026
```

**2. Open in VS Code with PlatformIO installed**
```bash
code .
```

**3. Build & upload to Arduino Nano**

Click the **Upload** button in PlatformIO toolbar, or:
```bash
pio run --target upload
```

**4. Open Serial Monitor at `9600` baud and wait for calibration**

> Buzzer beeps once on startup. LEDs stay off during the 50-iteration calibration phase.

---

## 🖥️ Serial Monitor Output

```
=== CALIBRATION STARTED ===

[CALIBRATION]  1/50  read=512
[CALIBRATION]  2/50  read=511
...
[CALIBRATION] 50/50  read=510

[NORMAL]  read=510  diff=2   nc=0
[NORMAL]  read=509  diff=1   nc=0
[METAL!]  read=489  diff=-23  threshold=5  buzzer=ON
[METAL!]  read=485  diff=-27  threshold=5  buzzer=ON
[NORMAL]  read=510  diff=1   nc=10  → buzzer OFF
```

---

## 🗺️ Roadmap

- [x] Pulse induction metal detection
- [x] 50-iteration adaptive auto-calibration
- [x] LED + buzzer real-time feedback
- [x] Anti-false-positive logic
- [ ] 🔜 **AI / ML integration** — classify metal types (ferrous vs non-ferrous)
- [ ] 🔜 OLED display for field readout
- [ ] 🔜 Battery-powered portable enclosure

---

## 🛠️ Built With

<div align="center">

<img src="https://img.shields.io/badge/PlatformIO-FF7F00?style=for-the-badge&logo=platformio&logoColor=white"/>
<img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white"/>
<img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white"/>
<img src="https://img.shields.io/badge/VS%20Code-007ACC?style=for-the-badge&logo=visualstudiocode&logoColor=white"/>

</div>

---

## 👤 Author

<div align="center">

**Devandra El Syadam**

Physics Student · Cybersecurity Enthusiast · Embedded Systems Builder

[![Portfolio](https://img.shields.io/badge/Portfolio-000000?style=for-the-badge&logo=netlify&logoColor=white)](https://devandraelsyadam.netlify.app)
[![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/naoriel0x)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://linkedin.com/in/devandra-el-syadam)

</div>

---

<div align="center">
<sub>Built with curiosity and too many oscilloscope readings ⚡</sub>
</div>
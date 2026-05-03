# 📶 WiFi Signal Strength Monitoring System

> NodeMCU (ESP8266) · I²C LCD · LED Signal Bar · Buzzer Alert

A portable, low-cost embedded system that continuously measures WiFi RSSI, classifies signal strength into three tiers, and delivers real-time visual and audio feedback — making dead zones visible without any special software.

**Team**  Sai Kiran Gugulothu  
**Institution** — IIIT Sri City | B.Tech ECE | 2025–26

---

## Demo

📹 [Project Video](demo/WN_Project_Video.mp4) &nbsp;|&nbsp; 📊 [Presentation Slides](docs/WN.pdf) &nbsp;|&nbsp; 📄 [Final Report](docs/Final.pdf)

---

## Features

| Feature | Details |
|---|---|
| RSSI Polling | Every 300 ms via `WiFi.RSSI()` |
| Signal Classification | Strong (> −65 dBm) · Medium (−65 to −75 dBm) · Weak (< −75 dBm) |
| LCD Display | 16×2 I²C — shows RSSI in dBm + status text |
| LED Bar | 3 LEDs mimic phone signal bars (3 / 2 / 1 ON) |
| Buzzer Alert | Silent on strong · Slow beep (200 ms/800 ms) on medium · Continuous on weak |
| Network Scanner | Lists all nearby SSIDs with RSSI and identifies the strongest |
| RSSI Smoothing | Rolling average buffer to suppress ±3–5 dBm fluctuation |

---

## Hardware

| Component | Pin |
|---|---|
| NodeMCU ESP8266 | — |
| 16×2 I²C LCD (0x27) | SDA → D2, SCL → D1 |
| LED 1 (Green) | D5 via 220 Ω |
| LED 2 (Yellow) | D6 via 220 Ω |
| LED 3 (Red) | D7 via 220 Ω |
| Active Buzzer | D0 |

> **Note:** The LCD runs on 5 V. Power it from an Arduino UNO's 5 V rail (not NodeMCU's 3.3 V).

---

## Signal Classification Logic

```
RSSI > −65 dBm  →  Strong  →  3 LEDs ON  |  Buzzer OFF   |  "Strong [|||]"
−65 to −75 dBm  →  Medium  →  2 LEDs ON  |  Slow beep    |  "Medium [|| ]"
RSSI < −75 dBm  →  Weak    →  1 LED ON   |  Continuous   |  "Weak Zone"
```

---

## Getting Started

### Prerequisites

- Arduino IDE with **ESP8266 board package** installed
- Libraries: `ESP8266WiFi` · `Wire` · `LiquidCrystal_I2C`

### Flash

1. Clone the repo:
   ```bash
   git clone https://github.com/<your-username>/WiFi-Signal-Monitor-NodeMCU.git
   ```
2. Open `src/wifi_monitor.ino` in Arduino IDE.
3. Edit credentials:
   ```cpp
   const char* ssid     = "YOUR_SSID";
   const char* password = "YOUR_PASSWORD";
   ```
4. Select **NodeMCU 1.0 (ESP-12E Module)** as the board and flash.

---

## System Flowchart

```
Power ON → Connect to WiFi → Read RSSI (every 300 ms)
         → Classify (Strong / Medium / Weak)
         → Update LCD + LEDs + Buzzer
         → Repeat
```

---

## Test Results

| Scenario | RSSI | LEDs | Buzzer | LCD |
|---|---|---|---|---|
| Strong | −50 dBm | 3 ON | OFF | `Strong [|||]` |
| Medium | −70 dBm | 2 ON | Slow beep | `Medium [|| ]` |
| Weak | −82 dBm | 1 ON | Continuous | `Weak Zone` |

---

## Challenges

- **I²C address conflict** — resolved by scanning and hardcoding `0x27`
- **RSSI fluctuation** — mitigated with rolling average
- **Buzzer timing vs polling loop** — required non-blocking delay management
- **5 V LCD on 3.3 V NodeMCU** — powered via external 5 V rail

---

## Future Work

- Mobile app dashboard with heatmap visualization
- Cloud logging to Firebase / ThingSpeak
- 2D coverage heatmap with GPS coordinates
- Auto network switching on signal drop
- OLED / TFT display upgrade
- Multi-node mesh mapping

---

## License

MIT — see [LICENSE](LICENSE) for details.

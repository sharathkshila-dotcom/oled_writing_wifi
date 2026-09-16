#  ESP32 OLED Web Controller

A wireless **ESP32-based OLED controller** that allows you to type text and draw directly on a **128×64 OLED display** using a mobile phone or computer web browser.

The ESP32 creates its own Wi-Fi network and hosts a web interface. Once connected, users can send text, draw on a digital canvas, or clear the OLED screen without using any physical buttons.

##  Features

*  ESP32 creates its own Wi-Fi Access Point
*  Control the OLED using a mobile phone or computer
*  Type text directly onto the OLED
*  Draw on a 128×64 web canvas
*  Clear the OLED screen remotely
*  Built-in ESP32 web server
*  Real-time drawing using HTTP requests
*  Simple I2C OLED connection
*  Developed using Arduino / PlatformIO

##  Components Required

| Component               |    Quantity |
| ----------------------- | ----------: |
| ESP32 Development Board |           1 |
| 128×64 I2C OLED Display |           1 |
| USB Cable               |           1 |
| Jumper Wires            | As required |

##  Circuit Connections

| ESP32   | OLED |
| ------- | ---- |
| 3V3     | VCC  |
| GND     | GND  |
| GPIO 21 | SDA  |
| GPIO 22 | SCL  |

**Important:** Connect the OLED VCC to **3.3V** and GND to **GND**.

##  Libraries

The project uses:

* `WiFi.h`
* `WebServer.h`
* `Wire.h`
* `Adafruit GFX Library`
* `Adafruit SSD1306`

Install the Adafruit libraries through the Arduino Library Manager or PlatformIO.

##  How It Works

```text
ESP32
  │
  ├── Creates Wi-Fi Access Point
  │      SSID: ESP32_Canvas
  │      Password: 
  │
  ├── Starts Web Server
  │
  └── Hosts Web Control Page
          │
          ▼
     Mobile / Computer
          │
          ├── Type Text
          │
          ├── Draw on Canvas
          │
          └── Clear Screen
          │
          ▼
        ESP32
          │
          ▼
      OLED Display
```

##  How to Use

### 1. Upload the Code

Open the project in **VS Code with PlatformIO** and upload the program to the ESP32.

### 2. Connect to ESP32 Wi-Fi

From your mobile phone or computer, connect to:

```text
Wi-Fi: ESP32_Canvas
Password: 
```

### 3. Open the Web Controller

Open a browser and enter:

```text
192.168.4.1
```

### 4. Control the OLED

The web page provides:

* **Type on OLED** — sends typed text to the display
* **Canvas** — draw using a mouse, finger, or touchscreen
* **Clear Screen** — clears the OLED display

##  Web Server Routes

| Route    | Function                 |
| -------- | ------------------------ |
| `/`      | Opens the web controller |
| `/draw`  | Draws a line on the OLED |
| `/type`  | Displays typed text      |
| `/clear` | Clears the OLED          |

##  Software

* **Microcontroller:** ESP32
* **Programming Language:** C++
* **Framework:** Arduino
* **Development Environment:** VS Code + PlatformIO
* **Communication:** Wi-Fi
* **Display Communication:** I2C
* **Web Protocol:** HTTP

##  Project Structure

```text
oled_writing/
│
├── include/
│   └── README
│
├── lib/
│   └── README
│
├── src/
│   └── main.cpp
│
├── test/
│   └── README
│
├── platformio.ini
└── .gitignore
```

##  Future Improvements

*  Upload images to the OLED
*  Add drawing controls
*  Add adjustable brush sizes
*  Add undo functionality
*  Save drawings
*  Add different text sizes
*  Add support for color OLED displays

##  Author

**Sharath**

GitHub: `sharathkshila-dotcom`

---

 If you find this project useful, consider giving the repository a star!

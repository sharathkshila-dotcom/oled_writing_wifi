//SHARATH
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WebServer server(80);

const char HTML_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>ESP32 OLED Canvas</title>
  <style>
    body { text-align: center; font-family: Arial, sans-serif; background: #121212; color: #fff; margin: 0; padding: 15px; user-select: none; }
    h3 { margin: 5px 0 15px; color: #4da6ff; }
    .input-box { width: 80%; max-width: 280px; padding: 10px; font-size: 16px; border-radius: 6px; border: 1px solid #444; background: #222; color: white; outline: none; }
    button { padding: 10px 20px; font-size: 15px; font-weight: bold; border-radius: 6px; border: none; color: white; cursor: pointer; margin: 8px 4px; }
    .btn-send { background: #007bff; }
    .btn-clear { background: #dc3545; }
    canvas { background: #000; border: 2px solid #4da6ff; touch-action: none; border-radius: 8px; box-shadow: 0px 4px 12px rgba(0,0,0,0.6); margin-top: 10px; }
  </style>
</head>
<body>
  <h3>ESP32 OLED Controller</h3>
  <div>
    <input type="text" id="textInput" class="input-box" placeholder="Type text here...">
    <br>
    <button class="btn-send" onclick="sendText()">Type on OLED</button>
  </div>
  <hr style="border-color: #333; margin: 15px 0;">
  <div>
    <canvas id="canvas" width="128" height="64"></canvas>
    <br>
    <button class="btn-clear" onclick="clearCanvas()">Clear Screen</button>
  </div>

  <script>
    function sendText() {
      const msg = document.getElementById('textInput').value;
      if (msg !== "") fetch(`/type?text=${encodeURIComponent(msg)}`);
    }

    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');
    let drawing = false, lastX = 0, lastY = 0;

    canvas.style.width = '256px';
    canvas.style.height = '128px';

    function getPos(e) {
      const rect = canvas.getBoundingClientRect();
      const touch = e.touches ? e.touches[0] : e;
      return {
        x: (touch.clientX - rect.left) / 2,
        y: (touch.clientY - rect.top) / 2
      };
    }

    canvas.addEventListener('pointerdown', (e) => {
      drawing = true;
      const p = getPos(e);
      lastX = p.x; lastY = p.y;
    });

    canvas.addEventListener('pointermove', (e) => {
      if (!drawing) return;
      const p = getPos(e);
      ctx.strokeStyle = 'white';
      ctx.lineWidth = 1;
      ctx.beginPath();
      ctx.moveTo(lastX, lastY);
      ctx.lineTo(p.x, p.y);
      ctx.stroke();

      fetch(`/draw?x1=${Math.round(lastX)}&y1=${Math.round(lastY)}&x2=${Math.round(p.x)}&y2=${Math.round(p.y)}`);
      lastX = p.x; lastY = p.y;
    });

    canvas.addEventListener('pointerup', () => drawing = false);
    canvas.addEventListener('pointerleave', () => drawing = false);

    function clearCanvas() {
      ctx.clearRect(0, 0, 128, 64);
      document.getElementById('textInput').value = "";
      fetch('/clear');
    }
  </script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", HTML_PAGE);
}

void handleDraw() {
  if (server.hasArg("x1") && server.hasArg("y1") && server.hasArg("x2") && server.hasArg("y2")) {
    int x1 = server.arg("x1").toInt();
    int y1 = server.arg("y1").toInt();
    int x2 = server.arg("x2").toInt();
    int y2 = server.arg("y2").toInt();

    display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
    display.display();
  }
  server.send(200, "text/plain", "OK");
}

void handleType() {
  if (server.hasArg("text")) {
    String message = server.arg("text");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.println(message);
    display.display();
  }
  server.send(200, "text/plain", "OK");
}

void handleClear() {
  display.clearDisplay();
  display.display();
  server.send(200, "text/plain", "Cleared");
}

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }
  
  display.clearDisplay();
  WiFi.softAP("ESP32_Canvas", "12345678");
  
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Wi-Fi Ready!");
  display.println("SSID: ESP32_Canvas");
  display.println("Pass: 12345678");
  display.println("URL: 192.168.4.1");
  display.display();

  server.on("/", handleRoot);
  server.on("/draw", handleDraw);
  server.on("/type", handleType);
  server.on("/clear", handleClear);
  
  server.begin();
}

void loop() {
  server.handleClient();
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi credentials
const char* ssid = "Harsh200";
const char* password = "H2a0r0s5h";

// Define motor driver pins
#define MOTOR1_IN1 D1
#define MOTOR1_IN2 D2
#define MOTOR2_IN1 D4
#define MOTOR2_IN2 D3

ESP8266WebServer server(80);

// Webpage stored as a String (Fixed Version)
const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Nakshatra</title>
    <style>
        body {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            min-height: 100vh;
            margin: 0;
        }
        div {
            text-align: center;
        }
        #manual_control {
            margin-top: 20px;
        }
        #manual_control a {
            margin: 5px;
            padding: 10px;
            color: #000;
            border: 1px solid #000;
        }
        a {
            text-decoration: none;
        }
    </style>
    <script>
        function sendRequest(url) {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", url, true);
            xhr.send();
        }
    </script>
</head>
<body>
    <div>
        <h1>Nakshatra</h1>
        <button onclick="sendRequest('/mode1')">Gamepad</button>
    </div>
    <div id="manual_control">
        <button onclick="sendRequest('/up')">▲</button><br>
        <button onclick="sendRequest('/left')">◄</button>
        <button onclick="sendRequest('/stop')">◯</button>
        <button onclick="sendRequest('/right')">►</button><br>
        <button onclick="sendRequest('/down')">▼</button>
    </div>
</body>
</html>
)rawliteral";

void setup() {
    Serial.begin(115200);
    pinMode(MOTOR1_IN1, OUTPUT);
    pinMode(MOTOR1_IN2, OUTPUT);
    pinMode(MOTOR2_IN1, OUTPUT);
    pinMode(MOTOR2_IN2, OUTPUT);
    
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", []() {
        server.send_P(200, "text/html", webpage);
    });

    server.on("/up", []() { forward(); server.send(200, "text/plain", "Moving Forward"); });
    server.on("/down", []() { backward(); server.send(200, "text/plain", "Moving Backward"); });
    server.on("/left", []() { left(); server.send(200, "text/plain", "Turning Left"); });
    server.on("/right", []() { right(); server.send(200, "text/plain", "Turning Right"); });
    server.on("/stop", []() { stopMotors(); server.send(200, "text/plain", "Stopping"); });

    server.begin();
    Serial.println("Web server started");
}

void loop() {
    server.handleClient();
}

void forward() {
    Serial.println("Moving Forward");
    digitalWrite(MOTOR1_IN1, HIGH);
    digitalWrite(MOTOR1_IN2, LOW);
    digitalWrite(MOTOR2_IN1, HIGH);
    digitalWrite(MOTOR2_IN2, LOW);
}

void backward() {
    Serial.println("Moving Backward");
    digitalWrite(MOTOR1_IN1, LOW);
    digitalWrite(MOTOR1_IN2, HIGH);
    digitalWrite(MOTOR2_IN1, LOW);
    digitalWrite(MOTOR2_IN2, HIGH);
}

void left() {
    Serial.println("Turning Left");
    digitalWrite(MOTOR1_IN1, LOW);
    digitalWrite(MOTOR1_IN2, HIGH);
    digitalWrite(MOTOR2_IN1, HIGH);
    digitalWrite(MOTOR2_IN2, LOW);
}

void right() {
    Serial.println("Turning Right");
    digitalWrite(MOTOR1_IN1, HIGH);
    digitalWrite(MOTOR1_IN2, LOW);
    digitalWrite(MOTOR2_IN1, LOW);
    digitalWrite(MOTOR2_IN2, HIGH);
}

void stopMotors() {
    Serial.println("Stopping");
    digitalWrite(MOTOR1_IN1, LOW);
    digitalWrite(MOTOR1_IN2, LOW);
    digitalWrite(MOTOR2_IN1, LOW);
    digitalWrite(MOTOR2_IN2, LOW);
}
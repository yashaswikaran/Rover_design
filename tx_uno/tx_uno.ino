#include <SPI.h>
#include <RH_NRF24.h>

#define CE_PIN 9
#define CSN_PIN 10
#define LED_PIN 13  // For transmission indicator

// Joystick pins
#define VRx A0
#define VRy A1
#define SW 2

RH_NRF24 nrf24(CE_PIN, CSN_PIN);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SW, INPUT_PULLUP);

  // Initialize radio with retries
  if (!initializeRadio()) {
    Serial.println("Radio initialization failed!");
    while(1) { // Blink LED rapidly if failed
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      delay(100);
    }
  }
  Serial.println("Transmitter ready");
}

bool initializeRadio() {
  if (!nrf24.init()) return false;
  if (!nrf24.setChannel(1)) return false;
  if (!nrf24.setRF(RH_NRF24::DataRate250kbps, RH_NRF24::TransmitPower0dBm)) return false;
  return true;
}

void loop() {
  uint8_t payload[3] = {
    map(analogRead(VRx), 0, 1023, 0, 255),
    map(analogRead(VRy), 0, 1023, 0, 255),
    digitalRead(SW) == LOW ? 1 : 0
  };

  Serial.print("Sending: X=");
  Serial.print(payload[0]);
  Serial.print(" Y=");
  Serial.print(payload[1]);
  Serial.print(" BTN=");
  Serial.println(payload[2]);

  if (nrf24.send(payload, sizeof(payload))) {
    nrf24.waitPacketSent();
    digitalWrite(LED_PIN, HIGH);  // Transmission indicator
    delay(10);
    digitalWrite(LED_PIN, LOW);
  } else {
    Serial.println("Send failed!");
  }

  delay(50);  // 20Hz update rate
}
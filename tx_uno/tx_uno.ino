#include <SPI.h>
#include <RH_NRF24.h>

// NRF24L01 Pins
#define CE_PIN 9
#define CSN_PIN 10

// Joystick Pins
#define VRx A0
#define VRy A1
#define SW 2

RH_NRF24 nrf24(CE_PIN, CSN_PIN);

void setup() {
  Serial.begin(9600);

  pinMode(SW, INPUT_PULLUP); // Button with internal pull-up

  if (!nrf24.init()) {
    Serial.println("NRF24 init failed");
    while (1); // Stop here
  }

  if (!nrf24.setChannel(1))
    Serial.println("Channel set failed");

  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("RF set failed");

  Serial.println("NRF24 Transmitter Ready");
}

void loop() {
  int xValue = analogRead(VRx);  // X-axis
  int yValue = analogRead(VRy);  // Y-axis
  int buttonState = digitalRead(SW); // LOW = pressed

  // Optional: Map to 0–255
  uint8_t xMapped = map(xValue, 0, 1023, 0, 255);
  uint8_t yMapped = map(yValue, 0, 1023, 0, 255);
  uint8_t button = (buttonState == LOW) ? 1 : 0;

  // Prepare payload: 3 bytes
  uint8_t payload[3] = { xMapped, yMapped, button };

  // Debug print
  Serial.print("Sending -> X: ");
  Serial.print(xMapped);
  Serial.print(" | Y: ");
  Serial.print(yMapped);
  Serial.print(" | Button: ");
  Serial.println(button);

  // Send data
  nrf24.send(payload, sizeof(payload));
  nrf24.waitPacketSent();

  delay(100); // Smooth transmission rate
}

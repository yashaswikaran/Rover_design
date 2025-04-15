#include <RH_NRF24.h>
#include <SPI.h>

#define CE_PIN 2   // D4
#define CSN_PIN 4  // D2

RH_NRF24 nrf24(CE_PIN, CSN_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!nrf24.init())
    Serial.println("NRF24 init failed");
  if (!nrf24.setChannel(1))
    Serial.println("Channel set failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("RF set failed");

  Serial.println("NRF24 RX Ready");
}

void loop() {
  if (nrf24.available()) {
    uint8_t buf[3];  // Expecting 3 bytes
    uint8_t len = sizeof(buf);

    if (nrf24.recv(buf, &len)) {
      if (len == 3) {
        uint8_t x = buf[0];
        uint8_t y = buf[1];
        uint8_t button = buf[2];

        Serial.print("Received -> X: ");
        Serial.print(x);
        Serial.print(" | Y: ");
        Serial.print(y);
        Serial.print(" | Button: ");
        Serial.println(button);
      } else {
        Serial.println("Unexpected payload size");
      }
    } else {
      Serial.println("Receive failed");
    }
  }
}

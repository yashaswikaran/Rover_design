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
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (nrf24.recv(buf, &len)) {
      buf[len] = '\0';  // null-terminate
      Serial.print("Received: ");
      Serial.println((char*)buf);
    } else {
      Serial.println("Receive failed");
    }
  }
}
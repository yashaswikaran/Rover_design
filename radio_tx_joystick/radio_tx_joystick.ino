#include <RH_NRF24.h>
#include <SPI.h>

#define CE_PIN 2    // D4
#define CSN_PIN 4   // D2
#define POT_PIN A0  // Analog pin for potentiometer

RH_NRF24 nrf24(CE_PIN, CSN_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!nrf24.init()) {
    Serial.println("NRF24 init failed");
  }

  if (!nrf24.setChannel(1)) {
    Serial.println("Channel set failed");
  }

  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm)) {
    Serial.println("RF set failed");
  }

  Serial.println("Setup complete. Ready to send data.");
}

void loop() {
  int potValue = analogRead(POT_PIN); // Read potentiometer value (0-1023)
  String valueString = String(potValue);

  uint8_t dataArray[valueString.length() + 1];
  valueString.getBytes(dataArray, valueString.length() + 1);

  Serial.print("Sending potentiometer value: ");
  Serial.println(valueString);

  nrf24.send(dataArray, sizeof(dataArray));
  nrf24.waitPacketSent();

  delay(1000); // Send every second
}

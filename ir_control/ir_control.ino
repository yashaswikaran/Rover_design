#include <IRremote.hpp> // include the library

#define front 0x18
#define right 0x5A
#define left  0x8
#define back  0x52
#define stop_movig  0x1C

#define IR_RECEIVE_PIN 4

int command = 0;

void setup() {
    Serial.begin(115200);
    IrReceiver.begin(IR_RECEIVE_PIN);
}

void loop() {
    if (IrReceiver.decode()) {
        IrReceiver.resume(); // Early enable receiving of the next IR frame
        command = IrReceiver.decodedIRData.command;  
    }
    switch(command) {
          case left: Serial.println("going left"); break;
          case right: Serial.println("Going right"); break;
          case front: Serial.println("goind front"); break;
          case back: Serial.println("going back"); break;
          case stop_movig: Serial.println("stopping"); break;
          default: Serial.println(command); break;
        }
}
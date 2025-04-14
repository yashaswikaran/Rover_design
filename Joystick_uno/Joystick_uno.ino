// Pin definitions
const int VRx = A0;  // X-axis
const int VRy = A1;  // Y-axis
const int SW = 2;    // Button

void setup() {
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP); // Button input with internal pull-up
}

void loop() {
  int xValue = analogRead(VRx);  // Read X-axis value
  int yValue = analogRead(VRy);  // Read Y-axis value
  int buttonState = digitalRead(SW); // Read button (LOW when pressed)

  // Print values to Serial Monitor
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | Button: ");
  Serial.println(buttonState == LOW ? "Pressed" : "Released");

  delay(500); // Delay to make output readable
}

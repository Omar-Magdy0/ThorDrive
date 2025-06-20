#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(9600);
  Serial.print("Result of myFunction(2, 3): ");
  pinMode(PC1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PC1, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("Led is trash");
  delay(100);                       // wait for a second
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
// #define led_pin 8
// // the setup function runs once when you press reset or power the board
// void setup() {
//   // initialize digital pin LED_BUILTIN as an output.
//   pinMode(led_pin, OUTPUT);
// }

// // the loop function runs over and over again forever
// void loop() {
//   digitalWrite(led_pin, HIGH);  // turn the LED on (HIGH is the voltage level)
//   delay(1000);                      // wait for a second
//   digitalWrite(led_pin, LOW);   // turn the LED off by making the voltage LOW
//   delay(2000);                      // wait for a second
// }

int greenLed = 2;
int yellowLed = 5;
int blueLed = 8;

void setup() {
  Serial.begin(9600);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'A') {
      digitalWrite(yellowLed, LOW);
      digitalWrite(blueLed, LOW);
      digitalWrite(greenLed, LOW);

      digitalWrite(greenLed, HIGH);
      delay(3000); 
      digitalWrite(greenLed, LOW);

    } else if (command == 'B') {
      digitalWrite(yellowLed, LOW);
      digitalWrite(blueLed, LOW);
      digitalWrite(greenLed, LOW);

      digitalWrite(yellowLed, HIGH);
      delay(3000);
      digitalWrite(yellowLed, LOW);

    } else if (command == 'C') {
      digitalWrite(yellowLed, LOW);
      digitalWrite(blueLed, LOW);
      digitalWrite(greenLed, LOW);

      digitalWrite(blueLed, HIGH);
      delay(3000);
      digitalWrite(blueLed, LOW);
    }
  }
}

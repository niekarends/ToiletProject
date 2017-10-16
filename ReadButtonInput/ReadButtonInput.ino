/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
const int ledPin = 6;
const int buttonPin = 7;

int previousValue = 0;
int currentValue = 0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  currentValue = digitalRead(buttonPin);
  // print out the value you read:
  if(currentValue != previousValue) {
    previousValue = currentValue;
    digitalWrite(buttonPin, currentValue);
    if(currentValue == 1) {
      Serial.println("high");
    }
    else {
      Serial.println("low");
    }
  }
  delay(1);        // delay in between reads for stability
}

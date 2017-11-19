const int redPin = 0;     // the number of the pushbutton pin
const int greenPin = 1;
const int bluePin = 2;

int currentRed = 0;
int currentBlue = 0;
int currentGreen = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

// 

void loop() {
  //  if (i > 254) {
  //    direction = -1;
  //  }
  //  if (i == 0) {
  //    direction = 1;
  //  }
  //  setColourRgb(i, i, i);
  //  i += direction;
  //  delay(5);

  fadeToColor(255, 0, 0, 2000);
//  delay(1000);
  fadeToColor(0, 0, 0, 2000);
//  delay(1000);
//  fadeToColor(0, 0, 255, 2000);
//  delay(1000);
}

void fadeToColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int fadeDuration) {
  int delayMS = fadeDuration / 255;

  float redstep = (red - currentRed) / 255;
  float greenstep = (green - currentGreen) / 255;
  float bluestep = (blue - currentBlue) / 255;

  for (int i = 0; i < 255; i++) {
    setColourRgb(currentRed + redstep * i, currentGreen + greenstep * i, currentBlue + bluestep * i);
    delay(delayMS);
  }
  currentRed = red;
  currentBlue = blue;
  currentGreen = green;
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}


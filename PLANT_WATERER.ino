#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
const int relayPin = 2;
const int sensorPin = 4;
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
float sensorValue = 0;
#define SENSOR_READ_TIME 1000
void setup() {
   // put your setup code here, to run once:
  Serial.begin(115200);
  // begins communication with serial monitor
  pinMode(relayPin, OUTPUT);
  // sets pin 2 to output
  pinMode(sensorPin, INPUT);
  // sets pin A0 to input
  digitalWrite(relayPin, HIGH);
  // turns on relay, in turn turning on pump
  // runs pump for 1/2 second
 if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed")); 
  while (true);
  }
 OLED.clearDisplay(); // clear display

  OLED.setTextSize(1);         // set text size
  OLED.setTextColor(WHITE);    // set text color
  OLED.setCursor(0, 10);  
}

void loop() {

   // put your main code here, to run repeatedly:
  OLED.println("MOISTURE LEVEL: ");
  // prints "MOISTURE LEVEL: "
  sensorValue = analogRead(sensorPin);
  // sets "sensorValue" to input value from A0
  OLED.println(sensorValue);
  OLED.display();
  // prints moisture level
  (sensorValue > 750) ? digitalWrite(relayPin, HIGH)
                      : digitalWrite(relayPin, LOW);

  OLED.println();
  // prints new line for spacing
  delay(SENSOR_READ_TIME);
  // waits 1 second before re-checking moisture level
}

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Define inpput and output pins
#define pulsePin 0
#define pulseLED 13

//Define acquisition variables and timers
unsigned long     timer = 0; 
unsigned long     tBeat = 0;
unsigned long     tBeatPrev = 0;

int pulse = 0;
int pulsePrev = 0;
int pulseThresh = 700;
int sampPeriod = 50;                //Sampling period in ms
int beatCount = 0;
float HR = 0.0;

//Define LED display dimensions
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  pinMode(pulseLED,OUTPUT);
  digitalWrite(pulseLED,LOW);
  
  //Initialize LED Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
   delay(2000);
   display.clearDisplay();
  
   display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 20);
  // Display static text
    display.println("Measuring ");
    display.display();
}

void loop() {
  


  if (millis() - timer > sampPeriod) {
      pulsePrev = pulse;
      pulse = analogRead(pulsePin);
      //Serial.println(pulse);


      if (pulse > pulseThresh && pulsePrev < pulseThresh) {
        tBeatPrev = tBeat;
        beatCount++;
        tBeat = millis();
        HR = round(60000.0/(tBeat - tBeatPrev));
        Serial.print(beatCount);
        Serial.print("     ");
        Serial.println(HR);  
        

        //Display the HR on the LED monitor
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0,15);
        display.print("Beat Count: ");
        display.println(beatCount);
        display.setCursor(0,30);
        display.print("Heart Rate: ");
        display.print(int(HR));
        display.println(" bpm");
        display.display();

      }
    
    
    timer = millis();
  }
}

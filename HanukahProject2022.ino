// C++ code
//
#include "Libraries\Adafruit_NeoPixel\Adafruit_NeoPixel.h"
#include "Libraries\ezButton\src\ezButton.h"


#define NUMPIXELS 12
#define PIN 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int potentVal;
int delayval = 100; // timing delay in milliseconds

int songStartTime;

int redColor = 200;
int greenColor = 0;
int blueColor = 0; 

ezButton button(4);

void setup()
{
	pinMode(3,OUTPUT);
  	//pinMode(4,INPUT);
  	pinMode(A0, INPUT);
  	Serial.begin(9600);
    pixels.begin();
  button.setDebounceTime(50); 

}


void setColor() {
  redColor = random(0, 255);

  greenColor = random(0, 255);

  blueColor = random(0, 255);

}

void loop()
{
    button.loop();

  	potentVal = analogRead(A0);
  	analogWrite(3,potentVal);
    
    if(button.isReleased()){
      songStartTime = millis();

      for(int a = 0; a < 5; a++){
       setColor();
       for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
        pixels.setBrightness(100);
        pixels.show();

        delay(delayval);
      }
      }
      for (int i = NUMPIXELS; i >= 0; i--) {
        pixels.setPixelColor(i, pixels.Color(0,0,0));

        pixels.show();

        delay(delayval);        
      }
      
    }
  #pragma region print_stuff
	  Serial.print(digitalRead(4));
  	Serial.print(",");
    Serial.print(potentVal);
    Serial.print("\n");
    #pragma endregion
}
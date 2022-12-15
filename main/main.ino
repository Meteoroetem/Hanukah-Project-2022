// C++ code
//
#include <Adafruit_NeoPixel.h>
#include <ezButton.h>

#define NUMPIXELS 12
#define PIN 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int potentVal;
int delayval = 100; // timing delay in milliseconds

int redColor = 200;
int greenColor = 0;
int blueColor = 0; 

ezButton button(4);

int notes[] = {
  440,
  440,
  494,
  523,
  523,
  494
};
int lengths[] = {
  172,
  78,
  484,
  172,
  109,
  531
};

void setup()
{
	pinMode(3,OUTPUT);
  	//pinMode(4,INPUT);
  	pinMode(A0, INPUT);
  	Serial.begin(9600);
    pixels.begin();
  button.setDebounceTime(10); 
}


void setColor() {
  redColor = random(0, 255);

  greenColor = random(0, 255);

  blueColor = random(0, 255);

}

void loop()
{
    
    button.loop();
    pixels.clear();
  	potentVal = analogRead(A0);
  	analogWrite(3,potentVal);
    
    if(button.isReleased()){
      /*for (int i = 0; i < 3; i++)
      {
        setColor();
        for (int i = 0; i < NUMPIXELS; i++) {
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));

        // This sends the updated pixel color to the hardware.
        pixels.show();

        // Delay for a period of time (in milliseconds).
        delay(delayval);
        }
      }
      for (int i = 0; i < NUMPIXELS; i++)
      {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));

        // This sends the updated pixel color to the hardware.
        pixels.show();

        // Delay for a period of time (in milliseconds).
        delay(delayval);
      }*/

      for (int i = 0; i < sizeof(notes); i++)
      {
        tone(9,notes[i],lengths[i]);
        delay(lengths[i]+10);
      }
      noTone(9);
      
    }
    #pragma region print_stuff
	  Serial.print(digitalRead(4));
  	Serial.print(",");
    Serial.print(potentVal);
    Serial.print("\n");
    #pragma endregion
}
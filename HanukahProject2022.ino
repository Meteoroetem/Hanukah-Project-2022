// C++ code
//
#include <Adafruit_NeoPixel.h>
#include <ezButton.h>


#define NUMPIXELS 16
#define PIN 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int potentVal;
int delayval = 100; // timing delay in milliseconds

int songStartTime = 0;
int notes[] = {440,440,494,523,523,494};
int lengths[] = {500,500,1000,500,500,1000};
float songSpeed = 1.7f;

int redColor = 200;
int greenColor = 0;
int blueColor = 0; 
int currentLed = 0;

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
  	analogWrite(3,255);
    
    if(button.isReleased()){
      songStartTime = millis();
      //tone(9,notes[0]);
      for(int i = 0; i < 6; i++){

        tone(9,notes[i]);

        setColor();
        for (int i = currentLed; i < currentLed+4; i++)
        {
          pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
          pixels.setBrightness(100);
          pixels.show();
          delay(50);
        }
        currentLed += 4;
        if (currentLed >= 16)
        {
          currentLed = 0;
        }
        
       
        
        delay((1/songSpeed)*lengths[i]);
        noTone(9);
        delay(100);
      }
      
      /*for(int a = 0; a < 5; a++){
       setColor();
       for (int i = 0; i < NUMPIXELS; i++) 
       {
        pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
        pixels.setBrightness(100);
        pixels.show();

        delay(delayval);
       }
      }*/
      for (int i = 0; i < NUMPIXELS; i++) {
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
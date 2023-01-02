// C++ code
//
#include <Adafruit_NeoPixel.h>
#include <ezButton.h>


#define NUMPIXELS 24
#define PIN 5
# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int potentVal;
int delayval = 100; // timing delay in milliseconds

int songStartTime = 0;
int notes[] = {440,440,494,523,523,494,659,659,587,523,494,
523,523,494,440,440,494,523,523,587,659,659,659,330,440,
440,440,587,587,587,698,659,659,523,494,440,415,415,330,
415,440,494,523,494,440,587,587,587,698,659,659,523,494,440,415,415,330,415,440,440,440};
int lengths[] = {500,500,1000,500,500,1000,500,500,200,200,500,500,500,1000,500,500,1000
,500,500,1000,500,500,500,500,500,500,1000,500,500,500,500,500,500,200,200,500,500,500,500,
500,500,500,200,200,500,500,500,500,500,500,500,200,200,500,500,500,500,500,500,500,1000};
float songSpeed = 2;

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
  	analogWrite(3,255);
    
    if(button.isReleased()){
      songStartTime = millis();
      //tone(9,notes[0]);
      for(int i = 0; i < my_sizeof(notes)/my_sizeof(notes[0]); i++){
        potentVal = analogRead(A0);
        songSpeed = potentVal/341;
        if(songSpeed < 0.5){
          songSpeed = 0.5;
        }
        tone(10,notes[i]);

        setColor();
        for (int i = currentLed; i < currentLed+4; i++)
        {
          pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
          pixels.setBrightness(15);
          pixels.show();
          delay(50);
        }
        currentLed += 4;
        if (currentLed >= 24)
        {
          currentLed = 0;
        }
        
       
        Serial.println(songSpeed);
        delay((1/(2*songSpeed))*lengths[i]);
        noTone(10);
        //delay(10);
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
      currentLed = 0;
    }
  #pragma region print_stuff
	  Serial.print(digitalRead(4));
  	Serial.print(",");
    Serial.print(analogRead(A0));
    Serial.print("\n");
    #pragma endregion
}
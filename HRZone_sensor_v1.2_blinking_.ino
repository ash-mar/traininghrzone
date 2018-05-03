/*
 Training Heart Rate (HR) Zone Monitor

 This code collects heart rate data from the Adafruit Pulse Sensor and categorizes them into 5 heart rate zones.
 The heart rate zones includes fatburning, cardio, intense and maximum heart rate zone. This zones are calculated based on the Maximum Heart Rate of an individual.
 The maximum heart rate can be calculated by substracting the individual's age from 220. The zones are specficied in terms of percentage of the maximum heart rate.
 For instance,
 Fatburning = 60-70% of Max HR;
 Cardio = 70-80% of Max HR;
 Intense = 80-90% of Max HR;
 Maximum = 90-100% of Max HR;

 When the individual's HR falls into the specific zones, it will cause the Neopixel ring to light up according to the zone he/she is in.
 When individual's HR is close to maximum HR, the Neopixel will color wipe in red and the vibrating motor will be activated indicating the HR is in a dangerous zone and individual needs to slow down. 

 Created 5/1/2018
 By Ashley Hah and Marissa Kuhns

 ENGR375 Bioinstrumentation and Measurement
 Biosensor Project
 Messiah College Department of Engineering
 */

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <Adafruit_NeoPixel.h> //including neopixel library
#include <PulseSensorPlayground.h> //including pulse sensor library
#ifdef __AVR__
  #include <avr/power.h>
#endif

//initializing pulse sensor
const int PulseWire = 10; // initialize pulsensor pin
int pin = 6; // initialize neopixel pin
int Threshold = 500; //determines which signal to count as a beat
const int age = 20; //initializing age for Max HR calculation
const int MaxHR = 220-age; //max HR calculation

//initializing HR zones
//const int recovery = 0.5 * MaxHR; //HR at recovery zone
const int fatburning = 0.6 * MaxHR; //HR at fatburning zone
const int cardio = 0.7 * MaxHR; //HR at cardio zone
const int intense = 0.8 * MaxHR; //HR at intense zone
const int maximum = 0.9 * MaxHR; //HR close to Max HR

int vibrator = 9; //initialize vibrator motor

// Parameter 1 = number of pixels in strip,  neopixel ring has 12
// Parameter 2 = pin number
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGBW     Pixels are wired for RGBW bitstream
//   NEO_KHZ800  800 KHz bitstream, correct for neopixel ring
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, pin, NEO_RGBW + NEO_KHZ800); //initializing neopixel
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

void setup() {
   #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  Serial.begin(9600); //setting serial monitor to the right baud rate

  //Assign initialized varaibles to pulse sensor
  pulseSensor.analogInput(PulseWire); 
  pulseSensor.setThreshold(Threshold);
  
//  pinMode(startbutton, INPUT); //set button is digital input
  pinMode(PulseWire, INPUT); //set pulse sensor as digital output
  pinMode(vibrator, OUTPUT); //set vibrator as digital output

  strip.begin(); 
  strip.setBrightness(30); //brightness setting
  strip.show(); //initialize all pixels to 'off'
 if (pulseSensor.begin()) {
 Serial.println("We created a pulseSensor Object !"); //print "We created a pulseSensor Object !" statement in Serial Monitor"
 }  
}
//initializing colorwipe function
void colorWipe(uint32_t c, uint8_t wait) { //colorwipe fills the dots one after the other with a color
    int i;

  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
void loop() {
//switchState = digitalRead(startbutton); //read state of button
int myBPM = pulseSensor.getBeatsPerMinute(); //initializing myBPM function

if(pulseSensor.sawStartOfBeat()){ ;// Constantly test to see if "a beat happened". 
 Serial.println("Recording");
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: "); // Print phrase "BPM: " 
 Serial.println(myBPM); //Print HR aka beats per minute
//myBPM >= recovery && 
if(myBPM <= fatburning){ //white light on when HR is less than 60% of max HR
  strip.setPixelColor(0,0,0,0,50); //(pin,green,red,blue,white)
  strip.setPixelColor(1,0,0,0,50);
  strip.setPixelColor(2,0,0,0,50);
    strip.show(); //show white light
    delay(10); //for stability
}
   
if(myBPM >= fatburning && myBPM <= cardio){ //white light + blue light on when HR is within 60-70% of Max HR
  strip.setPixelColor(0,0,0,0,50); //(pin,green,red,blue,white)
  strip.setPixelColor(1,0,0,0,50);
  strip.setPixelColor(2,0,0,0,50);
  strip.setPixelColor(3,0,0,50,0);
  strip.setPixelColor(4,0,0,50,0);
  strip.setPixelColor(5,0,0,50,0);
    strip.show(); //show white and blue light
    delay(10); //for stability
 }

if(myBPM >= cardio && myBPM <= intense){ //white light + blue light + green light on when HR is within 70-80% of Max HR
  strip.setPixelColor(0,0,0,0,50); //(pin,green,red,blue,white)
  strip.setPixelColor(1,0,0,0,50);
  strip.setPixelColor(2,0,0,0,50);
  strip.setPixelColor(3,0,0,50,0);
  strip.setPixelColor(4,0,0,50,0);
  strip.setPixelColor(5,0,0,50,0);
  strip.setPixelColor(6,50,0,0,0);
  strip.setPixelColor(7,50,0,0,0);
  strip.setPixelColor(8,50,0,0,0);
    strip.show(); //show white, blue and green light
    delay(10); // for stability
}

if(myBPM >= intense && myBPM <= maximum){ //white light + blue light + green light + red light on when HR 80-90% of Max HR
  strip.setPixelColor(0,0,0,0,50); //(pin,green,red,blue,white)
  strip.setPixelColor(1,0,0,0,50);
  strip.setPixelColor(2,0,0,0,50);
  strip.setPixelColor(3,0,0,50,0);
  strip.setPixelColor(4,0,0,50,0);
  strip.setPixelColor(5,0,0,50,0);
  strip.setPixelColor(6,50,0,0,0);
  strip.setPixelColor(7,50,0,0,0);
  strip.setPixelColor(8,50,0,0,0);
  strip.setPixelColor(9,0,50,0,0);
  strip.setPixelColor(10,0,50,0,0);
  strip.setPixelColor(11,0,50,0,0);
    strip.show(); //show white, blue, green and red light
    delay(10); //for stability
}
  
if(myBPM >= maximum){ //red colorwipe, vibrator activated whrn HR is more than 90% of Max HR
  digitalWrite(vibrator, HIGH); //activate vibratro
  colorWipe(strip.Color(0, 50, 0, 0), 50); //red color wipe
  colorWipe(strip.Color(0, 0, 0, 0), 50);
}
 else{
  colorWipe(strip.Color(0, 0, 0, 0), 50); //turn off color wipe if HR is less than 90% of Max HR
  digitalWrite(vibrator, LOW); //vibrator off when HR is less than 90% of Max HR
  delay (10); //for stability   
}
}
}









  


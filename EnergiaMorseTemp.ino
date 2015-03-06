//
// AnalogInput_InternalThermometer_430
// Analog Input - MSP430 Internal Thermometer
// 
// Demonstrates analog input by reading the internal temperature sensor. 
// 
// This example code is in the public domain.
// based on demo code Created by Robert Wessels
// Modified by Hermann Kurz (hkurz@jruby.de) to use morse code via leds
//
// Revision: 1.0
//   Tested on msp430g2231

#if defined(__MSP430G2452__) || defined(__MSP430G2553__) || defined(__MSP430G2231__) 
#else
#error Board not supported
#endif

int DIT = 200;
int DAH = 3 * DIT;

// uint8_t i = 0;
uint32_t temperature = 0;


void setup() {
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  analogReference(INTERNAL1V5);
  analogRead(TEMPSENSOR); // first reading usually wrong
}

void dot(uint8_t led)
{
  digitalWrite(led, HIGH);
  delay(DIT);
  digitalWrite(led, LOW);
  delay(DIT);  
}

void dash(uint8_t led)
{
  digitalWrite(led, HIGH);
  delay(DAH);
  digitalWrite(led, LOW);
  delay(DIT);
}

// morse a digit on given led
void morseDigit(uint8_t digit, uint8_t led){
  switch(digit) {
     case 0: dash(led); dash(led); dash(led); dash(led); dash(led); break;     
     case 1: dot(led);  dash(led); dash(led); dash(led); dash(led); break;  
     case 2: dot(led);  dot(led);  dash(led); dash(led); dash(led); break; 
     case 3: dot(led);  dot(led);  dot(led);  dash(led); dash(led); break; 
     case 4: dot(led);  dot(led);  dot(led);  dot(led);  dash(led); break;
     case 5: dot(led);  dot(led);  dot(led);  dot(led);  dot(led);  break;
     case 6: dash(led); dot(led);  dot(led);  dot(led);  dot(led);  break;
     case 7: dash(led); dash(led); dot(led);  dot(led);  dot(led);  break;
     case 8: dash(led); dash(led); dash(led); dot(led);  dot(led);  break;
     case 9: dash(led); dash(led); dash(led); dash(led); dot(led);  break;
  }
  // after digit
  delay(DAH); 
}

void morseDec(uint32_t ui) {
  uint8_t led;
// GREEN_LED for negative Temp, RED_LED for positive
  led = GREEN_LED;
  if (abs(ui) == ui) {
    led = RED_LED;
  }    
// display the absolute value even if negative
  ui = abs(ui);
// higher digit
// only if higher digit != 0
  if(((ui/10) % 10)  != 0){ 
    morseDigit((ui/10) % 10, led);
  }
// lower digit  
  morseDigit(ui % 10, led);
  }

// repeat endlessly
void loop() {
    // Formula: http://forum.43oh.com/topic/1954-using-the-internal-temperature-sensor/
    // Temp in C
    temperature = -((uint32_t)analogRead(TEMPSENSOR)*27069 - 18169625)  >> 16;
    morseDec(temperature);
    delay(30 * DAH);
}

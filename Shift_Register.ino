/*     ---------------------------------------------------------
 *     |  Arduino Experimentation Kit Example Code             |
 *     |  CIRC-05 .: 8 More LEDs :. (74HC595 Shift Register)   |
 *     ---------------------------------------------------------
 * 
 * We have already controlled 8 LEDs however this does it in a slightly
 * different manner. Rather than using 8 pins we will use just three
 * and an additional chip.
 *
 *
 */

#define SLIDER1  0

//Pin Definitions
//Pin Definitions
//The 74HC595 uses a serial communication 
//link which has three pins
/* FOR ARDUINO
int data = 2; 
int clock = 3;
int latch = 4;
*/
/*For DANGER SHIELD*/
int data = 4;
int clock = 8;
int latch = 7;
int val = 0;
int patternA[] = {/*LastBreadBoard -->*/1,1,1,1,/**/1,1,1,1,/*FirstBreadBoardBegins-->*/1,1,1,1,/**/1,1,1,1};
int patternB[] = {/*LastBreadBoard -->*/0,0,0,0,/**/1,1,1,1,/*FirstBreadBoardBegins-->*/0,0,0,0,/**/1,1,1,1};
int patternC[] = {/*LastBreadBoard -->*/0,1,1,0,/**/1,0,0,1,/*FirstBreadBoardBegins-->*/0,1,1,0,/**/1,0,0,1};
int num = 16;
//Used for single LED manipulation
int ledState = 0;
const int ON = HIGH;
const int OFF = LOW;
                        

/*
 * setup() - this function runs once when you turn your Arduino on
 * We set the three control pins to outputs
 */
void setup()
{
  Serial.begin(9600);
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);  
  pinMode(latch, OUTPUT);  
}

/*
 * loop() - this function will start after setup finishes and then repeat
 * we set which LEDs we want on then call a routine which sends the states to the 74HC595
 * 
 *    
 *    a=     e=
 *    b=     f=
 *    c=     g=
 *    d=     h=
 */
void loop()                     // run over and over again
{
  int delayTime = 2000; //the number of milliseconds to delay between LED updates              
  //updateLEDs(0); //All off
  //updateLEDs(1); //a ON
  //updateLEDs(2); // b ON
  //updateLEDs(3); //a,b ON
  //updateLEDs(4); // c ON, a,b OFF
  //updateLEDs(5); // a,c ON b OFF
  //updateLEDs(6); // a OFF b,c ON
  //updateLEDs(7); // a,b,c ON
  //updateLEDs(8); // d ON a,b,c OFF
  //updateLEDs(15); // a,b,c,d ON
  //updateLEDs(B11000110); // C  For Danger Shield
  
  updateLEDs(B11001111);// I
  delay(delayTime);
  updateLEDs(B10000010); // G for Danger Shield
  delay(delayTime);  
  //sliderTest();
    
  /*
  updateLEDsPattern(patternA,num);
  delay(delayTime);
  updateLEDsPattern(patternA,num);
  delay(delayTime);
  updateLEDsPattern(patternA,num);
  delay(delayTime);
  */
  /*
  for(int i = 0; i < 256; i++){
   updateLEDs(i);
   delay(delayTime); 
  }
  */
}
int numberGlyphs[] = 
{
  B11000000, //0
  B11111001, //1
  B10100100, //2
  B10110000, //3
  B10011001, //4
  B10010010, //5
  B10000010, //6
  B11111000, //7
  B10000000, //8
  B10011000, //9
  B11111111, //10 - CLEAR
};
void sliderTest(){
  val = analogRead(SLIDER1);
  val = map(val,0,1023,0,9);
  updateLEDs(numberGlyphs[val]);
 
}


/*
 * updateLEDs() - sends the LED states set in ledStates to the 74HC595
 * sequence
 */
void updateLEDs(int value){
  digitalWrite(latch, LOW);     //Pulls the chips latch low
  shiftOut(data, clock, MSBFIRST, value); //Shifts out the 8 bits to the shift register
  digitalWrite(latch, HIGH);   //Pulls the latch high displaying the data
}

/*
 * updateLEDsLong() - sends the LED states set in ledStates to the 74HC595
 * sequence. Same as updateLEDs except the shifting out is done in software
 * so you can see what is happening.
 */ 
void updateLEDsPattern(int value[], int num){
  digitalWrite(latch, LOW);    //Pulls the chips latch low
  
  for(int i = 0; i < num; i++){  //Will repeat 8 times (once for each bit)
  
  digitalWrite(data,value[i]);
  digitalWrite(clock,HIGH);
  delay(1);
  digitalWrite(clock,LOW);
  }
  digitalWrite(latch,HIGH);

  
  /*int bit = value & B10000000; //We use a "bitmask" to select only the eighth 
                               //bit in our number (the one we are addressing this time through
  value = value << 1;          //we move our number up one bit value so next time bit 7 will be
                               //bit 8 and we will do our math on it
  
  if(bit == 128){digitalWrite(data, HIGH);} //if bit 8 is set then set our data pin high
  else{digitalWrite(data, LOW);}            //if bit 8 is unset then set the data pin low
  digitalWrite(clock, HIGH);                //the next three lines pulse the clock pin
  delay(1);
  digitalWrite(clock, LOW);
  }
  digitalWrite(latch, HIGH);  //pulls the latch high shifting our data into being displayed
  */
  
  
  
}


//These are used in the bitwise math that we use to change individual LEDs
//For more details http://en.wikipedia.org/wiki/Bitwise_operation
int bits[] = {B00000001, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000};
int masks[] = {B11111110, B11111101, B11111011, B11110111, B11101111, B11011111, B10111111, B01111111};
/*
 * changeLED(int led, int state) - changes an individual LED 
 * LEDs are 0 to 7 and state is either 0 - OFF or 1 - ON
 */
 void changeLED(int led, int state){
   ledState = ledState & masks[led];  //clears ledState of the bit we are addressing
   if(state == ON){ledState = ledState | bits[led];} //if the bit is on we will add it to ledState
   updateLEDs(ledState);              //send the new LED state to the shift register
 }

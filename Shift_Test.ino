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

//Pin Definitions
//Pin Definitions
//The 74HC595 uses a serial communication 
//link which has three pins
int data = 2; 
int clock = 3;
int latch = 4;

/*
 * setup() - this function runs once when you turn your Arduino on
 * We set the three control pins to outputs
 */
void setup()
{
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);  
  pinMode(latch, OUTPUT);  
}

/*
 * loop() - this function will start after setup finishes and then repeat
 * we set which LEDs we want on then call a routine which sends the states to the 
 * 74HC595
 */
void loop()                     // run over and over again
{
  int delayTime = 100; //the number of milliseconds to delay between LED updates
  for(int i = 0; i < 256; i++){
   updateLEDs(i);
   delay(delayTime); 
  }
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

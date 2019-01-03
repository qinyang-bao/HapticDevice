/* Copy Right: Qinyang Bao 2018 */
/* 
 * This is the arduino code for my URA in 2A term
 * The goal is to output 6 (acceptable range 10KHz - 250KHz) PWM signal, each with adjustable duty cycle, in order to control 6 haptic motor drivers
 */

const byte interruptPin = 2;
// we can have up to 8 patterns in this implementation, however, there can be easily more patterns. 
// Simply modify the update_curr_pattern() function at the end of the file and change the corresponding parts in the setup().
const char NUM_PATTERNS = 8;
volatile unsigned char curr_pattern = 2;
unsigned char curr_sub_pattern = 0;


/* 
 * This is the data structure used to store the pattern in Arduino
 * Each sub pattern corresponds to one time interval in which the duty cycle of all the PWM signals are constant
 * Then, a pattern is simply the collection of as many sub patterns as needed.
 * 
 * I think this is not very intuitive to calculate and understand for humans (but easy to implement on Arduino), 
 * so there is a easier to understand data structure below that is commented out. One might want to write a simple program
 * to convert between the two data structures to make it easier to come up with the patterns.
 */
struct sub_pattern{
  char motor1_dc, motor2_dc, motor3_dc, motor4_dc, motor5_dc, motor6_dc; //duty cycle of motor 1 to 6, from 0 - 255 
  unsigned long len; //length in terms of delay()/millis() input
};

struct pattern{
  char sub_pattern_num;
  sub_pattern* sub_patterns;
};


/* The more humanly readable structure */
/*
 * Here, each sub pattern is one time interval in which the duty cycle of "one" PWM signal is constant;
 * meanwhile, the pattern is made up of six arrays of sub patterns, each describing the behaviour of one
 * PWM signal.
 */
 
/*
struct sub_pattern{
  char duty_cycle; // interms of 0 - 100
  char len // in terms of 1/10 second; 
};

struct pattern{
  sub_pattern* motor1_pattern;
  sub_pattern* motor2_pattern;
  sub_pattern* motor3_pattern;
  sub_pattern* motor4_pattern;
  sub_pattern* motor5_pattern;
  sub_pattern* motor6_pattern;
};
*/

pattern* null_pattern = NULL;
pattern* pattern_1 = NULL;
pattern* pattern_2 = NULL;
pattern* pattern_3 = NULL;
pattern* pattern_4 = NULL;
pattern* pattern_5 = NULL;
pattern* pattern_6 = NULL;
pattern* pattern_7 = NULL;
pattern** patterns = NULL;

void init_patterns(){
  // according to the data sheet http://www.ti.com/lit/ds/symlink/drv2603.pdf, when driving ERM, 
  // 50% duty cycle is 0 motion, 100% is full power, 0% is fulll power in reverse direction
  // we need to hardcode the patterns. THe patterns we have below are simply for testing, except for null_pattern while must exist to make sure 
  // that there is a way to have all motors stopped.

  //null pattern: do nothing (all motor 0% duty cycle)
  null_pattern = new pattern{1, new sub_pattern[1]{sub_pattern{127,127,127,127,127,127, 64000}}};

  //pattern 1: one motor on 100% duty cycle for a second while all other motors on 0% duty cycle, looping through each motor
  pattern_1 = new pattern{6, new sub_pattern[6]{sub_pattern{255,127,127,127,127,127, 64000}, 
                                                sub_pattern{127,255,127,127,127,127, 64000}, 
                                                sub_pattern{127,127,255,127,127,127, 64000}, 
                                                sub_pattern{127,127,127,255,127,127, 64000}, 
                                                sub_pattern{127,127,127,127,255,127, 64000},
                                                sub_pattern{127,127,127,127,127,255, 64000}}};

  // all motors on 50% duty cycle 
  pattern_2 = new pattern{6, new sub_pattern[6]{sub_pattern{191,191,191,191,191,191, 100}}};

  // fill in the patterns
  patterns = new pattern*[NUM_PATTERNS]{null_pattern, pattern_1, pattern_2, pattern_1, pattern_1, pattern_1, pattern_1, pattern_1};
}

/*
 * // This function is simply used for debugging reasons to verify if the patterns are initialized correctly, uncomment if needed
void print_patterns(){
    for (int i=0; i<NUM_PATTERNS; i++){
    Serial.println("New pattern: ");
    Serial.println("Sub-pattern Num:");
    Serial.println( int(patterns[i] -> sub_pattern_num));
    delay (64000);

    for (int j=0; j<patterns[i] -> sub_pattern_num; j++){
      Serial.println("Sub pattern: ");
      Serial.println( int( (patterns[i] -> sub_patterns)[j].motor1_dc));
      delay (64000);
      Serial.println( int( (patterns[i] -> sub_patterns)[j].motor2_dc));
      delay (64000);
      Serial.println( int( (patterns[i] -> sub_patterns)[j].motor3_dc));
      delay (64000);
      Serial.println( int( (patterns[i] -> sub_patterns)[j].motor4_dc));
      delay (64000);
      Serial.println( int( (patterns[i] -> sub_patterns)[j].motor5_dc));
      delay (64000);
      Serial.println( int( (patterns[i] -> sub_patterns)[j].motor6_dc));
      delay (64000);
      Serial.println(long( (patterns[i] -> sub_patterns)[j].len));
      delay (64000);
    }

    Serial.println();
  }
}
*/

/*
 * // This function is simply used for debugging reasons to see what is the current pattern, uncomment if needed
void print_curr_pattern(){
   
  Serial.println(int(curr_pattern));
  Serial.println(int((patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor1_dc));
  delay(64000);
  Serial.println(int((patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor2_dc));
  delay(64000);
  Serial.println(int((patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor3_dc));
  delay(64000);
  Serial.println(int((patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor4_dc));
  delay(64000);
  Serial.println(int((patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor5_dc));
  delay(64000);
  Serial.println(int((patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor6_dc));
  delay(64000);
  
}
*/

void setup() {
  noInterrupts();//stop interrupts
 
  /*
  //setup input and output pins
  // OC0A --- pin 6; OC0B --- pin 5;
  // OC1A --- pin 9; OC1B --- pin 10;
  // OC2A --- pin 11; OC2B --- pin 3

  //pin 4, 8, 12 as input --> use to determine which pattern to set to --> 4, 8, 12 as a binary number, 4 is the MSB
  
  //set pin 3,5,6 as output, without touching pin 0 and pin 1 which are used for serial communication with PC
  //set pin 2, 4 as input
  */

  //access the pinmode register directly and using OR to set the pins, faster than digitalWrite()
  DDRD = DDRD | 0b01101000;
  
  //set pin 9,10,11 as outout
  //set pin 8, 12 as input
  DDRB = DDRB | 0b00001110;
  
  /*
  // configure timers
  // reference:
  // https://cdn.sparkfun.com/assets/c/a/8/e/4/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf, section 19, 20, 21, 22
  // https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328
  // https://www.arduino.cc/en/Tutorial/SecretsOfArduinoPWM
  */

  /////////////////////////////////////////////////////////////////////////////////////////////
  // configure timer 0
  // COM0A1,COM0B1 (1010): set to non-inverted (clear on compare match)
  // (we have COM0A1, COM0A0, COM0B1, COM0B1)
  // WGM01, WGM00 (011): fast pwm
  // (we have WGM02, WGM01, WGM00)
  TCCR0A = _BV(COM0A1) | _BV(COM0B1)| _BV(WGM01) | _BV(WGM00);

  // CS00: no prescaler --- frequency: 16 * 10^6 / 1 / (1 + 255) = 62.5KHz
  TCCR0B = _BV(CS00);

  // set output compare registor to 0 --- duty cycle: (0+1) / 256 ~= 0
  // at the beginning, just set the duty cycle to 0; then change it later based on the pattern
  OCR0A = 0;
  OCR0B = 0;

  //////////////////////////////////////////////////////////////////////////////////////////////
  // configure timer 1
  //COM1A1 and COM1B1 same as in timer 0
  // WGM12 and WGM10 set top at 255 (so the same as timer 0)
  // (have WGM13, WGM12, WGM11, WGM10)
  TCCR1A = _BV(COM1A1) | _BV(COM1B1)| _BV(WGM10);

  // CS10: no prescaler --- frequency: 16 * 10^6 / 1 / (1 + 255) = 62.5KHz
  TCCR1B = _BV(CS10) | _BV(WGM12);

  // set output compare registor to 0 --- duty cycle: (0+1) / 256 ~= 0
  // at the beginning, just set the duty cycle to 0; then change it later based on the pattern
  OCR1A = 0;
  OCR1B = 0;

  ///////////////////////////////////////////////////////////////////////////////////////////
  //configure timer 2
  TCCR2A = _BV(COM2A1) | _BV(COM2B1)| _BV(WGM21) | _BV(WGM20);

  // CS20: no prescaler --- 16 * 10^6 / 1 / (1 + 255) = 62.5KHz
  TCCR2B = _BV(CS20);
  
  OCR2A = 0;
  OCR2B = 0;

  /////////////////////////////////////////////////////////////////////////////////////////

  init_patterns();

  // we attach an interrupt on the rising edge of pin 2
  attachInterrupt(digitalPinToInterrupt(interruptPin), update_curr_pattern, RISING);
  
  interrupts();//resume interrupts

  Serial.begin(9600);

}

// The idea for the main loop is to set the duty cycle for each PWM output based on the current sub pattern of the current pattern, then delay the amount of
// time indicated in the current sub pattern, then go to the next sub pattern of the current pattern. The current pattern would be updated by the interrupt.
void loop() {
  
  // set duty cycle for each motor
  char duty_cycle_1 = (patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor1_dc;
  
  // if duty cycle is 0,we simply set the corresponding pin as input to disable any output, 
  // since in fast pwm, you cannot have 0 duty cycle
  if (duty_cycle_1 == 0){
    //pinMode(6, INPUT); 

    // if the sixth pin is set, unset it by AND with a 0, faster than pinMode
    if ((DDRD >> 6) & 1){
    DDRD &= 0b10111111;
    }  
  }
  else{
    // turn pin 6 backback as output
    DDRD |= 0b01000000;

    //set duty cycle
    OCR0A = duty_cycle_1;
  }

  char duty_cycle_2 = (patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor2_dc;
  if (duty_cycle_2 == 0){
    // pinMode(5, INPUT);
  
    if((DDRD >> 5) & 1){
       DDRD &= 0b11011111;
    }
  } 
  else{
    // turn pin 5 back as output
    DDRD |= 0b00100000;
    OCR0B = duty_cycle_2;
  }

  char duty_cycle_3 = (patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor3_dc;
  if (duty_cycle_3 == 0){
    //pinMode(9, INPUT);
    
    if((DDRB >> 1) & 1){
      DDRB &= 0b11111101;
    }
  } 
  else{
    // turn pin 9 back as output
    DDRB |= 0b00000010;
    OCR1A = duty_cycle_3;
  }

  char duty_cycle_4 = (patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor4_dc;
  if (duty_cycle_4 == 0){
    //pinMode(10, INPUT);
    
    if((DDRB >> 2) & 1){
      DDRB &= 0b11111011;
    }
  } 
  else{
    // turn pin 10 back as output
    DDRB |= 0b00000100;
    OCR1B = duty_cycle_4;
  }

  char duty_cycle_5 = (patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor5_dc;
  if (duty_cycle_5 == 0){
    //pinMode(11, INPUT);
    
    if((DDRB >> 3) & 1){
      DDRB &= 0b11110111;
    }
  } 
  else{
    // turn pin 11 back as output
    DDRB |= 0b00001000;
    OCR2A = duty_cycle_5;
  }

  char duty_cycle_6 = (patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].motor6_dc;
  if (duty_cycle_6 == 0){
    //pinMode(3, INPUT);
    
    if((DDRD >> 3) & 1){
      DDRD &= 0b11110111;
    } 
  } 
  else{
    // turn pin 3 back as output
    DDRD |= 0b00001000;
    OCR2B = duty_cycle_6;
  }


/* Delay()
 *  as timer 1 is used, millis and delay will be affected as following:
 * 0x01: delay(64000) or 64000 millis() ~ 1 second
 * 0x02: delay(8000) or 8000 millis() ~ 1 second
 * 0x03: is the default
 * 0x04: delay(250) or 250 millis() ~ 1 second
 * 0x05: delay(62) or 62 millis() ~ 1 second
 * (Or 63 if you need to round up. The number is actually 62.5)
 * 
 * reference: https://playground.arduino.cc/Main/TimerPWMCheatsheet
 * since we set the prescaler to 1, our delay is 64 times faster
 */
 
  delay( (patterns[curr_pattern] -> sub_patterns)[curr_sub_pattern].len );

  // go to the next sub pattern
  curr_sub_pattern ++;
  if (curr_sub_pattern == patterns[curr_pattern] -> sub_pattern_num)
    curr_sub_pattern = 0;
}


// interrupt for pin 2
// updates the current pattern
void update_curr_pattern(){
  // use the binary value to represent different patterns (0-8), so up to 8 patterns
  // 000 -> pattern 0
  // 001 --> pattern 1
  // ...

  //directly accessing the input register, faster than using digitalRead()
  curr_pattern = char (( ((PIND & 0b00010000) >> 2) | ( (PINB & 0b00000001) << 1) | ((PINB & 0b00010000) >> 4 ) ));
}


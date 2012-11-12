#include "Delay.h"
#include "avr/interrupt.h"
#include "avr/power.h"
#include "avr/sleep.h"

unsigned PROGMEM DelayTime[32] = {
  2560, 2153, 1810, 1522, 1280, 1076,  905,  761, 
   640,  538,  453,  381,  320,  269,  226,  190,
   160,  135,  113,   95,   80,   67,   57,   48,
    40,   34,   28,   24,   20,   17,   14,   12
};
  
byte ColorVal[5];  // variables to equalize the colors (yellow will need more current than blue) Not higher than 25!
byte SpeedVal;      // Set the global display speed (0==slow, 31==fast)
byte FadeN;


ISR(PCINT0_vect) {  // Pin change interrupt for power on by button
  bitClear(GIMSK, PCIE); // Disable further pin change interrupts  
}


byte ddr0,ddr1,ddr2,ddr3,ddr4,ddr5,port0,port1,port2,port3,port4,port5;
#define nop() __asm__ __volatile__ ("nop")


void Fade(byte b) {
  port3 = port2;
  port2 = port1;
  port1 = port0;
  port0 = 1;
  port0 <<= (b>>5);
  ddr3  = ddr2;
  ddr2  = ddr1;
  ddr1  = ddr0;
  ddr0  = (b & 0x1F) | port0;
  for (byte i=0; i<32; i++) {
    for (byte k=18-SpeedVal; k; k--) {
      noInterrupts();
      DDRB  = ddr0;
      PORTB = port0;
      for (byte j=i+1; j; j--) nop();
      DDRB  = ddr1;
      PORTB = port1;
      for (byte j=i+i+33; j; j--) nop();
      DDRB  = ddr2;
      PORTB = port2;
      for (byte j=97-i-i; j; j--) nop();
      DDRB  = ddr3;
      PORTB = port3;
      for (byte j=33-i; j; j--) nop();
      PORTB = 0xFF;  // We end with all outputs high, all leds off
      interrupts();
    }
  }
}


void Fade2(byte b) {
  port5 = port4;
  port4 = port3;
  port3 = port2;
  port2 = port1;
  port1 = port0;
  port0 = 1;
  port0 <<= (b>>5);
  ddr5  = ddr4;
  ddr4  = ddr3;
  ddr3  = ddr2;
  ddr2  = ddr1;
  ddr1  = ddr0;
  ddr0  = (b & 0x1F) | port0;
  for (byte i=0; i<32; i++) {
    for (byte k=18-SpeedVal; k; k--) {
      noInterrupts();
      DDRB  = ddr0;
      PORTB = port0;
      for (byte j=i+1; j; j--) nop();
      DDRB  = ddr1;
      PORTB = port1;
      for (byte j=i+i+33; j; j--) nop();
      DDRB  = ddr2;
      PORTB = port2;
      for (byte j=100; j; j--) nop();
      DDRB  = ddr3;
      PORTB = port3;
      for (byte j=100; j; j--) nop();
      DDRB  = ddr4;
      PORTB = port4;
      for (byte j=97-i-i; j; j--) nop();
      DDRB  = ddr5;
      PORTB = port5;
      for (byte j=33-i; j; j--) nop();
      PORTB = 0xFF;  // We end with all outputs high, all leds off
      interrupts();
    }
  }
}


byte KeyPressed(void) {
  DDRB   = 0;
  PORTB  = 0xFF;
  
  for (byte i=255; i!=0; i--) {
    if (PINB == 0x1F) return 0;
  }
  return 1;
}


void PowerOff(void) {
  DDRB   = 0;               // All pins input
  PORTB  = 0xFF;            // With all pull-ups
  PCMSK  = 0xFF;            // Enable pin change interrupts on all pins
  
  for (byte i=255; i!=0; i--) { // Wait until all input pins are high 255 times in a row (switch has been released)
    if (PINB != 0x1F) i=255;
  }
  
  for (byte i=255; i; i--) {
    if (PINB == 0x1F) {         // only wake up if switch depressed 255 times in a row
      i  = 255;                 // Otherwise, restart counting and go to sleep (again)
      noInterrupts();           // We don't want to service the pin change interrupt until the sleep
                                // instruction has been executed. Otherwise we can sleep forever.
      bitSet(GIFR, PCIF);       // Clear pending interrupts
      bitSet(GIMSK, PCIE);      // Enable all pin change interrupts
      interrupts();
      sleep_cpu();              // Puts the device to sleep
    }
  }
  
  for (byte i=255; i!=0; i--) { // Wait until all input pins are high 255 times in a row (switch has been released)
    if (PINB != 0x1F) i=255;
  }
  
}

byte PROGMEM *RunProgram(byte PROGMEM *pt) {
  byte  Command, Param;
  
  //Serial<<"pt:"<<pt-Main<<"\n";
  while (Command = pgm_read_byte(pt++)) {
    //Serial<<"Loop:"<<pt-Main<<"\n";
    if (KeyPressed()) return NULL;
    Param   = Command & 31;
    Command >>=5;
    switch (Command) {
      case CALL:  // Call subroutine
        RunProgram((byte PROGMEM *)pgm_read_word(&Subroutines[Param]));
        break;
        
      case REPEAT:  // Repeat. Play a frame of ch bytes RepCnt times 
               // If Param==0, set ColorVal from extra byt. Upper 3 bits is channel, lower 5 is value
        { switch (Param) {
            case SETCOLOR:  // repeat 0 times is SetColorVal
              { byte Param2 = pgm_read_byte(pt++);
                byte Color  = Param2 >> 5;
                byte Val    = Param2 & 31;
                switch (Val) {
                  case UP:    ColorVal[Color]++; ColorVal[Color] &= 31; break;
                  case DOWN:  ColorVal[Color]--; ColorVal[Color] &= 31; break;
                  default:    ColorVal[Color] = Val; break;
                }
              }
              break;
              
            case CHAR:
              { byte ch = pgm_read_byte(pt++);
                for (byte i=0; i<TEXTDELAY; i++) {
                  if (!RunProgram(Charset + 6*ch)) return NULL;
                }
                if (!RunProgram(Charset + 6*_SPACE)) return NULL;
                delay(100);
              }
              break;
              
            default: // Normally, we repeat Param times
              { byte PROGMEM *NewPt;
                do {
                  NewPt = RunProgram(pt); 
                  if (!NewPt) return NULL;
                } while (--Param);
                pt = NewPt;  // skip the instruction range we just repeated
              }
              break;
          }
        }
        break;
        
      case SPEED:  // Speed. SpeedVal can be set from 0..31 (logarithmic steps)
                   // Delay after displaying 'our' color is DelayTime[SpeedVal] * ColorVal[Color] / C
        { switch (Param) {
            case UP:    SpeedVal++;         break;
            case DOWN:  SpeedVal--;         break;
            case FADE:  FadeN = 1;          break;
            case NOFADE:FadeN = 0;          break;
            default:    SpeedVal = Param;   break;
          }
          SpeedVal  &=31;  // Keep SpeedVal in range
          //Serial<<"SetSpeed Param: "<<Param<<" SpeedVal: "<<SpeedVal<<"\n";
        }
        break;
        
      default:  // Commands 0..4 are lighting of a number of LEDs from the same color
        if (FadeN) {
          Fade2((Command<<5) | Param);
          if (PINB!=0x1F) {
            byte i;
            for (i=255; i; i++) if (PINB==0x1f) break;
            if (!i) return NULL;
          }
        } else { 
          unsigned long Delay;
          byte          Color = Command;
          Delay = (long)((Param==0 ? AVG_ONTIME : ColorVal[Color]) * pgm_read_word(&DelayTime[SpeedVal]))<<2; 
          //Serial<<Color<<" "<<Param<<" "<<SpeedVal<<" "<<Delay<<"\n";
          noInterrupts();
          PORTB  = (1<<Color);
          DDRB  = Param | (1<<Color);
          interrupts();
          
          if (Param) Command=1;                    // Command is used as delay counter for Off(). For 'normal' colors, this is 1
          while (Command--) delayRealMicroseconds(Delay);
        } 
        break;
    }
  }
  return pt;  // pt now points 1 past the End/EndRep instruction
}

void setup(void) {
  //Serial.begin(115200);
  ADCSRA = 0;    // Disable AD converter
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
  sleep_enable();           // enables the sleep bit in the mcucr register
  power_adc_disable();
  power_usi_disable();
  // delay(1000);
  PowerOff();    // Don't start until we press the button
}


void loop(void) {
  RunProgram(Main);
  if (KeyPressed()) PowerOff();
}




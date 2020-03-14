//ledmatrix7219d88 output example

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "simAVRHeader.h"
#include "io.h"
#include "io.c"
#include "adc.c"
#include "adc.h"
#include "ledmatrix7219d88.h"
#include <stdlib.h>
#include <limits.h>
#include <assert.h>


uint8_t ledmatrix = 0;

	//display test rows
	uint8_t rightrow[8] = {
			0b00000000,
			0b00000000,
			0b00000001,
			0b00000010,
			0b00000100,
			0b10001000,
			0b01010000,
			0b00100000
	};

    uint8_t wrongrow[8] = {
			0b10000001,
			0b01000010,
			0b00100100,
			0b00011000,
			0b00011000,
			0b00100100,
			0b01000010,
			0b10000001
	};

           uint8_t one[8] = {
			0b00010000,
			0b00110000,
			0b01010000,
			0b00010000,
			0b00010000,
			0b00010000,
			0b01111110,
			0b00000000
	};

        uint8_t two[8] = {
			0b11111110,
			0b00000010,
			0b00000010,
			0b11111110,
			0b10000000,
			0b10000000,
			0b11111110,
			0b00000000
	};

        uint8_t three[8] = {
			0b11111110,
			0b00000010,
			0b00000010,
			0b11111110,
			0b00000010,
			0b00000010,
			0b11111110,
			0b00000000
	};

        uint8_t four[8] = {
			0b10000100,
			0b10000100,
			0b10000100,
			0b11111111,
			0b00000100,
			0b00000100,
			0b00000100,
			0b00000000
	};

        uint8_t five[8] = {
			0b11111111,
			0b10000000,
			0b10000000,
			0b11111111,
			0b00000001,
			0b00000001,
			0b11111111,
			0b00000000
	};
          uint8_t six[8] = {
			0b11111110,
			0b10000000,
			0b10000000,
			0b11111110,
			0b10000010,
			0b10000010,
			0b11111110,
			0b00000000
	};
          uint8_t seven[8] = {
			0b11111111,
			0b10000001,
			0b00000001,
			0b00000001,
			0b00000001,
			0b00000001,
			0b00000001,
			0b00000000
	};
          uint8_t eight[8] = {
			0b11111111,
			0b10000001,
			0b10000001,
			0b11111111,
			0b10000001,
			0b10000001,
			0b11111111,
			0b00000000
	};
          uint8_t nine[8] = {
			0b11111111,
			0b10000001,
			0b10000001,
			0b11111111,
			0b00000001,
			0b00000001,
			0b00000001,
			0b00000000
	};
            uint8_t go[8] = {
			0b00000000,
			0b00000000,
			0b11111111,
			0b10001001,
			0b10111001,
			0b10011001,
			0b11111111,
			0b00000000
	};

        



volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. Cprogrammer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0.Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks


void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, butrather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

unsigned int light_on = 0;

unsigned char num_lights = 4;
unsigned char number = 0;
unsigned char leftr = 0;
unsigned char rightr = 0;
unsigned char upr = 0;
unsigned char downr = 0;


unsigned char left = 0;
unsigned char right = 0;
unsigned char up = 0;
unsigned char down = 0;
unsigned char middle = 0;
 


 int score = 5;

/* Get a truly uniform random integer in a range. */

 int addscore() {
        getScore();
   score = score + 1;
        
   return score;
 }
 int deductscore() {
         getScore();
   score = score - 1;
         
   return score;
 }
 

void checkGameStatus(int score) {
  

    if(score == 0) {
        
            ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, wrongrow);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, wrongrow);
	_delay_ms(2000);   
            score = 0;
    
   }
   
 
    if(score == 1) {
        
            ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, one);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, one);
	_delay_ms(2000);   
            
    }

    if(score == 2) {
        
            ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, two);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, two);
	_delay_ms(2000);   
            
    }

  if (score == 3) {
            ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, three);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, three);
	_delay_ms(2000);
    } 
    
  if (score == 4) {
            ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, four);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, four);
	_delay_ms(2000);
    }    
    
  if (score == 5) {
            ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, five);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, five);
_delay_ms(2000);
    } 

  if (score == 6) {
            ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, six);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, six);
	_delay_ms(2000);
    } 

  if (score == 7) {
            ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, seven);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, seven);
	_delay_ms(2000);
    } 

  if (score == 8) {
            ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, eight);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, eight);
	_delay_ms(2000);
    } 

  if (score == 9) {
            ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, nine);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, nine);
	_delay_ms(2000);
    } 

  if (score == 10) {
            ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, wrongrow);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, wrongrow);
	_delay_ms(2000);
    } 



}


int getScore() {
        return score;
}

void setScore(int SCORE) {
        score = SCORE;
}


enum States{init, user_input} state;
void Joystick_Tck() {
        ADC_Init();
        int x = ADC_Read(0);
        int y = ADC_Read(1);
        int xy = ADC_Read(2);
   switch(state){

    
    case user_input:
       if(x<400) { //went left
        PORTB = 8;
                left = 1;

                down = 0;
                right = 0;
                up = 0;
                middle = 0;
                                state = user_input;
      }
      else if(x>600) { //went right
        PORTB = 16;
                right = 1;

                down = 0;
                left = 0;
                up = 0;
                middle = 0;
                
                                state = user_input;
      }
      else if(y>600) { //went down
          PORTB = 2;
                down = 1;

                right = 0;
                left = 0;
                up = 0;
                middle = 0;
                                state = user_input;
      }
      else if(y<400) { //went up
          PORTB = 4;
                up = 1;

                right = 0;
                left = 0;
                down = 0;
                middle = 0;
                                state = user_input;
      }
     else {  //middle
        PORTB = 1;
                middle = 1;

                right = 0;
                left = 0;
                down = 0;
                up = 0;
        state = user_input;
     }
     break;

                default:
                        state = user_input;
                        break;
   }

        switch (state) { //actions

                case user_input:
                break;
                default:
                        break;
        }


}



enum LED_States {resetGame, RandomizeLights} LED_State;

void Loop()
{
        //unsigned char start_btn= 0;
        //unsigned char restart_button = 0;
           
        //restart_button = ~PINC & 0x02;


        switch(LED_State) {
                case resetGame:
              //score = 5;
               
                LED_State = RandomizeLights;
               // LED_State = RandomizeLights;
                break;    

              case RandomizeLights: 
                break;

               default:
               state = resetGame;
               break;
        }

        switch(LED_State) {
                case resetGame:
                 ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, five);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, five);
//_delay_ms(2000);
              score = 5;
                break;
       
                case RandomizeLights:
            
                    light_on = rand() % 3;
                  
                  
                        if(light_on == 0) { //up
                                  upr = 1;
                                  
                                  rightr = 0;
                                  leftr = 0;
                                  downr = 0;
                                   
                                                                                        PORTD = 1;
                                                                                        if (score > 0) {
                                          state = RandomizeLights;
                                 }
                            if(score == 0) {
                                    ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                               //   _delay_ms(2000);
                          score = 5;
                        }
                          if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                               //   _delay_ms(2000);
                          score = 5;
                        }
                         
                            
                        }
                        else if(light_on == 1) { //left
                                  leftr = 1;
                                  
                                   rightr = 0;
                                   downr = 0;
                                    upr = 0;
                                                                PORTD = 16;
                                                                if (score > 0) {
                                          state = RandomizeLights;
                                 }
                              if(score == 0) {
                                      ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                             //     _delay_ms(2000);
                          score = 5;
                        }
                          if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                              //    _delay_ms(2000);
                          score = 5;
                        }
                            
                             
                        }

                        
                        else if(light_on == 2) { //down
                                 downr = 1;
                                 
                                 rightr = 0;
                                 leftr = 0;
                                 upr = 0;

                                    
                        
                                                                PORTD = 32;
                                                                if (score > 0) {
                                          state = RandomizeLights;
                                 }
                               if(score == 0) {
                                       ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                              //    _delay_ms(2000);
                          score = 5;
                        }
                          if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                              //    _delay_ms(2000);
                          score = 5;
                        }
                         
                        }
                        else if(light_on == 3) { //right
                                rightr = 1;

                                upr = 0;
                                downr = 0;
                                leftr = 0;
                                
                           
                                
                                                                PORTD = 64;
                                                                if (score > 0) {
                                          state = RandomizeLights;
                                 }
                               if(score == 0) {
                                       ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                                //  _delay_ms(2000);
                          score = 5;
                        }
                          if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                               //   _delay_ms(2000);
                          score = 5;
                        }
                        
                             
                        }	
                       
 if(leftr == 1 && left == 1) {
                                
                              
                                score = addscore();
                                checkGameStatus(score);
                                if (score > 0) {
                                          state = RandomizeLights;
                                 }
                                if(score == 0) {
                                        ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                                 // _delay_ms(2000);
                          score = 5;
                        }
                          if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                               //   _delay_ms(2000);
                          score = 5;
                        }
                        
                                
                        }
                         if(rightr == 1 && right == 1) {
                                
                               
                                score = addscore();
                                checkGameStatus(score);
                                if (score > 0) {
                                          state = RandomizeLights;
                                 }
                                if(score == 0) {
                                        ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                              //    _delay_ms(2000);
                          score = 5;
                        }
                          if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                             //     _delay_ms(2000);
                          score = 5;
                        }
                        }
                         if(upr == 1 && up == 1) {
                                
                              
                               score = addscore();
                                checkGameStatus(score);
                                if (score > 0) {
                                          state = RandomizeLights;
                                 }
                                if(score == 0) {
                                        ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                             //     _delay_ms(2000);
                          score = 5;
                        }
                          if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                             //     _delay_ms(2000);
                          score = 5;
                        }
                         
                                
                        }
                         if(downr == 1 && down == 1) {
                                
                             
                                score =addscore();
                                checkGameStatus(score);
                                if (score > 0) {
                                          state = RandomizeLights;
                                 }
                                 if(score == 0) {
                                         ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                              //    _delay_ms(2000);
                          score = 5;
                        }
                          if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                               //   _delay_ms(2000);
                          score = 5;
                        }
                        
                                
                        }

                        if(upr == 1 && (down == 1 || right == 1 || left ==1)) {
                                score = deductscore();
                                checkGameStatus(score);
                                if (score > 0) {
                                          state = RandomizeLights;
                                 }
                                 if(score == 0) {
                                         ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                            //      _delay_ms(2000);
                          score = 5;
                        }
                          if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                            //      _delay_ms(2000);
                          score = 5;
                        }
                         
                        }
                        if(downr == 1 && (up == 1 || right == 1 || left ==1)) {
                                score = deductscore();
                                checkGameStatus(score);
                                if (score > 0) {
                                          state = RandomizeLights;
                                 }
                               if(score == 0) {
                                       ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                            //      _delay_ms(2000);
                          score = 5;
                        }
                          if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                             //     _delay_ms(2000);
                          score = 5;
                        }
                        
                        }
                        if(rightr == 1 && (down == 1 || up == 1 || left ==1)) {
                                score = deductscore();
                                checkGameStatus(score);
                                if (score > 0) {
                                          state = RandomizeLights;
                                 }
                                if(score == 0) {
                                        ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                             //     _delay_ms(2000);
                          score = 5;
                        }
                          if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                             //     _delay_ms(2000);
                          score = 5;
                        }
                        

                        }
                        if(leftr == 1 && (down == 1 || right == 1 || up ==1)) {
                                score = deductscore();
                                checkGameStatus(score);
                                 if (score > 0) {
                                          state = RandomizeLights;
                                 }

                         if(score == 0) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                             //     _delay_ms(2000);
                          score = 5;
                        }
                         if(score == 7) {
                                  ledmatrix = 0;
	                          ledmatrix7219d88_setmatrix(0, five);
	                          ledmatrix = 1;
	                          ledmatrix7219d88_setmatrix(1, five);
                             //     _delay_ms(2000);
                          score = 5;
                        }
                         
                        
                        }
        
                      
                  
                  

   
                       break;
                default:
                state = resetGame;
                break;
        }

        

}

int main()
{
        //woo
    DDRB = 0xFF;
    PORTB = 0x00;
	DDRD = 0xFF; // Set port B to output
	PORTD = 0x00; // Init port B to 0s
        DDRC = 0xFF; //input
        PORTC = 0x00;

         unsigned long JOY_elapsedTime = 50;
         unsigned long RANDOM_elapsedTime = 100;
         const unsigned long timerPeriodJ = 50;
        // unsigned char button = ~PINC & 0x01;

        ledmatrix7219d88_init();
ledmatrix7219d88_init();
          ledmatrix = 0;
	ledmatrix7219d88_setmatrix(0, five);
	ledmatrix = 1;
	ledmatrix7219d88_setmatrix(1, five);
	_delay_ms(2000);
         
	
       
        
TimerSet(30);
TimerOn();
 
	while(1) {
		// User code (i.e. synchSM calls)
	if (JOY_elapsedTime >= 50 ) {
                Joystick_Tck();
            JOY_elapsedTime = 0;
       }
        if (RANDOM_elapsedTime >= 100 ) {
                Loop();
                RANDOM_elapsedTime = 0;
        }
      
        
       
          while (!TimerFlag); // Wait 1 sec
		   TimerFlag = 0;
                  JOY_elapsedTime += timerPeriodJ;
                   RANDOM_elapsedTime += timerPeriodJ;
		// Note: For the above a better style would use a synchSM with TickSM()
		// This example just illustrates the use of the ISR and flag
	}
     

        
        
}

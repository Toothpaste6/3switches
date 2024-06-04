// 3switches.c utilizes the arduino uno, 2 LEDs, and 3 push buttons. 2 blink only their respective LEDs, and the thrid blinks both
// W. Stone 4/11/2024 Initial code created for Lab8.1 Umass ECE231 Spring 2024 

#include <avr/io.h>
#include <util/delay.h>
#define REDBUTTON PD3   // Arduino Uno pin 3
#define GREENBUTTON PD4 // Arduino Uno pin 4
#define BOTHBUTTON PD5  // Arduino UNo pin 5
#define REDLED PD6      // Arduino Uno pin 6
#define GREENLED PD7    // Arduino Uno pin 7
#define DELAY 200       //Delay of 200ms

int main(void){
    unsigned char r_button, g_button, both;
    DDRD = 1<<REDLED|1<<GREENLED;           // Set as outputs
    PORTD = 1<<REDBUTTON|1<<GREENBUTTON|1<<BOTHBUTTON;    // Enable internal pull-ups
                   
    while(1){

        r_button = (PIND & (1<<REDBUTTON));     // 1 when not pressed
        g_button = (PIND & (1<<GREENBUTTON));   // 0 when pressed
        both = (PIND & (1<<BOTHBUTTON));

        if  (r_button){
            PORTD &= ~(1<<REDLED);      // Off when button not pressed
        } else {
            if (g_button){
                if (both){
                    PORTD |= (1<<REDLED);       // On when pressed
                    _delay_ms(DELAY);
                    PORTD &= ~(1<<REDLED);      // Off when button not pressed
                    _delay_ms(DELAY);
                }
            }
        }

        if  (g_button){                 
            PORTD &= ~(1<<GREENLED);     // Off when not pressed
        } else {
            if (r_button){
                if(both){
                    PORTD |= (1<<GREENLED);       // On when pressed
                    _delay_ms(DELAY);
                    PORTD &= ~(1<<GREENLED);     // Off when not pressed
                    _delay_ms(DELAY);
                }
            }
        }

        if  (both){                 
            PORTD &= ~(1<<GREENLED);     // Off when not pressed
            PORTD &= ~(1<<REDLED);
        } else {
            if (r_button){
                if(g_button){
                    PORTD |= (1<<GREENLED)|(1<<REDLED);       // On when pressed
                    _delay_ms(DELAY);
                    PORTD &= ~(1<<GREENLED);     // Off when not pressed
                    PORTD &= ~(1<<REDLED);
                    _delay_ms(DELAY);
                }
            }
        }
    }
}
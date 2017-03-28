#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
 * Code is from here:https://www.newbiehack.com/MicrocontrollerControlAHobbyServo.aspx
    * Hesistant bcause I am supposed to use port D. But we all know I can't get PWM out of it... so we shall see how this goes
 
 This helped me think why we need 16bit not 8 bit timers!
 http://www.embedds.com/controlling-servo-motor-with-avr/
 //code from embedds. oculdnt get it to work. even output a signal
 NOTES:
 - 16 bit timer1
 MODE14 - FAST PWM that specifies a maximum, 635535 in decimal 0xFFFF in hex store in OCR1A or ICR1 register
 GAVE UP on this one, tryign another, didn't explain how they got the ICR1 value,
 
 
 More NoteS:
 From here:
 http://extremeelectronics.co.in/avr-tutorials/servo-motor-control-by-using-avr-atmega32-microcontroller/
 explains how 4999 was chosen for ICR1 = Top Value = 4999 this is based on 16 Mhz.
 we have 8Mhz and i don't know wy they use a 64 prescaler, but we will too. 
 our top should be 2499. For ICR1
 
 More Notes:
 Gave up on extreme electronics. I cant find how to set up 16bit mode 14 FAst PWM for 328p. Its for atmega32
 Trying htis now: https://mil.ufl.edu/5666/handouts/ATMPWM.pdf
 phase correct mode. 
 ICRn (n is the timer number) is the maximum we are using tiemr 1 so 
 ICR1 is our max value. 
 we need system clock speed (8MHz) and timer1 clock speed (system divided by a presclaler)
 //pre scaler is set by the CSn bits in the TCCRn register n is the number again.
 ICR1 is the 50hz pwm signal
 OCR1A is ther servo A using timer 1
 
 */

//We need to use the 16bit register. makes sensesince we  are dealing iwth numbers bigger than 255!
// FAST pwm and we will use a top value! justl ike OCR1A for 8 bit

int main(void) {
    DDRB |= _BV(PB1);
    TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
    TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS11;
    ICR1 = 9999; //need this!!! to get to be the correct 16bit. fuckkkkk
    //the math to get that is you do 50hz = system clock/ (2*prescale (i used 8) * TOP) and TOP = IC1 thi is from the Mil.ufl link! works.
    
//
    for(int i= 0; i<=10; i++){
        _delay_ms(500);
    OCR1A = ICR1 - 2000; //18000
    
    _delay_ms(500);
    
    OCR1A = ICR1 - 1000; //1000 milisecond
           _delay_ms(500);
        
    }

	while (1) {
        //OCR1A =100;
        
        
//        ICR1 - 800;
//        _delay_ms(100);
//        OCR1A = ICR1 - 2200;
//        _delay_ms(100);
	}
	return 0; // never reached
}

/*
code from newbie hack
couldn't get an output of any kind.
and kept getting ICR1a not defined
int main(void)
{
    
    DDRD |= 0xFF;
    TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
    TCCR1B |= 1<<WGM13 |
    1<<WGM12 | 1<<CS10;
    ICR1 = 2499;
    
    OCR1A = ICR1 - 2000; //18000
    
    while (1)
    {
    }
}


*/

//using this code from Mil. UFL

/*

int main()
{
//    DDRD |= _BV(PD6);// set 6 to ouput
//    TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10;
//    TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10;
//    ICR1 = 2499; //for 50hz given that 8Mhz clock
//    OCR1A = 19999;

//    DDRD |= 0xFF;
//
//    TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (1<<WGM11) | (0<<WGM10);
//    TCCR1B=(0<<ICNC1) | (0<<ICES1) | (1<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
//    TCNT1H=0x00;
//    TCNT1L=0x00;
//    ICR1H=0x9C;
//    ICR1L=0x3F;
//    OCR1AH=0x0B;
//    OCR1AL=0xB8;
//    OCR1BH=0x00;
//    OCR1BL=0x00;
//        
    

        
        
        while (1)
        {
            // we have a working Timer
        }
    
    
    
}*/

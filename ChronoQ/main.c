/*
 * File:   main.c
 * Author: 7Robot
 *
 * Created on 15 septembre 2014, 20:06
 */

//configuration

//#pragma config XINST = OFF
//#pragma config FOSC = INTIO2



#include <stdio.h>
#include <stdlib.h>
#include <p18f25k80.h>
#include <xc.h>
#include <timers.h>
#include <p18cxxx.h>

////////////////////////////////////DEFINE /////////////////////////////////
#define SegmentA PORTBbits_t.PORTB7
#define SegmentB PORTBbits_t.PORTB6
#define SegmentC PORTBbits_t.PORTB5
#define SegmentD PORTBbits_t.PORTB4
#define SegmentE PORTBbits_t.PORTB3
#define SegmentF PORTBbits_t.PORTB2
#define SegmentG PORTBbits_t.PORTB1
#define SegmentH PORTBbits_t.PORTB0
#define USE_OR_MASKS
#define Afficheur1 PORTAbits_t.PORTA1
#define Afficheur2 PORTAbits_t.PORTA2
#define Afficheur3 PORTAbits_t.PORTA3
#define Afficheur4 PORTAbits_t.PORTA4
#define Afficheur5 PORTAbits_t.PORTA5


////////////////////////////////////////////////////////////////////////////




char dixieme_millisecondes = 0;
int millisecondes = 0;
int secondes = 0;
int test = 1;
int counter =0;
//Main Interrupt Service Routine (ISR)
void interrupt ISR()
{
   //Check if it is TMR0 Overflow ISR

   if(TMR0IE && TMR0IF)
   {
      //TMR0 Overflow ISR
      counter++;  //Increment Over Flow Counter

      if(counter==3)
      {

        PORTB=0b11111111;

         counter=0;  //Reset Counter
      }
      else
      {
          PORTB=0b00000000;
      }
      //Clear Flag
      TMR0IF=0;
   }
}


int main(int argc, char** argv) {

    //----Configure Timers----

    INTCON  =  0b11100000;

    TRISB = 0; // mets les ports B en sortie
    TRISA = 0; // mets les ports A en sortie

    // Configuration du timer0 pour la persistance retinienne



       //Setup Timer0
   T0PS0=1; //Prescaler is divide by 256
   T0PS1=1;
   T0PS2=1;
   PSA=0;      //Timer Clock Source is from Prescaler

   T0CS=0;     //Prescaler gets clock from FCPU (5MHz)

   T08BIT=1;   //8 BIT MODE

   TMR0IE=1;   //Enable TIMER0 Interrupt
   PEIE=1;     //Enable Peripheral Interrupt
   GIE=1;      //Enable INTs globally
   TMR0ON=0;      //Now start the timer!


    while (1) {

        for (int i =0 ; i<50;i++){}
    }

    return (EXIT_SUCCESS);
}

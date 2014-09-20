/*
 * File:   main.c
 * Author: 7Robot
 *
 * Created on 15 septembre 2014, 20:06
 */

//configuration

#pragma config XINST = OFF
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
#define Afficheur1 PORTAbits_t.RA1
#define Afficheur2 PORTAbits_t.RA2
#define Afficheur3 PORTAbits_t.RA3
#define Afficheur4 PORTAbits_t.RA4
#define Afficheur5 PORTAbits_t.RA5


////////////////////////////////VARIABLES GLOBALES////////////////////////////////////////////


char dixieme_millisecondes = 0;
int millisecondes = 0;
int secondes = 0;
char balayage = 0;


void rafraichissement (int);







//Main Interrupt Service Routine (ISR)
void interrupt low_interrupt()
{
   //Check if it is TMR0 Overflow ISR
   if(TMR0IE && TMR0IF)
   {
      //TMR0 Overflow ISR
       if (balayage ==4)
       {
           balayage = 0;
       }
       else
       {
           balayage++;  //Increment Over Flow Counter
       }
       
       rafraichissement(balayage);
      //Clear Flag
      TMR0IF=0;
   }
}



int main(int argc, char** argv) {

    ///////////////////////CONFIGURATION///////////////////////////////////////////
    INTCON  =  0b11100000;
    TRISB = 0; // mets les ports B en sortie
    TRISA = 0; // mets les ports A en sortie


       //Setup Timer0 la persistance retinienne
   T0PS0=1; //Prescaler is divide by 256
   T0PS1=1;
   T0PS2=1;
   PSA=0;      //Timer Clock Source is from Prescaler
   T0CS=0;     //Prescaler gets clock from FCPU (5MHz)
   T08BIT=1;   //8 BIT MODE
   TMR0IE=1;   //Enable TIMER0 Interrupt
   PEIE=1;     //Enable Peripheral Interrupt
   GIE=1;      //Enable INTs globally
   TMR0ON=1;      //Now start the timer!

       //setup Timer2
   
    while (1) {
    }

    return (EXIT_SUCCESS);
}


void rafraichissement (int afficheur)
{

       
    switch(afficheur)
    {
        case 0 :    PORTA =0b00000001; break;
        case 1 :    PORTA =0b00000010; break;
        case 2 :    PORTA =0b00000100; break;
        case 3 :    PORTA =0b00001000; break;
        case 4 :    PORTA =0b00100000; break;
        default : ;
    }
}

//intcon tmr4IP IPRX
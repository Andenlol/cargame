/*
 * main.c
 *
 * by André Lindgren and Alexander Nordström
 * Created 2018-02-20
 * Last changed 2018-03-05	
 *
 */

#include <pic32mx.h>
#include <stdint.h>
#include <stdlib.h>
#include "gameHeader.h"

// stdlib needs this
void* stdout;

// Code copied from https://github.com/is1200-example-projects
// See file COPYING for copyright
void pins_init(void) {
	// Potentiometer init
	/* PORTB.2 is analog pin with potentiometer*/
	AD1PCFG = ~(1 << 2);
	TRISBSET = (1 << 2);
	/* Use pin 2 for positive */
	AD1CHS = (0x2 << 16);
	
	/* Data format in uint32, 0 - 1024
	Manual sampling, auto conversion when sampling is done
	FORM = 0x4; SSRC = 0x7; CLRASAM = 0x0; ASAM = 0x0; */
	AD1CON1 = (0x4 << 8) | (0x7 << 5);
	
	AD1CON2 = 0x0;
	AD1CON3 |= (0x1 << 15);
	
	//Dont need
	/* Set up output pins */
	ODCE = 0x0;
	TRISECLR = 0xFF;
	
	/* Turn on ADC */
	AD1CON1 |= (0x1 << 15);		


	// SPI init
	/* Set up peripheral bus clock */
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;

	/* ODC
	 * For outputs pin only. 
	 * 0: for normal digital output 
	 * 1: For higher then VDD voltage (For our use all should be 0)
	 */
	ODCE = 0x0;     
	TRISECLR = 0xFF; // TRISE xxxx 0000 0000 (outputs)
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;   // PORTF 1111 1111 1111 1111
	PORTG = (1 << 9); // PORTG 0001 0000 0000
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;  // TRISF xxxx x000 xxxx (outputs)
	TRISGCLR = 0x200; // TRISG xx0x xxxx xxxx (outputs)
	
	/* Set up input pins */
	TRISDSET = (1 << 8); // TRISD xxxx 1xxx xxxx (inputs)
	TRISFSET = (1 << 1); // TRISF xxxx xxxx xxx1 (inputs)
	
	/* Set up SPI as master */
	SPI2CON = 0; // 0000 0000 0000
	SPI2BRG = 4;
	
	/* Clear SPIROV*/
	SPI2STATCLR &= ~0x40;
	/* Set CKP = 1, MSTEN = 1; */
    SPI2CON |= 0x60; // SPI2CON = 0110 0000
	
	/* Turn on SPI */
	SPI2CONSET = 0x8000; // SPI2CON = 1000 0000 0110 0000


	// Timer init
	T2CON = 0x070;
	TMR2 = 0x0;
	PR2 = (80000000 / 256) / 100; // 100 times per second
	IFS(0) = 0;
	T2CONSET = 0x8000;
}

// For polling timer
int timerEnd(void) {
	if(IFS(0) & 0x0100) {
		IFS(0) = 0;
		return(1);
	}
	else {
		return(0);
	}
}

int main (void) {
	pins_init();
	display_init();
	mainMenu();
	return 0;
}



/*
 * main.c
 *
 * Created: 03.04.2017 16:12:09
 *  Author: p2x93
 */ 

#include <avr/io.h>

#define FOSC 1000000 //Clock speed
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int ubrr) {
	//Set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//Enable receiver and transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	//Set frame format: 8data, 2stop bit
	UCSR0C = (3<<UCSZ00);
}

void USART_Transmit (unsigned char data) {
	//Wait for empty transmit buffer
	while ( !(UCSR0A & (1<<UDRE0)));
	
	//Put data into buffer, sends the data
	UDR0 = data;
}

int main(void) {
	//usart initialization function
	
	USART_Init(MYUBRR);
	
	while(1) {
		//Transmit HELLO to terminal
		
		USART_Transmit('H');
		USART_Transmit('E');
		USART_Transmit('L');
		USART_Transmit('L');
		USART_Transmit('O');
		USART_Transmit('!');
		USART_Transmit('\r');
		USART_Transmit('\n');
	}
}
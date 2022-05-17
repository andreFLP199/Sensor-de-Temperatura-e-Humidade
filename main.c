/*
 * TP3.c
 *
 * Created: 13/05/2022 11:26:22
 * Author : 20091
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "OS.h"
#define DHT11_PIN 7

uint32_t counter = 0;
uint16_t temp= 0;
char conver[10]={N0,N1,N2,N3,N4,N5,N6,N7,N8,N9};

void Request() /* Microcontroller send start pulse/request */
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN); /* set to low pin */
	_delay_ms(20); /* wait for 20ms */
	PORTD |= (1<<DHT11_PIN); /* set to high pin */
}

void Response() /* receive response from DHT11 */
{
	DDRD &= ~(1<<DHT11_PIN);
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

uint8_t Receive_data() /* receive data */
{
	for (int q=0; q<8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0); /* check received bit */
		_delay_us(30);
		if(PIND&(1<<DHT11_PIN))/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01); /* then its logic HIGH */
		else /* otherwise its logic LOW */
		c = (c<<1);
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}


void write(void){
	
	temp= counter;
	sel0;
	PORTD=conver[temp %10];
	sel4;
	temp= temp /10;
	//_delay_ms(5);

	
	sel0;
	PORTD=conver[temp %10];
	sel3;
	temp= temp /10;
	//_delay_ms(5);
	
	sel0;
	PORTD=conver[temp %10];
	sel2;
	temp= temp /10;
	_delay_ms(20);
	
	sel0;
	PORTD=conver[temp %10];
	sel1;
	temp= temp /10;
	_delay_ms(5);
	
}







int main(void)
{
	DDRD = 0xFF;
	DDRB = 0B00001111;
	char estadoBTN = SOLTO;
	char mostra = 1;
	char arrayt = 0;
	char ponteiro = 0;
	uint16_t array1[16];
	uint16_t array2[16];
	uint32_t sum1=0;
	uint32_t sum2=0;
	
	
	while(1)
	{
		if(BTNisPressed){
			estadoBTN = PRESSED;
		}
		if((BTNisPressed) == SOLTO && estadoBTN == PRESSED){
			if(mostra==1){
				mostra = 0;
			}
			else{mostra=1;}
			
			estadoBTN=SOLTO;
		}
		Request(); /* send start pulse */
		Response(); /* receive response */
		I_RH=Receive_data(); /* store first eight bit in I_RH */
		D_RH=Receive_data(); /* store next eight bit in D_RH */
		I_Temp=Receive_data(); /* store next eight bit in I_Temp */
		D_Temp=Receive_data(); /* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */
		
		_delay_ms(20);
		
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			/*ERRO*/
			
		}
		else
		{
			/* ATUALIZA DISPLAY */
			array1[ponteiro]= I_Temp*100+D_Temp*10;
			array2[ponteiro]= I_RH*100+D_RH*10;
			if (ponteiro>=9){
				ponteiro = 0;
			}else{ponteiro++;}
			
		}
		_delay_ms(20);
		sum1=0;
		sum2=0;
		for (char i=0; i<9; i++){
			sum1+=array1[i];
			sum2+=array2[i];
		}
		if (mostra==1){
			counter = sum1/10;
		}
		else{
			counter = sum2/10;
		}
		write();
	}
}

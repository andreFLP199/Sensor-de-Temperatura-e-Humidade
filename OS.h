/*
 * OS.h
 *
 * Created: 13/05/2022 11:36:31
 *  Author: 20091
 */ 


#ifndef OS_H_
#define OS_H_

#define D0 0xFF
#define D1 0B11111110
#define D2 0B11111101
#define D3 0B11111011
#define D4 0B11110111

#define sel0 (PORTB = D0)
#define sel1 (PORTB = D1)
#define sel2 (PORTB = D2)
#define sel3 (PORTB = D3)
#define sel4 (PORTB = D4)

#define NC 0B00000000
#define N0 0B00111111
#define N1 0B00000110
#define N2 0B01011011
#define N3 0B01001111
#define N4 0B01100110
#define N5 0B01101101
#define N6 0B01111101
#define N7 0B00000111
#define N8 0B01111111
#define N9 0B01101111

#define BTN 4
#define BTNisPressed (PINB & (1<<BTN))
#define BTN_DOWN 5
#define BTN_DOWNisPressed (PINB & (1<<BTN_DOWN))

#define MAX 9999
#define MIN 0000


#define SOLTO 0
#define PRESSED 1




#endif /* OS_H_ */
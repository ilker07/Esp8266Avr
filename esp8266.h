#ifndef ESP8266_H
#define ESP8266_H

#include <Arduino.h>


//#define USART_BAUDRATE 9600
#define UBRR_VALUE 8 //(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void usartBasla(void);
void usartGonder(String veri);
void kurulum(String deger,int sure);





#endif

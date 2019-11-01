#include "esp8266.h"
#include <util/delay.h>
#include <Arduino.h>

void usartBasla(void)
{
UBRR0H=(uint8_t)(UBRR_VALUE>>8);
UBRR0L=(uint8_t)UBRR_VALUE;
UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);//8 bit veri için
UCSR0B |= (1<<RXEN0)|(1<<TXEN0)  ;
}

void usartGonder(String veri)
{

 uint16_t i;
 for(i=0;i<veri.length();i++)
  {
    
    while(!(UCSR0A&(1<<UDRE0))){}
    UDR0 = veri[i] ;
  }

}


void kurulum(String deger,int sure)
{

   usartGonder(deger);
  while(sure--) {
    _delay_ms(1);

  }

}

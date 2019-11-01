#include "esp8266.h"  
#include <avr/io.h>
#include <util/delay.h>


uint8_t i=0;
String kelime="";
char data;
boolean geldi=false;
boolean temizlendi=false;




ISR(USART_RX_vect)
{  

  data=char(UDR0);
  kelime +=data;
 
   if(kelime.indexOf("IPD")>=0)
   {
    kelime="";
    geldi=true;
    temizlendi=true;
   }

   if(temizlendi)
   {
    i++;
    if(i>30)  //IPD yi yakaladıktan sonra 30 veri al.
    {
      i=0;
      temizlendi=false;
      UCSR0B &=~(1<<7);
      
    }
   }
  
}



int main()
{
  DDRD |=(1<<7);  //led output

  
  usartBasla();

  
  kurulum("AT\r\n",3000);
  kurulum("AT+CWMODE=1\r\n",2000);
  kurulum("AT+CWJAP=\"""ILKER""\",\"""ilkeraykut07""\"\r\n",5000);
  kurulum("AT+CIPMUX=1\r\n",200);
  kurulum("AT+CIPSERVER=1,80\r\n",1000);

    
  
  UCSR0B |=(1<<7); //İnterrupt Aktif.
  SREG |=(1<<7);   //Genel İnterruptlar Aktif.
 
   while(1)
   {
    if(geldi)
    {



    String  metin ="<br><div><h1>LED YAK SONDUR</h1></div>";
      metin +="<br><div ><a href=\"?pin=on\"><button id='acButon'   style='background-color:green;width:100px ; height:75'>Ledi Yak</button></a> ";
      metin += "<a href=\"?pin=off\"><button id='kapaButon' style='background-color:red;width:100;height:75' >Ledi Sondur</button></a></div>"; 
     
    
    
     if((kelime.indexOf("GET /?pin=on")>=0))
     {  
     PORTD|=1<<7;
     metin +="<span style='font-size:70px;font-weight:bold;color:green;'>ACIK</span>";
     metin +="<script>document.getElementById('acButon').disabled = true;";        
     }
      if((kelime.indexOf("GET /?pin=off")>=0))
      { 
       PORTD&=~(1<<7);
       metin+="<span style='font-size:70px;font-weight:bold;color:red;'>KAPALI</span>";    
                     
    }


     


     kurulum("AT+CIPSEND=0,"+String(metin.length())+"\r\n",500);
     kurulum(metin,1);
     kurulum("\r\n"+kelime+"\r\n",1);
    
     kelime="";
     
     kurulum("AT+CIPCLOSE=0\r\n",10);
     kurulum("AT+CWMODE=1\r\n",2000);
     kurulum("AT+CWJAP=\"""ILKER""\",\"""ilkeraykut07""\"\r\n",5000);

     
     geldi=false;
     UCSR0B |=(1<<7);
    
    }
    
    _delay_ms(200);
    
   
   }
   }

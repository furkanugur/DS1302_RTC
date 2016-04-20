#include "Arduino.h"
#include "DS1302.h"

DS1302::DS1302()
{
	sclk_pin_ = 6;
	io_pin_   = 7;
	ce_pin_   = 8;
}

DS1302::DS1302(int SCLK_pin, int IO_pin, int CE_pin)
{
	sclk_pin_ = SCLK_pin;
	io_pin_   = IO_pin;
	ce_pin_   = CE_pin;
}

void DS1302::readDateTime( uint8_t *p)
{
  int i;
  startRTC();
  toggleWrite( DS1302_CLOCK_BURST_READ, true);  
  for( i=0; i<8; i++)
  {
    *p++ = toggleRead();
  }
  stopRTC();
}

void DS1302::setDateTime( uint8_t *p)
{
	writeAddress (DS1302_ENABLE, 0);
	writeAddress (DS1302_TRICKLE, 0x00);
  int i;
  startRTC();
   
  toggleWrite( DS1302_CLOCK_BURST_WRITE, false);  
  for( i=0; i<8; i++)
  {
    toggleWrite( *p++, false);  
  }
  stopRTC();
}

uint8_t DS1302::readAddress(int address)
{
  uint8_t data;
  bitSet( address, DS1302_READBIT);  

  startRTC();
  toggleWrite( address, true);  
  data = toggleRead();
  stopRTC();

  return (data);
}

void DS1302::writeAddress( int address, uint8_t data)
{
  bitClear( address, DS1302_READBIT);   
  startRTC();
  toggleWrite( address, false); 
  toggleWrite( data, false); 
  stopRTC();  
}

void DS1302::startRTC( void)
{
  digitalWrite( ce_pin_, LOW);
  pinMode( ce_pin_, OUTPUT);  

  digitalWrite( sclk_pin_, LOW);
  pinMode( sclk_pin_, OUTPUT);

  pinMode( io_pin_, OUTPUT);

  digitalWrite( ce_pin_, HIGH);
  delayMicroseconds( 4);
}

void DS1302::stopRTC(void)
{
  digitalWrite( ce_pin_, LOW);
  delayMicroseconds( 4);
}

uint8_t DS1302::toggleRead( void)
{
  uint8_t i, data;

  data = 0;
  for( i = 0; i <= 7; i++)
  {
    digitalWrite( sclk_pin_, HIGH);
    delayMicroseconds( 1);
    digitalWrite( sclk_pin_, LOW);
    delayMicroseconds( 1);
    bitWrite( data, i, digitalRead( io_pin_)); 
  }
  return( data);
}

void DS1302::toggleWrite( uint8_t data, uint8_t release)
{
  int i;
  for( i = 0; i <= 7; i++)
  { 
    digitalWrite( io_pin_, bitRead(data, i));  
    delayMicroseconds( 1);
    digitalWrite( sclk_pin_, HIGH);     
    delayMicroseconds( 1);

    if( release && i == 7)
    {
      pinMode( io_pin_, INPUT);
    }
    else
    {
      digitalWrite( sclk_pin_, LOW);
      delayMicroseconds( 1);
    }
  }
}

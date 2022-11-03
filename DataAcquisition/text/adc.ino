#include "Adc.h"

void Adc_Init(void)
{
    // AREF = AVcc
    ADMUX = (1<<REFS0);

    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // set prescalar of 128 division factor  16000000/128 = 125000
    ADCSRA |= (1<<ADEN);  //enable ADC system
}

unsigned short Adc_ReadChannel(unsigned char ch)
{
 
  Adc_Init();

  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
 

  ADCSRA |= (1<<ADSC); //setting ADSC to 1 wlll start the conversion from 

  while(ADCSRA & (1<<ADSC)); //checks that the whole conversion is done

  unsigned short a = ADC; //when the coversion is done reading is stored in a variable called a

  ADCSRA &= !(1<<ADEN); //disable the ADC system after finishing
  
  return a; //value of a is returned

}

#include <avr/io.h>
#include "adc.h"  //all the libraries that are made are imported to be able to use them
#include "uarts.h"
#include "dio.h"

#define switch 5 //we defined the pin number of each component to be the refrence if any change is required regarding the hardware
#define switch2 4
#define led1 3
#define led2 2
#define led3 0
#define led4 1
#define LDR 0
#define temp 5

void init();       //function prototype for init function

int main(void){    // main function is started
    init();
    while(1)      //main loop is initialized
    { 
      unsigned char c =Dio_GetPinState('B',switch);     //checking if the first switch is on or off
      if(!c)       //if the fisrt switch is on
      {
          Uart_SendString("Light system is on \n");       //Uart_SendString function will be used to display "Light system is on" on the serial moniter 
          Dio_SetPinState('B',led1,'H');          //led 1 will turn on via setting its corresponding pin high
          _delay_ms(500);

          short LDR_reading=Adc_ReadChannel(LDR);       //ADC_READ function is used to read the LDR sensor-data and store them in a variable called "reading"
          char LDR_readingStr[4];               //an empty array of 4 characters called "readingStr" is created to store the sensor reading in it. Note that the maximum number of characters displaying the sensor reading will not exceed 4.
          sprintf(LDR_readingStr, "%d", LDR_reading);       //sprintf function is used to store the sensor readings in the "readingStr" arrray to be able to use Uart_SendString function
           
          Uart_SendString("reading is equal:\n");
          _delay_ms(500);
          Uart_SendString(LDR_readingStr);
          Uart_SendString("\n"); //each reading is printed on a new line
          _delay_ms(500); 
          //Uart_SendString function is used again to display sensor readings on the serial moniter

          
        if (LDR_reading<300) //if the light intensity is low depending on the sensor readings (<300)
        {
          Uart_SendString("Light intensity is low - LED will turn on \n");      //"light intensity is low" message will be displayed using Uart_SendString function
          Dio_SetPinState('B',led2,'H');       //led 2 will turn on by setting its corresponding pin high
        }
        
        else{      //if light intensity is high (greater than 300)
          Uart_SendString("Light intensity is high - LED will turn off \n");     //"light intensity is high" message will be displayed using Uart_SendString function
          Dio_SetPinState('B',led2,'L');}         //led 2 will turn off by setting its corresponding pin low

         
          
          
      }
       else{ //if first switch is off
          Uart_SendString("Light system is off \n");  //Uart_SendString function will be used to display "light system is off" on the serial moniter 
          Dio_SetPinState('B',led2,'L');        //led 2 will turn off by setting its corresponding pin low
          Dio_SetPinState('B',led1,'L');        //led 1 will turn off by setting its corresponding pin low
          _delay_ms(500);
       }
       Uart_SendString("----------------------------------------------------------- \n"); //a dotted line is displayed to seperate between first system and second system
       unsigned char b =Dio_GetPinState('B',switch2); //checking if the second switch is on or off
      if(!b) //if the second switch is on
      {
        Uart_SendString("Temperature system is on \n");    //Uart_SendString function will be used to display "Temperature system is on" on the serial moniter 
        Dio_SetPinState('B',led3,'H');        //led 3 will turn on via setting its corresponding pin high
        _delay_ms(500);
        short temp_reading=Adc_ReadChannel(temp);      //ADC_READ function is used to read the temperature sensor-data and store them in a variable called "temp_reading"
        char temp_readingStr[4];                        //an empty array of 4 characters called "temp_readingStr" is created to store the sensor reading in it
        sprintf(temp_readingStr,"%d", temp_reading);      //sprintf function is used to store the sensor readings in the "temp_reading2tr" arrray to be able to use Uart_SendString function
        Uart_SendString("reading is equal:\n");
        _delay_ms(500);
        Uart_SendString(temp_readingStr);
        Uart_SendString(" \n"); //each reading is printed on a new line
        _delay_ms(500);

        if (temp_reading>62) //if the temperature is high depending on the sensor readings
        {
          Uart_SendString("Temperature is high - AC will turn on \n");      //"Temperature is high" message will be displayed using Uart_SendString function
          Dio_SetPinState('B',led4,'H');       //led 4 will turn on by setting its corresponding pin high
        }
        
        else{      //if temperature is normal
          Uart_SendString("Temperature is normal - AC will turn off \n");     //"Temperature is normal" message will be displayed using Uart_SendString function
          Dio_SetPinState('B',led4,'L');}         //led 4 will turn off by setting its corresponding pin low
      } 

        else{
          Uart_SendString("Temperature system is off \n");     //Uart_SendString function will be used to display "Temperature system is off" on the serial moniter
          Dio_SetPinState('B',led3,'L');         //led 3 will turn off by setting its corresponding pin low
           Dio_SetPinState('B',led4,'L');         //led 4 will turn off by setting its corresponding pin low
          _delay_ms(500);}
          Uart_SendString("----------------------------------------------------------- \n");

          



    
       
    }

    return 0;
}


 void init(){
  Adc_Init();
  uart_init (9600);
  Dio_init();
}

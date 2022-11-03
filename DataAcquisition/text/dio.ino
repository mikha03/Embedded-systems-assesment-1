#include <avr/io.h>

#define switch 5 //we defined the pin number of each component to be the refrence if any change is required regarding the hardware
#define switch2 4 
#define led1 3
#define led2 2
#define led3 0
#define led4 1
#define LDR 0
#define temp 5

void Dio_SetPinDirection(unsigned char Port,unsigned char Pin, unsigned char Direction){        //This function is used to set pin direction (Input or Output)
if (Direction=='I'){    // if the user's chosen direction is input
  if (Port=='B'){DDRB=DDRB&~(1<<Pin);}   
  else if (Port=='D'){DDRD=DDRD&~(1<<Pin);}
  else if (Port=='C'){DDRC=DDRC&~(1<<Pin);}  // according to the user input, the chosen pin in the chosen port (B D C) will be set to 0 in the DDR(data direction registor) by clearing method(&~(1<<pin))
}
else if (Direction=='O'){   //if chosen direction is output
  if (Port=='B'){DDRB=DDRB|(1<<Pin);}
  else if (Port=='D'){DDRD=DDRD|(1<<Pin);}
  else if (Port=='C'){DDRC=DDRC|(1<<Pin);} // according to the user input, the chosen pin in the chosen port (B D C) will be set to 1 in the DDR(data direction registor) by setting method (|(1<<pin))
}
}




void Dio_SetPinState(unsigned char Port,unsigned char Pin, unsigned char State){       //This function is used to set pin state (High or Low)
if (State=='L'){
  if (Port=='B'){PORTB=PORTB&~(1<<Pin);}  
  else if (Port=='D'){PORTD=PORTD&~(1<<Pin);}  
  else if (Port=='C'){PORTC=PORTC&~(1<<Pin);} // according to the user input, the chosen pin in the chosen port (B D C) will be set to 0 in the PORT by clearing method(&~(1<<pin))
}

else if (State=='H'){
  if (Port=='B'){PORTB=PORTB|(1<<Pin);}   // according to the user input, the chosen pin in the chosen port (B D C) will be set to 1 in the PORT by setting method(|(1<<pin))
  else if (Port=='D'){PORTD=PORTD|(1<<Pin);}
  else if (Port=='C'){PORTC=PORTC|(1<<Pin);}
}
}



unsigned char Dio_GetPinState(unsigned char Port,unsigned char Pin){   //check the value of the pin (1 or 0) and store the answer in variable c
  unsigned char c;
  if (Port=='B'){c = (PINB & (1<<Pin)) !=  0;} 
  else if (Port=='D'){c = (PIND & (1<<Pin)) !=  0;}
  else if (Port=='C'){c = (PINC & (1<<Pin)) !=  0;}
  return c;
  
}


void Dio_init(){  //using the above functions to initialize the pins direction here instead of the main code 
  Dio_SetPinDirection('B', led2,'O');
  Dio_SetPinDirection('B', led1,'O');
  Dio_SetPinDirection('B', switch,'I');
  Dio_SetPinDirection('C', LDR,'I');
  Dio_SetPinState('B',switch,'H'); //used to turn on internal resistance in the switch pin
  Dio_SetPinDirection('B', switch2,'I');
  Dio_SetPinState('B',switch2,'H');
  Dio_SetPinDirection('B', led3,'O');
  Dio_SetPinDirection('B', led4,'O');
  Dio_SetPinDirection('C',temp,'I');
}

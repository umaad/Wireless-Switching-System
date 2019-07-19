

#include <avr/io.h>
# define F_CPU 11059200UL
#include <util/delay.h>
#define BaudRate 9600
#define BAUD_PRESCALE (((F_CPU/(BaudRate*16UL)))-1)
#define en PA7
#define rw PA6
#define rs PA5
#define LCD_data PORTC
#define ctrl PORTA

void LCD_cmd(unsigned char cmd);
void init_LCD (void);
void LCD_write(unsigned char data);
void LCD_write_string();
unsigned int press;



char hc_05_buffer1[25], hc_05_buffer2[50];
char temp;

void hc_05_bluetooth_transmit_byte(char data_byte);
char hc_05_bluetooth_receive_byte(void);
void hc_05_bluetooth_transmit_string(char *transmit_string);
void hc_05_bluetooth_transmit_command(char *transmit_string);
char *hc_05_bluetooth_receive_string(char *receive_string, unsigned char terminating_character);


void usart_init();

void usart_data_transmit(unsigned char data );

unsigned char usart_data_receive( void );

void usart_string_transmit(char *string);

char *usart_string_receive(char *receive_string,unsigned char terminating_character);

int main(void)
{
	
	DDRD = 0xFF;  //tx and rx
	DDRC = 0xFF;  //lcd data
	DDRB = 0xFF;   //relay
	DDRA= 0xFF;    //lcd ctrl
	
	init_LCD();
	LCD_write_string("WIRELESS SWITCHING ");
	LCD_cmd(0xc0);
	LCD_write_string("   WELCOME");
	
	
	
	char received_data;
	/*Variable declaration*/
	
	usart_init();
	/*USART initialization*/
	
	hc_05_bluetooth_transmit_string("Wireless Switching");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/

	hc_05_bluetooth_transmit_string("Final Defence");
	/*Transmits a string to Bluetooth Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/
	
	hc_05_bluetooth_transmit_string("Control Keys for Appliances:");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/
	
	hc_05_bluetooth_transmit_string("1=Appliance 1 ON or OFF");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return */
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line */

	hc_05_bluetooth_transmit_string("2=Appliance 2 ON or OFF");
	/*Transmits a string to Bluetooth*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth */

	hc_05_bluetooth_transmit_string("3=Appliance 3 ON or OFF");
	/*Transmits a string to Bluetooth */

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/

	hc_05_bluetooth_transmit_string("4=Appliance 4 ON ");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth */
	hc_05_bluetooth_transmit_string("7=Appliance 4 OFF");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth */
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth */
	
	hc_05_bluetooth_transmit_string("5=All Appliances ON");
	/*Transmits a string to Bluetooth */

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module */

	hc_05_bluetooth_transmit_string("6=All Appliances OFF");
	/*Transmits a string to Bluetooth */

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module */
	
	
	/*Checking the pressed key to Turn ON and OFF appliances*/
	while(1)
	{
		
		/*Start of infinite loop*/
		received_data=hc_05_bluetooth_receive_byte();
		/*Microcontroller will receive a character from Bluetooth Module*/
		
		if(received_data == '1')
		{
			PORTB^=0x01;
			
			/*Appliance 1 changes status*/
			
			if(PORTB & 0x01)
			{
				hc_05_bluetooth_transmit_string("Appliance 1 is ON");	   /*Transmits a string to Bluetooth of Module*/
				LCD_cmd(0xc0);
				LCD_write_string("BULB 1 ON");
				_delay_ms(1000);
				
			}
			else
			{
				hc_05_bluetooth_transmit_string("Appliance 1 is OFF");	   /*Transmits a string to Bluetooth of Module*/
				LCD_cmd(0xc0);
				LCD_write_string("BULB 1 OFF");
				_delay_ms(1000);
				
			}
		}
		else if(received_data == '2')
		{
			PORTB^=0x02;	   /*Appliance 2 changes status*/

			if(PORTB & 0x02)
			{
				hc_05_bluetooth_transmit_string("Appliance 2 is ON");   /*Transmits a string to Bluetooth of Module*/
				LCD_cmd(0xc0);
				LCD_write_string("BULB 2 ON");
				_delay_ms(1000);
				

			}
			else
			{
				hc_05_bluetooth_transmit_string("Appliance 2 is OFF");   /*Transmits a string to Bluetooth of Module*/
				LCD_cmd(0xc0);
				LCD_write_string("BULB 2 OFF");
				_delay_ms(1000);

			}
		}
		else if(received_data == '3')
		{
			PORTB^=0x04;   /*Appliance 3 changes status*/

			if(PORTB & 0x04)
			{
				hc_05_bluetooth_transmit_string("Appliance 3 is ON");   /*Transmits a string to Bluetooth of Module*/
				LCD_cmd(0xc0);
				LCD_write_string("BULB 3 ON");
				_delay_ms(1000);

			}
			else
			{
				hc_05_bluetooth_transmit_string("Appliance 3 is OFF");   /*Transmits a string to Bluetooth of Module*/
				LCD_cmd(0xc0);
				LCD_write_string("BULB 3 OFF");
				_delay_ms(1000);

			}
		}
		else if(received_data == '4')
		{
			PORTB^=0x08;  /*Appliance 4 changes status*/
			if(PORTB & 0x08)
			{
				hc_05_bluetooth_transmit_string("Appliance 4 is ON");
				LCD_cmd(0XC0);
				LCD_write_string("Door Open");
				_delay_ms(1000);
			}
			else
			{
				hc_05_bluetooth_transmit_string("Appliance 4 is OFF");  /*Transmits a string to Bluetooth of Module*/
				LCD_cmd(0XC0);
				LCD_write_string("Door Close");
				_delay_ms(1000);
			}
		}
		else if(received_data == '5')
		{
			PORTB^=0x07;
			if(PORTB & 0x07)
			{
				hc_05_bluetooth_transmit_string("All Appliance are ON");
				LCD_cmd(0XC0);
				LCD_write_string("All ON");
				_delay_ms(1000);
			}
			else
			
			{
				hc_05_bluetooth_transmit_string("All Appliance are OFF");  /*Transmits a string to Bluetooth of Module*/
				LCD_cmd(0XC0);
				LCD_write_string("All Appliance are OFF");
				_delay_ms(1000);
			}
		}
		
		else if (received_data== ' ')
		{
			LCD_cmd(0xc0);
			LCD_write_string("    WELCOME");
		}
		else
		{
			hc_05_bluetooth_transmit_string("Invalid Key");  /*Transmits a string to Bluetooth of Module*/
			LCD_cmd(0xc0);
			LCD_write_string("received_data");
			

		}
		
	}
}
	


void hc_05_bluetooth_transmit_byte(char data_byte)
{
	usart_data_transmit(data_byte);
}
char hc_05_bluetooth_receive_byte(void)
{
	return usart_data_receive();
}
void hc_05_bluetooth_transmit_string(char *transmit_string)
{
	usart_string_transmit(transmit_string);
}
char *hc_05_bluetooth_receive_string(char *receive_string, unsigned char terminating_character)
{
	unsigned char temp=0x00;
	for(unsigned char i=0;;i++)
	{
		*(receive_string+i)=usart_data_receive();
		if(*(receive_string+i)==terminating_character)
		break;
		else
		temp++;
	}
	*(receive_string+temp)='\0';
	return receive_string;
}


void usart_init()
{
	UBRRH = (BAUD_PRESCALE>>8);
	UBRRL =BAUD_PRESCALE;
	UCSRB|= (1<<RXEN)|(1<<TXEN);
	UCSRC |= (1 << URSEL) | (0<<USBS) | (1 << UCSZ0) | (1 << UCSZ1);
}


void usart_data_transmit(unsigned char data )
{
	while ( !( UCSRA & (1<<UDRE)) )
	;
	UDR = data;
	_delay_ms(1);
}

unsigned char usart_data_receive( void )
{
	while ( !(UCSRA & (1<<RXC)) );
	return UDR;
}

void usart_string_transmit(char *string)
{
	while(*string)
	{
		usart_data_transmit(*string++);
	}
}

char *usart_string_receive(char *receive_string,unsigned char terminating_character)
{
	unsigned char temp=0x00;
	for(unsigned char i=0;;i++)
	{
		*(receive_string+i)=usart_data_receive();
		if(*(receive_string+i)==terminating_character)
		break;
		else
		temp++;
	}
	*(receive_string+temp)='\0';
	return receive_string;
}
//LCD command

void init_LCD(void)
{
	LCD_cmd(0x38);
	_delay_ms(1);
	LCD_cmd(0x01);
	_delay_ms(1);
	LCD_cmd(0x80);
	_delay_ms(1);
	_delay_ms(10);
	LCD_cmd(0x06);
	_delay_ms(1);
	LCD_cmd(0x0c);
	_delay_ms(1);

	return ;
}
void LCD_cmd(unsigned char cmd)
{
	PORTC=cmd;
	ctrl=(0<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl=(0<<rs)|(0<<rw)|(0<<en);
	_delay_ms(1);
	return;
}
void LCD_write(unsigned char data)
{
	PORTC=data;
	ctrl=(1<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl=(1<<rs)|(0<<rw)|(0<<en);
	_delay_ms(1);
	return;
}
void LCD_write_string(unsigned char *str)
{
	int i=0;
	while(str[i]!='\0')
	{
		LCD_write(str[i]);
		i++;
	}
	return;
}

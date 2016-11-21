#include <stdio.h>
#include<wiringPi.h>
#include<unistd.h>
#include <fcntl.h>
#include <termios.h>


#define IN 27
#define TOUCH 3
#define PIEZO 23
#define CDSIN 28
#define CDSOUT 29


int main(void)
{

	int i; //piezo
	int state=0; //LED ON OFF
	int uart0_filestream = -1;
	uart0_filestream= open("/dev/ttyAMA0",O_RDWR | O_NOCTTY | O_NDELAY);
	if(uart0_filestream == -1)
	{
		printf("ERROR\n");
	}
	struct termios options;
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);
	int n=0;
	wiringPiSetup();

	pinMode(IN, OUTPUT);
	pinMode(TOUCH, INPUT);
	pinMode(PIEZO, PWM_OUTPUT);
	pinMode(CDSIN, INPUT);
	pinMode(CDSOUT, OUTPUT);
	digitalWrite(CDSOUT, 1);
	int d=0;
	while(1)
	{
		if(uart0_filestream != -1)
		{
			unsigned char rx_buffer[1];
			int rx_length = read(uart0_filestream, (void*)rx_buffer, 1);
			if(rx_length <0)
			{
			}
			else if(rx_length ==0){
			}
			else
			{
				rx_buffer[rx_length]='\0';
				if((rx_buffer[0])=='i'){
					if(state==0){
						printf("lamp ON\n");
						digitalWrite(IN,LOW);
						pwmWrite(PIEZO, 7);
						delay(300);
						pwmWrite(PIEZO, 0);
						state=1;
						delay(1000);
					} else if(state==1){
						printf("lamp OFF\n");
						digitalWrite(IN,HIGH);
						pwmWrite(PIEZO, 7);
						delay(300);
						pwmWrite(PIEZO, 0);
						state=0;
						delay(1000);
					}
				}
				printf("%i bytes read : %s\n", rx_length, rx_buffer);
			}
		}
		if(digitalRead(TOUCH)==0){
			if(state==0){
				printf("Lamp On\n");
				digitalWrite(IN,LOW);

				pwmWrite(PIEZO, 7);
				delay(300);
				pwmWrite(PIEZO, 0);

				state=1;
				delay(1000);
			} else if(state==1){
				printf("Lamp Off\n");
				digitalWrite(IN,HIGH);

				pwmWrite(PIEZO, 7);
				delay(300);
				pwmWrite(PIEZO, 0);
				
				state=0;
				delay(1000);
			}
		}

	}
}
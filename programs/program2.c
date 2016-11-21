#include <stdio.h>
#include<wiringPi.h>
#include<unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sr595.h>
#include <time.h>

#define IN 27
#define TOUCH 3
#define PIEZO 23
#define CDSIN 28
#define CDSOUT 29

#define INTERVAL 4
#define LED_NUM 14
#define DIG_NUM 5
#define DIG1 0
#define DIG2 1
#define DIG3 2
#define DIG4 3
#define DIG5 4
#define FND_A 5
#define FND_B 6
#define FND_C 7
#define FND_D 8
#define FND_E 9
#define FND_F 10
#define FND_G 11
#define FND_DP 12
#define FND_D5D6 13

#define DIG_ON 1
#define DIG_OFF 0
#define FND_ON 0
#define FND_OFF 1
#define BUF_SIZE 5
#define size(x) (sizeof(x) /sizeof(int))
void initAll();
void initDigit();
void initFnd();
void displayValue(int value[], int size);
void displayDigitValue(int value);
int ZERO[]={FND_A, FND_B, FND_C, FND_D, FND_E, FND_F};
int ONE[]={FND_B, FND_C};
int TWO[]={FND_A, FND_B, FND_D, FND_E, FND_G};
int THREE[]={FND_A, FND_B, FND_C, FND_D, FND_G};
int FOUR[]={FND_B, FND_C, FND_F, FND_G};
int FIVE[]={FND_A, FND_C, FND_D, FND_F, FND_G};
int SIX[]={FND_A, FND_C, FND_D, FND_E, FND_F, FND_G};
int SEVEN[]={FND_A, FND_B, FND_C, FND_F};
int EIGHT[]={FND_A, FND_B, FND_C, FND_D, FND_E, FND_F, FND_G};
int NINE[]={FND_A, FND_B, FND_C, FND_D, FND_F, FND_G};

int main(void)
{
	time_t timer;
	char strFormat[BUF_SIZE];
	int digitNum[4];
	int digNum=0;

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

	sr595Setup(100,LED_NUM, 0,1,2);
	initAll();

	pinMode(IN, OUTPUT);
	pinMode(TOUCH, INPUT);
	pinMode(PIEZO, PWM_OUTPUT);
	pinMode(CDSIN, INPUT);
	pinMode(CDSOUT, OUTPUT);
	digitalWrite(CDSOUT, 1);
	int d=0;
	while(1)
	{
		time(&timer);
		strftime(strFormat, BUF_SIZE, "%H%M", localtime(&timer));

		for(digNum=0;digNum<4;digNum++){
			digitNum[digNum]=strFormat[digNum]-'0';
			digitalWrite(100+digNum, DIG_ON);
			displayDigitValue(digitNum[digNum]);
			delay(INTERVAL);
			initAll();
		}
		digitalWrite(100+DIG5, DIG_ON);
		digitalWrite(100+FND_D5D6, FND_ON);


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

void initAll(){
	initDigit();
	initFnd();
}
void initDigit(){
	int i;
	for(i=0;i<DIG_NUM;i++){
		digitalWrite(100+i,DIG_OFF);
	}
}
void initFnd(){
	int i;
	for(i=DIG_NUM; i<LED_NUM; i++){
		digitalWrite(100+i, FND_OFF);
	}
}
void displayValue(int value[], int size){
	int i;
	initFnd();
	for(i=0;i<size;i++){
		digitalWrite(100+value[i], FND_ON);
	}
}
void displayDigitValue(int value){
	switch(value){
		case 0:
			displayValue(ZERO, size(ZERO));
			break;
		case 1:
			displayValue(ONE, size(ONE));
			break;
		case 2:
			displayValue(TWO, size(TWO));
			break;
		case 3:
			displayValue(THREE, size(THREE));
			break;
		case 4:
			displayValue(FOUR, size(FOUR));
			break;
		case 5:
			displayValue(FIVE, size(FIVE));
			break;
		case 6:
			displayValue(SIX, size(SIX));
			break;
		case 7:
			displayValue(SEVEN, size(SEVEN));
			break;
		case 8:
			displayValue(EIGHT, size(EIGHT));
			break;
		case 9:
			displayValue(NINE, size(NINE));
			break;
		}
}
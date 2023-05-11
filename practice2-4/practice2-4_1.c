#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <pthread.h>

const int FndSelectPin[6] = { 4, 17, 18, 27, 22, 23 }; 
const int FndPin[8] = { 6, 12, 13, 16, 19, 20, 26, 21 };
const int FndFont[6] = { 0x76, 0x79, 0x38, 0x38, 0x3F, 0 };

void Init() {
	int i;
	if( wiringPiSetupGpio() == -1 ) {
		printf( "wiringPiSetupGpio() error\n");
		exit(-1);
	}
	for( i = 0; i < 6; i++ ) {
		pinMode( FndSelectPin[ i ], OUTPUT );
		digitalWrite( FndSelectPin[ i ], HIGH );
	}
	for( i = 0; i < 8; i++ ) {
		pinMode( FndPin[ i ], OUTPUT );
		digitalWrite( FndPin[ i ], LOW );
	}
}

void FndSelect(int position)
{
	int i;

	for(i=0;i<6;i++)
	{
		if (i == position){
			digitalWrite(FndSelectPin[i], LOW);
		}
		else{
			digitalWrite(FndSelectPin[i], HIGH);
		}
	}
}

void FndDisplay(int position, int num){
	int i,j;
	int flag = 0;
	int shift = 0x01;

	for(i=0;i<8;i++){
		flag = (FndFont[num] & shift);
		digitalWrite(FndPin[i], flag);
		shift <<= 1;
	}
	FndSelect(position);
}

int start = 5;

void *mover_timer(void *data)
{
	while(1)
	{
		delay(500);
		start++;
	}
}

int main()
{
	int pos;
	pthread_t tid;

	Init();
	pthread_create(&tid, 0, mover_timer, 0);
	while(1)
	{
		for(pos = 0; pos < 6; pos++)
		{
			FndDisplay((start-pos + 6) % 6, pos);
			delay(1);
		}
	}
}


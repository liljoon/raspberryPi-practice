#include <wiringPi.h>
#include <pthread.h>
#include <stdio.h>
const int LedRed[8] = { 4, 17, 18, 27, 22, 23, 24, 25 };
const int Keypad[3] = { 6,12, 13 };

int KeypadRead()
{
	int i, keypadnum = -1;
	for (i = 0; i<8;i++)
	{
		if(!digitalRead(Keypad[i])){
			keypadnum = i;
			break;	
		}
	}
	return keypadnum;
}

void LedControl(int keypadnum)
{
	int i;
	for(i=0;i<8;i++)
	{
		if(i==keypadnum)
			digitalWrite(LedRed[i], HIGH);
		else
			digitalWrite(LedRed[i], LOW);
	}
}

int flag = 0;

void *checking(void *arg)
{
	while(1)
	{
		if (KeypadRead() == 2)
			flag = 1;
	}
}

int main()
{
	int i, keypadnum = -1;
	pthread_t tid;

	if (wiringPiSetupGpio() == -1)
		return 1;

	pthread_create(&tid, 0, checking, 0);
	for(i=0;i<8;i++)
	{
		pinMode(LedRed[i], OUTPUT);
		digitalWrite(LedRed[i], LOW);
	}

	for(i=0;i<2;i++)
		pinMode(Keypad[i], INPUT);

	while(1)
	{
		keypadnum = KeypadRead();
		if (keypadnum == 0)
		{
			while (1)
			{
				for (i=0;i<8;i++)
				{
					LedControl(i);
					delay(500);
					if (flag)
					{
						break;
					}
				}
				digitalWrite(LedRed[i-1] , LOW);
				if (flag)
				{
					flag = 0;
					break;
				}
			}
		}
		else if (keypadnum == 1)
		{
			while (1)
			{
				for(i=7;i>=0;i--)
				{
					LedControl(i);
					delay(500);
					if (flag)
					{
						break;
					}
				}
				digitalWrite(LedRed[i+1], LOW);
				if (flag)
				{
					flag = 0;
					break;
				}
			}
		}
	}
	return 0;
}


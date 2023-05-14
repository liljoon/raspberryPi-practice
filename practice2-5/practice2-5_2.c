#include <wiringPi.h>
#include <softPwm.h>

const Led[] = { 4, 17, 18, 27, 22, 23, 24, 25 };

int main(void)
{
	if (wiringPiSetupGpio() == -1)
		return 1;
	int i;
	for(i = 0; i < 8; i++)
	{
		pinMode(Led[i], OUTPUT);
		digitalWrite(Led[i], LOW);
	}
	softPwmCreate(Led[0], 0, 100);

	int brightness = 0;
	int dt = 1;
	while (1)
	{
		softPwmWrite(Led[0], brightness);
		if (brightness == 100)
			dt = -1;
		else if (brightness == 0)
			dt = 1;
		brightness += dt;
		delay(30);
	}

	return 0;
}

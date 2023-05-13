#include <wiringPi.h>
#include <softPwm.h>

#define LED 4

int main(void)
{
	if (wiringPiSetupGpio() == -1)
		return 1;
	pinMode(LED, OUTPUT);

	softPwmCreate(LED, 0, 100);

	int brightness = 0;
	int dt = 1;
	while (1)
	{
		softPwmWrite(LED, brightness);
		if (brightness == 100)
			dt = -1;
		else if (brightness == 0)
			dt = 1;
		brightness += dt;
		delay(30);
	}

	return 0;
}

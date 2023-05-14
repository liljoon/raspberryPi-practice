#include <wiringPi.h>
#include <softPwm.h>

// Motor 핀 설정
#define MOTOR_MT_N_PIN 17
#define MOTOR_MT_P_PIN 4
// Motor 회전 방향 정의
#define LEFT_ROTATE 1
#define RIGHT_ROTATE 2

// Motor 정지 함수
void MotorStop()
{
	softPwmWrite(MOTOR_MT_N_PIN, 0);
	softPwmWrite(MOTOR_MT_P_PIN, 0);
}

void MotorControl(int rotate, int speed)
{
	int pin_on, pin_off;

	if (rotate == LEFT_ROTATE)
	{
		pin_on = MOTOR_MT_N_PIN;
		pin_off = MOTOR_MT_P_PIN;
	}
	else
	{
		pin_off = MOTOR_MT_N_PIN;
		pin_on = MOTOR_MT_P_PIN;
	}

	digitalWrite(pin_off, LOW);
	softPwmWrite(pin_on, speed);
}

int main(void)
{
	if (wiringPiSetupGpio() == -1)
		return 1;

	// Motor 핀 출력으로 설정
	pinMode(MOTOR_MT_N_PIN, OUTPUT);
	pinMode(MOTOR_MT_P_PIN, OUTPUT);

	softPwmCreate(MOTOR_MT_N_PIN, 0, 128);
	softPwmCreate(MOTOR_MT_P_PIN, 0, 128);

	int speed = 32;
	int i;
	for (i = 0; i < 4; i++)
	{
		MotorControl(LEFT_ROTATE, speed);
		delay(2000);
		MotorStop();
		delay(2000);
		speed += 32;
	}
	speed = 128;
	for (i = 0; i < 4; i++)
	{
		MotorControl(RIGHT_ROTATE, speed);
		delay(2000);
		MotorStop();
		delay(2000);
		speed -= 32;
	}
	return 0;
}

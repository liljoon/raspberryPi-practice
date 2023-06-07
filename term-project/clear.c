#include <wiringPi.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_FILE ".fifo"

int main()
{
	int fd;
	char ch;

	fd = open(FIFO_FILE, O_WRONLY);
	ch = '2';
	write(fd, &ch, 1);
}

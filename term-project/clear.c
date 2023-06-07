#include <wiringPi.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define FIFO_FILE ".fifo"

int main()
{
	int fd;
	char ch;

	fd = open(FIFO_FILE, O_WRONLY);
	ch = '2';
	write(fd, &ch, 1);
	printf("Content-type:text/html\n\n");
	printf("<html>\n<head>\n<title>Stopwatch</title>\n</head>\n");
	printf("<body>\n<p>Stopwatch Clear</p>\n");
	printf("</body>\n</html>");
}

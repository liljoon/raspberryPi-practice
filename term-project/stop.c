#include <wiringPi.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_FILE ".fifo"

int main()
{
	int fd;
	char ch;

	fd = open(FIFO_FILE, O_WRONLY);
	ch = '0';
	write(fd, &ch, 1);
	printf("Content-type:text/html\n\n");
	printf("<html>\n<head>\n<title>Stopwatch</title>\n</head>\n");
	printf("<body>\n<p>Stopwatch Stop</p>\n");
	printf("</body>\n</html>");
}

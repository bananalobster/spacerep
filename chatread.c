#include <stdio.h>
#include <sys/poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
  int fd = open("M_FIFO", O_RDONLY);
	char buf[512];
	int rd = read(fd, buf, 512);
	
	printf("read: ");
	fflush(NULL);
	write(1, buf, rd);
	return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSZ  4096
unsigned char srbuffer[BUFSZ], swbuffer[BUFSZ];

int main(int argc, char **argv){
	struct sockaddr_in addr;
	int sock;
	struct hostent *hst;
	fd_set rset, wset, eset;
	int ioret;
	unsigned int srbufpos, swbufpos;

	signal(SIGPIPE, SIG_IGN);
	hst = gethostbyname(argv[1]);

//	addr.sin_family = AF_INET;
//	addr.sin_addr.s_addr = *((int*)hst->h_addr_list[0]);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	srbufpos = swbufpos = 0;

	for(;;){
		FD_ZERO(&rset);
		FD_ZERO(&wset);
		FD_ZERO(&eset);
		FD_SET(0, &rset);
		FD_SET(sock, &rset);
		FD_SET(1, &wset);
		FD_SET(sock, &wset);

		select(sock+1, &rset, &wset, NULL, NULL);
		if (FD_ISSET(0, &rset) && swbufpos < BUFSZ){
			ioret = read(0, swbuffer + swbufpos, BUFSZ - swbufpos);
			if (ioret) swbufpos += ioret;
		}
		if (FD_ISSET(1, &wset) && srbufpos){
			ioret = write(1, srbuffer, srbufpos);
			memmove(srbuffer, srbuffer + ioret, (srbufpos-=ioret));	
		}
		if (FD_ISSET(sock, &rset) && srbufpos < BUFSZ){
			ioret = read(sock, srbuffer + srbufpos, BUFSZ - srbufpos);
			if (ioret) srbufpos += ioret;
		}		
		if (FD_ISSET(sock, &wset) && swbufpos){
			ioret = write(sock, swbuffer, swbufpos);
			memmove(swbuffer, swbuffer + ioret, (swbufpos -= ioret));
		}
	}
	close(sock);
	return 0;
}

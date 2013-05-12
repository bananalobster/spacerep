#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define SZ  128

typedef struct msgbuf{
	long	mtype;
	char	mtext[SZ];
} message_buf;

void main(){
	int msqid;
	key_t key = 10;
	message_buf rbuf;

	if ((msqid = msgget(key, 0666)) < 0){
		perror("fail with msgget D:");
		exit(1);
	}

	if (msgrcv(msqid, &rbuf, SZ, 1, 0) < 0){
		perror("fail with msgrcv");
		exit(1);
	}
	
}

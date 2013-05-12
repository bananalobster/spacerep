#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>

#define SZ  128

typedef struct msgbuf{
	long	mtype;
	char	mtext[SZ];
} message_buf;

void main(){
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key = 10;
	message_buf sbuf;
	size_t buf_length;

	printf("%#lx  %#o\n", key, msgflg);

	if ((msqid = msgget(key, msgflg)) < 0){
		perror("fail with msgget D:");
		exit(1);
	}
	else
		printf("ok; msqid = %d\n", msqid);

	sbuf.mtype = 1;

	(void) strcpy(sbuf.mtext, "6996");
	printf("ok; msqid = %d\n", msqid);

	buf_length = strlen(sbuf.mtext) + 1;

	if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0){
		perror("D:");
		exit(1);
	}
	else
		printf("Message: \"%s\" Sent\n", sbuf.mtext);

	exit(0);
	
}

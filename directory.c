#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

void main(){
  DIR *dir;
	struct dirent *dirp;

	dir = opendir(".");
	while(dirp = readdir(dir)){
		printf("name : %s\n", dirp->d_name);
	}
}

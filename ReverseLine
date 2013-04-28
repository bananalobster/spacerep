#include <stdio.h>

void main (){
  char tmp;
	int i, am = 255;
	char a[256] = "retsbol";

//	for(i = 0; i <= am; i++){
//		printf("%c",a[i]);
//	}
//	printf("\n");
	for(i = 0; i <= am/2; i++){
		tmp = a[i];
		a[i] = a[am - i];
		a[am - i] = tmp;
	}
	for(i = 0; i <= am; i++){
		printf("%c",a[i]);
	}
	printf("\n");
}

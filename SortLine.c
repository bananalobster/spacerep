#include <stdio.h>

void main(){
  char tmp;
	int i, j, am, e = 1, counter = 0;
	char a[] = "retsbol";

	for (j = 0; j <= sizeof(a); j++){
		for (i = 0; i <= sizeof(a); i++){
			counter++;
			if (e*a[i+1] < e*a[i]){
				tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
			}
		}	
	}
	for (i = 0; i <= sizeof(a); i++){
		printf("%c",a[i]);
	}
	printf("\n %d\n", counter);
}

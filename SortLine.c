#include <stdio.h>

#define	N 255

int main(){
	char tmp;
	int i, fl, am, e = 1, len = 0;
	char a[N];

	/* input */
	scanf("%s", a);

	/* length */
	do {
		len++;
	} while (a[len]*e > 13);

	/* check input */
//	for (i = 0; i <= len; i++){
//		printf("%c", a[i]);
//	}

	/* sort */
	do{
		fl = 0;
		for (i = 0; i < len-1; i++){
			if  (e*a[i+1] < e*a[i]){
				fl = 1;
				tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
			}
		}	
	}while (fl != 0);

	/* output */
	for (i = 0; i <= len; i++){
		printf("%c", a[i]);
	}
	printf("\n");

	return 0;
}

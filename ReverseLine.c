#include <stdio.h>

#define N 255

int main () {
	char tmp;
	int len = 0, i = 0, e = 1;
	char a[N];

	/* input */
	scanf("%s", a);

	/* length */
	do {
		len++;
	} while (a[len]*e > 13);

	printf("\n");
//	printf("%d  ", len);


	/* reverse */
	for (i = 0; i <= len/2; i++) {
		tmp = a[i];
		a[i] = a[len - i];
		a[len - i] = tmp;
	}


	/* output */
	for (i = 0; i < len; i++) {
		printf("%c",a[i]);
	}

	printf("\n");
	return 0;
}

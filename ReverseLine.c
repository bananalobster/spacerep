#include <stdio.h>

#define N 5

int main () {
	char tmp;
	int i = 1;
	char a[] = "retsbol";

	/* input */
//	while (i < N) {
//		a[i] = getchar;
//		i++;
//	}

	printf("\n");

	/* reverse */
	for (i = 1; i <= sizeof(a)/2; i++) {
		tmp = a[i];
		a[i] = a[sizeof(a) - i];
		a[sizeof(a) - i] = tmp;
	}


	/* output */
	for (i = 0; i <= sizeof(a); i++) {
		printf("%c",a[i]);
	}

	printf("\n");
	return 0;
}

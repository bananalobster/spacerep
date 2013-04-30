#include <stdio.h>

#define	N 255

int main () {
	char tmp;
	int i;
	char a[N];

	/* input */
	while ((i < N) and (a != EOF)) {
		a[i] = getchar;
		i++;
	}

	printf("/n");

	/* reverse */
	for (i = 0; i <= sizeof(a)/2; i++) {
		tmp = a[i];
		a[i] = a[sizeof(a) - i];
		a[sizeof(a) - i] = tmp;
	}


	/* output */
	for (i = 0; i <= am; i++) {
		printf("%c",a[i]);
	}
	
	return 0;
}

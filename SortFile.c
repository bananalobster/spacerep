#include <stdio.h>

#define	N 256

int main(){
	FILE * f;
	int len = -1, fl, q, tmp, a[N];

	/* open file */
	f = fopen("text.txt","r");
	
	/* read from file */
	if (f == NULL) perror("Error opening file");
	else{
		while (feof(f) == 0){
			len++;
			fscanf(f, "%d", &a[len]);
		}
		fclose(f);
	}

	/* check input */
//	for (q = 0; q <= len; q++){
//		printf("%d\n", a[q]);
//	}

	/* sort */
	do{
		fl = 0;
		for (q = 0; q < len; q++){
			if (a[q] < a[q+1]){
				fl = 1;
				tmp = a[q];
				a[q] = a[q+1];
				a[q+1] = tmp;
			}
		}
	}while (fl != 0);

	/* rewrite file */
	f = fopen("text.txt","w");
	for (q = 0; q <= len-1; q++){
		fprintf(f, "%d\n", a[q]);
	}
	fprintf(f, "%d", a[len]);
	fclose(f);

	printf("Sort completed\n");
	return 0;
}

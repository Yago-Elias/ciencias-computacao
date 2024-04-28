#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contaChar(char str[], char c) {
	int i, cont = 0;
	for (i=0; i < strlen(str); i++) {
		if (str[i] == c)
			cont++;
	}
	return cont;
}

int main() {
	char s[] = "papagaio";
	int n = contaChar(s, 'a'); 
	printf("%s, n = %d\n", s, n);
	return 0;
}

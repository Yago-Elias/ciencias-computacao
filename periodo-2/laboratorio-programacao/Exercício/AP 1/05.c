#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apagaChar(char str[], char c) {
	int i;
	for (i=0; i < strlen(str); i++) {
		if (str[i] == c)
			str[i] = ' ';
	}
}

int main() {
	char s[] = "papagaio";
	
	apagaChar(s, 'a');
	
	printf("%s\n", s);
	return 0;
}

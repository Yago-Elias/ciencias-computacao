#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define T 5

int main() {
	int n, p, t=1;
	srand(time(NULL));	
	
	n = (rand() % 100) + 1;
	
	printf("A sorte foi lançada dê seu palpite!\n");
	
	while (1) {
		printf("palpite: ");
		scanf("%d", &p);
		
		if (p == n) {
			printf("Você venceu\n");
			break;
		}
		else {
			if (t == T) {
				printf("Você perdeu\n");
				break;
			}
			else {
				if (p < n)
					printf("Foi pouco\n");
				else
					printf("Foi muito\n");
			}
		}
		
		t++;
	}
	
	return 0;
}

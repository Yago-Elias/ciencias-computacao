#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	float notas[10][3];
	int i, pior[3] = {0};
	
	srand(time(NULL));
	
	for (i=0; i<10; i++) {
		notas[i][0] = (rand() % 100) / 10.0;
		notas[i][1] = (rand() % 100) / 10.0;
		notas[i][2] = (rand() % 100) / 10.0;
	}
	
	for (i=0; i<10; i++) {
		if (notas[i][0] < notas[i][1] && notas[i][0] < notas[i][2])
			pior[0]++;
		
		if (notas[i][1] < notas[i][0] && notas[i][1] < notas[i][2])
			pior[1]++;
		
		if (notas[i][2] < notas[i][0] && notas[i][2] < notas[i][1])
			pior[2]++;
			
		printf("%.2f %.2f %.2f\n", notas[i][0], notas[i][1], notas[i][2]);
	}
	
	printf("%d %d %d\n", pior[0], pior[1], pior[2]);
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define TAM 7

void printVector(int [], int);

int main(){
    int vetor[TAM] = {7,3,2,6,4,1,5}, x = 0, y = 0, aux = 0;
    
    printVector(vetor,TAM);
    
    for (x = 0; x < TAM-1; x++ ) {
        for(y = 0; y < TAM-1-x; y++) {
            if (vetor[y] > vetor[y+1]) {
                printf("%d<->%d ", vetor[y], vetor[y+1]);

                aux = vetor[y];
                vetor[y] = vetor[y+1];
                vetor[y+1] = aux;
            }
        }
        printf("\n");
        printVector(vetor,TAM);
    }
    return 0;
}
void printVector(int vetor[], int n){
    int x;
    for(x = 0; x < n; x++ )
        printf("[%d] ", vetor[x]);
    printf("\n");
}

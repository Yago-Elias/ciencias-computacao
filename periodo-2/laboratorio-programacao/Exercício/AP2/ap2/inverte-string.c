/*
Desenvolcido por Delair Cavalcante.

É apresentado nesse código uma forma de inverter strings de qualquer tamanho
*/
#include <stdio.h>

int main(){
    char palavra[30];
    int i = 0;
    printf("Escreva uma palavra\n");
    scanf("%[^\n]", palavra);
    while(1){
        if(palavra[i] == '\0'){
            break;
        }else{
            i = i + 1;
        }
    }
    printf("A palavra tem %d letras\n", i);
    char aux;
    int final = i - 1;

    int cont;
    if(i % 2 == 0){
        cont = i / 2;
    }else{
        cont = (i / 2) + 1;
    }

    for (int inicio = 0; inicio < cont; inicio++){
        aux = palavra[inicio];
        palavra[inicio] = palavra[final];
        palavra[final] = aux;
        final = final - 1;
    }
    printf("a palavra %s é a inversão?\n", palavra);

    return 0;

}
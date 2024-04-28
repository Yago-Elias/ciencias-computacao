#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

/*Crie uma estrutura Filme em C para guardar informações de filmes (nome e ano de lançamento).*/
typedef struct Filme
{
    int ano;
    char nome[40];
} filme;

int func(const void * a, const void * b)
{
    const int* ano1 = (const int*)a;
    const int* ano2 = (const int*)b;
    return (*(int*)a - *(int*)b);
}

/*
Leia a partir do arquivo de texto filmes.txt as informações de 20 filmes e registre-as em um vetor
com o tipo da estrutura que você criou.
*/
void film(filme f[])
{
    int i;
    FILE *file = fopen("filmes.txt", "r");
    if (file == NULL) exit(EXIT_FAILURE);
    
    for (i = 0; i < SIZE; ++i)
    {
        fscanf(file, "%[^ ]s", f[i].nome);
        fscanf(file, "%d", &f[i].ano);
    }
    fclose(file);
}

/*
Crie uma função que receba um vetor da estrutura Filme e ordene os filmes no vetor por ano
de lançamento, do mais recente para o mais antigo. Demonstre o uso da função imprimindo os
filmes ordenados.
*/
void sort_film(filme f[])
{
    int i;
    qsort(f, SIZE, sizeof(filme), func);
    printf("Filmes ordenados por ano de lançamento:");
    for (i = 0; i < SIZE; i++)
        printf("%s  %d", f[i].nome, f[i].ano);
    printf("\n");
}

/*
Grave em um novo arquivo de texto chamado filmes_ordenados.txt os filmes do vetor que foi
ordenado.
*/
void write_film(filme f[])
{
    int i;
    FILE *file = fopen("filmes_ordenados.txt", "a");
    if (file == NULL) exit(EXIT_FAILURE);
    for (i = 0; i < SIZE; i++)
        fprintf(file, "%s %d", f[i].nome, f[i].ano);
    fclose(file);
}

int main()
{
    filme filmes[SIZE];
    filme f[SIZE];
    film(filmes);
    sort_film(filmes);
    write_film(filmes);
    return 0;
}
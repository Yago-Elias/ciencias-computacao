#include <stdio.h>

struct Aluno
{
    unsigned int matricula: 14;
    unsigned int sexo: 1;
    unsigned int rendimento: 7;
    unsigned int primeira_vez: 1;
    unsigned int: 9;
} aluno;


int main()
{
    printf ("Tamanho: %d bytes\n", sizeof(aluno));
    return 0;
}

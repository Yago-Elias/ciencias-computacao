#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

typedef struct Aluno
{
    int matricula;
    float nota1, nota2, nota3;
} aluno;

aluno banco[SIZE];

FILE *open_file(char name_file[], char modo[])
{
    FILE *file = fopen(name_file, modo);
    if (file == NULL) exit(EXIT_FAILURE);
    return file;
}

void read_file()
{
    int i;
    FILE *file = open_file("notas50alunos.txt", "r");
    for (i = 0; i < SIZE; i++)
    {
        fscanf(file, "%d%f%f%f", 
        &banco[i].matricula, &banco[i].nota1, 
        &banco[i].nota2, &banco[i].nota3);
    }
}

void write_file()
{
    int i;
    FILE *file = open_file("notas50alunos.bin", "ab");
    for (i = 0; i < SIZE; i++)
        fwrite(&banco[i], sizeof(aluno), 1, file);
}

void find_student(int index)
{
    aluno find_aluno;
    int find;
    FILE *file = open_file("notas50alunos.bin", "rb");
    find = fseek(file, sizeof(aluno) * (index - 1), SEEK_SET);
    if (find == 0)
    {
        printf("\nAchou aluno: %d\n", find);
        fread(&find_aluno, sizeof(aluno), 1, file);
        printf("\tMatrícula: %d\n\tNota 1: %.1f\n\tNota 2: %.1f\n\tNota 3: %.1f", 
        find_aluno.matricula, find_aluno.nota1, find_aluno.nota2, find_aluno.nota3);
    }
    else
        printf("Matrícula não encontrado\n");
}

int main()
{
    int i;
    read_file();
    for (i = 0; i < SIZE; i++)
        printf("\n[%d] Matrícula: %d\nNota 1: %.1f\nNota 2: %.1f\nNota 3: %.1f", 
    i+1, banco[i].matricula, banco[i].nota1, banco[i].nota2, banco[i].nota3);
    
    //write_file();
    //find_student(5);
    
    return 0;
}
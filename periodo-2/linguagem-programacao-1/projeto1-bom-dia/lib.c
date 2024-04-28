#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

/*
Abri o arquivo que contém as opções suportadas pelo software retornando um ponteiro de arquivo, 
caso ocorra o erro ao tentar abrir, o programa é encerrado
*/
FILE* abrir_aqruivo ()
{
    FILE* arquivo;
    arquivo = fopen ("ajuda.txt", "r");

    if (arquivo == NULL)
    {
        exit(EXIT_FAILURE);
    }
    return arquivo;
}

/*
Ler o conteúdo do arquivo e mostra na tela, depois encerra o programa
*/
void ajuda ()
{
    FILE* arquivo = abrir_aqruivo ();
    char caractere;
    while (1)
    {
        fread (&caractere, sizeof (caractere), 1, arquivo);
        if (feof (arquivo))
        {
            printf ("\n");
            break;
        }
        printf ("%c", caractere);
    }
    fclose (arquivo);
    exit (0);
}

void versao ()
{
    printf ("bomdia 1.0\nCopyright (C) 2022.\nEste é o software livre: você é livre para alterá-lo e redistribuí-lo.");
    printf ("\nNão há garantia, na medida do permitido por lei.\n\nEscrito por Yago Elias.\n");
    exit (0);
}

int parametro (const char *parametro)
{
    if (!strcmp(parametro, "--pt") || !strcmp(parametro, "-1"))
        return 0;
    else if (!strcmp(parametro, "--en") || !strcmp(parametro, "-2"))
        return 1;
    else if (!strcmp(parametro, "--es") || !strcmp(parametro, "-3"))
        return 2;
    else if (!strcmp(parametro, "--fr") || !strcmp(parametro, "-4"))
        return 3;
    else if (!strcmp(parametro, "--it") || !strcmp(parametro, "-5"))
        return 4;
    else if (!strcmp(parametro, "--ru") || !strcmp(parametro, "-6"))
        return 5;
    else if (!strcmp(parametro, "--ko") || !strcmp(parametro, "-7"))
        return 6;
    else if (!strcmp(parametro, "--ja") || !strcmp(parametro, "-8"))
        return 7;
    else if (!strcmp(parametro, "--help") || !strcmp(parametro, "-h"))
    {
        ajuda ();
    }
    else if (!strcmp(parametro, "--version") || !strcmp(parametro, "-v"))
    {
        versao ();
    }
    else
        return -1;
}

void erro (const char *parametro)
{
    /*
    Pode haver diferentes formas de argumentos que o programa precisa tratar, assim é verificado o 
    caso de haver uma letra ou palavra, e mostra na tela que esses argumentos não são válidos no programa
    */

    // Guarda o tamanho da string para verificar se o argumento está no formato '-h', '--help', 'h' ou 'help'.
    //E de acordo com o tamanho é possível prever seu formato
    int comprimento = strlen (parametro);

    // Caso de ser uma ou mais letras qualquer sem o traço '-'. Exemplo: ./bomdia a, ./bomdia h, ./bomdia help
    if (parametro[0] != '-')
        printf ("bomdia: opção inválida - '%s'\nUse './bomdia --help' para mais informações\n", parametro);
    
    // Caso de ser uma letra qualquer com o traço '-'. Exemplo: ./bomdia -a, ./bomdia -k
    else if (comprimento == 2)
    {
        char argumento = parametro[1];
        printf ("bomdia: opção inválida - '%c'\nUse './bomdia --help' para mais informações\n", argumento);
    }
    // Caso de ser uma string com mais de dois caracteres.
    else if (comprimento > 2)
        printf ("bomdia: opção inválida - '%s'\nUse './bomdia --help' para mais informações\n", parametro);

    exit (0);
}
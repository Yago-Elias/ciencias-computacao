#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"

int main (int argc, char const *argv[])
{
    int lingua;
    // vetor de string contendo a mensagem 'bom dia' em diferentes idiomas
    char bomDia[8][50] = {
        "Bom dia", "Goode morning", "Buen día", "Bonjour", 
        "Buongiorno", "Доброе утро", "좋은 아침이에요", "おはよう"
    };
    
    // Se não for fornecido nenhum argumento será mostrado uma mensagem de erro seguido das opções
    if (argc == 1)
    {
        printf ("bomdia: operando ausente\n");
        ajuda ();
    }
    // Mostra a mensagem 'bom dia' de acordo com a especificação do idioma
    else if (argc == 2)
    {
        // A função retorna um inteiro que é usado como índice do vetor se for diferente de -1 e encerra o programa
        lingua = parametro (argv[1]);
        if (lingua != -1)
        {
            printf ("%s\n", bomDia[lingua]);
            exit (0);
        }
    }
    // Se o número de argumentos for mais que dois será mostrado uma mensagem de erro
    else if (argc > 2)
    {
        printf ("bomdia: permitido apenas 1 operando\nUse './bomdia --help' para mais informações\n");
        return 0;
    }
    
    erro (argv[1]);
}
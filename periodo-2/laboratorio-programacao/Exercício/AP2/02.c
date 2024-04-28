#include <stdio.h>

struct Produto
{
    unsigned int codigo: 31;
    unsigned int excluido: 1;
    char nome[20];
    char marca[20];
    float preco;
};

int menu ();
void cadastrar (struct Produto prod[], int cod, int indice);
void excluir (struct Produto prod[]);
void listar (struct Produto prod[]);


int main()
{
    int opcao, codigo=0, indice=0;
    struct Produto bd_produto[100] = {0, 0, " ", " ", 0.0};

    while (1)
    {
        opcao = menu ();
        switch (opcao)
        {
        case 1:
            codigo += 1;
            cadastrar (bd_produto, codigo, indice);
            indice += 1;
            break;
        case 2:
            excluir (bd_produto);
            break;
        case 3:
            listar (bd_produto);
            break;
        default:
            printf ("====================================\n");
            printf ("           OPÇÃO INVÁLIDA           \n");
        }

    }
    
    return 0;
}

int menu ()
{
    int opcao;

    printf ("====================================\n");
    printf (" [1]   Cadastrar um produto         \n");
    printf (" [2]   Excluir um produto           \n");
    printf (" [3]   Listar produtos              \n");
    printf ("====================================\n >");
    scanf (" %d", &opcao);
    return opcao;
}

void cadastrar (struct Produto prod[], int cod, int indice)
{
    prod[indice].codigo = cod;
    printf (" Nome: ");
    scanf ("%s", prod[indice].nome);
    printf (" Marca: ");
    scanf ("%s", prod[indice].marca);
    printf (" reço: ");
    scanf (" %f", &prod[indice].preco);
}

void excluir (struct Produto prod[])
{
    int busca_codigo;

    printf (" Código: ");
    scanf (" %d", &busca_codigo);

    for (size_t i = 0; i < 100; i++)
    {
        if (prod[i].codigo != 0)
            if (prod[i].codigo == busca_codigo)
                prod[i].excluido = 1;
    }
    
}

void listar (struct Produto prod[])
{
    for (int i = 0; i < 100; i++)
    {
        if (prod[i].codigo != 0 && prod[i].excluido == 0)
        {
            printf (" cod %d\n nom %s\n mar %s\n pre %.2f\n", prod[i].codigo, prod[i].nome, prod[i].marca, prod[i].preco);
        }
        
    }
}
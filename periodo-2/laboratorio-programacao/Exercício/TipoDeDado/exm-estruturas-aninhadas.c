#include <stdio.h>

struct Endereco
{
	char rua[50];
	int numero;
};

struct Cadastro
{
	char nome[30];
	int idade;
	struct Endereco endereco;
};

int main()
{
	struct Cadastro c = {"Noeh", 82, {"R. dos Alagados", 105}};

	printf("%s %d anos: %s, %d\n", c.nome, c.idade, c.endereco.rua, c.endereco.numero);
	return 0;
}
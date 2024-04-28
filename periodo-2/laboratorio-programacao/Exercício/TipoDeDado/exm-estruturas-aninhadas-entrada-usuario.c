/*
Neste exemplo é tratado sobre a forma que o C trata a
entrada do usuário, e como fazer formatação no scanf
*/

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
	struct Cadastro c;

	//recebe os caracteres do buffer até o \n
	scanf ("%[^\n]", c.nome);
	scanf ("%d", &c.idade);

	//retira do buffer o caractere \n, para não ser obtido pelo próximo scanf
	scanf ("%*c");

	scanf ("%[^\n]", c.endereco.rua);
	scanf ("%d", &c.endereco.numero);

	printf("%s %d anos: %s, %d\n", c.nome, c.idade, c.endereco.rua, c.endereco.numero);
	return 0;
}
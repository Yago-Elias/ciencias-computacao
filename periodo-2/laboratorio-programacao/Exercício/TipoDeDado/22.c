#include <stdio.h>

struct Pessoa
{
	char nome[30];
	int idade;
	char endereco[50];
} pessoa;

int main()
{
	printf ("Nome: ");
	scanf ("%s", pessoa.nome);
	printf ("Idade: ");
	scanf ("%d", &pessoa.idade);
	printf ("Endereço: ");
	scanf ("%s", pessoa.endereco);

	printf ("Olá %s, você tem %d anos. E você mora na %s\n", pessoa.nome, pessoa.idade, pessoa.endereco);
	return 0;
}
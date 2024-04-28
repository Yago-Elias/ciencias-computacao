#include <stdio.h>

struct Pessoa
{
	char nome[30];
	int idade;
};

int main()
{
	int i, i_velha, i_nova, id_velha=0, id_nova=200;
	struct Pessoa pessoa[50];

	for (i = 0; i < 50; ++i)
	{
		scanf ("%s%d", pessoa[i].nome, &pessoa[i].idade);
		if (pessoa[i].idade < id_nova)
		{
			id_nova = pessoa[i].idade;
			i_nova = i;
		}
		if (pessoa[i].idade > id_velha)
		{
			id_velha = pessoa[i].idade;
			i_velha = i;
		}
	}

	printf("-- Pessoa mais velha --\n");
	printf ("Nome: %s\nIdade: %d\n", pessoa[i_velha].nome, pessoa[i_velha].idade);
	printf("-- Pessoa mais nova  --\n");
	printf ("Nome: %s\nIdade: %d\n", pessoa[i_nova].nome, pessoa[i_nova].idade);
	return 0;
}
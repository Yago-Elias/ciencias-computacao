#include <stdio.h>
#include <stdlib.h>

typedef struct Endereco
{
	unsigned int oct1:8;
	unsigned int oct2:8;
	unsigned int oct3:8;
	unsigned int oct4:8;
} endereco;

void inicializar (endereco ip[]);

int main()
{
	endereco ip[30];
	inicializar (ip);
	int i;

	printf ("\nTipo <endereco> %ld bytes\n", sizeof (endereco));

	for (i = 0; i < 30; ++i)
		printf("IP [%d]: %d.%d.%d.%d\n", i+1, ip[i].oct1, ip[i].oct2, ip[i].oct3, ip[i].oct4);

	return 0;
}

void inicializar (endereco ip[])
{
	int i, oct1, oct2, oct3, oct4;

	for (i = 0; i < 30; ++i)
	{
		oct1 = rand () % 256;
		oct2 = rand () % 256;
		oct3 = rand () % 256;
		oct4 = rand () % 256;

		ip[i].oct1 = oct1;
		ip[i].oct2 = oct2;
		ip[i].oct3 = oct3;
		ip[i].oct4 = oct4;
	}
}
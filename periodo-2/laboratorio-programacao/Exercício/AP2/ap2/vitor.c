#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum Naipe {paus=1, ourus, copas, espadas} naipe;

typedef struct Carta
{
	int numero;
	naipe np;
} carta;

void inicializar (carta baralho[]);
void embaralhar (carta *embaralhar[], carta baralho[]);

int main()
{
	carta baralho[52];
	carta *embaralhadas[52]={NULL};

	int i;

	inicializar (baralho);
	embaralhar (embaralhadas, baralho);

	for (i = 0; i < 52; ++i)
	{
		//printf(" %d %d\n", baralho[i].numero, baralho[i].np);
		printf(" %d %d\n", embaralhadas[i]->numero, embaralhadas[i]->np);
		/*switch (naipe)
		{
			case 1:
				if (baralho[i].numero == 11)
					printf(" 11 Valete paus\n");
				else if (baralho[i].numero == 12)
					printf(" 12 Dama paus\n");
				else if (baralho[i].numero == 13)
					printf(" 13 Rei paus\n");
				else
					printf(" %d %d paus\n", baralho[i].numero, baralho[i].np);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
		}*/
	}
	return 0;
}

void inicializar (carta baralho[])
{
	int i;
	for (i = 0; i < 52; ++i)
	{
		baralho[i].numero = i + 1;
		if (i < 13)
			baralho[i].np = paus;
		if (i >= 13 && i < 27)
			baralho[i].np = ourus;
		if (i >= 27 && i < 40)
			baralho[i].np = copas;
		if (i >= 40)
			baralho[i].np = espadas;
	}
}

void embaralhar (carta *embaralhar[], carta baralho[])
{
	int i, num, comp_num;
	srand (time(NULL));

	for (i = 0; i < 52; ++i)
	{
		num = rand () % 52;
		comp_num = 51 - num;
		embaralhar[i] = &baralho[num];
	}
}

/*aux = carta[rand];
carta[rand]=carta[rand];
aux
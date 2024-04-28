#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int numeroDePassageiros;
	char classe[30];
} VagaoDePassageiros;

typedef struct {
	char mercadoriaTransportada[30];
	float pesoEmToneladas;
} VagaoDeMercadoria;

typedef struct {
	char tipo;
	union {
		VagaoDePassageiros passageiros;
		VagaoDeMercadoria mercadoria;
	} carga;
} Vagao;

void printTrem(Vagao trem[], int tam);

int main() {
	VagaoDeMercadoria c[2] = {{"Trigo", 5.9}, {"Granito", 18.5}};
	VagaoDePassageiros p[3] = {{20,"primeira classe"}, {40,"classe economica"}, {32,"classe economica"}};
	Vagao trem[5] = {{'P', .carga.passageiros=p[0]}, {'M', .carga.mercadoria=c[0]}, {'P', .carga.passageiros=p[2]}, 
					 {'P', .carga.passageiros=p[1]}, {'M', .carga.mercadoria=c[1]}};
	printTrem(trem, 5);
    return 0;
}

void printTrem(Vagao trem[], int tam)
{
	for (int i = 0; i < tam; ++i)
	{
		if (trem[i].tipo == 'P')
		{
			printf("[%d, %s]\n", trem[i].carga.passageiros.numeroDePassageiros, trem[i].carga.passageiros.classe);
		}
		else
		{
			printf("[%s, %f]\n", trem[i].carga.mercadoria.mercadoriaTransportada, trem[i].carga.mercadoria.pesoEmToneladas);
		}
	}
}
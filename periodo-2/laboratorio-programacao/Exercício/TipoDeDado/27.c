#include <stdio.h>

struct Formulario
{
	unsigned int primeiraVisita:1;
	unsigned int visitarNovamente:1;
	unsigned int dedosPerdidos:5;
	unsigned int criancaPerdida:1;
	unsigned int quantosDias:8;
};

int main()
{
	int num, i, resposta, formulario[5]={0};
	struct Formulario visita[50];

	printf ("Número de pessoas que irão responder o questinário\n->");
	scanf ("%d", &num);

	for (i = 0; i < num; ++i)
	{
		printf ("=======================  %d° VISITA  =======================\n", i + 1);
		
		printf ("É sua primeira visita?\n->");
		scanf ("%d", &resposta);
		visita[i].primeiraVisita = resposta;

		printf ("Pretende nos visitar novamente?\n->");
		scanf ("%d", &resposta);
		visita[i].visitarNovamente = resposta;

		printf ("Número de dedos perdidos no aquário das piranhas:\n->");
		scanf ("%d", &resposta);
		visita[i].dedosPerdidos = resposta;

		printf ("Você perdeu uma criança na exibição dos tubarões?\n->");
		scanf ("%d", &resposta);
		visita[i].criancaPerdida = resposta;

		printf ("Quantos dias da semana você passaria aqui se fosse possível?\n->");
		scanf ("%d", &resposta);
		visita[i].quantosDias = resposta;
		printf ("============================================================\n");

		if (visita[i].primeiraVisita)
			formulario[0] += 1;
		if (visita[i].visitarNovamente)
			formulario[1] += 1;
		if (visita[i].dedosPerdidos)
			formulario[2] += visita[i].dedosPerdidos;
		if (visita[i].quantosDias)
			formulario[3] += visita[i].quantosDias;
	}
	formulario[4] = formulario[3] / num;

	printf ("Primeira visita: %d\n", formulario[0]);
	printf ("Visitar novamente: %d\n", formulario[1]);
	printf ("Dedos perdidos: %d\n", formulario[2]);
	printf ("Médias de visitas: %d\n", formulario[4]);

	return 0;
}
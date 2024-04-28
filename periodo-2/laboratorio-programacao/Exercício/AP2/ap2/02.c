#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	int num_voo;
	char cod_origem[4];
	char cod_destino[4];
	char hora[4];
	char minuto[4];
} reserva;

int main()
{
	int i, x, y, hora, minuto, segundo1, segundo2;
	reserva passagem[300], aux;

	for (i = 0; i < 300; ++i)
		scanf (" %d %s %s %[0-9] %*c %[0-9] %*c", &passagem[i].num_voo, passagem[i].cod_origem,
			passagem[i].cod_destino, passagem[i].hora, passagem[i].minuto);

	for (x = 0; x < 300-1; x++ )
	{
        for(y = 0; y < 300-1-x; y++)
        {
        	hora = atoi(passagem[y].hora);
        	minuto = atoi(passagem[y].minuto);
        	segundo1 = 3600 * hora + 60 * minuto;

        	hora = atoi(passagem[y+1].hora);
        	minuto = atoi(passagem[y+1].minuto);
        	segundo2 = 3600 * hora + 60 * minuto;
            
            if (segundo1 > segundo2)
            {
                aux = passagem[y];
                passagem[y] = passagem[y+1];
                passagem[y+1] = aux;
            }
        }
    }

    for (i = 0; i < 300; ++i)
    {
    	printf("%d %s %s %s:%s\n", passagem[i].num_voo, passagem[i].cod_origem,
			passagem[i].cod_destino, passagem[i].hora, passagem[i].minuto);
    }
	return 0;
}
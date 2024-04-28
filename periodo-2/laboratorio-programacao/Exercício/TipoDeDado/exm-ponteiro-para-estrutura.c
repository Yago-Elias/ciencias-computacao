/*
Exemplo que trata sobre o uso de ponteiro para estruturas, 
como acessar as variáveis do ponteiro.
*/

#include <stdio.h>

struct Ponto
{
	int x, y;
};

int main()
{
	struct Ponto r = {3, 4};
	struct Ponto *p;

	/*a seguinte atribuição é válido apenas quando as variáveis 
	são declaradas do mesmo tipo
	*/
	p = &r;

	/*
	ao se tratar de ponteiro, primeiro deve ser informado
	para o mesmo que estamos pedindo para ele acessar o valor
	que está armazenado no endereço que ele guardou.
	*/
	printf("%d %d\n", (*p).x, (*p).y);

	//mostra o endereço da memória do ponteiro p
	printf("%d\n", p);
	return 0;
}
/*
É passado como parâmetro o argumento fornecido na execusão do programa, onde será verificado e retornar um valor inteiro que corresponderá ao índice do vetor declarado no main, em caso de não haver argumento será retornado -1, indicando a inexistência do mesmo no programa
*/
int parametro (const char *parametro);

/*
Exibe na tela erros relacionados ao argumento que não existe no programa
*/
void erro (const char *parametro);

/*
Exibe na tela as opções que o programa pode executar
*/
void ajuda ();

/*
Exibe na tela a versão do programa
*/
void versao ();
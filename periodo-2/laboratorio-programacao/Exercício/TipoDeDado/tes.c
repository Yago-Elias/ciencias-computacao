#include <stdio.h>
#include "f_26.h"

int main()
{
	int bg1 = 104, bg2 = 44; 
	printf ("\033[%dm \u265a \033[m", bg1);
	printf ("\033[%dm \u265a \033[m\n", bg2);
	return 0;
}
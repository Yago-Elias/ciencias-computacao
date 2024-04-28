#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tipoDado30.h"

int main()
{
    int opc_menu, indice_paciente=0, indice_medico=0, indice_consulta=0;
    cadastro pacientes[5] = {0, " ", " ", " "}, medicos[3] = {0, " ", " ", " "};
    consulta consultas[30] = {0, 0, 0, 0, " "};

    while (1)
    {
        mostra_dados (consultas, pacientes, medicos);
        opc_menu = menu ();

        switch (opc_menu)
        {
        case 1:
            cadastrar (pacientes, &indice_paciente, 5);
            break;
        case 2:
            cadastrar (medicos, &indice_medico, 3);
            break;
        case 3:
            cadastrar_consulta (consultas, &indice_consulta);
            break;
        case 4:
            pesquisar_consulta (consultas, medicos, pacientes);
            break;
        case 5:
            relatorio (consultas, pacientes);
            break;
        default:
            system ("clear");
            printf ("==================================\n");
            printf ("          OPÇÃO INVÁLIDA          \n");
            break;
        }   
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tipoDado30.h"

int menu ()
{
    int opcao;

    printf ("==================================\n");
    printf (" [1] Cadastrar paciente           \n");
    printf (" [2] Cadastrar médico             \n");
    printf (" [3] Cadastrar consulta           \n");
    printf (" [4] Pesquisar consulta do médico \n");
    printf (" [5] Relatório das consultas/dia  \n");
    printf ("==================================\n>");
    scanf (" %d", &opcao);    
    return opcao;
}

int verifica_codigo (cadastro cadastros[], int tamanho, int codigo, int indice)
{
    int i;
    for (i = 0; i < tamanho; i++)
        if (i != indice && cadastros[i].codigo == codigo)
            return 1;
    return 0;
}

int cadastrar (cadastro cadastros[], int *indice, int tamanho)
{
    int i = *indice;
    int codigo_valido, codigo;
    if (i < tamanho)
    {
        system ("clear");
        printf ("==================================\n");
        do
        {
            printf (" Código: ");
            scanf (" %d", &cadastros[i].codigo);
            codigo = cadastros[i].codigo;
            codigo_valido = verifica_codigo (cadastros, tamanho, codigo, i);

        } while (codigo_valido);
        printf (" Nome: ");
        scanf (" %[^\n]", cadastros[i].nome);
        printf (" Endereço: ");
        scanf (" %[^\n]", cadastros[i].endereco);
        printf (" Fone: ");
        scanf (" %[^\n]", cadastros[i].fone);
        printf ("==================================\n");
        sleep (1);
        system ("clear");
        printf ("==================================\n");
        printf ("  CADASTRO REALIZADO COM SUCESSO  \n");
        *indice += 1;
    }
    else
    {
        system ("clear");
        printf ("==================================\n");
        printf (" NÃO HÁ MAIS VAGAS PARA CADASTRAR \n");
    }
}

int verifica_codigo_consulta (consulta consultas[], int tamanho, int codigo)
{
    int i;
    for (i = 0; i < tamanho; i++)
        if (consultas[i].codigo == codigo)
            return 1;
    return 0;
}

void cadastrar_consulta (consulta consultas[], int *indice)
{
    int i = *indice;
    int codigo_consulta_invalido=0, codigo;

    if (i < 30)
    {
        system ("clear");
        printf ("==================================\n");
        do
        {
            printf (" Número da consulta: ");
            scanf (" %d", &codigo);
            codigo_consulta_invalido = verifica_codigo_consulta (consultas, 30, codigo);
        } while (codigo_consulta_invalido);
        consultas[i].codigo = codigo;
        
        printf (" Dia da semana\n");
        printf ("  [1] Segunda\n  [2] Terça\n  [3] Quarta\n  [4] Quinta\n  [5] Sexta\n>");
        scanf (" %d", &consultas[i].diaSemana);
        printf (" Hora: ");
        scanf (" %s", consultas[i].hora);
        printf (" Código do médico: ");
        scanf (" %d", &consultas[i].codMed);
        printf (" Código do paciente: ");
        scanf (" %d", &consultas[i].codPac);
        system ("clear");
        printf ("==================================\n");
        printf (" CONSULTA CADASTRADA COM SUCESSO  \n");

        *indice += 1;
    }
    else
    {
        system ("clear");
        printf ("==================================\n");
        printf (" NÃO HÁ MAIS VAGAS PARA CADASTRAR \n");
    }
    
}

int busca (cadastro cadastros[], int tamanho, int busca_codigo)
{
    int i;
    for (i = 0; i < tamanho; i++)
        if (cadastros[i].codigo == busca_codigo)
            return i;
    return -1;
}

void dia_semana (int dia)
{
    switch (dia)
    {
    case segunda:
        printf ("Segunda-feira\n");
        break;
    case terca:
        printf ("Terça-feira\n");
        break;
    case quarta:
        printf ("Quarta-feira\n");
        break;
    case quinta:
        printf ("Quinta-feira\n");
        break;
    case sexta:
        printf ("Sexta-feira\n");
        break;
    }
}

void pesquisar_consulta (consulta consultas[], cadastro medico[], cadastro paciente[])
{
    int i, codigo_medico, dia, consulta=0, indice_medico, indice_paciente;

    system ("clear");
    printf ("==================================\n");

    mostra_dados (consultas, paciente, medico);

    printf (" Código do médico: ");
    scanf (" %d", &codigo_medico);
    printf (" Dia da semana\n");
    printf ("  [1] Segunda\n  [2] Terça\n  [3] Quarta\n  [4] Quinta\n  [5] Sexta\n >");
    scanf (" %d", &dia);
    printf ("==================================\n");
    sleep (1);
    system ("clear");

    consulta = 1;

    indice_medico = busca (medico, 3, codigo_medico);

    if (indice_medico != -1)
    {
        int codigo_paciente;

        printf ("======================================================================\n");
        printf (" Médico: %-25s Dia da semana: ", medico[indice_medico].nome);
        dia_semana (dia);
        
        printf ("======================================================================\n");
        printf (" N° da consulta | Código do paciente |        Nome do paciente        \n");
        for (i = 0; i < 30; i++)
        {
            if (consultas[i].codigo != 0)
                if (consultas[i].codMed == codigo_medico && consultas[i].diaSemana == dia)
                {
                    codigo_paciente = consultas[i].codPac;
                    indice_paciente = busca (paciente, 5, codigo_paciente);

                    printf ("----------------------------------------------------------------------\n");
                    printf ("   %-10d   |   %-14d   | %-30s\n", consultas[i].codigo, codigo_paciente, paciente[indice_paciente].nome);
                }
            else
                break;
        }
        printf ("======================================================================\n");
    }
    else
    {
        printf ("==================================\n");
        printf (" NÃO HÁ CONSULTAS COM ESSE MÉDICO \n");
    }
}

void relatorio (consulta consultas[], cadastro paciente[])
{
    int i, dia, indice_paciente, codigo_paciente;

    printf (" Dia da semana\n");
    printf ("  [1] Segunda\n  [2] Terça\n  [3] Quarta\n  [4] Quinta\n  [5] Sexta\n>");
    scanf (" %d", &dia);

    printf ("======================================================================\n");
    printf (" Dia da semana | ");
    dia_semana (dia);
    printf ("======================================================================\n");
    printf (" Código do paciente |        Nome do paciente                         \n");
    for (i = 0; i < 30; i++)
    {
        if (consultas[i].codigo != 0)
        {
            switch (dia)
            {
                case segunda:
                    codigo_paciente = consultas[i].codPac;
                    indice_paciente = busca (paciente, 5, codigo_paciente);
                    printf ("----------------------------------------------------------------------\n");
                    printf ("  %-14d   | %-30s\n", codigo_paciente, paciente[indice_paciente].nome);
                    break;
                case terca:
                    codigo_paciente = consultas[i].codPac;
                    indice_paciente = busca (paciente, 5, codigo_paciente);
                    printf ("----------------------------------------------------------------------\n");
                    printf ("  %-14d   | %-30s\n", codigo_paciente, paciente[indice_paciente].nome);
                    break;
                case quarta:
                    codigo_paciente = consultas[i].codPac;
                    indice_paciente = busca (paciente, 5, codigo_paciente);
                    printf ("----------------------------------------------------------------------\n");
                    printf ("  %-14d   | %-30s\n", codigo_paciente, paciente[indice_paciente].nome);
                    break;
                case quinta:
                    codigo_paciente = consultas[i].codPac;
                    indice_paciente = busca (paciente, 5, codigo_paciente);
                    printf ("----------------------------------------------------------------------\n");
                    printf ("  %-14d   | %-30s\n", codigo_paciente, paciente[indice_paciente].nome);
                    break;
                case sexta:
                    codigo_paciente = consultas[i].codPac;
                    indice_paciente = busca (paciente, 5, codigo_paciente);
                    printf ("----------------------------------------------------------------------\n");
                    printf ("  %-14d    | %-30s\n", codigo_paciente, paciente[indice_paciente].nome);
                    break;
            }
        }
    }
    printf ("======================================================================\n");
    
}

void mostra_dados (consulta consultas[], cadastro paciente[], cadastro medico[])
{
    int i;

    for (i = 0; i < 30; i++)
        if (consultas[i].codigo != 0)
            printf ("%d %d %d %d %s\n", consultas[i].codigo, consultas[i].codMed, consultas[i].codPac, consultas[i].diaSemana, consultas[i].hora);
    for (i = 0; i < 5; i++)
        if (i < 5 && paciente[i].codigo != 0)
            printf ("%d %s\n", paciente[i].codigo, paciente[i].nome);
    for (i = 0; i < 3; i++)
        if (i < 3 && medico[i].codigo != 0)
            printf ("%d %s\n", medico[i].codigo, medico[i].nome);
}
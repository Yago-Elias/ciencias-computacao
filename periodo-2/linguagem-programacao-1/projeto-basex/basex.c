#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

enum Error {MISSING_ARGUMENTS=1, EXCEEDED_ARGUMENTS, INVALID_PARAMETER, INVALID_INPUT, INVALID_BASE};
enum Parameter {ALL=20, HELP, BIN=2, OCT=8, DEC=10, HEX=16};

void error(int argc, char *argv[]);
int to_decimal(char number[], int base);
void to_base(int number, int base);
void execute(int argc, char *argv[]);

enum Error code_error=0;
char number_out[30];
char message_error[][61] = {
    "Parâmetro(s) ausente(s)\nMais detalhes: ./basex --help", "Limite de parâmetro ultrapassado", 
    "./basex: parâmetro de converção inválido -", "Base numérica ou número inválido", 
    "Parâmetro inválido ou ausente\nMais detalhes: ./basex --help"
};
char help[][71] = {
    {"Usage:\n ./basex [OPTION]\n ./basex NUMBER [BASE] [CONVERSION BASE]..."}, 
    {"BASE:\n --b, --o, --d, --h"}, 
    {"CONVERSION BASE:\n --b\t\tconvertion to binary base"}, 
    {" --o\t\tconvertion to octal base"}, 
    {" --d\t\tconvertion to decimal base"}, 
    {" --h\t\tconvertion to hexadecimal base"}, 
    {" --all\t\tconvertion to binary, octal, decimal and hexadecimal base,"}, 
    {"\t\texcept the base of the number itself"}, 
    {"OPTION:\n --help\t\tshow this help"}
};

int main(int argc, char *argv[])
{
    execute(argc, argv);
    return 0;
}

int base(char base[])
{
    if (base != NULL)
    {
        if (!strcmp(base, "--b")) return BIN;
        else if (!strcmp(base, "--o")) return OCT;
        else if (!strcmp(base, "--d")) return DEC;
        else if (!strcmp(base, "--h")) return HEX;
        else if (!strcmp(base, "--all")) return ALL;
        else if (!strcmp(base, "--help")) return HELP;
    }
    return INVALID_INPUT;
}

int check_number(char number[], int base)
{
    int i, character, length = strlen(number);
    int rule_bin, rule_oct, rule_dec, rule_hex;
    for (i = 0; i < length; i++)
    {
        character = toupper(number[i]);
        rule_bin = (character < '0' || character > '1');
        rule_oct = (character < '0' || character > '7');
        rule_dec = (character < '0' || character > '9');
        rule_hex = (rule_dec && (character < 'A' || character > 'F'));
        if (base == BIN && rule_bin) return INVALID_INPUT;
        if (base == OCT && rule_oct) return INVALID_INPUT;
        if (base == DEC && rule_dec) return INVALID_INPUT;
        if (base == HEX && rule_hex) return INVALID_INPUT;
    }
    return 0;
}

void error(int argc, char *argv[])
{
    int i, err, parameter_base=0, base_input=0, invalid_parameter=0;
    
    if (argc >= 3)
    {
        base_input = base(argv[2]);
        parameter_base = check_number(argv[1], base_input);
        for (i = 3; i < argc; i++)
            if (argv[i] != NULL && invalid_parameter != INVALID_INPUT)
                invalid_parameter = base(argv[i]);
            else break;
    }
    
    if (argc == 1) code_error = MISSING_ARGUMENTS;
    else if (argc == 2 && base(argv[1]) != HELP) code_error = INVALID_PARAMETER;
    else if (argc == 3) code_error = INVALID_PARAMETER;
    else if (base_input == INVALID_INPUT) code_error = INVALID_INPUT;
    else if (parameter_base != 0) code_error = INVALID_INPUT;
    else if (invalid_parameter == INVALID_INPUT) code_error = INVALID_BASE;

    switch (code_error)
    {
    case MISSING_ARGUMENTS: err =  0;
        break;
    case EXCEEDED_ARGUMENTS: err =  1;
        break;
    case INVALID_BASE: err =  2;
        break;
    case INVALID_INPUT: err =  3;
        break;
    case INVALID_PARAMETER: err =  4;
        break;
    default: err = -1;
    }
    if (err != -1)
    {
        if (err == 2)
            printf("%s '%s'\n", message_error[err], argv[--i]);
        else
            printf("%s\n", message_error[err]);
        exit(code_error);
    }
}

int to_decimal(char number[], int base)
{
    int i, index, length, character, k=0, num=0, value=1, number_dec=0;
    length = strlen(number);
    index = length - 1;

    for (i = 0; i < length; i++)
    {
        character = toupper(number[index]);
        num = character % '0';
        if (character >= 'A' && character <= 'F')
            num = character % 55;
        while (k < i)
        {
            value = value * base;
            k++;
        }
        number_dec += num * value;
        index--;
    }
    return number_dec;
}

void to_base(int number, int base)
{
    int i = 0, index, rest;
    char number_c[40] = {'\0'};
    char aux = 48;
    while (number >=  base)
    {
        rest = number % base;
        number = number / base;
        if (base == HEX && rest > 9) aux = 87;
        number_c[i] = rest + aux;
        aux = 48;
        i++;
    }
    rest = number;
    if (base == HEX && rest > 9) aux = 87;
    number_c[i] = number + aux;
    
    index = strlen(number_c) - 1;
    i = index;
    for (; i >= 0; i--)
        number_out[i] = number_c[index-i];
    number_out[++index] = '\0';
}

void execute(int argc, char *argv[])
{
    error(argc, argv);
    int i, base_out, base_input, number_input;
    int bases[] = {BIN, OCT, DEC, HEX};
    
    if (argc == 2)
    {
        if (base(argv[1]) == HELP)
            for (i = 0; i < 9; i++)
                printf("%s\n", help[i]);
    }
    else if (argc > 3)
    {
        base_input = base(argv[2]);
        if (base_input == DEC) number_input = atoi(argv[1]);
        else number_input = to_decimal(argv[1], base_input);

        if (base(argv[3]) == ALL)
        {
            printf("%s(%d)\n", argv[1], base_input);
            for (i = 0; i < 4; i++)
            {
                base_out = bases[i];
                if (base_input != base_out)
                {
                    to_base(number_input, base_out);
                    printf(">> %s(%d)\n", number_out, base_out);
                }
            }
        }
        else
        {
            printf("%s(%d)\n", argv[1], base_input);
            for (i = 3; i < 6; i++)
            {
                if (argv[i] != NULL)
                {
                    base_out = base(argv[i]);
                    to_base(number_input, base_out);
                    printf(">> %s(%d)\n", number_out, base_out);
                }
                else break;
            }
        }
    }
}
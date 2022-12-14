#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum error {MISSING_ARGUMENTS=1, EXCEEDED_ARGUMENTS, INVALID_PARAMETER, INVALID_INPUT, 
INVALID_BASE};
enum base {BIN=2, OCT=8, DEC=10, HEX=16};

void error(int argc, char const *argv[]);
void aux_convert(int number, int base);
void convert(int argc, char const *argv[]);
void execute(int argc, char const *argv[]);

int code_error=0;
char number_decimal[50];
char number_octal[50];
char number_hexadecimal[50];
char message_error[][50] = {
    "Argumentos ausentes", "Limite de argumento ultrapassado", "Parâmetro inválido", 
    "Base inválida"
};

int main(int argc, char const *argv[])
{
    execute(argc, argv);
    return 0;
}

int base(const char base[])
{
    if (!strcmp(base, "--b")) return BIN;
    else if (!strcmp(base, "--o")) return OCT;
    else if (!strcmp(base, "--d")) return DEC;
    else if (!strcmp(base, "--h")) return HEX;
    return 0;
}

int check_base(const char number[], int base)
{
    int i, len = strlen(number);
    for (i = 0; i < len; i++)
    {
        int rule_bin, rule_oct, rule_dec, rule_hex;
        rule_bin = (number[i] < '0' || number[i] > '1');
        rule_oct = (number[i] < '0' || number[i] > '7');
        rule_dec = (number[i] < '0' || number[i] > '9');
        rule_hex = (rule_dec || number[i] < 'a' || number[i] > 'f' || number[i] < 'A' || number[i] > 'F');
        if (base == BIN && rule_bin) return 1;
        if (base == OCT && rule_oct) return 1;
        if (base == DEC && rule_dec) return 1;
        if (base == HEX && rule_hex) return 1;
    }
    return 0;
}

void error(int argc, const char *argv[])
{
    int err, bs, parameter=0;

    if (argc >= 3)
    {
        bs = base(argv[2]);
        parameter = check_base(argv[1], bs);
    }

    if (argc == 1 || argc == 3) code_error = MISSING_ARGUMENTS;
    else if (argc > 6) code_error = EXCEEDED_ARGUMENTS;
    else if (parameter) code_error = INVALID_INPUT;
    else if (bs == 0) code_error = INVALID_BASE;
    
    switch (code_error)
    {
    case MISSING_ARGUMENTS:
        err =  0;
        break;
    case EXCEEDED_ARGUMENTS:
        err =  1;
        break;
    case INVALID_PARAMETER:
        err =  2;
        break;
    case INVALID_INPUT:
        err =  3;
        break;
    case INVALID_BASE:
        err =  3;
        break;
    default:
        err = -1;
        break;
    }
    if (err != -1)
    {
        printf("%s\n", message_error[err]);
        exit(code_error);
    }
}

//      0       1      2     3     4     5
// [./basex] [23456] [--d] [--b] [--h] [--0]

void aux_convert(int number, int base)
{
    int i = 0, rest=number;
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
    if (base == HEX && rest > 9) aux = 87;
    number_c[i] = number + aux;
    
    i = strlen(number_c) - 1;
    for (;i >= 0; i--)
        printf("%c", number_c[i]);
    printf("\n");
}

void convert(int argc, char const *argv[])
{
    int i, bs, number;
    
    if (argc == 2 && !strcmp(argv[1], "--help"))
    {
        printf("help\n");  
    }
    else if (argc > 2)
    {
        for (i = 3; i < 6; i++)
        {
            bs = base(argv[2]);
            number = atoi(argv[1]);
            if (argv[i] != NULL)
            {
                aux_convert(number, bs);

                // if (!strcmp(argv[i], "--all"))
                // {
                //     printf("Binário\n");
                //     printf("Octal\n");
                //     printf("Decimal\n");
                //     printf("Hexadeximal\n");
                // }
                // else if (!strcmp(argv[i], "--b"))
                //     printf("Binário\n");
                // else if (!strcmp(argv[i], "--o"))
                //     printf("Octal\n");
                // else if (!strcmp(argv[i], "--d"))
                //     printf("Decimal\n");
                // else if (!strcmp(argv[i], "--h"))
                //     printf("Hexadeximal\n");
            }
        }
    }
}

void execute(int argc, char const *argv[])
{
    error(argc, argv);
    convert(argc, argv);
}
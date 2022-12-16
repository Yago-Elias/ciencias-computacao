#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum error {ALL=20, MISSING_ARGUMENTS, EXCEEDED_ARGUMENTS, 
INVALID_PARAMETER, INVALID_INPUT, INVALID_BASE};
enum base {BIN=2, OCT=8, DEC=10, HEX=16};

void error(int argc, char const *argv[]);
int to_decimal(const char number[], int base);
void to_base(int number, int base);
void execute(int argc, char const *argv[]);

int code_error=0;
char number_base[50];
char message_error[][40] = {
    "Argumentos ausentes", "Limite de argumento ultrapassado", "Base numérica de converção inválida", 
    "Base numérica ou número inválido"
};
char help[][80] = {
    "./basex --help  |  ./basex [number] [base] [parameter]", "PARAMETER:", 
    "--b\t\t\tconversão para a base binária", "--o\t\t\tconversão para a base octal", 
    "--d\t\t\tconversão para a base decimal", "--h\t\t\tconversão para a base hexadecimal", 
    "--all\t\t\tconversão para a base binária, octal, decimal e hexadecimal", 
    "--help\t\t\texibe as bases de conversão"
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
    else if (!strcmp(base, "--all")) return ALL;
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
        rule_hex = (rule_dec && (number[i] < 'a' || number[i] > 'f'));
        if (base == BIN && rule_bin) return 1;
        if (base == OCT && rule_oct) return 1;
        if (base == DEC && rule_dec) return 1;
        if (base == HEX && rule_hex) return 1;
    }
    return 0;
}

void error(int argc, const char *argv[])
{
    int err, parameter_base=1, parameter_invalid=1, base_input=1;

    if (argc >= 3)
    {
        base_input = base(argv[2]);
        for (int i = 3; i < 6; i++)
            if (argv[i] != NULL && parameter_invalid != 0)
                parameter_invalid = base(argv[i]);
            else break;
        parameter_base = check_base(argv[1], base_input);
    }

    if (argc == 1 || argc == 3) code_error = MISSING_ARGUMENTS;
    else if (argc > 6) code_error = EXCEEDED_ARGUMENTS;
    else if (parameter_invalid == 0) code_error = INVALID_PARAMETER;
    else if (parameter_base) code_error = INVALID_INPUT;
    else if (base_input == 0) code_error = INVALID_BASE;
    
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

int to_decimal(const char number[], int base)
{
    int i, index, length, k=0, num=0, value=1, number_dec=0;
    length = strlen(number);
    index = length - 1;

    for (i = 0; i < length; i++)
    {
        num = number[index] % '0';
        if (number[index] >= 'a' && number[index] <= 'f')
            num = number[index] % 87;
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
        number_base[i] = number_c[index-i];
    number_base[index+1] = '\0';
}
//      0       1      2     3     4     5
// [./basex] [23456] [--d] [--b] [--h] [--0]
void execute(int argc, char const *argv[])
{
    error(argc, argv);
    int i, bs=0, base_input, number_input;
    int bases[] = {BIN, OCT, DEC, HEX};
    
    if (argc == 2)
    {
        if (!strcmp(argv[1], "--help"))
            for (i = 0; i < 8; i++)
                printf("%s\n", help[i]);
    }
    else if (argc > 3)
    {
        base_input = base(argv[2]);
        if (bs == DEC) number_input = atoi(argv[1]);
        else number_input = to_decimal(argv[1], base_input);

        if (base(argv[3]) == ALL)
        {
            for (i = 0; i < 4; i++)
            {
                bs = bases[i];
                if (base_input != bs)
                {
                    to_base(number_input, bs);
                    printf("%s(%d)  %s(%d)\n", argv[1], base_input, number_base, bs);
                }
            }
        }
        else
        {
            for (i = 3; i < 6; i++)
            {
                if (argv[i] != NULL)
                {
                    bs = base(argv[i]);
                    to_base(number_input, bs);
                    printf("%s(%d)  %s(%d)\n", argv[1], base_input, number_base, bs);
                }
                else break;
            }
        }
    }
}
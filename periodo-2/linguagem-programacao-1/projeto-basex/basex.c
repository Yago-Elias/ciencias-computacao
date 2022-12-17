#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INFO_VERSION "1.2.0"

enum error {MISSING_ARGUMENTS=1, EXCEEDED_ARGUMENTS, INVALID_PARAMETER, INVALID_INPUT, INVALID_BASE};
enum parameter {ALL=20, HELP, VERSION, BIN=2, OCT=8, DEC=10, HEX=16};

void error(int argc, char const *argv[]);
int to_decimal(const char number[], int base);
void to_base(int number, int base);
void execute(int argc, char const *argv[]);

enum error code_error=0;
char number_base[30];
char message_error[][61] = {
    "Parâmetro(s) ausente(s)\nMais detalhes: ./basex --help", "Limite de parâmetro ultrapassado", 
    "Parâmetro de converção inválido", "Base numérica ou número inválido", 
    "Parâmetro inválido ou ausente\nMais detalhes: ./basex --help"
};
char help[][105] = {
    "Usage:\n ./basex [options]\n ./basex [number] [base] [parameter]...", 
    "BASE:", " --b, --o, --d, --h", "PARAMETER:",  " --b\t\tconversão para a base binária", 
    " --o\t\tconversão para a base octal", " --d\t\tconversão para a base decimal", 
    " --h\t\tconversão para a base hexadecimal", 
    " --all\t\tconversão para a base binária, octal, decimal e hexadecimal,", 
    "\t\texceto a base do próprio número", "OPTIONS:", " --help\t\tmostra esta ajuda", 
    " --verion\tmostra a versão atual do software"
};
char version[] = {"basex 1.2.0\nCopyright (c) 2022 Yago Elias\nMIT License\nWritten by Yago Elias\n"};

int main(int argc, char const *argv[])
{
    execute(argc, argv);
    return 0;
}

int base(const char base[])
{
    if (base != NULL)
    {
        if (!strcmp(base, "--b")) return BIN;
        else if (!strcmp(base, "--o")) return OCT;
        else if (!strcmp(base, "--d")) return DEC;
        else if (!strcmp(base, "--h")) return HEX;
        else if (!strcmp(base, "--all")) return ALL;
        else if (!strcmp(base, "--help")) return HELP;
        else if (!strcmp(base, "--version")) return VERSION;
    }
    return 0;
}

int check_base(const char number[], int base)
{
    int i, length = strlen(number);
    for (i = 0; i < length; i++)
    {
        int character, rule_bin, rule_oct, rule_dec, rule_hex;
        character = number[i];
        if (character >= 'A' && character <= 'F') character += 32;
        rule_bin = (character < '0' || character > '1');
        rule_oct = (character < '0' || character > '7');
        rule_dec = (character < '0' || character > '9');
        rule_hex = (rule_dec && (character < 'a' || character > 'f'));
        if (base == BIN && rule_bin) return 1;
        if (base == OCT && rule_oct) return 1;
        if (base == DEC && rule_dec) return 1;
        if (base == HEX && rule_hex) return 1;
    }
    return 0;
}

void error(int argc, const char *argv[])
{
    int err, parameter_base=0, parameter_invalid=1, base_input=1;
    
    if (argc == 2)
        parameter_invalid = (base(argv[1]) == HELP || base(argv[1]) == VERSION);
    else if (argc >= 3)
    {
        base_input = base(argv[2]);
        for (int i = 3; i < 6; i++)
            if (argv[i] != NULL && parameter_invalid != 0)
                parameter_invalid = base(argv[i]);
            else break;
        parameter_base = check_base(argv[1], base_input);
    }
    if (argc == 1 || argc == 3) code_error = MISSING_ARGUMENTS;
    else if (argc == 2 && parameter_invalid == 0) code_error = INVALID_PARAMETER;
    else if (argc > 6) code_error = EXCEEDED_ARGUMENTS;
    else if (base_input == 0 || parameter_base) code_error = INVALID_BASE;
    else if (parameter_invalid == 0) code_error = INVALID_INPUT;
    
    switch (code_error)
    {
    case MISSING_ARGUMENTS: err =  0;
        break;
    case EXCEEDED_ARGUMENTS: err =  1;
        break;
    case INVALID_INPUT: err =  2;
        break;
    case INVALID_BASE: err =  3;
        break;
    case INVALID_PARAMETER: err =  4;
        break;
    default: err = -1;
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
        if (num >= 'A' && num <= 'F')
            num += 32;
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

void execute(int argc, char const *argv[])
{
    error(argc, argv);
    int i, bs=0, base_input, number_input;
    int bases[] = {BIN, OCT, DEC, HEX};
    
    if (argc == 2)
    {
        if (base(argv[1]) == HELP)
        {
            for (i = 0; i < 13; i++)
                printf("%s\n", help[i]);
        }
        else if (base(argv[1]) == VERSION) printf("%s", version);
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {WRONG_WORD, CORRECT_WORD, REPEATED_LETTER, UNREPEATED_LETTER, LETTER_FOUND, 
LETTER_NOT_FOUND, SCREEN_SIZE=40} config;

void initialize(char word[], int size);
void execute();
int found_letter(char secret_word[], char word[], char letter);
void show_letters(char word[]);
int repeated_letter(char word[], char letter);
void print_erro(char erro[], int err);
void clear_screen();
void screen(char word[], int attempts);

int main()
{
	execute();
	return 0;
}

int found_letter(char secret_word[], char word[], char letter)
{
    int i;
    config found = LETTER_NOT_FOUND;
    for (i = 0; i < strlen(secret_word); i++)
    {
        if (secret_word[i] == letter)
        {
            word[i] = letter;
            found = LETTER_FOUND;
        }
    }
    return found;
}

void show_letters(char word[])
{
    int i, size = strlen(word), center_text;
    center_text = (SCREEN_SIZE - 2 * size) / 2;

    printf("\033[2;%dH", center_text);
    for (i = 0; i < size; i++)
        printf("%2c", word[i]);
}

int repeated_letter(char word[], char letter)
{
    int i = 0;
    while (word[i] != 0)
    {
        if (word[i] == letter)
            return REPEATED_LETTER;
        ++i;
    }
    return UNREPEATED_LETTER;
}

void print_erro(char erro[], int err)
{
    if (err != 0)
        printf(" %s\n", erro);
}

void initialie(char word[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        word[i] = '_';
}

void screen(char word[], int attempts)
{
    printf("\033[1J \033[1;1H");
    printf(
        "========================================\n"
        "|                                      |\n"
        "========================================\n");
    show_letters(word);
    printf("\n\n TRY [%d/5] ", attempts);
}

void execute()
{
    char secret_word[] = {"recursividade"};
	char word[20];
	char letras_escolhidas[26] = {0};
	char game[][41] = {"--------------  YOU WIN  ---------------", "--------------  YOU LOSE  --------------", "letra repetida"};
	char erros[][20] = {{"erro"}, {" "}};
	char letter;
	int attempts = 5, ind_letter = 0, result_game=WRONG_WORD;
	config conf;

	initialie(word, strlen(secret_word));

	while (attempts > 0)
	{
	    do
	    {
    	    screen(word, attempts);
    	    scanf(" %c", &letter);
    	    conf = repeated_letter(letras_escolhidas,  letter);
	        print_erro(erros[1], conf);
	    }while (conf == REPEATED_LETTER);

	    letras_escolhidas[ind_letter] = letter;
	    ind_letter++;

	    if (found_letter (secret_word, word, letter) == LETTER_NOT_FOUND)
	        attempts -= 1;
	    if (strcmp (secret_word, word) == 0)
	    {
	        result_game = CORRECT_WORD;
            screen(secret_word, attempts);
	        printf("\n%s\n", game[result_game]);
	        break;
	    }
	}
	if (result_game == CORRECT_WORD)
	{
	    screen(secret_word, attempts);
	    printf("\n%s\n", game[result_game]);
	}
}

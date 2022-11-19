#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {WRONG_WORD, CORRECT_WORD, REPEATED_LETTER, UNREPEATED_LETTER, 
LETTER_FOUND, LETTER_NOT_FOUND, SCREEN_SIZE=40} config;

void initialize(char word[], int size);
void execute();
int found_letter(char secret_word[], char word[], char letter);
void show_letters(char word[]);
int repeated_letter(char word[], char letter);
void print_erro(char erro[], int err);
void clear_screen();
void screen(char word[], int attempts);
int choose_word(char list_word);

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
    int i, size, center_text;
    size = strlen(word);
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

int choose_word(char list_word)
{
    return rand() % 21;
}

void initialize(char word[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        word[i] = '_';
    word[i] = '\0';
}

void screen(char word[], int attempts)
{
    printf("\033[1J \033[1;1H");
    printf(
        "========================================\n"
        "|                                      |\n"
        "========================================\n");
    show_letters(word);
    printf("\n\n TRY [%02d/10] ", attempts);
}

void execute()
{
    char list_word[20][15] = {
        {"algoritmo"}, {"internet "}, {"digital"}, {"holograma"}, 
        {"camelo"}, {"formiga"}, {"chinchila"}, {"coelho"}, 
        {"ervilha"}, {"alcachofra"}, {"espinafre"}, {"cogumelo"}, 
        {"submarino"}, {"triciclo"}, {"planador"}, {"caminhonete"}, 
        {"faculdade"}, {"intelecto"}, {"instrutor"}, {"pesquisa"}
    };
    srand(time(NULL));
    char secret_word[15], word[15], letter;
	char typed_letters[26] = {0};
	char game[][41] = {
        "--------------  YOU LOSE ---------------", 
        "--------------  YOU WIN ----------------", 
        "letra repetida"};
	char erros[][20] = {{"erro"}, {" "}};
	int attempts = 10, ind_letter = 0, result_game=WRONG_WORD, chosen_word;
	config conf;

    chosen_word = rand() % 21;
    strcpy(secret_word, list_word[chosen_word]);
	initialize(word, strlen(secret_word));

	while (attempts > 0 && result_game != CORRECT_WORD)
	{
	    do
	    {
    	    screen(word, attempts);
    	    scanf(" %c", &letter);
    	    conf = repeated_letter(typed_letters,  letter);
	        print_erro(erros[1], conf);
	    }while (conf == REPEATED_LETTER);

	    typed_letters[ind_letter] = letter;
	    ind_letter++;

	    if (found_letter (secret_word, word, letter) == LETTER_NOT_FOUND)
	        attempts -= 1;
	    if (strcmp (secret_word, word) == 0)
	        result_game = CORRECT_WORD;
	}
    screen(secret_word, attempts);
    printf("\n%s\n", game[result_game]);
}

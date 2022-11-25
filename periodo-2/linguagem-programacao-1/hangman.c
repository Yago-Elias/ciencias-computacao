#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define COLOR(result) (result == 1 ? BRIGHT_GREEN : BRIGHT_RED)

#define CLR_COLOR "\033[m"
#define BLUE "\033[1;94m"
#define BRIGHT_RED "\033[1;91m"
#define BRIGHT_GREEN "\033[1;92m"
#define YELLOW "\033[93m"

typedef enum {WRONG_WORD, CORRECT_WORD, REPEATED_LETTER, NOT_LETTER, UNREPEATED_LETTER, 
LETTER_FOUND, IS_LETTER, LETTER_NOT_FOUND, ERROR_OPEN_FILE, WORD_LENGTH=12, SCREEN_SIZE=40} config;

int found_letter(char secret_word[], char word[], char letter);
void show_letters(char word[]);
int check_input(char typed_letters[], char letter);
void init(char word[], int size);
void screen(char word[], int attempts, char game[][280], int error_code);
void choose_word(char select_word[]);
void execute();

int main()
{
	execute();
	return 0;
}

int found_letter(char secret_word[], char word[], char letter)
{
    int i, length = strlen(secret_word);
    letter = toupper(letter);
    config found = LETTER_NOT_FOUND;

    for (i = 0; i < length; i++)
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
    int i, length, center_text;
    length = strlen(word);
    center_text = (SCREEN_SIZE - 2 * length) / 2;

    printf("\033[2;%dH ", center_text);
    for (i = 0; i < length; i++)
        printf("%s%2c", YELLOW, word[i]);
    printf("%s", CLR_COLOR);
}

int check_input(char typed_letters[], char letter)
{
    int i = 0;
    if (isalpha(letter) != 0)
    {
        letter = toupper(letter);
        while (typed_letters[i] != '\0')
        {
            if (typed_letters[i] == letter)
                return REPEATED_LETTER;
            ++i;
        }
    return UNREPEATED_LETTER;
    }
    else
        return NOT_LETTER;
}

void init(char word[], int length)
{
    int i;
    for (i = 0; i < length; i++)
        word[i] = '_';
    word[i] = '\0';
}

void screen(char word[], int attempts, char game[][280], int error_code)
{
    int length, center_text;
    length = strlen(game[error_code]);
    center_text = (SCREEN_SIZE - length) / 2;

    printf("\033[1J \033[1;1H");
    printf(
        "%s╒════════════════════════════════════════╕\n"
        "╎                                        ╎\n"
        "╘════════════════════════════════════════╛%s\n", BLUE, CLR_COLOR);
    show_letters(word);
    
    if (error_code == REPEATED_LETTER || error_code == NOT_LETTER)
        printf("\033[1;%dH%s╡ %s %s╞", center_text, BLUE, game[error_code], BLUE);
    printf("\033[4;2H%s%s TRY [%02d/10]%s ", CLR_COLOR, YELLOW, attempts, CLR_COLOR);
}

void choose_word(char secret_word[])
{
    int word_position;
    char select_word[12];
	FILE* file = fopen("list_words.dat","rb");
	if (file == NULL)
	{
		printf("ERROR OPENING FILE\n");
		exit(ERROR_OPEN_FILE);
	}

    word_position = rand() % 21;
    fseek(file, WORD_LENGTH * word_position, SEEK_SET);
    fread(&select_word, sizeof(char), WORD_LENGTH, file);
    strcpy(secret_word, select_word);
	fclose(file);
}

void execute()
{
    srand(time(NULL));
    char letter;
    char secret_word[15], word[15], typed_letters[22] = {"\0"};
	char game[][280] = {
        "YOU LOSE", 
        "YOU  WIN", 
        "REPEATED LETTER", 
        "NOT IS LETTER", 
        "TYPE ONLY ONE LETTER"
    };
	int attempts = 10, ind_letter = 0, result_game=WRONG_WORD, error_code;

    choose_word(secret_word);
	init(word, strlen(secret_word));

	while (attempts > 0 && result_game != CORRECT_WORD)
	{
	    do
	    {
    	    screen(word, attempts, game, error_code);
    	    scanf(" %c", &letter);
    	    error_code = check_input(typed_letters,  letter);
	    }while (error_code == REPEATED_LETTER || error_code == NOT_LETTER);
        error_code = UNREPEATED_LETTER;

	    typed_letters[ind_letter] = toupper(letter);
	    ind_letter++;

	    if (found_letter(secret_word, word, letter) == LETTER_NOT_FOUND)
	        attempts -= 1;
        else if (strcmp(secret_word, word) == 0)
	        result_game = CORRECT_WORD;
	}
    screen(secret_word, attempts, game, error_code);
    printf("\n%s═══════════════╡ %8s ╞═══════════════%s\n", COLOR(result_game), game[result_game], CLR_COLOR);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define RST_COLOR "\033[m"
#define BRIGHT_BLUE "\033[1;94m"
#define BRIGHT_RED "\033[1;91m"
#define BRIGHT_GREEN "\033[1;92m"
#define YELLOW "\033[93m"
#define COLOR(result) (result == FALSE ? BRIGHT_RED : BRIGHT_GREEN)

typedef enum {WRONG_WORD, CORRECT_WORD, REPEATED_LETTER, NOT_LETTER, IS_STRING, UNREPEATED_LETTER, 
LETTER_FOUND, LETTER_NOT_FOUND, ERROR_OPEN_FILE, WORD_LENGTH=12, SCREEN_SIZE=40} config;

void found_letter(char secret_word[], char word[]);
void error();
void show_letters(char word[], int line);
void user_input();
void init(char word[], int size);
void print_error();
void screen(char word[]);
void choose_word(char select_word[]);
void execute();

int attempts = 10, error_code, run_game=TRUE, result_game=WRONG_WORD;
char letter, str_input[20], typed_letters[22] = {"\0"};
const char game[][50] = {"YOU LOSE", "YOU  WIN", "REPEATED LETTER", "NOT IS LETTER", "TYPE ONLY ONE LETTER"};

int main()
{
	execute();
	return 0;
}

void found_letter(char secret_word[], char word[])
{
    int i, found, length = strlen(secret_word);
    found = LETTER_NOT_FOUND;

    for (i = 0; i < length; i++)
    {
        if (secret_word[i] == letter)
        {
            word[i] = letter;
            found = LETTER_FOUND;
        }
    }
    if (found == LETTER_NOT_FOUND) attempts -= 1;
}

void error()
{
    int ind_letter, center_text, i=0;
    error_code = 0;
    if (strlen(str_input) > 1) error_code = IS_STRING;
    else if (isalpha(letter) == FALSE) error_code = NOT_LETTER; 
    else if (isalpha(letter) != FALSE)
    {
        while (typed_letters[i] != '\0')
        {
            if (typed_letters[i] == letter)
            {
                error_code = REPEATED_LETTER;
                break;
            }
            i++;
        }
        if (error_code != REPEATED_LETTER)
        {
            ind_letter = strlen(typed_letters);
            typed_letters[ind_letter] = letter;
            error_code = UNREPEATED_LETTER;
        }
    }
}

void show_letters(char word[], int line)
{
    int i, length, center_text;
    length = strlen(word);
    center_text = (SCREEN_SIZE - 2 * length) / 2;
    printf("\033[%d;%dH ", line, center_text);
    for (i = 0; i < length; i++)
        printf("%s%2c", YELLOW, word[i]);
    printf("%s", RST_COLOR);
}

void user_input()
{
    scanf("%s", str_input);
    if (strlen(str_input) == 1)
        letter = toupper(str_input[0]);
}

void init(char word[], int length)
{
    int i;
    for (i = 0; i < length; i++)
        word[i] = '_';
    word[i] = '\0';
}

void print_error()
{
    int error=FALSE, center_text;
    if (error_code == REPEATED_LETTER || error_code == NOT_LETTER)
        error = error_code;
    else if (error_code == IS_STRING)
        error = error_code;
    else if (error_code == ERROR_OPEN_FILE)
    {
        printf("%s<ERROR OPENING FILE>%s\n", BRIGHT_RED, RST_COLOR);
        exit(ERROR_OPEN_FILE);
    }
    if (error != FALSE)
    {
        center_text = (SCREEN_SIZE - strlen(game[error])) / 2;
        printf("\033[1;%dH%s╡ %s %s╞", center_text, BRIGHT_BLUE, game[error], BRIGHT_BLUE);
    }
}

void screen(char word[])
{
    printf("\033[1J \033[1;1H");
    printf(
        "%s╒════════════════════════════════════════╕\n"
        "╎                                        ╎\n"
        "╎                                        ╎\n"
        "╎                                        ╎\n"
        "╞═[%02d/10]════════════════════════════════╛\n╎\n"
        "╘══╡%s\n", 
        run_game == TRUE ? BRIGHT_BLUE : COLOR(result_game), attempts, RST_COLOR);
    show_letters(word, 3);
    show_letters(typed_letters, 6);
    print_error();
    printf("\033[7;5H%s", BRIGHT_GREEN);
    if (run_game != TRUE)
        printf("\033[1;16H%s╡ %8s ╞%s\033[8;1H", COLOR(result_game), game[result_game], RST_COLOR);
}

void choose_word(char secret_word[])
{
    int word_position, err;
    char select_word[12];
	FILE* file = fopen("list_words.dat","rb");
	if (file == NULL)
		error_code = ERROR_OPEN_FILE;
    else
    {
        word_position = rand() % 21;
        fseek(file, WORD_LENGTH * word_position, SEEK_SET);
        fread(&select_word, sizeof(char), WORD_LENGTH, file);
        strcpy(secret_word, select_word);
        fclose(file);
    }
    error();
}

void execute()
{
    srand(time(NULL));
    int err;
    char secret_word[15], word[15];
    choose_word(secret_word);
	init(word, strlen(secret_word));

	while (run_game)
	{
	    do
	    {
    	    screen(word);
    	    user_input();
            error();
            err = (error_code == REPEATED_LETTER || error_code == NOT_LETTER || error_code == IS_STRING);
	    }while (err);

	    found_letter(secret_word, word);
        if (!strcmp(secret_word, word) == CORRECT_WORD)
	        result_game = CORRECT_WORD;
        run_game = (attempts > 0 && result_game != CORRECT_WORD);
	}
    screen(secret_word);
}

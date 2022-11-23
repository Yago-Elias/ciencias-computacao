#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef enum {WRONG_WORD, CORRECT_WORD, REPEATED_LETTER, UNREPEATED_LETTER, 
LETTER_FOUND, LETTER_NOT_FOUND, ERROR_OPEN_FILE, WORD_LENGTH=15, SCREEN_SIZE=40} config;

void initialize(char word[], int size);
void execute();
int found_letter(char secret_word[], char word[], char letter);
void show_letters(char word[]);
int repeated_letter(char typed_letters[], char letter);
void print_error(char error_message[][21], int error_code);
void screen(char word[], int attempts);
void choose_word(char select_word[]);

int main()
{
	execute();
	return 0;
}

int found_letter(char secret_word[], char word[], char letter)
{
    int i, size = strlen(secret_word);
    letter = toupper(letter);
    config found = LETTER_NOT_FOUND;

    for (i = 0; i < size; i++)
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
    //printf("\033[m");
}

int repeated_letter(char typed_letters[], char letter)
{
    int i = 0;
    letter = toupper(letter);
    while (typed_letters[i] != '\0')
    {
        if (typed_letters[i] == letter)
            return REPEATED_LETTER;
        ++i;
    }
    return UNREPEATED_LETTER;
}

void print_error(char error_message[][21], int error_code)
{
    int error = -1;
    switch (error_code)
    {
    case REPEATED_LETTER:
        error = 0;
        break;
    case 3:
        error = 1;
        break;
    }
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
        "\033[34m╒════════════════════════════════════════╕\033[m\n"
        "\033[34m╎                                        ╎\033[m\n"
        "\033[34m╘════════════════════════════════════════╛\033[m\n");
    show_letters(word);
    printf("\n\n TRY [%02d/10] ", attempts);
}

void choose_word(char secret_word[])
{
    int word_position;
    char select_word[15];
	FILE* file = fopen("list_words.dat","rb");
	if (file == NULL)
	{
		printf("ERROR OPENING FILE\n");
		exit(ERROR_OPEN_FILE);
	}

    word_position = rand() % 21;
    fseek(file, sizeof(char) * word_position, SEEK_SET);
    fread(&select_word, sizeof(char), WORD_LENGTH, file);
    strcpy(secret_word, select_word);
	fclose(file);
}

void execute()
{
    srand(time(NULL));
    char secret_word[15], word[15], typed_letters[26] = {"\0"}, letter;
	char game[][51] = {
        "\033[91m--------------  YOU LOSE ---------------\033[m", 
        "\033[92m--------------  YOU WIN ----------------\033[m", 
    };
	char error[][21] = {{"repeated letter"}, {"type only one letter"}};
	int attempts = 10, ind_letter = 0, result_game=WRONG_WORD;
	config error_code;

    choose_word(secret_word);
	initialize(word, strlen(secret_word));

	while (attempts > 0 && result_game != CORRECT_WORD)
	{
	    do
	    {
    	    screen(word, attempts);
            printf("%s\n", secret_word);
    	    scanf(" %c", &letter);
    	    error_code = repeated_letter(typed_letters,  letter);
	        print_error(error, error_code);
	    }while (error_code == REPEATED_LETTER);

	    typed_letters[ind_letter] = toupper(letter);
	    ind_letter++;

	    if (found_letter (secret_word, word, letter) == LETTER_NOT_FOUND)
	        attempts -= 1;
	    if (strcmp (secret_word, word) == 0)
	        result_game = CORRECT_WORD;
	}
    screen(secret_word, attempts);
    printf("\n%s\n", game[result_game]);
}

#define B_REI "\u2654"
#define B_RAINHA "\u2655"
#define B_TORRE "\u2656"
#define B_BISPO "\u2657"
#define B_CAVALO "\u2658"
#define B_P "\u2659"
#define P_REI "\u265a"
#define P_RAINHA "\u265b"
#define P_TORRE "\u265c"
#define P_BISPO "\u265d"
#define P_CAVALO "\u265e"
#define P_P "\u265f"

struct Soldado {
    char nome[10];
    int cor;
    int linha;
    int coluna;
};

void inicializar (struct Soldado *tabuleiro[8][8], struct Soldado pb[], struct Soldado pp[]);
void coordenada (int linha, char coluna, int *i, int *j);
int cor_fundo (int i, int j);
void mover_peca (struct Soldado *tabuleiro[8][8], struct Soldado peca[], int i, int j);
void interface (struct Soldado *tabuleiro[8][8]);
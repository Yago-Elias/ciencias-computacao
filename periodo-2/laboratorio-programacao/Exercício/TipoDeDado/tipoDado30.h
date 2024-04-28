enum semana {segunda=1, terca, quarta, quinta, sexta};

typedef struct Cadastro
{
    int codigo;
    char nome[30];
    char fone[12];
    char endereco[50];
} cadastro;

typedef struct Consulta
{
    int codigo, diaSemana, codMed, codPac;
    char hora[6];
} consulta;

int menu ();

int cadastrar (cadastro cadastros[], int *indice, int tamanho);

void cadastrar_consulta (consulta consultas[], int *indice);

void pesquisar_consulta (consulta consultas[], cadastro medico[], cadastro paciente[]);

void relatorio (consulta consultas[], cadastro cadastros[]);

void mostra_dados (consulta consultas[], cadastro paciente[], cadastro medico[]);
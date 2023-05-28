#ifndef _DADOS_H_
#define _DADOS_H_
#include "constantes.h"

typedef struct
{
    char logradouro[50];
    char bairro[50];
    char cidade[50];
    char estado[10];
    char numero[10];
} Endereco;

typedef struct
{
    char matricula[10];
    char cpf[12];
    char nome[50];
    Endereco *endereco;
} Aluno;

typedef struct
{
    char matricula[10];
    char cpf[12];
    char nome[50];
    Endereco *endereco;
} Professor;

typedef struct
{
    char codigo[10];
    char nome_disciplina[50];
    Professor *professor;
    Aluno lista_alunos[MAX_ALUNO];
    float media_turma;
} Turma;


Endereco *criarEndereco(
                        char *logradouro,
                        char *bairro,
                        char *cidade,
                        char *estado,
                        char *numero
);

void destruirEndereco(Endereco *);

Aluno *criarAluno(
                char *matricula,
                char *cpf,
                char *nome,
                Endereco *end
);

Aluno *atualizarAluno(
                char *matricula,
                char *cpf,
                char *nome,
                Endereco *end
);


void destruirAluno(Aluno *aluno);

Professor *criarProfessor(
                    char *matricula,
                    char *cpf,
                    char *nome,
                    Endereco *end
);

Professor *atualizarProfessor(
                    char *matricula,
                    char *cpf,
                    char *nome,
                    Endereco *end
);

void destruirProfessor(Professor *);

Turma *criarTurma(
                char *codigo,
                char *nome_disciplina,
                Professor *professor,
                Aluno *lista_alunos,
                float *media_turma
);

Turma *atualizarTurma(
                char *codigo,
                char *nome_disciplina,
                Professor *professor,
                Aluno *lista_alunos,
                float *media_turma
);

void destruirTurma(Turma *);



#endif
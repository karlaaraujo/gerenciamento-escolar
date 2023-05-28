#include "dados.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Aluno *criarAluno(char *matricula,
                  char *cpf,
                  char *nome,
                  Endereco *end)
{
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));

    if (aluno)
    {
        strcpy(aluno->matricula, matricula); 
        strcpy(aluno->cpf, cpf);
        strcpy(aluno->nome, nome);
        aluno->endereco = end;
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }
    
    return aluno;
}

void destruirAluno(Aluno *aluno)
{
    if (aluno)
    {
        Endereco *end = aluno->endereco;
        destruirEndereco(end);
        free(aluno);
    }
}

Endereco *criarEndereco(char *logradouro,
                        char *bairro,
                        char *cidade,
                        char *estado,
                        char *numero)
{
    Endereco *endereco = (Endereco *)malloc(sizeof(Endereco));

    if (endereco)
    {
        strcpy(endereco->logradouro, logradouro);
        strcpy(endereco->bairro, bairro);
        strcpy(endereco->cidade, cidade);
        strcpy(endereco->estado, estado);
        strcpy(endereco->numero, numero);
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }

    return endereco;
}

void destruirEndereco(Endereco *endereco)
{
    if (endereco)
        free(endereco);
}

Professor *criarProfessor(char *matricula,
                  char *cpf,
                  char *nome,
                  Endereco *end)
{
    Professor *professor = (Professor *)malloc(sizeof(Professor));

    if (professor)
    {
        strcpy(professor->matricula, matricula); 
        strcpy(professor->cpf, cpf);
        strcpy(professor->nome, nome);
        professor->endereco = end;
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }

    return professor;
}

void destruirProfessor(Professor *professor)
{
    if (professor)
    {
        Endereco *end = professor->endereco;
        destruirEndereco(end);
        free(professor);
    }
}

Turma *criarTurma(
                char *codigo,
                char *nome_disciplina,
                Professor *professor,
                Aluno *lista_alunos,
                float *media_turma
)
{
    Turma *turma = (Turma *)malloc(sizeof(Turma));

    if (turma)
    {
        strcpy(turma->codigo, codigo); 
        strcpy(turma->nome_disciplina, nome_disciplina);
        turma->professor = professor;
        turma->lista_alunos = lista_alunos;
        turma->media_turma = media_turma;
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }

    return turma;
}

void destruirTurma(Turma *turma)
{
    if (turma)
    {
        free(turma);
    }
}

#include "tratadores.h"
#include "menus.h"
#include <stdio.h>
#include "constantes.h"
#include <string.h>
#include "dados.h"
#include <stdlib.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

rapidjson::Value serializarEndereco(Endereco* endereco, rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value endereco_obj(rapidjson::kObjectType);

    rapidjson::Value logradouro(endereco->logradouro, allocator);
    endereco_obj.AddMember("logradouro", logradouro, allocator);

    rapidjson::Value bairro(endereco->bairro, allocator);
    endereco_obj.AddMember("bairro", bairro, allocator);

    rapidjson::Value cidade(endereco->cidade, allocator);
    endereco_obj.AddMember("cidade", cidade, allocator);

    rapidjson::Value estado(endereco->estado, allocator);
    endereco_obj.AddMember("estado", estado, allocator);

    rapidjson::Value numero(endereco->numero, allocator);
    endereco_obj.AddMember("numero", numero, allocator);

    return endereco_obj;
}

void salvarDados(Aluno** alunos, int qtd_atual_aluno, Professor** professores, int qtd_atual_prof, Turmas** turmas, int qtd_atual_turma)
{
    FILE* arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Value alunos_array(rapidjson::kArrayType);
    for (int i = 0; i < qtd_atual_aluno; i++) {
        if (alunos[i] != NULL) {
            rapidjson::Value aluno_obj(rapidjson::kObjectType);
        
            rapidjson::Value matricula(alunos[i]->matricula, doc.GetAllocator());
            aluno_obj.AddMember("matricula", matricula, doc.GetAllocator());

            rapidjson::Value cpf(alunos[i]->cpf, doc.GetAllocator());
            aluno_obj.AddMember("cpf", cpf, doc.GetAllocator());

            rapidjson::Value nome(alunos[i]->nome, doc.GetAllocator());
            aluno_obj.AddMember("nome", nome, doc.GetAllocator());

            rapidjson::Value endereco(serializarEndereco(alunos[i]->endereco, doc.GetAllocator()), doc.GetAllocator());
            aluno_obj.AddMember("endereco", endereco, doc.GetAllocator());

            alunos_array.PushBack(aluno_obj, doc.GetAllocator());
        }
    }
    doc.AddMember("alunos", alunos_array, doc.GetAllocator());

    rapidjson::Value professores_array(rapidjson::kArrayType);
    for (int i = 0; i < qtd_atual_prof; i++) {
        if (professores[i] != NULL) {
            rapidjson::Value professor_obj(rapidjson::kObjectType);
          
            rapidjson::Value matricula(professores[i]->matricula, doc.GetAllocator());
            professor_obj.AddMember("matricula", matricula, doc.GetAllocator());

            rapidjson::Value cpf(professores[i]->cpf, doc.GetAllocator());
            professor_obj.AddMember("cpf", cpf, doc.GetAllocator());

            rapidjson::Value nome(professores[i]->nome, doc.GetAllocator());
            professor_obj.AddMember("nome", nome, doc.GetAllocator());

            rapidjson::Value endereco(serializarEndereco(professores[i]->endereco, doc.GetAllocator()), doc.GetAllocator());
            professor_obj.AddMember("endereco", endereco, doc.GetAllocator());

            professores_array.PushBack(professor_obj, doc.GetAllocator());
        }
    }
    doc.AddMember("professores", professores_array, doc.GetAllocator());

    rapidjson::Value turmas_array(rapidjson::kArrayType);
    for (int i = 0; i < qtd_atual_turma; i++) {
        if (turmas[i] != NULL) {
            rapidjson::Value turma_obj(rapidjson::kObjectType);

            rapidjson::Value codigo(turmas[i]->codigo, doc.GetAllocator());
            turma_obj.AddMember("codigo", codigo, doc.GetAllocator());

            rapidjson::Value disciplina(turmas[i]->disciplina, doc.GetAllocator());
            turma_obj.AddMember("disciplina", disciplina, doc.GetAllocator());

            rapidjson::Value matricula_professor_responsavel(turmas[i]->matricula_professor_responsavel, doc.GetAllocator());
            turma_obj.AddMember("matricula_professor_responsavel", matricula_professor_responsavel, doc.GetAllocator());

            rapidjson::Value qtd_alunos_matriculados(turmas[i]->qtd_alunos_matriculados, doc.GetAllocator());
            turma_obj.AddMember("qtd_alunos_matriculados", qtd_alunos_matriculados, doc.GetAllocator());

            rapidjson::Value matricula_alunos(turmas[i]->matricula_alunos, doc.GetAllocator());
            turma_obj.AddMember("matricula_alunos", matricula_alunos, doc.GetAllocator());

            rapidjson::Value media_turma(turmas[i]->media_turma, doc.GetAllocator());
            turma_obj.AddMember("media_turma", media_turma, doc.GetAllocator());

            turmas_array.PushBack(turma_obj, doc.GetAllocator());
        }
    }
    doc.AddMember("turmas", turmas_array, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    const char* json_str = buffer.GetString();
    fputs(json_str, arquivo);

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}


void carregarDados(Aluno** alunos, int* qtd_atual_aluno, Professor** professores, int* qtd_atual_prof, Turmas** turmas, int qtd_atual_turma)
{
    FILE* arquivo;
    arquivo = fopen("dados.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de dados não encontrado. Criando novo arquivo...\n");
        return;
    }

    fread(qtd_atual_aluno, sizeof(int), 1, arquivo);
    for (int i = 0; i < *qtd_atual_aluno; i++) {
        Aluno* aluno = (Aluno*)malloc(sizeof(Aluno));
        fread(aluno, sizeof(Aluno), 100, arquivo);
        alunos[i] = aluno;
    }

    fread(qtd_atual_prof, sizeof(int), 1, arquivo);
    for (int i = 0; i < *qtd_atual_prof; i++) {
        Professor* professor = (Professor*)malloc(sizeof(Professor));
        fread(professor, sizeof(Professor), 100, arquivo);
        professores[i] = professor;
    }
    //turmas
    fread(&qtd_atual_turma, sizeof(int), 1, arquivo);
    for (int i = 0; i < qtd_atual_turma; i++) {
        Turmas* turma = (Turmas*)malloc(sizeof(Turmas));
        fread(turma, sizeof(Turmas), 100, arquivo);
        turmas[i] = turma;
    }


    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}

//menu alunos

void tratador_menu_aluno(Aluno **alunos, int *qtd_atual_aluno)
{
    int opcao = menu_crud_aluno();
    Aluno *aluno = NULL;
    switch (opcao)
    {
    case 1:
        if (*qtd_atual_aluno >= MAX_ALUNO)
        {
            printf("Número máximo de alunos atingido\n");
        }
        else
        {
            // Passo 1: buscar posicao disponível
            int i = 0;
            for (; i < *qtd_atual_aluno; i++)
            {
                if (alunos[i] != NULL)
                {
                    // significa que esta posição está livre para uso
                    break;
                }
            }
            Aluno *aluno = construir_aluno();
            alunos[i] = aluno;
            *qtd_atual_aluno++;
        }
        break;
    case 2:
    {
        int posicao = 0;
        aluno = buscar_aluno(alunos, &posicao);
        if (aluno)
        {
            imprimir_aluno(aluno);
        }
        else
        {
            printf("Aluno nao encontrado!!\n");
        }
    }
    break;
    case 3:
    {
        int posicao = 0;
        aluno = buscar_aluno(alunos, &posicao);

        if (aluno)
        {
            imprimir_aluno(aluno);
            printf("Atualizar aluno\n");
            printf("Nova Matricula\t> ");
            fgets(aluno->matricula, 9, stdin);
            printf("Novo CPF\t> ");
            fgets(aluno->cpf, 9, stdin);
            printf("Novo Nome\t> ");
            fgets(aluno->nome, 49, stdin);
            aluno->endereco = construir_endereco();
            printf("Aluno atualizado!\n");
        }
        else
        {
            printf("Aluno nao encontrado!!\n");
        }
        
    }

    break;
    case 4:
    {
        int posicao = 0;
        aluno = buscar_aluno(alunos, &posicao);
        if (aluno)
        {
            destruirAluno(aluno);
            alunos[posicao] = NULL;
            printf("Aluno destruido\n");
        }
        else
        {
            printf("Aluno nao encontrado!!\n");
        }
    }

    break;
    default:
        printf("Retornando ao menu principal\n");
        break;
    }
}

void tratador_menu_professor(Professor **professores, int *qtd_atual_professores)
{
    int opcao = menu_crud_professor();
    Professor *professor = NULL;
    switch (opcao)
    {
    case 1:
        if (*qtd_atual_professores >= MAX_PROFESSOR)
        {
            printf("Número máximo de professores atingido\n");
        }
        else
        {
            // Passo 1: buscar posicao disponível
            int i = 0;
            for (; i < *qtd_atual_professores; i++)
            {
                if (professores[i] != NULL)
                {
                    // significa que esta posição está livre para uso
                    break;
                }
            }
            Professor *professor = construir_professor();
            professores[i] = professor;
            *qtd_atual_professores++;
        }
        break;
    case 2:
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);
        if (professor)
        {
            imprimir_professor(professor);
        }
        else
        {
            printf("Professor não encontrado!!\n");
        }
    }
    break;
    case 3:
    {
        printf("Implementar a atualização de professor\n");
    }

    break;
    case 4:
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);
        if (professor)
        {
            destruirProfessor(professor);
            professores[posicao] = NULL;
            printf("Professor destruido\n");
        }
        else
        {
            printf("Professor não encontrado!!\n");
        }
    }

    break;
    default:
        printf("Retornando ao menu principal\n");
        break;
    }
}


Endereco *construir_endereco()
{
    Endereco endereco;

    printf("Logradouro\t> ");
    fgets(endereco.logradouro, 49, stdin);
    printf("Bairro\t> ");
    fgets(endereco.bairro, 49, stdin);
    printf("Cidade\t> ");
    fgets(endereco.cidade, 49, stdin);
    printf("Estado\t> ");
    fgets(endereco.estado, 9, stdin);
    printf("Número\t> ");
    fgets(endereco.numero, 9, stdin);

    return criarEndereco(endereco.logradouro, endereco.bairro, endereco.cidade, endereco.estado, endereco.numero);
}

Aluno *construir_aluno()
{
    Aluno aluno;
    printf("Matricula\t> ");
    fgets(aluno.matricula, 9, stdin);
    printf("CPF\t> ");
    fgets(aluno.cpf, 9, stdin);
    printf("Nome\t> ");
    fgets(aluno.nome, 49, stdin);
    aluno.endereco = construir_endereco();
    return criarAluno(aluno.matricula, aluno.cpf, aluno.nome, aluno.endereco);
}

Aluno *buscar_aluno(Aluno **alunos, int *posicao)
{
    char matricula[50];
    printf("Matricula > ");
    fgets(matricula, 49, stdin);
    Aluno *resultado = NULL;
    int pos_resultado = -1;
    for (int i = 0; i < MAX_ALUNO; i++)
    {
        // Vamos testar se o aluno existe e se a matricula e a buscada
        // strcmp compara strings. Se for 0 indica que são iguais
        if (alunos[i] && !strcmp(matricula, alunos[i]->matricula))
        {
            resultado = alunos[i];
            break;
        }
    }
    *posicao = pos_resultado;
    return resultado;
}

void tratador_estatistica()
{
    int opcao = menu_estatistica();
}

void imprimir_aluno(Aluno *aluno)
{
    printf("Matricula: %s", aluno->matricula);
    printf("Nome: %s", aluno->nome);
    printf("CPF: %s", aluno->cpf);
    imprimir_endereco(aluno->endereco);
}

void imprimir_endereco(Endereco *endereco)
{
    printf("Logradouro: %s", endereco->logradouro);
    printf("Numero: %s", endereco->numero);
    printf("Bairro: %s", endereco->bairro);
    printf("Cidade: %s", endereco->cidade);
    printf("Estado: %s", endereco->estado);
}

Professor *construir_professor()
{
    Professor professor;
    printf("Matrícula\t> ");
    fgets(professor.matricula, 9, stdin);
    printf("CPF\t> ");
    fgets(professor.cpf, 9, stdin);
    printf("Nome\t> ");
    fgets(professor.nome, 49, stdin);
    printf("Endereço\t> \n");
    professor.endereco = construir_endereco();
    
    return criarProfessor(professor.matricula, professor.cpf, professor.nome, professor.endereco);
}

Professor *buscar_professor(Professor **professores, int *posicao)
{
    char matricula[50];
    printf("Matricula > ");
    fgets(matricula, 49, stdin);
    Professor *resultado = NULL;
    int pos_resultado = -1;
    for (int i = 0; i < MAX_PROFESSOR; i++)
    {

        if (professores[i] && !strcmp(matricula, professores[i]->matricula))
        {
            resultado = professores[i];
            break;
        }
    }
    *posicao = pos_resultado;
    return resultado;
}

void imprimir_professor(Professor *professor)
{
    printf("Matricula: %s", professor->matricula);
    printf("Nome: %s", professor->nome);
    printf("CPF: %s", professor->cpf);
    imprimir_endereco(professor->endereco);
}

void tratador_menu_prof(Professor **professores, int *qtd_atual_prof){
    int opcao = menu_crud_professor();
    Professor *professor = NULL;
    switch (opcao)
    {
    case 1:
        if (*qtd_atual_prof >= MAX_PROFESSOR)
        {
            printf("Número máximo de professores atingido\n");
        }
        else
        {
            int i = 0;
            for (; i < *qtd_atual_prof; i++)
            {
                if (professores[i] != NULL)
                {
                    break;
                }
            }
            Professor *professor = construir_professor();
            professores[i] = professor;
            (*qtd_atual_prof)++;
        }
        break;
    case 2:
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);
        if (professor)
        {
            imprimir_professor(professor);
        }
        else
        {
            printf("Professor nao encontrado!!\n");
        }
    }
    break;
    case 3:
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);

        if (professor)
        {
            imprimir_professor(professor);
            printf("Atualizar professor\n");
            printf("Nova Matricula\t> ");
            fgets(professor->matricula, 9, stdin);
            printf("Novo CPF\t> ");
            fgets(professor->cpf, 9, stdin);
            printf("Novo Nome\t> ");
            fgets(professor->nome, 49, stdin);
            professor->endereco = construir_endereco();
            printf("Professor atualizado!\n");
        }
        else
        {
            printf("Professor nao encontrado!!\n");
        }
        
    }

    break;
    case 4:
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);
        if (professor)
        {
            destruirProfessor(professor);
            professores[posicao] = NULL;
            printf("Professor destruido\n");
        }
        else
        {
            printf("Professor nao encontrado!!\n");
        }
    }

    break;
    default:
        printf("Retornando ao menu principal\n");

}
}

void listarProfessores(const Professor* professores, int numProfessores) 
    {
    printf("Lista de professores:\n");
    for (int i = 0; i < numProfessores; i++) {
        printf("Professor %d:\n", i + 1);
        printf("Matrícula: %s\n", professores[i].matricula);
        printf("CPF: %s\n", professores[i].cpf);
        printf("Nome: %s\n", professores[i].nome);
    }
    }

void listarProfessoresSemTurmas(const Professor* professores, int numProfessores, const Turmas* turmas, int numTurmas) {
    printf("Matrículas dos professores sem turmas:\n");
    for (int i = 0; i < numProfessores; i++) {
        int possuiTurma = 0;
        for (int j = 0; j < numTurmas; j++) {
            if (turmas[j].matricula_professor_responsavel == professores[i].matricula) {
                possuiTurma = 1;
                break;
            }
        }
        if (!possuiTurma) {
            printf("Matrícula: %s\n", professores[i].matricula);
        }
    }
    }

    void calcularMediaGeralTurmas(const Turmas* turmas, int numTurmas) {
    float somaNotas = 0;
    int numTurmasValidas = 0;
    int i = 0;
    int notaMedia = atoi(turmas[i].media_turma);
    for (int i = 0; i < numTurmas; i++) {
        if (notaMedia != 0) {
            somaNotas += notaMedia;
            numTurmasValidas++;
        }
    }
    if (numTurmasValidas > 0) {
        float mediaGeral = somaNotas / numTurmasValidas;
        printf("Média geral das turmas: %.2f\n", mediaGeral);
    } else {
        printf("Não há turmas cadastradas com notas.\n");
    }
    }


void tratador_menu_estatisticas(Aluno** alunos, int numAlunos, Professor** professores, int numProfessores, Turmas** turmas, int numTurmas)
{
    int opcao = menu_estatistica();
    switch (opcao)
    {
    case 1:
        {
          void listarProfessores(const Professor* professores, int numProfessores);
        }
        break;

    case 2:
    {
        void listarProfessoresSemTurmas(const Professor* professores, int numProfessores, const Turmas* turmas, int numTurmas);
        }
        break;
    case 3:
    {
        void calcularMediaGeralTurmas(const Turmas* turmas, int numTurmas);
    }
        break;
}
}

Turmas *construir_turma()
{
    Turmas turma;
    printf("Digite o codigo da turma: ");
    fgets(turma.codigo, 9, stdin);

    printf("Digite o nome da disciplina: ");
    fgets(turma.disciplina, 50, stdin);

    printf("Digite a matricula do professor responsavel: ");
    fgets(turma.matricula_professor_responsavel, 9, stdin);

    printf("Digite o numero de alunos: ");
    fgets(turma.qtd_alunos_matriculados, 3, stdin);

    printf("Digite a matricula dos alunos: ");
    fgets(turma.matricula_alunos, 9, stdin);

    printf("Digite a media da turma: ");
    fgets(turma.media_turma, 9, stdin);

    return criarTurma(turma.codigo, 
    turma.disciplina, 
    turma.matricula_professor_responsavel,
     turma.qtd_alunos_matriculados, 
     turma.matricula_alunos, 
     turma.media_turma);
}

void imprimir_turma(Turmas *turma)
{
    printf("Codigo da turma: %s\n", turma->codigo);
    printf("Nome da disciplina: %s\n", turma->disciplina);
    printf("Matricula do professor responsavel: %s\n", turma->matricula_professor_responsavel);
    printf("Numero de alunos: %s\n", turma->qtd_alunos_matriculados);
    printf("Matricula dos alunos: %s\n", turma->matricula_alunos);
    printf("Media da turma: %s\n", turma->media_turma);
}

void destruir_turma(Turmas *turma)
{
    free(turma);
}

void tratar_menu_turmas(Turmas **turma, int *qtd_alunos_matriculados) {
    int opcao = menu_crud_turma();
    switch (opcao) {
        case 1: {
            if (*qtd_alunos_matriculados >= MAX_ALUNOS_TURMA) {
                printf("Número máximo de alunos atingido\n");
            } else {
                // Passo 1: buscar posição disponível
                int i = 0;
                for (; i < *qtd_alunos_matriculados; i++) {
                    if (turma[i] == NULL) {
                        // significa que esta posição está livre para uso
                        break;
                    }
                }
                Turmas *nova_turma = construir_turma();
                turma[i] = nova_turma;
                (*qtd_alunos_matriculados)++;
            }
            break;
        }
        case 2: {
            char codigo[9];
            printf("Digite o código da turma: ");
            fgets(codigo, 9, stdin);

            // Procurar a turma pelo código fornecido
            for (int i = 0; i < *qtd_alunos_matriculados; i++) {
                if (turma[i] != NULL && strcmp(turma[i]->codigo, codigo) == 0) {
                    imprimir_turma(turma[i]);
                    return;
                }
            }

            printf("Turma não encontrada.\n");
            break;
        }
        case 3: {
            char codigo[9];
            printf("Digite o código da turma que deseja atualizar: ");
            fgets(codigo, 9, stdin);

            // Procurar a turma pelo código fornecido
            for (int i = 0; i < *qtd_alunos_matriculados; i++) {
                if (turma[i] != NULL && strcmp(turma[i]->codigo, codigo) == 0) {
                    // Atualizar os dados da turma
                    Turmas *turma_atualizada = turma[i];
                    printf("Digite o novo código da turma (ou deixe em branco para não atualizar): ");
                    fgets(turma_atualizada->codigo, 9, stdin);

                    printf("Digite a nova disciplina (ou deixe em branco para não atualizar): ");
                    fgets(turma_atualizada->disciplina, 50, stdin);

                    printf("Deseja atualizar o professor responsável? (s/n): ");

                    char opcao[2];
                    fgets(opcao, 2, stdin);

                    if (opcao[0] == 's' || opcao[0] == 'S') {
                        printf("Digite a nova matrícula do professor responsável: ");
                        fgets(turma_atualizada->matricula_professor_responsavel, 9, stdin);
                    }

                    printf("Digite o novo número de alunos (ou deixe em branco para não atualizar): ");
                    fgets(turma_atualizada->qtd_alunos_matriculados, 9, stdin);

                    printf("Digite as novas matrículas dos alunos (ou deixe em branco para não atualizar): ");
                    fgets(turma_atualizada->matricula_alunos, 9, stdin);
                    
                    printf("Digite a nova média da turma (ou deixe em branco para não atualizar): ");
                    fgets(turma_atualizada->media_turma, 9, stdin);

                    printf("Turma atualizada com sucesso.\n");
                    return;
                }
            }
            printf("Turma não encontrada.\n");
            break;
        }
    }
}
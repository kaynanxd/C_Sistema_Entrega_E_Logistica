#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarar estrutura
typedef struct {
    int idfuncionario;
    char *nomefuncionario;
} estruturafuncionario;

// Alocar memória para a lista da estrutura
estruturafuncionario* alocarEstruturaFuncionario(int numdefuncionarios) {
    estruturafuncionario *funcionario = malloc(numdefuncionarios * sizeof(estruturafuncionario));
    if (funcionario == NULL) {
        printf("Erro ao alocar memória para a estrutura de funcionario.");
        exit(1);
    }
    return funcionario;
}

// Função para adicionar funcionario
void adicionarfuncionario(estruturafuncionario **funcionario, int *numdefuncionarios) {
    for (int i = 0; i < *numdefuncionarios; i++) {
        (*funcionario)[i].nomefuncionario = malloc(30 * sizeof(char));

        printf("Informe o nome do funcionario: ");
        fgets((*funcionario)[i].nomefuncionario, 30, stdin);
        (*funcionario)[i].nomefuncionario[strcspn((*funcionario)[i].nomefuncionario, "\n")] = 0;

        printf("Informe o ID do funcionario: ");
        scanf("%d", &(*funcionario)[i].idfuncionario);
        getchar();
    }
}

// Função para salvar funcionario dentro do arquivo
void salvarfuncionario(estruturafuncionario *funcionario, int numdefuncionarios) {
    FILE* arq_funcionarios = fopen("arq_funcionarios.txt", "w");
    if (arq_funcionarios == NULL) {
        printf("Erro ao encontrar o arquivo");
        return;
    }

    for (int i = 0; i < numdefuncionarios; i++) {
        fprintf(arq_funcionarios, "===== Informações dos funcionarios (%d) =====\n", i + 1);
        fprintf(arq_funcionarios, "Nome: %s\n", funcionario[i].nomefuncionario);
        fprintf(arq_funcionarios, "ID: %d\n", funcionario[i].idfuncionario);
    }

    fclose(arq_funcionarios);
    printf("Os dados dos funcionarios cadastrados foram salvos com sucesso.\n");
}

// Função para contar a quantidade de funcionarios no arquivo
int contarfuncionariosNoArquivo() {
    FILE *arq_funcionarios = fopen("arq_funcionarios.txt", "r");
    if (arq_funcionarios == NULL) {
        printf("Erro ao abrir o arquivo de funcionarios.\n");
        return 0;
    }

    int count = 0;
    char buffer[200];

    while (fgets(buffer, sizeof(buffer), arq_funcionarios) != NULL) {
        if (strstr(buffer, "===== Informações dos funcionarios") != NULL) {
            count++;
        }
    }

    fclose(arq_funcionarios);
    return count;
}

// Função para exibir todos funcionarios
void visualizarfuncionario(estruturafuncionario *funcionario, int numdefuncionarios) {
    FILE *arq_funcionarios = fopen("arq_funcionarios.txt", "r");
    if (arq_funcionarios == NULL) {
        printf("Erro ao abrir o arquivo de funcionarios.\n");
        return;
    }

    char buffer[200];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), arq_funcionarios) != NULL && i < numdefuncionarios) {
        if (strstr(buffer, "===== Informações dos funcionarios") != NULL) {
            printf("%s", buffer);

            if (fgets(buffer, sizeof(buffer), arq_funcionarios)) {
                char *nome = strstr(buffer, "Nome: ");
                nome += strlen("Nome: ");
                printf("Nome:%s", nome);
            }

            if (fgets(buffer, sizeof(buffer), arq_funcionarios)) {
                char *id = strstr(buffer, "ID: ");
                id += strlen("ID: ");
                printf("ID:%s", id);
            }
            printf("\n");

            i++;
        }
    }

    fclose(arq_funcionarios);
}

// Função para alterar funcionario
void alterarFuncionario(estruturafuncionario *funcionario, int numdefuncionarios) {
    int idParaAlterar;
    char novoNome[30];
    int novoId;

    printf("Informe o ID do funcionario que deseja alterar: ");
    scanf("%d", &idParaAlterar);
    getchar(); // Limpar o buffer do teclado

    for (int i = 0; i < numdefuncionarios; i++) {
        if (funcionario[i].idfuncionario == idParaAlterar) {
            printf("Informe o novo nome do funcionario: ");
            fgets(novoNome, 30, stdin);
            novoNome[strcspn(novoNome, "\n")] = 0;

            printf("Informe o novo ID do funcionario: ");
            scanf("%d", &novoId);
            getchar(); // Limpar o buffer do teclado

            // Liberar a memória alocada para o nome anterior
            free(funcionario[i].nomefuncionario);

            // Alocar memória para o novo nome
            funcionario[i].nomefuncionario = malloc(30 * sizeof(char));
            strcpy(funcionario[i].nomefuncionario, novoNome);

            funcionario[i].idfuncionario = novoId;

            printf("Dados do funcionario alterados com sucesso.\n");
            return;
        }
    }

    printf("Funcionario com ID %d não encontrado.\n", idParaAlterar);
}

// Função para liberar memória dos mallocs
void liberarMemorias(estruturafuncionario *funcionario, int numdefuncionarios) {
    for (int i = 0; i < numdefuncionarios; i++) {
        free(funcionario[i].nomefuncionario);
    }

    free(funcionario);
}

// Função para ler os dados do arquivo e armazená-los na estrutura
void lerFuncionariosDoArquivo(estruturafuncionario *funcionario, int numdefuncionarios) {
    FILE *arq_funcionarios = fopen("arq_funcionarios.txt", "r");
    if (arq_funcionarios == NULL) {
        printf("Erro ao abrir o arquivo de funcionarios.\n");
        return;
    }

    char buffer[200];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), arq_funcionarios) != NULL && i < numdefuncionarios) {
        if (strstr(buffer, "===== Informações dos funcionarios") != NULL) {
            if (fgets(buffer, sizeof(buffer), arq_funcionarios)) {
                char *nome = strstr(buffer, "Nome: ");
                nome += strlen("Nome: ");
                funcionario[i].nomefuncionario = malloc(30 * sizeof(char));
                strcpy(funcionario[i].nomefuncionario, nome);
                funcionario[i].nomefuncionario[strcspn(funcionario[i].nomefuncionario, "\n")] = 0;
            }

            if (fgets(buffer, sizeof(buffer), arq_funcionarios)) {
                char *id = strstr(buffer, "ID: ");
                id += strlen("ID: ");
                sscanf(id, "%d", &funcionario[i].idfuncionario);
            }

            i++;
        }
    }

    fclose(arq_funcionarios);
}

// Função principal
int main() {
    int numdefuncionarios, numTipoDeOperacao;

    printf("===== Menu de Operações =====\n \n Adicionar -> 1 \n Visualizar -> 2 \n Alterar -> 3 \n Deletar -> 4 \n\nQual operação deseja realizar: ");
    scanf("%d", &numTipoDeOperacao);
    getchar();

    if (numTipoDeOperacao == 1) {
        printf("\nQuantos funcionarios você deseja adicionar: \n");
        scanf("%d", &numdefuncionarios);
        getchar();
        estruturafuncionario *funcionario = alocarEstruturaFuncionario(numdefuncionarios);
        adicionarfuncionario(&funcionario, &numdefuncionarios);
        salvarfuncionario(funcionario, numdefuncionarios);
        liberarMemorias(funcionario, numdefuncionarios);
    } else if (numTipoDeOperacao == 2) {
        numdefuncionarios = contarfuncionariosNoArquivo();
        if (numdefuncionarios > 0) {
            estruturafuncionario *funcionario = alocarEstruturaFuncionario(numdefuncionarios);
            visualizarfuncionario(funcionario, numdefuncionarios);
            liberarMemorias(funcionario, numdefuncionarios);
        } else {
            printf("Não há veículos registrados para visualizar.\n");
        }
    } else if (numTipoDeOperacao == 3) {
    numdefuncionarios = contarfuncionariosNoArquivo();
    if (numdefuncionarios > 0) {
        estruturafuncionario *funcionario = alocarEstruturaFuncionario(numdefuncionarios);
        lerFuncionariosDoArquivo(funcionario, numdefuncionarios); // Ler do arquivo
        alterarFuncionario(funcionario, numdefuncionarios);
        salvarfuncionario(funcionario, numdefuncionarios);
        liberarMemorias(funcionario, numdefuncionarios);
    } else {
        printf("Não há funcionários registrados para alterar.\n");
    }
}
     else if (numTipoDeOperacao == 4) {
        numdefuncionarios = contarfuncionariosNoArquivo();
        estruturafuncionario *funcionario = alocarEstruturaFuncionario(numdefuncionarios);
        visualizarfuncionario(funcionario, numdefuncionarios);
        liberarMemorias(funcionario, numdefuncionarios);
    } else {
        printf("Erro ao selecionar a operação\n");
    }

    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

    //declarar estrutura
typedef struct{
    int idfuncionario;
    char *nomefuncionario;
} estruturafuncionario;

    //aloca memoria pra a lista da estrutura
estruturafuncionario* alocarEstruturaFuncionario(int numdefuncionarios) {
    estruturafuncionario *funcionario = malloc(numdefuncionarios * sizeof(estruturafuncionario));
    if (funcionario == NULL) {
        printf("Erro ao alocar memória para a estrutura de funcionario.");
        exit(1);
    }
    return funcionario;
}

    // Função para abrir o arquivo
FILE* abrirArquivo(char* nomeArquivo, char* modo) {
    FILE* arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    return arquivo;
}

    //Função para voltar para menu ou encerrar programa
void voltarencerrarprograma(){
    int menuEncerrar;
    printf("\nPressione 0 para sair do programa e 1 para voltar ao menu de operações : \n");
    scanf("%d", &menuEncerrar);
        if (menuEncerrar == 0)
        {
            exit(0);
        }
}
    //funcao para salvar funcionario dentro do arquivo
void salvarfuncionario(estruturafuncionario *funcionario,int numdefuncionarios,char *modo ) {
    //a proxima linha chama a funcao de abrir arquivo
    FILE* arq_funcionarios = abrirArquivo("arq_funcionarios.txt", modo);
        for (int i = 0; i < numdefuncionarios; i++) {
            fprintf(arq_funcionarios, "===== Informações dos funcionarios (%d) =====\n", i + 1);
            fprintf(arq_funcionarios, "Nome: %s\n", funcionario[i].nomefuncionario);
            fprintf(arq_funcionarios, "ID: %d\n", funcionario[i].idfuncionario);
            }
    fclose(arq_funcionarios);
}

    //funcao para verificar se Id ja existe
int verificarId(int idfuncionario)
{
    //proxima linha chama funcao de abrir arquivo
    FILE *arq_funcionarios = fopen("arq_funcionarios.txt", "r");
        if (arq_funcionarios == NULL)
        {
        return 0;
        }
    char linha[200];
    int idLido;

    while (fgets(linha, sizeof(linha), arq_funcionarios))
    {
        if (sscanf(linha, "ID: %d", &idLido) == 1)

        {
            if (idLido == idfuncionario)
            {
                return 1;
            }
        }
    }
    return 0;
}

    //funcao para adicionarfuncionario
void adicionarfuncionario(estruturafuncionario **funcionario, int *numdefuncionarios){
    
    for (int i = 0; i < *numdefuncionarios; i++) {
        
        (*funcionario)[i].nomefuncionario = malloc(30 * sizeof(char));
        printf("Informe o nome do funcionario: ");
        fgets((*funcionario)[i].nomefuncionario, 30, stdin);
        
        while(1){
        (*funcionario)[i].nomefuncionario[strcspn((*funcionario)[i].nomefuncionario, "\n")] = 0;
        printf("Informe o ID do funcionario(4 Digitos): ");
        scanf("%d", &(*funcionario)[i].idfuncionario);
        getchar();
        if ((*funcionario)[i].idfuncionario < 1000 || (*funcionario)[i].idfuncionario > 9999)
            {
                printf("ID inválido. Tente novamente.\n");
                continue;
            }
        if(verificarId((*funcionario)[i].idfuncionario) || ((*funcionario)[i].idfuncionario == (*funcionario)[i-1].idfuncionario))
                {
                printf("Já existe um funcionario com esse ID. Tente novamente.\n");
                continue;
                }
        break;
        }
    }
}
    

    //funcao para contar a quantidade de funcionarios no arquivo
int contarfuncionariosNoArquivo() {
        //a proxima linha chama a funcao de abrir arquivo
    FILE *arq_funcionarios = fopen("arq_funcionarios.txt", "r");

    int contador = 0;
    char buffer[200];
        while (fgets(buffer, sizeof(buffer), arq_funcionarios)) {
            if (strstr(buffer, "===== Informações dos funcionarios")) { contador++;}
            }
    fclose(arq_funcionarios);
    return contador;
}
   //funcao para exibir todos funcionarios
void visualizarfuncionario() {
    //a proxima linha chama a funcao de abrir arquivo
    FILE* arq_funcionarios = abrirArquivo("arq_funcionarios.txt", "r");
    
    char buffer[200];
        while (fgets(buffer, sizeof(buffer), arq_funcionarios)) 
        {
            printf("%s", buffer);
        }

    fclose(arq_funcionarios);
    voltarencerrarprograma();
}

 //lerFuncionariosDoArquivo
void lerFuncionariosDoArquivo(estruturafuncionario *funcionario, int numdefuncionarios) {
      //a proxima linha chama a funcao de abrir arquivo
    FILE* arq_funcionarios = abrirArquivo("arq_funcionarios.txt", "r");
    
    char buffer[200];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), arq_funcionarios) && i < numdefuncionarios) {
        if (strstr(buffer, "===== Informações dos funcionarios")) {
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
    //funcao para alterarFuncionario
void alterarFuncionario(estruturafuncionario *funcionario, int numdefuncionarios) {
    int idParaAlterar;
    char novoNome[30];
    int novoId;

    printf("Informe o ID do funcionario que deseja alterar: ");
    scanf("%d", &idParaAlterar);
    getchar();
    for (int i = 0; i < numdefuncionarios; i++) {
        if (funcionario[i].idfuncionario == idParaAlterar) {
            printf("Informe o novo nome do funcionario: ");
            fgets(novoNome, 30, stdin);
            novoNome[strcspn(novoNome, "\n")] = 0;
        while(1){
            printf("Informe o novo ID do funcionario: ");
            scanf("%d", &novoId);
            getchar(); 
            if (novoId < 1000 || novoId > 9999)
            {
                printf("ID inválido. Tente novamente.\n");
                continue;
            }
            if(verificarId(novoId)){
               printf("Alguem ja possui esse id, tente novamente :\n");
               continue;
                }
            break;
            }
            // Libera a memoria alocada para o nome anterior
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

    //funcao para deletarFuncionario 
void deletarFuncionario(estruturafuncionario **funcionario, int *numdefuncionarios) {
    int idParaDeletar;
    printf("Informe o ID do funcionario que deseja deletar: ");
    scanf("%d", &idParaDeletar);
    getchar();

    int indiceParaRemover = -1;
    for (int i = 0; i < *numdefuncionarios; i++) {
        if ((*funcionario)[i].idfuncionario == idParaDeletar) {
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover == -1) {
        printf("Funcionario com ID %d não encontrado.\n", idParaDeletar);
        return;
    }

    // Liberar memoria do funcionario removido
    free((*funcionario)[indiceParaRemover].nomefuncionario);

    // troca dos elementos restantes
    for (int i = indiceParaRemover; i < (*numdefuncionarios) - 1; i++) {
        (*funcionario)[i] = (*funcionario)[i + 1];
    }

    (*numdefuncionarios)--;
    
    *funcionario = realloc(*funcionario, (*numdefuncionarios) * sizeof(estruturafuncionario));
    if (*numdefuncionarios > 0 && *funcionario == NULL) {
        printf("Erro ao realocar memória após a remoção do funcionário.\n");
        exit(1);
    }

    salvarfuncionario(*funcionario, *numdefuncionarios,"w");
    printf("Funcionario com ID %d foi removido com sucesso.\n", idParaDeletar);
}
//funcao para liberar memoria dos mallocs
void liberarMemorias(estruturafuncionario *funcionario, int numdefuncionarios) {
    for (int i = 0; i < numdefuncionarios; i++) {
        free(funcionario[i].nomefuncionario);
    }
    free(funcionario);
    voltarencerrarprograma();
} 

    //funcao principal
int main(){
    
    estruturafuncionario *funcionario;
    int numdefuncionarios, numTipoDeOperacao;
//while com loop ate o programa encerrar    
    while(1)
    {
        printf("===== Menu de Operações =====\n \n Adicionar -> 1 \n Visualizar -> 2 \n alterar -> 3 \n Deletar -> 4 \n sair do programa -> 5 \n\nQual operação deseja realizar: ");
          scanf("%d", &numTipoDeOperacao);
            getchar();
        
        switch(numTipoDeOperacao)
        {
//chamada para adicionar funcionario
        case 1:
            printf("\nQuantos funcionarios você deseja adicionar: \n");
            scanf("%d", &numdefuncionarios);
            getchar();
            estruturafuncionario *funcionario = alocarEstruturaFuncionario(numdefuncionarios);
            adicionarfuncionario(&funcionario, &numdefuncionarios);
            salvarfuncionario(funcionario, numdefuncionarios,"a");
            printf("Os dados dos funcionarios cadastrados foram salvos com sucesso.\n");
            liberarMemorias(funcionario, numdefuncionarios);
            
            break;
    
//chamada para visualizar funcionarios   
        case 2:
            numdefuncionarios = contarfuncionariosNoArquivo();
            visualizarfuncionario();
            break;
    
//chamada para alterar dados dos funcionarios    
        case 3: 
        numdefuncionarios = contarfuncionariosNoArquivo();
        if (numdefuncionarios > 0) {
            estruturafuncionario *funcionario = alocarEstruturaFuncionario(numdefuncionarios);
            lerFuncionariosDoArquivo(funcionario, numdefuncionarios); // Ler do arquivo
            alterarFuncionario(funcionario, numdefuncionarios);
            salvarfuncionario(funcionario, numdefuncionarios,"w");
            liberarMemorias(funcionario, numdefuncionarios);
        } 
        break;

//chamada para deletar funcionario    
        case 4:
        numdefuncionarios = contarfuncionariosNoArquivo();
        if (numdefuncionarios > 0) {
            estruturafuncionario *funcionario = alocarEstruturaFuncionario(numdefuncionarios);
            lerFuncionariosDoArquivo(funcionario, numdefuncionarios);
            deletarFuncionario(&funcionario, &numdefuncionarios);
            liberarMemorias(funcionario, numdefuncionarios);
        } 
        break;
//chamada para encerrar programa  
       case 5:
            exit(0);
            }
        
    }
    
}

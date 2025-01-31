#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//declarar estrutura
typedef struct{
    int idcliente;
    char *nomecliente;
    char *enderecocliente;
    int tiposervicocliente;
} estruturacliente;

//aloca memoria pra a lista da estrutura
estruturacliente* alocarEstruturacliente(int numdeclientes) {
    estruturacliente *cliente = malloc(numdeclientes * sizeof(estruturacliente));
    if (cliente == NULL) {
        printf("Erro ao alocar memória para a estrutura de cliente.");
        exit(1);
    }
    return cliente;
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

//funcao para salvar cliente dentro do arquivo
void salvarcliente(estruturacliente *cliente, int numdeclientes, char *modo ) {
    //a proxima linha chama a funcao de abrir arquivo
    FILE* arq_clientes = abrirArquivo("arq_clientes.txt", modo);
        for (int i = 0; i < numdeclientes; i++) {
            fprintf(arq_clientes, "===== Informações dos clientes (%d) =====\n", i + 1);
            fprintf(arq_clientes, "Nome cliente: %s\n", cliente[i].nomecliente);
            fprintf(arq_clientes, "ID: %d\n", cliente[i].idcliente);
            fprintf(arq_clientes, "Endereco completo: %s\n", cliente[i].enderecocliente);
            fprintf(arq_clientes, "Tipo de servico solicitado %d\n", cliente[i].tiposervicocliente);
            }
    fclose(arq_clientes);
}

//funcao para verificar se Id ja existe
int verificarId(int idcliente)
{
    //proxima linha chama funcao de abrir arquivo
    FILE *arq_clientes = fopen("arq_clientes.txt", "r");
        if (arq_clientes == NULL)
        {
        return 0;
        }
    char linha[200];
    int idLido;

    while (fgets(linha, sizeof(linha), arq_clientes))
    {
        if (sscanf(linha, "ID: %d", &idLido) == 1)

        {
            if (idLido == idcliente)
            {
                return 1;
            }
        }
    }
    return 0;
}

//funcao para adicionarcliente
void adicionarcliente(estruturacliente **cliente, int *numdeclientes){
    for (int i = 0; i < *numdeclientes; i++) {
        (*cliente)[i].nomecliente = malloc(30 * sizeof(char));
        (*cliente)[i].enderecocliente = malloc(50 * sizeof(char));
        
        if ((*cliente)[i].nomecliente == NULL) {
            printf("Erro ao alocar memória para o nome do cliente.\n");
            exit(1);
        }
        printf("Informe o Nome cliente: ");
        fgets((*cliente)[i].nomecliente, 30, stdin);
        (*cliente)[i].nomecliente[strcspn((*cliente)[i].nomecliente, "\n")] = 0;

        printf("Informe o Endereco completo: ");
        fgets((*cliente)[i].enderecocliente, 50, stdin);
        (*cliente)[i].enderecocliente[strcspn((*cliente)[i].enderecocliente, "\n")] = 0;

        printf("Informe o servico solicitado ; '1'Economico '2'Padrao '3'Premiun ");
        scanf("%d", &(*cliente)[i].tiposervicocliente);

        while(1){
            printf("Informe o ID do cliente(4 Digitos): ");
            scanf("%d", &(*cliente)[i].idcliente);
            getchar();
            if ((*cliente)[i].idcliente < 1000 || (*cliente)[i].idcliente > 9999) {
                printf("ID inválido. Tente novamente.\n");
                continue;
            }
            if(verificarId((*cliente)[i].idcliente) || ((*cliente)[i].idcliente == (*cliente)[i-1].idcliente)) {
                printf("Já existe um cliente com esse ID. Tente novamente.\n");
                continue;
            }
            break;
        }
    }
}

//funcao para contar a quantidade de clientes no arquivo
int contarclientesNoArquivo() {
        //a proxima linha chama a funcao de abrir arquivo
    FILE *arq_clientes = fopen("arq_clientes.txt", "r");

    int contador = 0;
    char buffer[200];
        while (fgets(buffer, sizeof(buffer), arq_clientes)) {
            if (strstr(buffer, "===== Informações dos clientes")) { contador++;}
            }
    fclose(arq_clientes);
    return contador;
}

//funcao para exibir todos clientes
void visualizarcliente() {
    //a proxima linha chama a funcao de abrir arquivo
    FILE* arq_clientes = abrirArquivo("arq_clientes.txt", "r");
    
    char buffer[200];
        while (fgets(buffer, sizeof(buffer), arq_clientes)) 
        {
            printf("%s", buffer);
        }

    fclose(arq_clientes);
}

//lerclientesDoArquivo
void lerclientesDoArquivo(estruturacliente *cliente, int numdeclientes) {
    FILE* arq_clientes = abrirArquivo("arq_clientes.txt", "r");
    char buffer[200];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), arq_clientes) && i < numdeclientes) {
        if (strstr(buffer, "===== Informações dos clientes")) {
            cliente[i].nomecliente = malloc(30 * sizeof(char));
            cliente[i].enderecocliente = malloc(50 * sizeof(char));
            if (cliente[i].nomecliente == NULL) {
                printf("Erro ao alocar memória para o nome do cliente.\n");
                exit(1);
            }

            if (fgets(buffer, sizeof(buffer), arq_clientes) && strstr(buffer, "Nome cliente: ")) {
                sscanf(buffer, "Nome cliente: %[^\n]", cliente[i].nomecliente);
            }

            if (fgets(buffer, sizeof(buffer), arq_clientes) && strstr(buffer, "ID: ")) {
                sscanf(buffer, "ID: %d", &cliente[i].idcliente);
            }
            
            if (fgets(buffer, sizeof(buffer), arq_clientes) && strstr(buffer, "Endereco completo: ")) { // Lê o endereço
                sscanf(buffer, "Endereco completo: %[^\n]", cliente[i].enderecocliente);
            }

            if (fgets(buffer, sizeof(buffer), arq_clientes) && strstr(buffer, "Tipo de servico solicitado ")) {
                sscanf(buffer, "Tipo de servico solicitado %d", &cliente[i].tiposervicocliente);
            }

            i++;
        }
    }

    fclose(arq_clientes);
}

//funcao para alterarcliente

// Função para alterar cliente
void alterarcliente(estruturacliente *cliente, int numDecliente) {
    int idParaAlterar, infoAlterar;
    char novoTipo[30],novaendereco[50];
    int novoId , novotiposervico;
    visualizarcliente();
    printf("\n===== Informações que podem ser alteradas =====\n");
    printf("Nome -> 1 \nID -> 2 \nEndereco -> 3 \ntipo de servico solicitado-> 4\n");
    
    printf("\nQual informação deseja alterar: ");
    scanf("%d", &infoAlterar);
    getchar();
    
    printf("\nInforme o ID do Cliente que deseja alterar: ");
    scanf("%d", &idParaAlterar);
    getchar();
    
    int encontrado = 0;

    for (int i = 0; i < numDecliente; i++) {
        if (cliente[i].idcliente == idParaAlterar) {
            
            encontrado = 1;
            
            if (infoAlterar == 1) {
                printf("\nInforme o novo nome do cliente : ");
                fgets(novoTipo, 30, stdin);
                novoTipo[strcspn(novoTipo, "\n")] = 0;
                free(cliente[i].nomecliente);
                cliente[i].nomecliente = malloc(30 * sizeof(char));  // Alocar nova memória
                strcpy(cliente[i].nomecliente, novoTipo);
            }

            else if (infoAlterar == 2) {
                while(1){
                printf("\nInforme o novo ID do cliente: ");
                scanf("%d", &novoId);
                getchar();
                if (novoId < 1000 || novoId > 9999) {
                    printf("ID inválido. Tente novamente.\n");
                    continue;
                }
                if(verificarId(novoId)) {
                    printf("Já existe um cliente com esse ID. Tente novamente.\n");
                    continue;
                }
                break;
            }
                cliente[i].idcliente = novoId;
            }
            
            else if (infoAlterar == 3) {
                printf("\nInforme o novo endereco do cliente: ");
                fgets(novaendereco, 50, stdin);
                novaendereco[strcspn(novaendereco, "\n")] = 0;
                free(cliente[i].enderecocliente);
                cliente[i].enderecocliente = malloc(50 * sizeof(char));  // Alocar nova memória
                strcpy(cliente[i].enderecocliente, novaendereco);
            }

            else if (infoAlterar == 4) {
                printf("\nInforme o novo tipo de servico solicitado '1' economico '2' padrao '3' premiun: ");
                scanf("%d", &novotiposervico);
                getchar();
                cliente[i].tiposervicocliente = novotiposervico;
            }

            

            printf("\nDados do cliente alterados com sucesso.\n");
            break;
        }
    }
    
    if (!encontrado) {
        printf("cliente com ID %d não encontrado.\n", idParaAlterar);
    }
}

//funcao para deletarcliente 
void deletarcliente(estruturacliente **cliente, int *numdeclientes) {
    int idParaDeletar;
    printf("Informe o ID do cliente que deseja deletar: ");
    scanf("%d", &idParaDeletar);
    getchar();

    int indiceParaRemover = -1;
    for (int i = 0; i < *numdeclientes; i++) {
        if ((*cliente)[i].idcliente == idParaDeletar) {
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover == -1) {
        printf("cliente com ID %d não encontrado.\n", idParaDeletar);
        return;
    }

    // Liberar memoria do cliente removido
    free((*cliente)[indiceParaRemover].nomecliente);

    // troca dos elementos restantes
    for (int i = indiceParaRemover; i < (*numdeclientes) - 1; i++) {
        (*cliente)[i] = (*cliente)[i + 1];
    }

    (*numdeclientes)--;

    *cliente = realloc(*cliente, (*numdeclientes) * sizeof(estruturacliente));
    if (*numdeclientes > 0 && *cliente == NULL) {
        printf("Erro ao realocar memória após a remoção do cliente.\n");
        exit(1);
    }

    salvarcliente(*cliente, *numdeclientes,"w");
    printf("cliente com ID %d foi removido com sucesso.\n", idParaDeletar);
}

//funcao para liberar memoria dos mallocs
void liberarMemorias(estruturacliente *cliente, int numdeclientes) {
    for (int i = 0; i < numdeclientes; i++) {
        free(cliente[i].nomecliente);
    }
    free(cliente);
    voltarencerrarprograma();
}

//funcao principal
int main(){
    
    estruturacliente *cliente;
    int numdeclientes, numTipoDeOperacao;
//while com loop ate o programa encerrar    
    while(1)
    {
        printf("===== Menu de Operações =====\n \n Adicionar -> 1 \n Visualizar -> 2 \n alterar -> 3 \n Deletar -> 4 \n sair do programa -> 5 \n\nQual operação deseja realizar: ");
          scanf("%d", &numTipoDeOperacao);
            getchar();
        
        switch(numTipoDeOperacao)
        {
//chamada para adicionar cliente
        case 1:
            printf("\nQuantos clientes você deseja adicionar: \n");
            scanf("%d", &numdeclientes);
            getchar();
            estruturacliente *cliente = alocarEstruturacliente(numdeclientes);
            adicionarcliente(&cliente, &numdeclientes);
            salvarcliente(cliente, numdeclientes,"a");
            printf("Os dados dos clientes cadastrados foram salvos com sucesso.\n");
            liberarMemorias(cliente, numdeclientes);
            
            break;
    
//chamada para visualizar clientes   
        case 2:
            numdeclientes = contarclientesNoArquivo();
            visualizarcliente();
            voltarencerrarprograma();
            break;
    
//chamada para alterar dados dos clientes    
        case 3: 
        numdeclientes = contarclientesNoArquivo();
        if (numdeclientes > 0) {
            estruturacliente *cliente = alocarEstruturacliente(numdeclientes);
            lerclientesDoArquivo(cliente, numdeclientes); // Ler do arquivo
            alterarcliente(cliente, numdeclientes);
            salvarcliente(cliente, numdeclientes,"w");
            liberarMemorias(cliente, numdeclientes);
        } 
        break;

//chamada para deletar cliente    
        case 4:
        numdeclientes = contarclientesNoArquivo();
        if (numdeclientes > 0) {
            estruturacliente *cliente = alocarEstruturacliente(numdeclientes);
            lerclientesDoArquivo(cliente, numdeclientes);
            deletarcliente(&cliente, &numdeclientes);
            liberarMemorias(cliente, numdeclientes);
        } 
        break;
//chamada para encerrar programa  
       case 5:
            exit(0);
            }
        
    }
    
}
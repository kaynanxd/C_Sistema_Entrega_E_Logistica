#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int idveiculo;
    char *nomeveiculo;
    int cargaveiculo;
    int statusveiculo;
} estruturaveiculo;

typedef struct
{
    int idfuncionario;
    char *nomefuncionario;
} estruturafuncionario;

typedef struct
{
    int idcliente;
    char *nomecliente;
    char *enderecocliente;
    int tiposervicocliente;
} estruturacliente;

typedef struct
{
    int idcliente;
    int idfuncionario;
    int idveiculo;
    int idEntrega;
    char *origemEntrega;
    char *destinoEntrega;
    int tempoEntrega;
} estruturaentrega;

//funcao para limpar terminal
void limparTerminal() {
    #ifdef _WIN32
        system("cls"); // Comando para Windows
    #else
        system("clear"); // Comando para Linux e macOS
    #endif
}

// funcao para alocar memoria para estruturas
estruturafuncionario *alocarEstruturaFuncionario(int numdefuncionarios)
{
    return (estruturafuncionario *)malloc(numdefuncionarios * sizeof(estruturafuncionario));
}
estruturacliente *alocarEstruturacliente(int numdeclientes)
{
    return (estruturacliente *)malloc(numdeclientes * sizeof(estruturacliente));
}
estruturaveiculo *alocarEstruturaVeiculo(int numdeveiculos)
{
    return (estruturaveiculo *)malloc(numdeveiculos * sizeof(estruturaveiculo));
}
estruturaentrega *alocarestruturaentrega(int numdeentregas)
{
    return (estruturaentrega *)malloc(numdeentregas * sizeof(estruturaentrega));
}
// Funcao para abrir o arquivo
FILE *abrirArquivo(const char *nomeArquivo, char *modo)
{
    FILE *arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    return arquivo;
}
// Funcao para voltar para menu ou encerrar programa
void voltarencerrarprograma()
{
    int menuEncerrar;
    printf("\nPressione 0 para sair do programa ou 1 para voltar ao menu de operacoes : \n");
    scanf("%d", &menuEncerrar);
    if (menuEncerrar == 0)
    {
        exit(0);
    }
}
// Funcao Para Salvar Dados Dentro do arquivo txt
typedef enum
{
    FUNCIONARIO,
    CLIENTE,
    VEICULO,
    ENTREGA,
    ENTREGAREALIZADA
} TipoRegistro;

void salvarDadosNoArquivo(void *dados, int numRegistros, char *modo, TipoRegistro tipo)
{

    const char *nomeArquivo;
    const char *nometipo;
    switch (tipo)
    {
    case FUNCIONARIO:
        nomeArquivo = "arq_funcionarios.txt";
        nometipo = "Funcionario";
        break;
    case CLIENTE:
        nomeArquivo = "arq_clientes.txt";
        nometipo = "Cliente";
        break;
    case VEICULO:
        nomeArquivo = "arq_veiculos.txt";
        nometipo = "Veiculo";
        break;
    case ENTREGA:
        nomeArquivo = "arq_entregas.txt";
        nometipo = "Entrega";
        break;
    case ENTREGAREALIZADA:
        nomeArquivo = "arq_entregas_realizadas.txt";
        nometipo = "Entrega Realizadas";
        break;
    default:
        return;
    }

    FILE *arquivo = fopen(nomeArquivo, modo);
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    for (int i = 0; i < numRegistros; i++)
    {
        fprintf(arquivo, "===== Registro %s =====\n", nometipo);

        if (tipo == FUNCIONARIO)
        {
            estruturafuncionario *funcionario = (estruturafuncionario *)dados;
            fprintf(arquivo, "Nome: %s\n", funcionario[i].nomefuncionario);
            fprintf(arquivo, "ID: %d\n", funcionario[i].idfuncionario);
        }
        else if (tipo == CLIENTE)
        {
            estruturacliente *cliente = (estruturacliente *)dados;
            fprintf(arquivo, "Nome cliente: %s\n", cliente[i].nomecliente);
            fprintf(arquivo, "ID: %d\n", cliente[i].idcliente);
            fprintf(arquivo, "Endereco completo: %s\n", cliente[i].enderecocliente);
            fprintf(arquivo, "Tipo de servico solicitado: %d\n", cliente[i].tiposervicocliente);
        }
        else if (tipo == VEICULO)
        {
            estruturaveiculo *veiculo = (estruturaveiculo *)dados;
            fprintf(arquivo, "Nome: %s\n", veiculo[i].nomeveiculo);
            fprintf(arquivo, "ID: %d\n", veiculo[i].idveiculo);
            fprintf(arquivo, "Capacidade de carga em KG: %d\n", veiculo[i].cargaveiculo);
            fprintf(arquivo, "Status veiculo: %d\n", veiculo[i].statusveiculo);
        }
        else if (tipo == ENTREGA)
        {
            estruturaentrega *entrega = (estruturaentrega *)dados;
            fprintf(arquivo, "ID: %d\n", entrega[i].idEntrega);
            fprintf(arquivo, "Origem: %s\n", entrega[i].origemEntrega);
            fprintf(arquivo, "Destino: %s\n", entrega[i].destinoEntrega);
            fprintf(arquivo, "Tempo estimado da entrega (em horas): %d\n", entrega[i].tempoEntrega);
        }
        else if (tipo == ENTREGAREALIZADA)
        {
            estruturaentrega *entrega = (estruturaentrega *)dados;
            fprintf(arquivo, "ID da entrega realizada: %d\n", entrega[i].idEntrega);
            fprintf(arquivo, "ID do cliente: %d\n", entrega[i].idcliente);
            fprintf(arquivo, "ID do funcionario: %d\n", entrega[i].idfuncionario);
            fprintf(arquivo, "ID do veiculo: %d\n", entrega[i].idveiculo);
            fprintf(arquivo, "Origem: %s\n", entrega[i].origemEntrega);
            fprintf(arquivo, "Destino: %s\n", entrega[i].destinoEntrega);
            fprintf(arquivo, "Tempo Para Conclusao Da Entrega (Em Horas): %d\n", entrega[i].tempoEntrega);
        }
    }
    fclose(arquivo);
}
// funcao verificar se id ja existe
int verificarId(int id, TipoRegistro tipo)
{
    const char *nomeArquivo;
    switch (tipo)
    {
    case FUNCIONARIO:
        nomeArquivo = "arq_funcionarios.txt";
        break;
    case CLIENTE:
        nomeArquivo = "arq_clientes.txt";
        break;
    case VEICULO:
        nomeArquivo = "arq_veiculos.txt";
        break;
    case ENTREGA:
        nomeArquivo = "arq_entregas.txt";
        break;
    }
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        return 0;
    }
    char linha[200];
    int idLido;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (sscanf(linha, "ID: %d", &idLido) == 1)

        {
            if (idLido == id)
            {
                fclose(arquivo);
                return 1;
            }
        }
    }
    fclose(arquivo);
    return 0;
}
// Funcao para gerar ID único de 4 digitos
int gerarIdUnico(TipoRegistro tipo)
{
    int id;
    do
    {
        id = rand() % 9000 + 1000; // Gera um número entre 1000 e 9999
    } while (verificarId(id, tipo)); // Garante que o ID nao esta em uso
    return id;
}

// funcoes para gerar relatorio entrega
int *lerIds(const char *nomeArquivo, int *tamanho)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro: Arquivo %s nao encontrado ou nao pode ser aberto.\n", nomeArquivo);
        *tamanho = 0;
        return NULL;
    }

    int *ids = NULL;
    int id;
    *tamanho = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), arquivo))
    {
        if (sscanf(buffer, "ID: %d", &id) == 1)
        {
            ids = realloc(ids, (*tamanho + 1) * sizeof(int));
            if (ids == NULL)
            {
                printf("Erro: Falha ao alocar memória para IDs.\n");
                fclose(arquivo);
                return NULL;
            }
            ids[*tamanho] = id;
            (*tamanho)++;
        }
    }

    fclose(arquivo);
    return ids;
}

int *lerStatusVeiculo(const char *nomeArquivo, int *tamanho)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro: Arquivo %s nao encontrado ou nao pode ser aberto.\n", nomeArquivo);
        *tamanho = 0;
        return NULL;
    }

    int *status = NULL;
    int statusVeiculo;
    *tamanho = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), arquivo))
    {
        if (sscanf(buffer, "Status veiculo: %d", &statusVeiculo) == 1)
        {
            status = realloc(status, (*tamanho + 1) * sizeof(int));
            if (status == NULL)
            {
                printf("Erro: Falha ao alocar memória para status.\n");
                fclose(arquivo);
                return NULL;
            }
            status[*tamanho] = statusVeiculo;
            (*tamanho)++;
        }
    }

    fclose(arquivo);
    return status;
}

char **lerEnderecos(const char *nomeArquivo, int *tamanho)
{
    FILE *arquivo = abrirArquivo(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        *tamanho = 0;
        return NULL;
    }

    char **enderecos = NULL;
    *tamanho = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), arquivo))
    {
        if (sscanf(buffer, "Endereco completo: %[^\n]", buffer) == 1)
        {
            enderecos = realloc(enderecos, (*tamanho + 1) * sizeof(char *));
            if (enderecos == NULL)
            {
                printf("Erro: Falha ao alocar memória para enderecos.\n");
                fclose(arquivo);
                return NULL;
            }
            enderecos[*tamanho] = strdup(buffer);
            (*tamanho)++;
        }
    }

    fclose(arquivo);
    return enderecos;
}

int verificarId2(int id, int *ids, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (ids[i] == id)
        {
            return 1;
        }
    }
    return 0;
}
//

void AdicionarDadosNoArquivo(void **registro, int *num, TipoRegistro tipo)
{
    for (int i = 0; i < *num; i++)
    {
        switch (tipo)
        {
        case FUNCIONARIO:
        {
            estruturafuncionario *f = (estruturafuncionario *)(*registro);
            f[i].nomefuncionario = (char *)malloc(30 * sizeof(char));

            printf("Informe o nome do funcionario: ");
            fgets(f[i].nomefuncionario, 30, stdin);
            f[i].nomefuncionario[strcspn(f[i].nomefuncionario, "\n")] = 0;

            f[i].idfuncionario = gerarIdUnico(FUNCIONARIO);
            printf("ID do funcionario gerado: %d\n", f[i].idfuncionario);
            break;
        }
        case CLIENTE:
        {
            estruturacliente *c = (estruturacliente *)(*registro);
            c[i].nomecliente = (char *)malloc(30 * sizeof(char));
            c[i].enderecocliente = (char *)malloc(50 * sizeof(char));

            if (c[i].nomecliente == NULL || c[i].enderecocliente == NULL)
            {
                printf("Erro ao alocar memória para o cliente.\n");
                return;
            }

            printf("Informe o nome do cliente: ");
            fgets(c[i].nomecliente, 30, stdin);
            c[i].nomecliente[strcspn(c[i].nomecliente, "\n")] = 0;

            printf("Informe o endereco do cliente: ");
            fgets(c[i].enderecocliente, 50, stdin);
            c[i].enderecocliente[strcspn(c[i].enderecocliente, "\n")] = 0;

            do {
                printf("Informe o servico solicitado ('1' Economico, '2' Padrao, '3' Premium): ");
                scanf("%d", &c[i].tiposervicocliente);
                getchar();
                if (c[i].tiposervicocliente < 1 || c[i].tiposervicocliente > 3) {
                    printf("Opcao invalida. Por favor, digite um numero entre 1 e 3\n");
                }
            } while (c[i].tiposervicocliente < 1 || c[i].tiposervicocliente > 3);

            c[i].idcliente = gerarIdUnico(CLIENTE);
            printf("ID do cliente gerado: %d\n", c[i].idcliente);
            break;
        }
        case VEICULO:
        {
            estruturaveiculo *v = (estruturaveiculo *)(*registro);
            v[i].nomeveiculo = (char *)malloc(30 * sizeof(char));

            printf("Informe o tipo do veiculo: ");
            fgets(v[i].nomeveiculo, 30, stdin);
            v[i].nomeveiculo[strcspn(v[i].nomeveiculo, "\n")] = 0;

            
            printf("Informe a capacidade de carga em KG: ");
            scanf("%d", &v[i].cargaveiculo);
            getchar();
            
            do {
            printf("Informe o status do veiculo ('0' ocupado, '1' disponivel): ");
            scanf("%d", &v[i].statusveiculo);
            getchar();
            if (v[i].statusveiculo < 0 || v[i].statusveiculo > 1) {
                printf("Opcao invalida. Por favor, digite 0 ou 1 :\n");
            }
            } while (v[i].statusveiculo < 0 || v[i].statusveiculo > 1);

            v[i].idveiculo = gerarIdUnico(VEICULO);
            printf("ID do veiculo gerado: %d\n", v[i].idveiculo);
            break;
        }
        /////
        case ENTREGA:
        {
            estruturaentrega *e = (estruturaentrega *)(*registro);
            e[i].origemEntrega = (char *)malloc(50 * sizeof(char));
            e[i].destinoEntrega = (char *)malloc(50 * sizeof(char));

            printf("\n===== Cadastrar uma entrega =====\n");

            // Pergunta a origem e destino
            printf("Informe a origem da entrega: ");
            fgets(e[i].origemEntrega, 50, stdin);
            e[i].origemEntrega[strcspn(e[i].origemEntrega, "\n")] = 0;
            
            printf("Informe o destino da entrega: ");
            fgets(e[i].destinoEntrega, 50, stdin);
            e[i].destinoEntrega[strcspn(e[i].destinoEntrega, "\n")] = 0;
            
            printf("Informe o tempo estimado da entrega em horas: ");
            scanf("%d", &e[i].tempoEntrega);

            e[i].idEntrega = gerarIdUnico(ENTREGA);
            printf("Entrega cadastrada com ID: %d\n", e[i].idEntrega);
            getchar();

            break;
        }
        case ENTREGAREALIZADA:
        {
            estruturaentrega e; // Estrutura para a entrega realizada

            int tamanhoClientes, tamanhoFuncionarios, tamanhoVeiculos, tamanhoEnderecos, tamanhoStatus;
            int *idsClientes = lerIds("arq_clientes.txt", &tamanhoClientes);
            char **enderecosClientes = lerEnderecos("arq_clientes.txt", &tamanhoEnderecos);
            int *statusVeiculo = lerStatusVeiculo("arq_veiculos.txt", &tamanhoStatus);
            int *idsFuncionarios = lerIds("arq_funcionarios.txt", &tamanhoFuncionarios);
            int *idsVeiculos = lerIds("arq_veiculos.txt", &tamanhoVeiculos);

            if (!idsClientes || !enderecosClientes || !statusVeiculo || !idsFuncionarios || !idsVeiculos)
            {
                printf("Erro ao carregar dados necessarios para a entrega.\n");

                return;
            }

            // Solicita o ID da entrega
            int idEntregaVerificada;
            printf("Digite o ID da entrega desejada: ");
            scanf("%d", &idEntregaVerificada);
            getchar();

            // Abre o arquivo de entregas cadastradas
            FILE *arquivoEntregas = fopen("arq_entregas.txt", "r");
            if (!arquivoEntregas)
            {
                printf("Erro ao abrir o arquivo de entregas.\n");
                return;
            }

            char buffer[200];
            int encontrado = 0;

            // Busca a origem e o destino no arquivo
            while (fgets(buffer, sizeof(buffer), arquivoEntregas))
            {
                if (strstr(buffer, "===== Registro Entrega ====="))
                {
                    int idLido;
                    char origemLido[50];
                    char destinoLido[50];

                    // Ler o ID da entrega
                    if (fgets(buffer, sizeof(buffer), arquivoEntregas) && sscanf(buffer, "ID: %d", &idLido) == 1)
                    {
                        if (idLido == idEntregaVerificada)
                        {
                            // Ler a origem
                            if (fgets(buffer, sizeof(buffer), arquivoEntregas) && sscanf(buffer, "Origem: %[^\n]", origemLido) == 1)
                            {
                                e.origemEntrega = strdup(origemLido); // Copia a origem
                            }

                            // Ler o destino
                            if (fgets(buffer, sizeof(buffer), arquivoEntregas) && sscanf(buffer, "Destino: %[^\n]", destinoLido) == 1)
                            {
                                e.destinoEntrega = strdup(destinoLido); // Copia o destino
                            }

                            encontrado = 1;
                            break;
                        }
                    }
                }
            }

            fclose(arquivoEntregas);

            if (!encontrado)
            {
                printf("Entrega com ID %d nao encontrada.\n", idEntregaVerificada);
                return;
            }

            // Solicita o ID do cliente
            int idClienteVerificado;
            while (1)
            {
                printf("Digite o ID do cliente desejado: ");
                scanf("%d", &idClienteVerificado);
                getchar();

                if (!verificarId2(idClienteVerificado, idsClientes, tamanhoClientes))
                {
                    printf("ID do cliente %d nao encontrado.\n", idClienteVerificado);
                    continue;
                }
                break;
            }

            // Verificar ID do funcionario
            int idFuncionarioVerificado;
            while (1)
            {
                printf("Digite o ID do funcionario responsavel: ");
                scanf("%d", &idFuncionarioVerificado);
                getchar();
                if (!verificarId2(idFuncionarioVerificado, idsFuncionarios, tamanhoFuncionarios))
                {
                    printf("ID do funcionario %d nao encontrado.\n", idFuncionarioVerificado);
                    continue;
                }
                break;
            }

            // Verificar ID do veiculo
            int idVeiculoVerificado;
            while (1)
            {
                printf("Digite o ID do veiculo desejado: ");
                scanf("%d", &idVeiculoVerificado);
                getchar();

                if (!verificarId2(idVeiculoVerificado, idsVeiculos, tamanhoVeiculos))
                {
                    printf("ID do veiculo %d nao encontrado.\n", idVeiculoVerificado);
                    continue;
                }

                // Verificar se o veiculo esta disponivel
                int statusDoVeiculo = -1;
                for (int j = 0; j < tamanhoVeiculos; j++)
                {
                    if (idsVeiculos[j] == idVeiculoVerificado)
                    {
                        statusDoVeiculo = statusVeiculo[j];
                        break;
                    }
                }

                if (statusDoVeiculo == 0)
                {
                    printf("Veiculo %d esta ocupado. Escolha outro.\n", idVeiculoVerificado);
                    continue;
                }

                break;
            }

            // Preenche o tempo estimado
            printf("Informe o Tempo Total Para Conclusao Da Entrega(Em Horas): ");
            scanf("%d", &e.tempoEntrega);

            e.idcliente = idClienteVerificado;
            e.idfuncionario = idFuncionarioVerificado;
            e.idveiculo = idVeiculoVerificado;

            // Salva a entrega realizada no arquivo
            FILE *arquivoEntregasRealizadas = fopen("arq_entregas_realizadas.txt", "a");
            if (!arquivoEntregasRealizadas)
            {
                printf("Erro ao abrir o arquivo de entregas realizadas.\n");
                free(e.origemEntrega);
                free(e.destinoEntrega);
                return;
            }

            // Escreve os dados da entrega realizada
            fprintf(arquivoEntregasRealizadas, "===== Registro Entrega Realizada =====\n");
            fprintf(arquivoEntregasRealizadas, "ID da entrega realizada: %d\n", idEntregaVerificada);
            fprintf(arquivoEntregasRealizadas, "ID do cliente: %d\n", e.idcliente);
            fprintf(arquivoEntregasRealizadas, "ID do funcionario: %d\n", e.idfuncionario);
            fprintf(arquivoEntregasRealizadas, "ID do veiculo: %d\n", e.idveiculo);
            fprintf(arquivoEntregasRealizadas, "Origem: %s\n", e.origemEntrega);
            fprintf(arquivoEntregasRealizadas, "Destino: %s\n", e.destinoEntrega);
            fprintf(arquivoEntregasRealizadas, "Tempo Para Conclusao Da Entrega (Em Horas): %d\n", e.tempoEntrega);
            fclose(arquivoEntregasRealizadas);

            printf("Entrega realizada com sucesso e salva em arq_entregas_realizadas.txt.\n");

            // Libera memória alocada para origem e destino
            free(e.origemEntrega);
            free(e.destinoEntrega);
            break;
        }
        }
    }
}

// funcao para exibir a quantidade de registros num arquivo
int ContarDadosNoArquivo(const char *nome_arquivo, const char *termo_busca)
{
    FILE *arq = fopen(nome_arquivo, "r");
    if (arq == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    int contador = 0;
    char buffer[200];
    // Le cada linha do arquivo
    while (fgets(buffer, sizeof(buffer), arq))
    {
        // Verifica se a linha contém o termo de busca
        if (strstr(buffer, termo_busca))
        {
            contador++;
        }
    }
    fclose(arq);
    return contador;
}

// funcao para exibir todos os dados em um txt
void VisualizarDadosNoArquivo(TipoRegistro tipo)
{
    const char *nomeArquivo;

    switch (tipo)
    {
    case FUNCIONARIO:
        nomeArquivo = "arq_funcionarios.txt";
        break;
    case CLIENTE:
        nomeArquivo = "arq_clientes.txt";
        break;
    case VEICULO:
        nomeArquivo = "arq_veiculos.txt";
        break;
    case ENTREGA:
        nomeArquivo = "arq_entregas.txt";
        break;
        case ENTREGAREALIZADA:
        nomeArquivo = "arq_entregas_realizadas.txt";
        break;
    default:
        printf("Tipo invalido!\n");
        return;
    }

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char buffer[200];
    while (fgets(buffer, sizeof(buffer), arquivo))
    {
        printf("%s", buffer);
    }

    fclose(arquivo);
    voltarencerrarprograma();
    limparTerminal();
}

void lerDadosDoArquivo(void *registro, int num, TipoRegistro tipo)
{
    FILE *arquivo;
    char buffer[200];
    int i = 0;
    // Abrir o arquivo com base no tipo de registro
    switch (tipo)
    {
    case FUNCIONARIO:
        arquivo = abrirArquivo("arq_funcionarios.txt", "r");
        break;
    case CLIENTE:
        arquivo = abrirArquivo("arq_clientes.txt", "r");
        break;
    case VEICULO:
        arquivo = abrirArquivo("arq_veiculos.txt", "r");
        break;
    case ENTREGA:
        arquivo = abrirArquivo("arq_entregas.txt", "r");
        break;
    case ENTREGAREALIZADA:
        arquivo = abrirArquivo("arq_entregas_realizadas.txt", "r");
        break;
    default:
        return;
    }

    while (fgets(buffer, sizeof(buffer), arquivo) && i < num)
    {
        // Verificar se a linha contém as informacoes esperadas para cada tipo de registro
        switch (tipo)
        {
        case FUNCIONARIO:
        {
            estruturafuncionario *f = (estruturafuncionario *)registro;
            if (strstr(buffer, "===== Registro Funcionario"))
            {
                if (fgets(buffer, sizeof(buffer), arquivo))
                {
                    char *nome = strstr(buffer, "Nome: ");
                    nome += strlen("Nome: ");
                    f[i].nomefuncionario = (char *)malloc(30 * sizeof(char));
                    strcpy(f[i].nomefuncionario, nome);
                    f[i].nomefuncionario[strcspn(f[i].nomefuncionario, "\n")] = 0;
                }

                if (fgets(buffer, sizeof(buffer), arquivo))
                {
                    char *id = strstr(buffer, "ID: ");
                    id += strlen("ID: ");
                    sscanf(id, "%d", &f[i].idfuncionario);
                }
                i++;
            }
            break;
        }
        case CLIENTE:
        {
            estruturacliente *c = (estruturacliente *)registro;
            if (strstr(buffer, "===== Registro Cliente"))
            {
                c[i].nomecliente = (char *)malloc(30 * sizeof(char));
                c[i].enderecocliente = (char *)malloc(50 * sizeof(char));

                // Ler nome
                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Nome cliente: "))
                {
                    sscanf(buffer, "Nome cliente: %[^\n]", c[i].nomecliente);
                }

                // Ler ID
                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "ID: "))
                {
                    sscanf(buffer, "ID: %d", &c[i].idcliente);
                }

                // Ler endereco
                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Endereco completo: "))
                {
                    sscanf(buffer, "Endereco completo: %[^\n]", c[i].enderecocliente);
                }

                // Ler tipo de servico
                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Tipo de servico solicitado: "))
                {
                    sscanf(buffer, "Tipo de servico solicitado: %d", &c[i].tiposervicocliente);
                }

                i++;
            }
            break;
        }
        case VEICULO:
        {
            estruturaveiculo *v = (estruturaveiculo *)registro;
            if (strstr(buffer, "===== Registro Veiculo"))
            {
                v[i].nomeveiculo = (char *)malloc(30 * sizeof(char));

                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Nome: "))
                {
                    sscanf(buffer, "Nome: %[^\n]", v[i].nomeveiculo);
                }

                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "ID: "))
                {
                    sscanf(buffer, "ID: %d", &v[i].idveiculo);
                }

                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Capacidade de carga em KG: "))
                {
                    sscanf(buffer, "Capacidade de carga em KG: %d", &v[i].cargaveiculo);
                }

                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Status veiculo: "))
                {
                    sscanf(buffer, "Status veiculo: %d", &v[i].statusveiculo);
                }

                i++;
            }
            break;
        }
        case ENTREGA:
        {
            estruturaentrega *e = (estruturaentrega *)registro;
            if (strstr(buffer, "===== Registro Entrega"))
            {
                e[i].origemEntrega = (char *)malloc(50 * sizeof(char));
                e[i].destinoEntrega = (char *)malloc(50 * sizeof(char));

                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "ID: "))
                {
                    sscanf(buffer, "ID: %d", &e[i].idEntrega);
                }
                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Origem: "))
                {
                    sscanf(buffer, "Origem: %[^\n]", e[i].origemEntrega);
                }
                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Destino: "))
                {
                    sscanf(buffer, "Destino: %[^\n]", e[i].destinoEntrega);
                }
                if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Tempo estimado da entrega (em horas): "))
                {
                    sscanf(buffer, "Tempo estimado da entrega (em horas): %d", &e[i].tempoEntrega);
                }
                i++;
            }
            break;
        }
        case ENTREGAREALIZADA:
        {
            estruturaentrega *e = (estruturaentrega *)registro;
            if (strstr(buffer, "===== Registro Entrega Realizada")){
            e[i].origemEntrega = (char *)malloc(50 * sizeof(char));
            e[i].destinoEntrega = (char *)malloc(50 * sizeof(char));
            if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "ID da entrega realizada: "))
            {
                sscanf(buffer, "ID da entrega realizada: %d", &e[i].idEntrega);
            }
            if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "ID do cliente: "))
            {
                sscanf(buffer, "ID do cliente: %d", &e[i].idcliente);
            }
            if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "ID do funcionario: "))
            {
                sscanf(buffer, "ID do funcionario: %d", &e[i].idfuncionario);
            }
            if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "ID do veiculo: "))
            {
                sscanf(buffer, "ID do veiculo: %d", &e[i].idveiculo);
            }
            if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Origem: "))
            {
                sscanf(buffer, "Origem: %[^\n]", e[i].origemEntrega);
            }
            if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Destino: "))
            {
                sscanf(buffer, "Destino: %[^\n]", e[i].destinoEntrega);
            }
            if (fgets(buffer, sizeof(buffer), arquivo) && strstr(buffer, "Tempo Para Conclusao Da Entrega (Em Horas): "))
            {
                sscanf(buffer, "Tempo Para Conclusao Da Entrega (Em Horas): %d", &e[i].tempoEntrega);
            }
            i++;
           }
        break;  
        }

        }
    }

    fclose(arquivo);
}

void alterarDados(void *registro, int num, TipoRegistro tipo)
{
    int idParaAlterar, infoAlterar;
    int encontrado = 0;

    printf("\nInforme o ID que deseja alterar: ");
    scanf("%d", &idParaAlterar);
    getchar();

    switch (tipo)
    {
    case FUNCIONARIO:
    {
        estruturafuncionario *funcionario = (estruturafuncionario *)registro;
        for (int i = 0; i < num; i++)
        {
            if (funcionario[i].idfuncionario == idParaAlterar)
            {
                encontrado = 1;
                printf("\n===== Informacoes que podem ser alteradas =====\n");
                printf("Nome -> 1 \n");
                printf("\nQual informacao deseja alterar: ");
                scanf("%d", &infoAlterar);
                getchar();

                if (infoAlterar == 1)
                {
                    char novoNome[30];
                    printf("Informe o novo nome do funcionario: ");
                    fgets(novoNome, 30, stdin);
                    novoNome[strcspn(novoNome, "\n")] = 0;
                    free(funcionario[i].nomefuncionario);
                    funcionario[i].nomefuncionario = (char *)malloc(30 * sizeof(char));
                    strcpy(funcionario[i].nomefuncionario, novoNome);
                }
            }
        }
        if (encontrado==0)
        {
            printf("Registro com o ID %d nao encontrado.\n", idParaAlterar);
            break;
        }
        printf("Dados do Funcionario Alterados com sucesso.\n"); 
        break;
    }
    case CLIENTE:
    {
        estruturacliente *cliente = (estruturacliente *)registro;
        for (int i = 0; i < num; i++)
        {
            if (cliente[i].idcliente == idParaAlterar)
            {
                encontrado = 1;
                printf("\n===== Informacoes que podem ser alteradas =====\n");
                printf("Nome -> 1 \nEndereco -> 2 \nTipo de servico -> 3\n");
                printf("\nQual informacao deseja alterar: ");
                scanf("%d", &infoAlterar);
                getchar();

                if (infoAlterar == 1)
                {
                    char novoNome[30];
                    printf("Informe o novo nome do cliente: ");
                    fgets(novoNome, 30, stdin);
                    novoNome[strcspn(novoNome, "\n")] = 0;
                    free(cliente[i].nomecliente);
                    cliente[i].nomecliente = (char *)malloc(30 * sizeof(char));
                    if (cliente[i].nomecliente == NULL)
                    {
                        printf("Erro ao alocar memória para o nome do cliente.\n");
                        return;
                    }
                    strcpy(cliente[i].nomecliente, novoNome);
                }

                else if (infoAlterar == 2)
                {
                    char novoEndereco[50];
                    printf("Informe o novo endereco do cliente: ");
                    fgets(novoEndereco, 50, stdin);
                    novoEndereco[strcspn(novoEndereco, "\n")] = 0;
                    free(cliente[i].enderecocliente);
                    cliente[i].enderecocliente = (char *)malloc(50 * sizeof(char));
                    strcpy(cliente[i].enderecocliente, novoEndereco);
                }
                else if (infoAlterar == 3)
                {
                    int novoTipoServico;
                    do {
                    printf("Informe o novo tipo de servico solicitado ('1' Economico, '2' Padrao, '3' Premium): ");
                    scanf("%d", &novoTipoServico);
                    if(novoTipoServico<1 || novoTipoServico>3){
                        printf("Opcao Invalida. Digite Um Numero Entre 1 Ou 3 :");
                    }
                    } while(novoTipoServico<1 || novoTipoServico>3);
                
                    cliente[i].tiposervicocliente = novoTipoServico;
                }
            }
        }
        if (encontrado==0)
        {
            printf("Registro com o ID %d nao encontrado.\n", idParaAlterar);
            break;
        }
        printf("Dados do Cliente alterados com sucesso.\n"); 
        break;
    }
    case VEICULO:
    {
        estruturaveiculo *veiculo = (estruturaveiculo *)registro;
        for (int i = 0; i < num; i++)
        {
            if (veiculo[i].idveiculo == idParaAlterar)
            {
                encontrado = 1;
                printf("\n===== Informacoes que podem ser alteradas =====\n");
                printf("Tipo -> 1 \nCapacidade de carga -> 2 \nStatus -> 3\n");
                printf("\nQual informacao deseja alterar: ");
                scanf("%d", &infoAlterar);
                getchar();

                if (infoAlterar == 1)
                {
                    char novoTipo[30];
                    printf("Informe o novo tipo do veiculo: ");
                    fgets(novoTipo, 30, stdin);
                    novoTipo[strcspn(novoTipo, "\n")] = 0;
                    free(veiculo[i].nomeveiculo);
                    veiculo[i].nomeveiculo = (char *)malloc(30 * sizeof(char));
                    strcpy(veiculo[i].nomeveiculo, novoTipo);
                }
                else if (infoAlterar == 2)
                {
                    int novaCarga;
                    printf("Informe a nova capacidade de carga em KG: ");
                    scanf("%d", &novaCarga);
                    veiculo[i].cargaveiculo = novaCarga;
                }
                else if (infoAlterar == 3)
                {
                    int novoStatus;
                    do{
                    printf("Informe o novo status do veiculo (0 para Ocupado e 1 para Disponivel): ");
                    scanf("%d", &novoStatus);
                    if (novoStatus < 0 || novoStatus > 1) {
                        printf("Opcao invalida. Por favor, digite 0 ou 1 :\n");
                    }
                    } while (novoStatus < 0 || novoStatus > 1);
                    veiculo[i].statusveiculo = novoStatus;
                }
            }
        }
        if (encontrado==0)
        {
            printf("Registro com o ID %d nao encontrado.\n", idParaAlterar);
            break;
        }
        printf("Dados do veiculo alterados com sucesso.\n"); 
        break;
    }

    case ENTREGA:
    {
        estruturaentrega *entrega = (estruturaentrega *)registro;
        for (int i = 0; i < num; i++)
        {
            if (entrega[i].idEntrega == idParaAlterar)
            {
                encontrado = 1;
                printf("\n===== Informacoes que podem ser alteradas =====\n");
                printf("Origem da entrega -> 1 \nDestino da entrega -> 2\nTempo Estimado da entrega (Em horas) -> 3\n");
                printf("\nQual informacao deseja alterar: ");
                scanf("%d", &infoAlterar);
                getchar();

                if (infoAlterar == 1)
                {
                    char novoTipo[30];
                    printf("Informe o novo origem da entrega: ");
                    fgets(novoTipo, 30, stdin);
                    novoTipo[strcspn(novoTipo, "\n")] = 0;
                    free(entrega[i].origemEntrega);
                    entrega[i].origemEntrega = (char *)malloc(30 * sizeof(char));
                    strcpy(entrega[i].origemEntrega, novoTipo);
                }
                else if (infoAlterar == 2)
                {
                    char novoTipo[30];
                    printf("Informe o novo destino da entrega: ");
                    fgets(novoTipo, 30, stdin);
                    novoTipo[strcspn(novoTipo, "\n")] = 0;
                    free(entrega[i].destinoEntrega);
                    entrega[i].destinoEntrega = (char *)malloc(30 * sizeof(char));
                    strcpy(entrega[i].destinoEntrega, novoTipo);
                }
                else if (infoAlterar == 3)
                {
                int novoTempo=0;
                printf("Informe o novo Tempo Estimado Da Entrega (Em horas):");
                scanf("%d", &novoTempo);
                entrega[i].tempoEntrega = novoTempo;
                }
            }
        }
        if (encontrado==0)
        {
            printf("Registro com o ID %d nao encontrado.\n", idParaAlterar);
            break;
        }
        printf("Informacoes Da Entrega Alterados Com Sucesso ! \n"); 
        break;
    }
}
}

void DeletarDadosNoArquivo(void **registro, int *numregistros, TipoRegistro tipo)
{
    int idParaDeletar;
    printf("Informe o ID que deseja deletar: ");
    scanf("%d", &idParaDeletar);
    getchar();

    int indiceParaRemover = -1;

    // Procura pelo ID a ser removido
    for (int i = 0; i < *numregistros; i++)
    {
        if (tipo == FUNCIONARIO)
        {
            estruturafuncionario *funcionario = (estruturafuncionario *)*registro;
            if (funcionario[i].idfuncionario == idParaDeletar)
            {
                indiceParaRemover = i;
                break;
            }
        }
        else if (tipo == CLIENTE)
        {
            estruturacliente *cliente = (estruturacliente *)*registro;
            if (cliente[i].idcliente == idParaDeletar)
            {
                indiceParaRemover = i;
                break;
            }
        }
        else if (tipo == VEICULO)
        {
            estruturaveiculo *veiculo = (estruturaveiculo *)*registro;
            if (veiculo[i].idveiculo == idParaDeletar)
            {
                indiceParaRemover = i;
                break;
            }
        }
        else if (tipo == ENTREGA)
        {
            estruturaentrega *entrega = (estruturaentrega *)*registro;
            if (entrega[i].idEntrega == idParaDeletar)
            {
                indiceParaRemover = i;
                break;
            }
        }
        else if (tipo == ENTREGAREALIZADA)
        {
            estruturaentrega *entrega = (estruturaentrega *)*registro;
            if (entrega[i].idEntrega == idParaDeletar)
            {
                indiceParaRemover = i;
                break;
            }
        }
    }

    if (indiceParaRemover == -1)
    {
        printf("Registro com ID %d nao encontrado.\n", idParaDeletar);
        return;
    }

    // Libera memória e move os elementos
    if (tipo == FUNCIONARIO)
    {
        estruturafuncionario *funcionario = (estruturafuncionario *)*registro;
        free(funcionario[indiceParaRemover].nomefuncionario);
        for (int i = indiceParaRemover; i < (*numregistros) - 1; i++)
        {
            funcionario[i] = funcionario[i + 1];
        }
        *registro = realloc(*registro, (*numregistros - 1) * sizeof(estruturafuncionario));
    }
    else if (tipo == CLIENTE)
    {
        estruturacliente *cliente = (estruturacliente *)*registro;
        free(cliente[indiceParaRemover].nomecliente);
        for (int i = indiceParaRemover; i < (*numregistros) - 1; i++)
        {
            cliente[i] = cliente[i + 1];
        }
        *registro = realloc(*registro, (*numregistros - 1) * sizeof(estruturacliente));
    }
    else if (tipo == VEICULO)
    {
        estruturaveiculo *veiculo = (estruturaveiculo *)*registro;
        free(veiculo[indiceParaRemover].nomeveiculo);
        for (int i = indiceParaRemover; i < (*numregistros) - 1; i++)
        {
            veiculo[i] = veiculo[i + 1];
        }
        *registro = realloc(*registro, (*numregistros - 1) * sizeof(estruturaveiculo));
    }
    else if (tipo == ENTREGA)
    {
        estruturaentrega *entrega = (estruturaentrega *)*registro;
        free(entrega[indiceParaRemover].origemEntrega);
        free(entrega[indiceParaRemover].destinoEntrega);
        for (int i = indiceParaRemover; i < (*numregistros) - 1; i++)
        {
            entrega[i] = entrega[i + 1];
        }
        *registro = realloc(*registro, (*numregistros - 1) * sizeof(estruturaentrega));
    }
    else if (tipo == ENTREGAREALIZADA)
    {
        estruturaentrega *entrega = (estruturaentrega *)*registro;
        free(entrega[indiceParaRemover].origemEntrega);
        free(entrega[indiceParaRemover].destinoEntrega);
        for (int i = indiceParaRemover; i < (*numregistros) - 1; i++)
        {
            entrega[i] = entrega[i + 1];
        }
        *registro = realloc(*registro, (*numregistros - 1) * sizeof(estruturaentrega));
    }

    (*numregistros)--;

    if (*numregistros > 0 && *registro == NULL)
    {
        printf("Erro ao realocar memória após a remocao.\n");
        exit(1);
    }

    // Chamada correta para salvar os dados
    salvarDadosNoArquivo(*registro, *numregistros, "w", tipo);

    printf("Registro com ID %d foi removido com sucesso.\n", idParaDeletar);
}

// funcao para liberar memoria dos mallocs
void liberarMemorias(void *registro, int numregistros, TipoRegistro tipo)
{
    if (registro == NULL)
        return;

    if (tipo == FUNCIONARIO)
    {
        estruturafuncionario *funcionario = (estruturafuncionario *)registro;
        for (int i = 0; i < numregistros; i++)
        {
            free(funcionario[i].nomefuncionario);
        }
    }
    else if (tipo == CLIENTE)
    {
        estruturacliente *cliente = (estruturacliente *)registro;
        for (int i = 0; i < numregistros; i++)
        {
            free(cliente[i].nomecliente);
        }
    }
    else if (tipo == VEICULO)
    {
        estruturaveiculo *veiculo = (estruturaveiculo *)registro;
        for (int i = 0; i < numregistros; i++)
        {
            free(veiculo[i].nomeveiculo);
        }
    }
    else if (tipo == ENTREGA)
    {
        estruturaentrega *entrega = (estruturaentrega *)registro;
        for (int i = 0; i < numregistros; i++)
        {
            free(entrega[i].origemEntrega);
            free(entrega[i].destinoEntrega);
        }
    }

    free(registro);
    voltarencerrarprograma();
}
// funcoes para chamada principal
void setorfuncionario()
{
    estruturafuncionario *funcionario;
    int numdefuncionarios, numTipoDeOperacao;
    // while com loop ate o programa encerrar
    while (1)
    {
        limparTerminal();
        printf("===== Menu de Operacoes - Funcionarios =====\n \n Adicionar -> 1 \n Visualizar -> 2 \n alterar -> 3 \n Deletar -> 4\n Voltar Para Menu De Setores -> 5 \n Encerrar Programa -> 6\n\nQual operacao deseja realizar: ");
        scanf("%d", &numTipoDeOperacao);
        getchar();

        switch (numTipoDeOperacao)
        {
            // chamada para adicionar funcionario
        case 1:
            printf("\nQuantos funcionarios voce deseja adicionar: \n");
            scanf("%d", &numdefuncionarios);
            getchar();
            estruturafuncionario *funcionario = alocarEstruturaFuncionario(numdefuncionarios);
            AdicionarDadosNoArquivo((void **)&funcionario, &numdefuncionarios, FUNCIONARIO);
            salvarDadosNoArquivo(funcionario, numdefuncionarios, "a", FUNCIONARIO);
            printf("Os dados dos funcionarios cadastrados foram salvos com sucesso.\n");
            liberarMemorias(funcionario, numdefuncionarios, FUNCIONARIO);

            break;

            // chamada para visualizar funcionarios
        case 2:
            VisualizarDadosNoArquivo(FUNCIONARIO);
            break;

            // chamada para alterar dados dos funcionarios
        case 3:
            numdefuncionarios = ContarDadosNoArquivo("arq_funcionarios.txt", "===== Registro Funcionario");
            if (numdefuncionarios > 0)
            {
                estruturafuncionario *funcionario = alocarEstruturaFuncionario(numdefuncionarios);
                /*lerFuncionariosDoArquivo(funcionario, numdefuncionarios); // Ler do arquivo */
                lerDadosDoArquivo(funcionario, numdefuncionarios, FUNCIONARIO);
                alterarDados(funcionario, numdefuncionarios, FUNCIONARIO);
                salvarDadosNoArquivo(funcionario, numdefuncionarios, "w", FUNCIONARIO);
                liberarMemorias(funcionario, numdefuncionarios, FUNCIONARIO);
            }
            break;

            // chamada para deletar funcionario
        case 4:
            numdefuncionarios = ContarDadosNoArquivo("arq_funcionarios.txt", "===== Registro Funcionario");
            if (numdefuncionarios > 0)
            {
                estruturafuncionario *funcionario = alocarEstruturaFuncionario(numdefuncionarios);
                lerDadosDoArquivo(funcionario, numdefuncionarios, FUNCIONARIO);
                DeletarDadosNoArquivo((void **)&funcionario, &numdefuncionarios, FUNCIONARIO);
                liberarMemorias(funcionario, numdefuncionarios, FUNCIONARIO);
            }
            break;
        // chamada para voltar para menu de setor
        case 5:
            return;
            break;
        // chamada para encerrar programa
        case 6:
            exit(0);
        }
    }
}
void setorveiculo()
{
    estruturaveiculo *veiculo;
    int numdeveiculos, numTipoDeOperacao;
    // while com loop ate o programa encerrar
    while (1)
    {
        limparTerminal();
        printf("===== Menu de Operacoes - Veiculos =====\n \n Adicionar -> 1 \n Visualizar -> 2 \n alterar -> 3 \n Deletar -> 4 \n Voltar Para Menu De Setores -> 5 \n Encerrar Programa -> 6 \n\nQual operacao deseja realizar: ");
        scanf("%d", &numTipoDeOperacao);
        getchar();

        switch (numTipoDeOperacao)
        {
            // chamada para adicionar veiculo
        case 1:
            printf("\nQuantos veiculos voce deseja adicionar: \n");
            scanf("%d", &numdeveiculos);
            getchar();
            estruturaveiculo *veiculo = alocarEstruturaVeiculo(numdeveiculos);
            AdicionarDadosNoArquivo((void **)&veiculo, &numdeveiculos, VEICULO);
            salvarDadosNoArquivo(veiculo, numdeveiculos, "a", VEICULO);
            printf("Os dados dos veiculos cadastrados foram salvos com sucesso.\n");
            liberarMemorias(veiculo, numdeveiculos, VEICULO);

            break;

            // chamada para visualizar veiculos
        case 2:
            VisualizarDadosNoArquivo(VEICULO);
            break;

            // chamada para alterar dados dos veiculos
        case 3:
            numdeveiculos = ContarDadosNoArquivo("arq_veiculos.txt", "===== Registro Veiculo");
            if (numdeveiculos > 0)
            {
                estruturaveiculo *veiculo = alocarEstruturaVeiculo(numdeveiculos);
                lerDadosDoArquivo(veiculo, numdeveiculos, VEICULO);
                alterarDados(veiculo, numdeveiculos, VEICULO);
                salvarDadosNoArquivo(veiculo, numdeveiculos, "w", VEICULO);
                liberarMemorias(veiculo, numdeveiculos, VEICULO);
            }
            break;

            // chamada para deletar veiculo
        case 4:
            numdeveiculos = ContarDadosNoArquivo("arq_veiculos.txt", "===== Registro Veiculo");
            if (numdeveiculos > 0)
            {
                estruturaveiculo *veiculo = alocarEstruturaVeiculo(numdeveiculos);
                lerDadosDoArquivo(veiculo, numdeveiculos, VEICULO);
                DeletarDadosNoArquivo((void **)&veiculo, &numdeveiculos, VEICULO);
                liberarMemorias(veiculo, numdeveiculos, VEICULO);
            }
            break;
        // chamada para voltar para menu de setor
        case 5:
            return;
            break;
        // chamada para encerrar programa
        case 6:
            exit(0);
        }
    }
}
void setorcliente()
{
    estruturacliente *cliente;
    int numdeclientes, numTipoDeOperacao;
    // while com loop ate o programa encerrar
    while (1)
    {
        limparTerminal();
        printf("===== Menu de Operacoes - Clientes =====\n \n Adicionar -> 1 \n Visualizar -> 2 \n alterar -> 3 \n Deletar -> 4 \n Voltar Para Menu De Setores -> 5 \n Encerrar Programa -> 6\n\nQual operacao deseja realizar: ");
        scanf("%d", &numTipoDeOperacao);
        getchar();

        switch (numTipoDeOperacao)
        {
            // chamada para adicionar cliente
        case 1:
            printf("\nQuantos clientes voce deseja adicionar: ");
            scanf("%d", &numdeclientes);
            getchar();
            estruturacliente *cliente = alocarEstruturacliente(numdeclientes);
            AdicionarDadosNoArquivo((void **)&cliente, &numdeclientes, CLIENTE);
            salvarDadosNoArquivo(cliente, numdeclientes, "a", CLIENTE);
            printf("Os dados dos clientes cadastrados foram salvos com sucesso.\n");
            liberarMemorias(cliente, numdeclientes, CLIENTE);

            break;

            // chamada para visualizar clientes
        case 2:
            VisualizarDadosNoArquivo(CLIENTE);
            break;

            // chamada para alterar dados dos clientes
        case 3:
            numdeclientes = ContarDadosNoArquivo("arq_clientes.txt", "===== Registro Cliente");
            if (numdeclientes > 0)
            {
                estruturacliente *cliente = alocarEstruturacliente(numdeclientes);
                lerDadosDoArquivo(cliente, numdeclientes, CLIENTE);
                alterarDados(cliente, numdeclientes, CLIENTE);
                salvarDadosNoArquivo(cliente, numdeclientes, "w", CLIENTE);
                liberarMemorias(cliente, numdeclientes, CLIENTE);
            }
            break;

            // chamada para deletar cliente
        case 4:
            numdeclientes = ContarDadosNoArquivo("arq_clientes.txt", "===== Registro Cliente");
            if (numdeclientes > 0)
            {
                estruturacliente *cliente = alocarEstruturacliente(numdeclientes);
                lerDadosDoArquivo(cliente, numdeclientes, CLIENTE);
                DeletarDadosNoArquivo((void **)&cliente, &numdeclientes, CLIENTE);
                liberarMemorias(cliente, numdeclientes, CLIENTE);
            }
            break;
        // chamada para voltar para menu de setor
        case 5:
            return;
            break;
        // chamada para encerrar programa
        case 6:
            exit(0);
        }
    }
}
void setorentrega()
{
    estruturaentrega *entrega;

    int numdeentregas, numTipoDeOperacao;

    while (1)
    {
        limparTerminal();
        printf("===== Menu de Operacoes - Entregas =====\n \n Adicionar Entrega a Ser Feita -> 1 \n Visualizar Entregas Pendentes -> 2 \n Alterar Entrega Pendente-> 3 \n Deletar Entrega Pendente -> 4 \n Realizar Entrega -> 5 \n Deletar Uma Entrega Concluida -> 6 \n Voltar Para Menu de Setores -> 7 \n Sair do programa -> 8 \n\nQual operacao deseja realizar: ");
        scanf("%d", &numTipoDeOperacao);
        getchar();

        switch (numTipoDeOperacao)
        {

        case 1:
            printf("\nQuantas entregas voce deseja adicionar: ");
            scanf("%d", &numdeentregas);
            getchar();
            estruturaentrega *entrega = alocarestruturaentrega(numdeentregas);
            AdicionarDadosNoArquivo((void **)&entrega, &numdeentregas, ENTREGA);
            salvarDadosNoArquivo(entrega, numdeentregas, "a", ENTREGA);
            printf("\nOs dados dos entregas cadastrados foram salvos com sucesso.\n");
            liberarMemorias(entrega, numdeentregas, ENTREGA);

            break;

        case 2:
            VisualizarDadosNoArquivo(ENTREGA);
            break;
        case 3:
            numdeentregas = ContarDadosNoArquivo("arq_entregas.txt", "===== Registro Entrega");
            if (numdeentregas > 0)
            {
                estruturaentrega *entrega = alocarestruturaentrega(numdeentregas);
                lerDadosDoArquivo(entrega, numdeentregas, ENTREGA);
                alterarDados(entrega, numdeentregas, ENTREGA);
                salvarDadosNoArquivo(entrega, numdeentregas, "w", ENTREGA);
                liberarMemorias(entrega, numdeentregas, ENTREGA);
            }
            break;

        case 4:
            numdeentregas = ContarDadosNoArquivo("arq_entregas.txt", "===== Registro Entrega");
            if (numdeentregas > 0)
            {
                estruturaentrega *entrega = alocarestruturaentrega(numdeentregas);
                lerDadosDoArquivo(entrega, numdeentregas, ENTREGA);
                DeletarDadosNoArquivo((void **)&entrega, &numdeentregas, ENTREGA);
                liberarMemorias(entrega, numdeentregas, ENTREGA);
            }
            break;

        case 5:
            printf("\nQuantas entregas voce deseja realizar: ");
            scanf("%d", &numdeentregas);
            getchar();
            entrega = alocarestruturaentrega(numdeentregas);
            AdicionarDadosNoArquivo((void **)&entrega, &numdeentregas, ENTREGAREALIZADA);
            printf("\nOs dados dos entregas realizadas foram salvos com sucesso.\n");
            liberarMemorias(entrega, numdeentregas, ENTREGAREALIZADA);
            break;
        case 6:
            numdeentregas = ContarDadosNoArquivo("arq_entregas_realizadas.txt", "===== Registro Entrega Realizada");
            if (numdeentregas > 0)
                {
                    estruturaentrega *entrega = alocarestruturaentrega(numdeentregas);
                    lerDadosDoArquivo(entrega, numdeentregas, ENTREGAREALIZADA);
                    DeletarDadosNoArquivo((void **)&entrega, &numdeentregas, ENTREGAREALIZADA);
                    liberarMemorias(entrega, numdeentregas, ENTREGA);
                }
            break;
        case 7:
            return;
            break;
        case 8:
            exit(0);
        }
    }
}
// funcao principal
int main()
{
    srand(time(NULL));
    while (1)
    {
        int setor = 0;
        printf("\nDigite em qual setor deseja entrar: \n\n 1: Funcionarios \n 2: Clientes \n 3: Veiculos \n 4: Entregas \n 5: Exibir Relatorios Das Entregas \n 6: Sair Do Programa \n\n");
        scanf("%d", &setor);
        switch (setor)
        {
        case 1:
            setorfuncionario();
            break;

        case 2:
            setorcliente();
            break;

        case 3:
            setorveiculo();
            break;

        case 4:
            setorentrega();
            break;

        case 5:
            VisualizarDadosNoArquivo(ENTREGAREALIZADA);
            break;

        case 6:
            exit(0);
        }
    }
}

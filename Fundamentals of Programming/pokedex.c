#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>

#define ARQUIVO_CSV "pokedex.csv"

#define MAX_POKEMONS 721
#define TAMANHO_MAX_LINHA 1024

//===============================================================================================//

// Estrutura para representar as escolhas do usuário
typedef struct {
    int numero[3];
    char nome[3][30];
    char tipo1[3][15];
    char tipo2[3][15];
    int statusTotal[3];
    int hp[3];
    int ataque[3];
    int defesa[3];
    int atqSpec[3];
    int defSpec[3];
    int velocidade[3];
    int geracao[3];
    int lendario[3];
    char cor[3][15];
    float altura[3];
    float peso[3];
    int taxadeCap[3];
    int xp[3];
} Escolha;

//===============================================================================================//

// Estrutura para representar os dados de uma linha do CSV
typedef struct {
    int numero;
    char nome[30];
    char tipo1[15];
    char tipo2[15];
    int statusTotal;
    int hp;
    int ataque;
    int defesa;
    int atqSpec;
    int defSpec;
    int velocidade;
    int geracao;
    int lendario;
    char cor[15];
    float altura;
    float peso;
    int taxadeCap;
    int xp;
    int evolucao;
    int preEvolucao;
} RegistroCSV;

//===============================================================================================//

// Estrutura para representar a mochila do usuário
typedef struct {
    int posicaoMochila[6];
    int numero[6];
    char nome[6][30];
    char tipoUm[6][15];
    char tipoDois[6][15];
    int statusTotal[6];
    int ataque[6];
    int defesa[6];
    int atqSpec[6];
    int defSpec[6];
    int velocidade[6];
    int geracao[6];
    int lendario[6];
    char cor[6][15];
    float altura[6];
    float peso[6];
    int taxadeCap[6];
    int evolucao[6];
    int preEvolucao[6];
    int xp[6];
    int pokeball;
    int greatball;
    int ultraball;
    int masterball;
} Mochila;

//===============================================================================================//


typedef struct {
    int numero;
    char nome[30];
    char tipoUm[15];
    char tipoDois[15];
    int statusTotal;
    int hp;
    int ataque;
    int defesa;
    int atqSpec;
    int defSpec;
    int velocidade;
    int geracao;
    int lendario;
    char cor[15];
    float altura;
    float peso;
    int taxadeCap;
    int evolucao;
    int preEvolucao;
} Pokemon;

// Estrutura para representar a coleção completa de Pokémon do usuário
typedef struct {
    int posicaoColecao[100];
    int numero[100];
    char nome[100][30];
    char tipoUm[100][15];
    char tipoDois[100][15];
    int statusTotal[100];
    int ataque[100];
    int defesa[100];
    int atqSpec[100];
    int defSpec[100];
    int velocidade[100];
    int geracao[100];
    int lendario[100];
    char cor[100][15];
    float altura[100];
    float peso[100];
    int taxadeCap[100];
    int evolucao[100];
    int preEvolucao[100];
    int xp[100];
} Colecao;

//===============================================================================================//

// Função para inicializar os dados da mochila do usuário
void inicializarMochila(Mochila *mochila) {
    // Loop para inicializar cada slot da mochila
    for (int i = 0; i < 6; ++i) {
        // Inicializa os campos individuais de cada Pokémon na mochila
        mochila->posicaoMochila[i] = 0;
        mochila->numero[i] = 0;
        strcpy(mochila->nome[i], "");
        strcpy(mochila->tipoUm[i], "");
        strcpy(mochila->tipoDois[i], "");
        mochila->statusTotal[i] = 0;
        mochila->ataque[i] = 0;
        mochila->defesa[i] = 0;
        mochila->atqSpec[i] = 0;
        mochila->defSpec[i] = 0;
        mochila->velocidade[i] = 0;
        mochila->geracao[i] = 0;
        mochila->lendario[i] = 0;
        strcpy(mochila->cor[i], "");
        mochila->altura[i] = 0.0;
        mochila->peso[i] = 0.0;
        mochila->taxadeCap[i] = 0;
        mochila->evolucao[i] = 0.0;
        mochila->preEvolucao[i] = 0.0;
        mochila->xp[i] = 0;
    }

    // Inicializa o número de cada tipo de Pokébola na mochila
    mochila->pokeball = 10;
    mochila->greatball = 10;
    mochila->ultraball = 10;
    mochila->masterball = 10;
}

//===============================================================================================//

// Função para inicializar os dados da coleção de Pokémon do usuário
void inicializarColecao(Colecao *colecao) {
    // Loop para inicializar cada slot da coleção
    for (int i = 0; i < 100; ++i) {
        // Inicializa os campos individuais de cada Pokémon na coleção
        colecao->posicaoColecao[i] = 0;
        colecao->numero[i] = 0;
        strcpy(colecao->nome[i], "");
        strcpy(colecao->tipoUm[i], "");
        strcpy(colecao->tipoDois[i], "");
        colecao->statusTotal[i] = 0;
        colecao->ataque[i] = 0;
        colecao->defesa[i] = 0;
        colecao->atqSpec[i] = 0;
        colecao->defSpec[i] = 0;
        colecao->velocidade[i] = 0;
        colecao->geracao[i] = 0;
        colecao->lendario[i] = 0;
        strcpy(colecao->cor[i], "");
        colecao->altura[i] = 0.0;
        colecao->peso[i] = 0.0;
        colecao->taxadeCap[i] = 0;
        colecao->evolucao[i] = 0;
        colecao->preEvolucao[i] = 0;
        colecao->xp[i] = 0;
    }
}

//===============================================================================================//

// Função para calcular a média da experiência (xp) dos Pokémon na mochila
RegistroCSV calcularMedia(Mochila *mochila, RegistroCSV *registro) {
    RegistroCSV resultado;

    // Inicializa o acumulador de xp e o contador de Pokémon na mochila
    resultado.xp = 0;
    int contador = 0;

    // Loop para percorrer cada slot da mochila
    for (int i = 0; i < 6; i++) {
        // Verifica se o Pokémon na posição i possui xp não nula
        if (mochila->xp[i] != 0) {
            contador++; // Incrementa o contador se xp não for zero
        }

        resultado.xp += mochila->xp[i]; // Acumula o xp do Pokémon na posição i
    }

    // Calcula a média da experiência arredondando para o inteiro mais próximo
    resultado.xp = round(resultado.xp / contador);
    
    // Atualiza o campo xp no registro passado por referência
    registro->xp = resultado.xp;

    return resultado;
}

// Função para contar o número de linhas em um arquivo CSV
int contarLinhas() {
    FILE *arquivo;
    int numLinhas = 0;
    char caractere;

    // Abrir o arquivo em modo de leitura
    arquivo = fopen(ARQUIVO_CSV, "r");

    // Verificar se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", ARQUIVO_CSV);
        return -1; // Retornar um valor negativo para indicar erro
    }

    // Contar o número de linhas no arquivo
    while ((caractere = fgetc(arquivo)) != EOF) {
        if (caractere == '\n') {
            numLinhas++;
        }
    }

    // Fechar o arquivo
    fclose(arquivo);

    return numLinhas;
}

//===============================================================================================//

// Função para ler uma linha aleatória de um arquivo CSV e exibir os detalhes do Pokémon encontrado
void lerLinhaAleatoria(RegistroCSV *registro, int numLinhas, Mochila *mochila) {
    // Abrir o arquivo CSV em modo de leitura
    FILE *arquivo = fopen("pokedex.csv", "r");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Gerar um índice aleatório para selecionar uma linha no arquivo
    srand((unsigned int)time(NULL));
    int linhaAleatoria = rand() % (numLinhas + 1);
    int linhaAtual = 0;

    // Reposicionar o indicador de posição do arquivo para o início
    rewind(arquivo);

    // Pular linhas até chegar à linha aleatória
    while (linhaAtual < linhaAleatoria) {
        char caractere = fgetc(arquivo);
        if (caractere == '\n') {
            linhaAtual++;
        }
    }

    // Ler os dados da linha aleatória para a estrutura de registro
    if (fscanf(arquivo, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
               &registro->numero, registro->nome, registro->tipo1, registro->tipo2, &registro->statusTotal, &registro->hp,
               &registro->ataque, &registro->defesa, &registro->atqSpec, &registro->defSpec, &registro->velocidade, &registro->geracao,
               &registro->lendario, registro->cor, &registro->altura, &registro->peso, &registro->taxadeCap)) {

        sleep(1); // Esperar por 1 segundo (opcional)
        calcularMedia(mochila, registro); // Calcular a média da experiência (xp) e atualizar o registro
        printf("================================================================\n");
        printf("\nPokemon encontrado!!!\n");
        sleep(2); // Esperar por 2 segundos (opcional)
        
        // Exibir detalhes do Pokémon encontrado
        printf("\nPokémon para captura:\n");
        printf("Número: %d\n", registro->numero);
        printf("Nome: %s\n", registro->nome);
        printf("Tipo 1: %s\n", registro->tipo1);
        printf("Tipo 2: %s\n", registro->tipo2);
        printf("Status Total: %d\n", registro->statusTotal);
        printf("HP: %d\n", registro->hp);
        printf("Ataque: %d\n", registro->ataque);
        printf("Defesa: %d\n", registro->defesa);
        printf("Ataque Especial: %d\n", registro->atqSpec);
        printf("Defesa Especial: %d\n", registro->defSpec);
        printf("Velocidade: %d\n", registro->velocidade);
        printf("Geração: %d\n", registro->geracao);
        printf("Lendário: %d\n", registro->lendario);
        printf("Cor: %s\n", registro->cor);
        printf("Altura: %.2f\n", registro->altura);
        printf("Peso: %.2f\n", registro->peso);
        printf("Taxa de Captura: %d\n", registro->taxadeCap);
        printf("Level: %d\n", registro->xp);
        printf("================================================================\n");
    }

    // Fechar o arquivo
    fclose(arquivo);
}

//===============================================================================================//

// Função para calcular a probabilidade de captura
double calcularProbabilidadeCaptura(int taxaDeCaptura, double multiplicador) {
    // Se o multiplicador for zero, a probabilidade é sempre 100%
    if (multiplicador == 0.0) {
        return 1.0;
    }

    // Fórmula para calcular a probabilidade usando a fórmula de captura Pokémon
    double alpha = log(0.2) / -255;
    double probabilidade = 1 - exp(-alpha * taxaDeCaptura * multiplicador);
    return probabilidade;
}

//===============================================================================================//

// Função para realizar a captura com 3 chances
void capturarPokemon(RegistroCSV *registro, Mochila *mochila, Colecao *colecao) {
    int tentativas = 3;

    // Loop para realizar até 3 tentativas de captura
    while (tentativas > 0) {
        sleep(1);
        printf("\nVocê tem %d pokeballs, %d greatballs, %d ultraballs, %d masterballs\n", mochila->pokeball, mochila->greatball, mochila->ultraball, mochila->masterball);
        char tipoBola;
        printf("\nVocê tem %d tentativas para capturar o Pokémon!\n", tentativas);
        printf("\nEscolha uma pokebola: pokeball (P), greatball (G), ultraball (U), masterball (M): ");
        scanf(" %c", &tipoBola);

        // Variável para armazenar a quantidade de bolas disponíveis e o multiplicador de captura
        int *quantidadeBola;
        double multiplicador = 1.0;

        // Determina a bola escolhida e seu multiplicador associado
        switch (tipoBola) {
            case 'P':
            case 'p':
                quantidadeBola = &mochila->pokeball;
                break;
            case 'G':
            case 'g':
                quantidadeBola = &mochila->greatball;
                multiplicador = 1.5;
                break;
            case 'U':
            case 'u':
                quantidadeBola = &mochila->ultraball;
                multiplicador = 2.0;
                break;
            case 'M':
            case 'm':
                quantidadeBola = &mochila->masterball;
                multiplicador = 0.0; // Masterball sempre captura com sucesso
                break;
            default:
                printf("Tipo de bola inválido.\n");
                continue; // Reinicia o loop para uma nova tentativa
        }

        // Verifica se há bolas disponíveis do tipo escolhido
        if (*quantidadeBola <= 0) {
            printf("Você não tem mais %s.\n", tipoBola == 'P' || tipoBola == 'p' ? "pokeballs" : (tipoBola == 'G' || tipoBola == 'g' ? "greatballs" : (tipoBola == 'U' || tipoBola == 'u' ? "ultraballs" : "masterballs")));
            tentativas--;
            printf("\nVocê tem %d tentativas para capturar o Pokémon!\n", tentativas);
            continue; // Reinicia o loop para uma nova tentativa
        }

        // Utiliza uma bola da mochila
        (*quantidadeBola)--;

        sleep(1);
        printf("\nCapturando Pokémon (Tentativa %d)...\n", 4 - tentativas);
        double probabilidade = calcularProbabilidadeCaptura(registro->taxadeCap, multiplicador);
        printf("\nA probabilidade de sucesso na captura é: %.2f%%\n", probabilidade * 100);

        // Simulação da captura
        int resultadoCaptura = rand() % 101;

        // Verifica se a captura foi bem-sucedida
        if (resultadoCaptura <= probabilidade * 100) {
            printf("Você capturou %s!\n", registro->nome);

            int i;

            // Adiciona o Pokémon à mochila
            for (i = 1; i < 6; ++i) {
                if (mochila->posicaoMochila[i] == 0) {
                    mochila->posicaoMochila[i] = i + 1;
                    mochila->numero[i] = registro->numero;
                    strcpy(mochila->nome[i], registro->nome);
                    strcpy(mochila->tipoUm[i], registro->tipo1);
                    strcpy(mochila->tipoDois[i], registro->tipo2);
                    mochila->statusTotal[i] = registro->statusTotal;
                    mochila->ataque[i] = registro->ataque;
                    mochila->defesa[i] = registro->defesa;
                    mochila->atqSpec[i] = registro->atqSpec;
                    mochila->defSpec[i] = registro->defSpec;
                    mochila->velocidade[i] = registro->velocidade;
                    mochila->geracao[i] = registro->geracao;
                    mochila->lendario[i] = registro->lendario;
                    strcpy(mochila->cor[i], registro->cor);
                    mochila->altura[i] = registro->altura;
                    mochila->peso[i] = registro->peso;
                    mochila->taxadeCap[i] = registro->taxadeCap;
                    mochila->xp[i] = registro->xp;
                    break;
                }
            }

            // Adiciona o Pokémon à coleção se a mochila estiver cheia
            if (i == 6) {
                for (i = 0; i < 100; ++i) {
                    if (colecao->posicaoColecao[i] == 0) {
                        colecao->posicaoColecao[i] = i + 1;
                        colecao->numero[i] = registro->numero;
                        strcpy(colecao->nome[i], registro->nome);
                        strcpy(colecao->tipoUm[i], registro->tipo1);
                        strcpy(colecao->tipoDois[i], registro->tipo2);
                        colecao->statusTotal[i] = registro->statusTotal;
                        colecao->ataque[i] = registro->ataque;
                        colecao->defesa[i] = registro->defesa;
                        colecao->atqSpec[i] = registro->atqSpec;
                        colecao->defSpec[i] = registro->defSpec;
                        colecao->velocidade[i] = registro->velocidade;
                        colecao->geracao[i] = registro->geracao;
                        colecao->lendario[i] = registro->lendario;
                        strcpy(colecao->cor[i], registro->cor);
                        colecao->altura[i] = registro->altura;
                        colecao->peso[i] = registro->peso;
                        colecao->taxadeCap[i] = registro->taxadeCap;
                        colecao->xp[i] = registro->xp;
                        break;
                    }
                }
            }

            return; // A captura foi bem-sucedida, a função encerra
        } else {
            printf("A captura do Pokémon %s falhou.\n", registro->nome);
            tentativas--;
            sleep(1);
            printf("\nVocê ainda tem %d tentativas para capturar o Pokémon!\n", tentativas);
        }
    }

    printf("Suas tentativas acabaram. O Pokémon %s escapou!\n", registro->nome);
}

//===============================================================================================//

// Função para mostrar os Pokémon na mochila
void mostrarMochila(Mochila *mochila) {
    printf("\nPokémons na Mochila:\n");
    sleep(1);

    // Itera sobre os slots da mochila
    for (int i = 0; i < 6; ++i) {
        // Verifica se o slot contém um Pokémon
        if (mochila->numero[i] != 0) {
            printf("\n================================================================\n");
            printf("Pokemon posição %d\n", mochila->posicaoMochila[i]);
            printf("Nome: %s\n", mochila->nome[i]);
            printf("Número na Pokedex: %d\n", mochila->numero[i]);
            printf("Tipo Um: %s\n", mochila->tipoUm[i]);
            printf("Tipo Dois: %s\n", mochila->tipoDois[i]);
            printf("Status Total: %d\n", mochila->statusTotal[i]);
            printf("Ataque: %d\n", mochila->ataque[i]);
            printf("Defesa: %d\n", mochila->defesa[i]);
            printf("AtqSpec: %d\n", mochila->atqSpec[i]);
            printf("DefSpec: %d\n", mochila->defSpec[i]);
            printf("Velocidade: %d\n", mochila->velocidade[i]);
            printf("Geração: %d\n", mochila->geracao[i]);
            printf("Lendario: %d\n", mochila->lendario[i]);
            printf("Cor: %s\n", mochila->cor[i]);
            printf("Altura: %.2f\n", mochila->altura[i]);
            printf("Peso: %.2f\n", mochila->peso[i]);
            printf("Taxa de Captura: %d\n", mochila->taxadeCap[i]);
            printf("Level: %d\n", mochila->xp[i]);
        }
    }

    sleep(1);
    // Mostra a quantidade de diferentes tipos de Pokébolas disponíveis
    printf("Quantidade de Pokébolas: %d\n", mochila->pokeball);
    printf("Quantidade de Greatballs: %d\n", mochila->greatball);
    printf("Quantidade de Ultraballs: %d\n", mochila->ultraball);
    printf("Quantidade de Masterballs: %d\n", mochila->masterball);
}

//===============================================================================================//

// Função para mostrar os Pokémon na coleção
void mostrarColecao(Colecao *colecao) {
    printf("\nPokémons na Coleção:\n");
    sleep(1);

    // Itera sobre os slots da coleção
    for (int i = 0; i < 100; ++i) {
        // Verifica se o slot contém um Pokémon
        if (colecao->posicaoColecao[i] != 0) {
            printf("\n================================================================\n");
            printf("Pokemon posição %d\n", colecao->posicaoColecao[i]);
            printf("Nome: %s\n", colecao->nome[i]);
            printf("Número na Pokedex: %d\n", colecao->numero[i]);
            printf("Tipo Um: %s\n", colecao->tipoUm[i]);
            printf("Tipo Dois: %s\n", colecao->tipoDois[i]);
            printf("Status Total: %d\n", colecao->statusTotal[i]);
            printf("Ataque: %d\n", colecao->ataque[i]);
            printf("Defesa: %d\n", colecao->defesa[i]);
            printf("AtqSpec: %d\n", colecao->atqSpec[i]);
            printf("DefSpec: %d\n", colecao->defSpec[i]);
            printf("Velocidade: %d\n", colecao->velocidade[i]);
            printf("Geração: %d\n", colecao->geracao[i]);
            printf("Lendario: %d\n", colecao->lendario[i]);
            printf("Cor: %s\n", colecao->cor[i]);
            printf("Altura: %.2f\n", colecao->altura[i]);
            printf("Peso: %.2f\n", colecao->peso[i]);
            printf("Taxa de Captura: %d\n", colecao->taxadeCap[i]);
            printf("Level: %d\n", colecao->xp[i]);
        }
    }
}

//===============================================================================================//

// Função para verificar e mostrar a mochila com opção de visualização
void verificarMostrarMochila(Mochila *mochila) {
    char resposta;
    int respostaValida = 0;

    do {
        printf("\n================================================================\n");
        printf("\nDeseja ver a mochila? (S para Sim, N para Não): ");
        scanf(" %c", &resposta);

        if (resposta == 'S' || resposta == 's') {
            mostrarMochila(mochila);
            respostaValida = 1; // A resposta é válida, podemos sair do loop
        } else if (resposta == 'N' || resposta == 'n') {
            printf("Você escolheu não ver a mochila.\n");
            respostaValida = 1; // A resposta é válida, podemos sair do loop
        } else {
            printf("Resposta inválida. Por favor, insira S ou N.\n");
        }
    } while (!respostaValida);
}

//===============================================================================================//

// Função para verificar e mostrar a coleção com opção de visualização
void verificarMostrarColecao(Colecao *colecao) {
    char resposta;
    int respostaValida = 0;

    do {
        printf("================================================================\n");
        printf("Deseja ver a coleção? (S para Sim, N para Não): ");
        scanf(" %c", &resposta);

        if (resposta == 'S' || resposta == 's') {
            mostrarColecao(colecao);
            respostaValida = 1; // A resposta é válida, podemos sair do loop
        } else if (resposta == 'N' || resposta == 'n') {
            printf("Você escolheu não ver a coleção.\n");
            respostaValida = 1; // A resposta é válida, podemos sair do loop
        } else {
            printf("Resposta inválida. Por favor, insira S ou N.\n");
        }
    } while (!respostaValida);
}

//===============================================================================================//

// Função principal para jogar Pokémon, permitindo procurar e capturar Pokémon aleatórios
void jogarPokemon(RegistroCSV *registro, Mochila *mochila, Colecao *colecao, int numLinhas) {
    char escolha, jogarNovamente;

    do {
        do {
            sleep(2);
            printf("\n\nProcurar Pokemon? (S/N): ");
            scanf(" %c", &escolha);
            escolha = toupper(escolha);

            if (escolha != 'S' && escolha != 'N') {
                printf("Opção inválida. Por favor, escolha S ou N.\n");
            }

        } while (escolha != 'S' && escolha != 'N');

        if (escolha == 'S') {
            // Procura e captura um Pokémon aleatório
            lerLinhaAleatoria(registro, numLinhas, mochila);
            capturarPokemon(registro, mochila, colecao);
            
            // Mostra a mochila e a coleção após a captura
            verificarMostrarMochila(mochila);
            verificarMostrarColecao(colecao);

            // Pergunta se deseja jogar novamente
            printf("\nDeseja jogar novamente? (S/N): ");
            scanf(" %c", &jogarNovamente);
            jogarNovamente = toupper(jogarNovamente);

        } else {
            printf("\nVocê optou por não jogar Pokémon. Até a próxima!\n");
            jogarNovamente = 'N';  // Garante que o loop seja encerrado se o usuário optar por não jogar
        }

    } while (jogarNovamente == 'S');
}

//===============================================================================================//

void escolhaPokemon(Escolha *escolha, Mochila *mochila) {
    // Abre o arquivo CSV contendo os dados dos Pokémons
    FILE *arquivo = fopen("pokedex.csv", "r");
    if (arquivo == NULL) { // Verifica se houve falha na abertura do arquivo
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Define as linhas dos três primeiros Pokémons na pokedex
    int linhaBulbasaur = 1;
    int linhaCharmander = 4;
    int linhaSquirtle = 7;
    int linhaAtual = 0;

    // Reseta a posição do arquivo para o início
    rewind(arquivo);

    // Pula linhas até a linha do Bulbasaur
    while (linhaAtual < linhaBulbasaur) {
        char caractere = fgetc(arquivo);
        if (caractere == '\n') {
            linhaAtual++;
        }
    }

    // Lê os dados do Bulbasaur do arquivo e preenche a estrutura Escolha
    if (fscanf(arquivo, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
               &escolha->numero[0], escolha->nome[0], escolha->tipo1[0], escolha->tipo2[0],
               &escolha->statusTotal[0], &escolha->hp[0], &escolha->ataque[0], &escolha->defesa[0],
               &escolha->atqSpec[0], &escolha->defSpec[0], &escolha->velocidade[0], &escolha->geracao[0],
               &escolha->lendario[0], escolha->cor[0], &escolha->altura[0], &escolha->peso[0],
               &escolha->taxadeCap[0])) {

        // Imprime os dados do Bulbasaur na tela
        printf("\n================================================================\n");
        printf("\nPokémon para escolher:\n");
        escolha->xp[0] = 5;
        printf("Número: %d\n", escolha->numero[0]);
        printf("Nome: %s\n", escolha->nome[0]);
        printf("Tipo 1: %s\n", escolha->tipo1[0]);
        printf("Tipo 2: %s\n", escolha->tipo2[0]);
        printf("Status Total: %d\n", escolha->statusTotal[0]);
        printf("HP: %d\n", escolha->hp[0]);
        printf("Ataque: %d\n", escolha->ataque[0]);
        printf("Defesa: %d\n", escolha->defesa[0]);
        printf("Ataque Especial: %d\n", escolha->atqSpec[0]);
        printf("Defesa Especial: %d\n", escolha->defSpec[0]);
        printf("Velocidade: %d\n", escolha->velocidade[0]);
        printf("Geração: %d\n", escolha->geracao[0]);
        printf("Lendário: %d\n", escolha->lendario[0]);
        printf("Cor: %s\n", escolha->cor[0]);
        printf("Altura: %.2f\n", escolha->altura[0]);
        printf("Peso: %.2f\n", escolha->peso[0]);
        printf("Taxa de Captura: %d\n", escolha->taxadeCap[0]);
        printf("Level: %d\n", escolha->xp[0]);
        printf("\n================================================================\n");
    }

    // Reinicializa a variável linhaAtual
    linhaAtual = 0;

    // Reseta a posição do arquivo para o início
    rewind(arquivo);

    // Pula linhas até a linha do Charmander
    while (linhaAtual < linhaCharmander) {
        char caractere = fgetc(arquivo);
        if (caractere == '\n') {
            linhaAtual++;
        }
    }

    // Lê os dados do Charmander do arquivo e preenche a estrutura Escolha
    if (fscanf(arquivo, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
               &escolha->numero[1], escolha->nome[1], escolha->tipo1[1], escolha->tipo2[1],
               &escolha->statusTotal[1], &escolha->hp[1], &escolha->ataque[1], &escolha->defesa[1],
               &escolha->atqSpec[1], &escolha->defSpec[1], &escolha->velocidade[1], &escolha->geracao[1],
               &escolha->lendario[1], escolha->cor[1], &escolha->altura[1], &escolha->peso[1],
               &escolha->taxadeCap[1])) {

        // Adiciona um delay de 1 segundo
        sleep(1);

        // Preenche o campo de experiência e imprime os dados do Charmander na tela
        escolha->xp[1] = 5;
        printf("Número: %d\n", escolha->numero[1]);
        printf("Nome: %s\n", escolha->nome[1]);
        printf("Tipo 1: %s\n", escolha->tipo1[1]);
        printf("Tipo 2: %s\n", escolha->tipo2[1]);
        printf("Status Total: %d\n", escolha->statusTotal[1]);
        printf("HP: %d\n", escolha->hp[1]);
        printf("Ataque: %d\n", escolha->ataque[1]);
        printf("Defesa: %d\n", escolha->defesa[1]);
        printf("Ataque Especial: %d\n", escolha->atqSpec[1]);
        printf("Defesa Especial: %d\n", escolha->defSpec[1]);
        printf("Velocidade: %d\n", escolha->velocidade[1]);
        printf("Geração: %d\n", escolha->geracao[1]);
        printf("Lendário: %d\n", escolha->lendario[1]);
        printf("Cor: %s\n", escolha->cor[1]);
        printf("Altura: %.2f\n", escolha->altura[1]);
        printf("Peso: %.2f\n", escolha->peso[1]);
        printf("Taxa de Captura: %d\n", escolha->taxadeCap[1]);
        printf("Level: %d\n", escolha->xp[1]);
        printf("\n================================================================\n");
    }

    // Reinicializa a variável linhaAtual
    linhaAtual = 0;

    // Reseta a posição do arquivo para o início
    rewind(arquivo);

    // Pula linhas até a linha do Squirtle
    while (linhaAtual < linhaSquirtle) {
        char caractere = fgetc(arquivo);
        if (caractere == '\n') {
            linhaAtual++;
        }
    }

    // Lê os dados do Squirtle do arquivo e preenche a estrutura Escolha
    if (fscanf(arquivo, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
               &escolha->numero[2], escolha->nome[2], escolha->tipo1[2], escolha->tipo2[2],
               &escolha->statusTotal[2], &escolha->hp[2], &escolha->ataque[2], &escolha->defesa[2],
               &escolha->atqSpec[2], &escolha->defSpec[2], &escolha->velocidade[2], &escolha->geracao[2],
               &escolha->lendario[2], escolha->cor[2], &escolha->altura[2], &escolha->peso[2],
               &escolha->taxadeCap[2])) {

        // Adiciona um delay de 1 segundo
        sleep(1);

        // Preenche o campo de experiência e imprime os dados do Squirtle na tela
        escolha->xp[2] = 5;
        printf("Número: %d\n", escolha->numero[2]);
        printf("Nome: %s\n", escolha->nome[2]);
        printf("Tipo 1: %s\n", escolha->tipo1[2]);
        printf("Tipo 2: %s\n", escolha->tipo2[2]);
        printf("Status Total: %d\n", escolha->statusTotal[2]);
        printf("HP: %d\n", escolha->hp[2]);
        printf("Ataque: %d\n", escolha->ataque[2]);
        printf("Defesa: %d\n", escolha->defesa[2]);
        printf("Ataque Especial: %d\n", escolha->atqSpec[2]);
        printf("Defesa Especial: %d\n", escolha->defSpec[2]);
        printf("Velocidade: %d\n", escolha->velocidade[2]);
        printf("Geração: %d\n", escolha->geracao[2]);
        printf("Lendário: %d\n", escolha->lendario[2]);
        printf("Cor: %s\n", escolha->cor[2]);
        printf("Altura: %.2f\n", escolha->altura[2]);
        printf("Peso: %.2f\n", escolha->peso[2]);
        printf("Taxa de Captura: %d\n", escolha->taxadeCap[2]);
        printf("Level: %d\n", escolha->xp[2]);
        printf("\n================================================================\n");
    }

    // Reseta a posição do arquivo para o início
    rewind(arquivo);

    // Fecha o arquivo após o uso
    fclose(arquivo);

    // Inicializa a variável de escolha com 0
    int i = 0;

    // Adiciona um delay de 2 segundos para dar um efeito visual
    sleep(2);

    // Imprime mensagem para escolher um Pokémon inicial
    printf("\nEscolha seu Pokémon inicial!\n");

    do {
        // Solicita ao usuário que digite a escolha entre 1 e 3
        printf("\nDigite 1 - Bulbasaur; 2 - Charmander; 3 - Squirtle: ");
        scanf("%d", &i);

        // Verifica se a escolha é inválida e exibe mensagem de erro
        if (i < 1 || i > 3) {
            printf("Opção inválida. Tente novamente.\n");
        }

    } while (i < 1 || i > 3);

    // Exibe a escolha do usuário
    printf("Você escolheu o %s!\n", escolha->nome[i - 1]);

    // Preenche os dados do Pokémon escolhido na mochila
    mochila->posicaoMochila[0] = 1;
    mochila->numero[0] = escolha->numero[i - 1];
    strcpy(mochila->nome[0], escolha->nome[i - 1]);
    strcpy(mochila->tipoUm[0], escolha->tipo1[i - 1]);
    strcpy(mochila->tipoDois[0], escolha->tipo2[i - 1]);
    mochila->statusTotal[0] = escolha->statusTotal[i - 1];
    mochila->ataque[0] = escolha->ataque[i - 1];
    mochila->defesa[0] = escolha->defesa[i - 1];
    mochila->atqSpec[0] = escolha->atqSpec[i - 1];
    mochila->defSpec[0] = escolha->defSpec[i - 1];
    mochila->velocidade[0] = escolha->velocidade[i - 1];
    mochila->geracao[0] = escolha->geracao[i - 1];
    mochila->lendario[0] = escolha->lendario[i - 1];
    strcpy(mochila->cor[0], escolha->cor[i - 1]);
    mochila->altura[0] = escolha->altura[i - 1];
    mochila->peso[0] = escolha->peso[i - 1];
    mochila->taxadeCap[0] = escolha->taxadeCap[i - 1];
    mochila->xp[0] = escolha->xp[i - 1];

    // Adiciona um delay de 2 segundos para dar um efeito visual
    sleep(2);

    // Chama a função para mostrar a mochila
    mostrarMochila(mochila);
}


////////////////////////////////////////// VINCULA A STRUCT COM A ARQUIVO //////////////////////////////////////////////////////////////


void Vincular_Pokedex_Struct(Pokemon pokedex[], char *arquivoPokedex) {
    FILE *file = fopen(arquivoPokedex, "r");

    if (file == NULL) {
        printf("\nNão foi possível abrir o arquivo.\n");
        exit(1);
    }

    char linha[TAMANHO_MAX_LINHA];
    int linhaAtual = 0;

    while (fgets(linha, sizeof(linha), file)) {
        if (linhaAtual == 0) {
            // Ignora a primeira linha de cabeçalho.
            linhaAtual++;
            continue;
        }

        char *token;
        int col = 0;
        token = strtok(linha, ",");

        while (token != NULL) {
            // Remover espaços em branco no início e no final da string
            char *trimmed = token;
            while (*trimmed == ' ' || *trimmed == '\t') {
                trimmed++;
            }

            size_t len = strlen(trimmed);
            while (len > 0 && (trimmed[len - 1] == ' ' || trimmed[len - 1] == '\t' || trimmed[len - 1] == '\n')) {
                trimmed[--len] = '\0';
            }

            switch (col) {
                case 0:
                    pokedex[linhaAtual - 1].numero = atoi(trimmed);
                    break;
                case 1:
                    strncpy(pokedex[linhaAtual - 1].nome, trimmed, sizeof(pokedex[linhaAtual - 1].nome));
                    break;
                case 2:
                    strncpy(pokedex[linhaAtual - 1].tipoUm, trimmed, sizeof(pokedex[linhaAtual - 1].tipoUm));
                    break;
                case 3:
                    strncpy(pokedex[linhaAtual - 1].tipoDois, trimmed, sizeof(pokedex[linhaAtual - 1].tipoDois));
                    break;
                case 4:
                    pokedex[linhaAtual - 1].statusTotal = atoi(trimmed);
                    break;
                case 5:
                    pokedex[linhaAtual - 1].hp = atoi(trimmed);
                    break;
                case 6:
                    pokedex[linhaAtual - 1].ataque = atoi(trimmed);
                    break;
                case 7:
                    pokedex[linhaAtual - 1].defesa = atoi(trimmed);
                    break;
                case 8:
                    pokedex[linhaAtual - 1].atqSpec = atoi(trimmed);
                    break;
                case 9:
                    pokedex[linhaAtual - 1].defSpec = atoi(trimmed);
                    break;
                case 10:
                    pokedex[linhaAtual - 1].velocidade = atoi(trimmed);
                    break;
                case 11:
                    pokedex[linhaAtual - 1].geracao = atoi(trimmed);
                    break;
                case 12:
                    pokedex[linhaAtual - 1].lendario = atoi(trimmed);
                    break;
                case 13:
                    strncpy(pokedex[linhaAtual - 1].cor, trimmed, sizeof(pokedex[linhaAtual - 1].cor));
                    break;
                case 14:
                    pokedex[linhaAtual - 1].altura = atof(trimmed);
                    break;
                case 15:
                    pokedex[linhaAtual - 1].peso = atof(trimmed);
                    break;
                case 16:
                    pokedex[linhaAtual - 1].taxadeCap = atoi(trimmed);
                    break;
                case 17:
                    pokedex[linhaAtual - 1].evolucao = atoi(trimmed);
                    break;
                case 18:
                    pokedex[linhaAtual - 1].preEvolucao = atoi(trimmed);
                    break;
            }

            token = strtok(NULL, ",");
            col++;
        }

        linhaAtual++;
    }

    fclose(file);
}

///////////////////////////////////////////////// FUNCAO PARA CALCULAR A EFETIVIDADE DO ATCK ////////////////////////////////////////

int CalculaEficaciaAtack(Pokemon pokedex[], int NumeroPokemon1, int NumeroPokemon2){

    int Imunidade = 0;
    int Nao_Eficaz_Especial = 100;
    int Nao_Eficaz_Normal = 150;
    int Eficaz = 200;
    int Super_Eficaz_Normal = 300;
    int Hiper_Eficaz_Especial = 500;
    int Vantagens=0;
    int Desvantagens=0;

    ////////////////////////////////////////////////      VANTAGENS    ///////////////////////////////////////////////////////////

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Planta") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Planta") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Water") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Water") == 0)) {

    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Fire") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Fire") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Aço") == 0)) {
 
    Vantagens++;
 
    }   

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Water") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Water") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Fogo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Fogo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0)) {
 
    Vantagens++;
 
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Electric") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Electric") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Water") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Water") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0)) {
   
    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Voador") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Voador") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Inseto") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Inseto") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0)) {
   
    Vantagens++;
   
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Gelo") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0)) {
   
    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Pedra") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Inseto") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fogo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Inseto") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fogo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0)) {
   
    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Terra") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Venenoso") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Venenoso") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Aço") == 0)) {

    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Aço") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Aço") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0)) {

    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Sombrio") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Psychic") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Psychic") == 0)) {
   
    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Psychic") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Psychic") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Venenoso") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Venenoso") == 0)) {
 
    Vantagens++;
 
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Venenoso") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Venenoso") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0)) {
    
    Vantagens++;
   
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Bug") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Psychic") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Psychic") == 0)) {
    
    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Fada") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Fada") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Dragão") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Dragão") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0)) {

    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Ghost") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Psychic") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Psychic") == 0)) {

    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Dragon") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Dragon") == 0)) {
    
    Vantagens++;
  
    }

    ///////////////////////////////////////// DESVANTAGENS //////////////////////////////////////////////////////////////

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Normal") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Normal") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0)) {

    Desvantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Planta") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Planta") == 0) &&
        (strcmp(pokedex[NumeroPokemon2].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fire") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 ||
        strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Venenoso") == 0 ||
        strcmp(pokedex[NumeroPokemon2].tipoDois, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fire") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0 ||
        strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Venenoso") == 0)) {

        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Fire") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Fire") == 0) &&
        (strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Water") == 0 ||
        strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Water") == 0)) {
        
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Water") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Water") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0)) {
   
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Eletric") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0)) {

        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Voador") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Voador") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0)) {
       
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Gelo") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Aço") == 0)) {
    
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Pedra") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Water") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Aço") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Water") == 0)) {
   
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Terra") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Water") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Water") == 0)) {
        
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Aço") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Aço") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0)) {

        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Lutador") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Psychic") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Psychic") == 0)) {
        
        Desvantagens++;
    
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Sombrio") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fada") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0)) {

    Desvantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Psychic") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Psychic") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Sombrio") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Sombrio") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Ghost") == 0)) {

    Desvantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Venenoso") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Venenoso") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Psychic") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Psychic") == 0)) {
    
    Desvantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Bug") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Fire") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Fire") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0)) {
    
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Fada") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Fada") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Venenoso") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Aço") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Venenoso") == 0)) {
        
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Ghost") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Sombrio") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Sombrio") == 0)) {
        
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Dragon") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fada") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0)) {
        
        Desvantagens++;

    }

                ///////////////////////////////// IMUNIDADE ////////////////////////////////////

        if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Normal") == 0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost")==0 ){

            return Imunidade;

        }else{
            if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Lutador")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost")==0){

                return Imunidade;

            }else{
                if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Venenoso")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço")==0){

                    return Imunidade;

                }else{
                    if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Terra")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador")==0){

                        return Imunidade;

                    }else{
                        if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Ghost")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Normal")==0){

                            return Imunidade;

                        }else{
                            if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Eletric")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra")==0){

                                return Imunidade;

                            }else{
                                if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Psychic")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Sombrio")==0){

                                    return Imunidade;

                                }else{
                                    if(strcmp(pokedex[NumeroPokemon1].tipoUm,"Dragon")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada")==0 ){

                                        return Imunidade;

                                    }else{
                                        if(Vantagens == Desvantagens){

                                            return Eficaz;

                                        }else{
                                            if(Vantagens-Desvantagens>=1){

                                                return Super_Eficaz_Normal;

                                            }else{
                                                if(Vantagens-Desvantagens>=2){

                                                    return Hiper_Eficaz_Especial;

                                                }else{
                                                    if(Desvantagens-Vantagens>=1){

                                                        return Nao_Eficaz_Normal;

                                                    }else{
                                                        if(Desvantagens-Vantagens>=2){

                                                            return Nao_Eficaz_Especial;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }



    return 0;

}



/////////////////////////////////////////////////// FUNCAO PARA A BATALHA ////////////////////////////////////////////////////////////////

void BatalhaPokemon(Pokemon pokedex[], int NumeroPokemon1, int NumeroPokemon2, int NivelPokemon1, int NivelPokemon2) {

    int Pokemon_Velocidade_Maior;
    int Pokemon_Velocidade_Menor;
    int HP_Pokemon_Velocidade_Maior;
    int HP_Pokemon_Velocidade_Menor;
    int Nivel_Pokemon_Velocidade_Maior;
    int Nivel_Pokemon_Velocidade_Menor;

    int Taxa_Eficacia_Atck;


    printf("\nBATALHA!\n");
    printf("%s VS %s\n", pokedex[NumeroPokemon1].nome, pokedex[NumeroPokemon2].nome);

    if (pokedex[NumeroPokemon1].velocidade > pokedex[NumeroPokemon2].velocidade) {

        printf("%s COMEÇA ATACANDO!\n", pokedex[NumeroPokemon1].nome);

        Pokemon_Velocidade_Maior = NumeroPokemon1;
        Pokemon_Velocidade_Menor = NumeroPokemon2;

        HP_Pokemon_Velocidade_Maior = pokedex[NumeroPokemon1].hp;
        HP_Pokemon_Velocidade_Menor = pokedex[NumeroPokemon2].hp;

        Nivel_Pokemon_Velocidade_Maior = NivelPokemon1;
        Nivel_Pokemon_Velocidade_Menor = NivelPokemon2;

    } else {
        printf("%s COMEÇA ATACANDO!\n", pokedex[NumeroPokemon2].nome);

        Pokemon_Velocidade_Maior = NumeroPokemon2;
        Pokemon_Velocidade_Menor = NumeroPokemon1;

        HP_Pokemon_Velocidade_Maior = pokedex[NumeroPokemon2].hp;
        HP_Pokemon_Velocidade_Menor = pokedex[NumeroPokemon1].hp;

        Nivel_Pokemon_Velocidade_Maior = NivelPokemon2;
        Nivel_Pokemon_Velocidade_Menor = NivelPokemon1;

    }

    while (HP_Pokemon_Velocidade_Maior > 0 && HP_Pokemon_Velocidade_Menor > 0) {

        int ataque, defesa;
        int escolhaAtaque;
        int dano;

        printf("\n%s ATACA\n",pokedex[Pokemon_Velocidade_Maior].nome);

        do {
            printf("Escolha o tipo de ataque (1 para normal, 2 para especial): ");
            scanf("%d", &escolhaAtaque);

            if (escolhaAtaque == 1) {
                ataque = pokedex[Pokemon_Velocidade_Maior].ataque;
                defesa = pokedex[Pokemon_Velocidade_Menor].defesa;
            } else if (escolhaAtaque == 2) {
                ataque = pokedex[Pokemon_Velocidade_Maior].atqSpec;
                defesa = pokedex[Pokemon_Velocidade_Menor].defSpec;
            } else {
                printf("Opção Inválida!\n");
            }
        } while (escolhaAtaque < 1 || escolhaAtaque > 2);

        /////////////////////////// CALCULO DO DANO POKEMON COM VELOCIDADE MAIOR //////////////////////////////////////


        Taxa_Eficacia_Atck = CalculaEficaciaAtack(pokedex,Pokemon_Velocidade_Maior,Pokemon_Velocidade_Menor);

        dano = (((2 * Nivel_Pokemon_Velocidade_Maior + 10) / 250.0) * ((float)ataque / defesa)) * Taxa_Eficacia_Atck;

        if(ataque==pokedex[Pokemon_Velocidade_Maior].atqSpec){

            dano += 5;
        }

        HP_Pokemon_Velocidade_Menor -= dano;


        ///////////////////////////////////////EXIBE A EFICACIA DO ATCK //////////////////////////////////

        if(Taxa_Eficacia_Atck==0){

            printf("\n%s POSSUI IMUNIDADE AO SEU ATAQUE!\n",pokedex[Pokemon_Velocidade_Menor].nome);

        }else{

            if(Taxa_Eficacia_Atck == 100){

                printf("\nATAQUE NÃO EFICAZ!\n");

            }else{
                if(Taxa_Eficacia_Atck==150){

                    printf("\nATAQUE NÃO MUITO EFICAZ!\n");

                }else{
                    if(Taxa_Eficacia_Atck==200){
                        
                    printf("\nATAQUE EFICAZ!\n");

                    }else{
                        if(Taxa_Eficacia_Atck==300){

                        printf("\nATAQUE SUPER EFICAZ!\n");

                        }else{
                            if(Taxa_Eficacia_Atck==500){

                            printf("\nATAQUE HIPER EFICAZ!\n");

                            }
                        }
                    }
                }
                    
            }
        }

        printf("%s ataca %s e causa %d de dano!\n", pokedex[Pokemon_Velocidade_Maior].nome, pokedex[Pokemon_Velocidade_Menor].nome, dano);

        if (HP_Pokemon_Velocidade_Menor <= 0) {
            printf("%s Perdeu!\n", pokedex[Pokemon_Velocidade_Menor].nome);
            break;
        }

        printf("%s tem %d HP restantes.\n", pokedex[Pokemon_Velocidade_Menor].nome, HP_Pokemon_Velocidade_Menor);

        ///////////////////// TURNO DO POKEMON COM VELOCIDADE MENOR //////////////////////////////////

        printf("\n%s ATACA\n",pokedex[Pokemon_Velocidade_Menor].nome);

        do {
            printf("Escolha o tipo de ataque (1 para normal, 2 para especial): ");
            scanf("%d", &escolhaAtaque);

            if (escolhaAtaque == 1) {
                ataque = pokedex[Pokemon_Velocidade_Menor].ataque;
                defesa = pokedex[Pokemon_Velocidade_Maior].defesa;
            } else if (escolhaAtaque == 2) {
                ataque = pokedex[Pokemon_Velocidade_Menor].atqSpec;
                defesa = pokedex[Pokemon_Velocidade_Maior].defSpec;
            } else {
                printf("Opção Inválida!\n");
            }
        } while (escolhaAtaque < 1 || escolhaAtaque > 2);

        //////////////////////////////////////// DANO POKEMON VELOCIDADE MENOR /////////////////////////////////////////

        Taxa_Eficacia_Atck = CalculaEficaciaAtack(pokedex,Pokemon_Velocidade_Menor,Pokemon_Velocidade_Maior);

        dano = (((2 * Nivel_Pokemon_Velocidade_Menor + 10) / 250.0) * ((float)ataque / defesa)) * Taxa_Eficacia_Atck;

        if(ataque==pokedex[Pokemon_Velocidade_Menor].atqSpec){
            
            dano+=5;
        }

        HP_Pokemon_Velocidade_Maior -= dano;


        ///////////////////////////////////////EXIBE A EFICACIA DO ATCK //////////////////////////////////

        if(Taxa_Eficacia_Atck==0){

            printf("\n%s POSSUI IMUNIDADE AO SEU ATAQUE!\n",pokedex[Pokemon_Velocidade_Menor].nome);

        }else{

            if(Taxa_Eficacia_Atck == 100){

                printf("\nATAQUE NÃO EFICAZ!\n");

            }else{
                if(Taxa_Eficacia_Atck==150){

                    printf("\nATAQUE NÃO MUITO EFICAZ!\n");

                }else{
                    if(Taxa_Eficacia_Atck==200){
                        
                    printf("\nATAQUE EFICAZ!\n");

                    }else{
                        if(Taxa_Eficacia_Atck==300){

                        printf("\nATAQUE SUPER EFICAZ!\n");

                        }else{
                            if(Taxa_Eficacia_Atck==500){

                            printf("\nATAQUE HIPER EFICAZ!\n");

                            }
                        }
                    }
                }
                    
            }
        }

        printf("%s ataca %s e causa %d de dano!\n", pokedex[Pokemon_Velocidade_Menor].nome, pokedex[Pokemon_Velocidade_Maior].nome, dano);

        if (HP_Pokemon_Velocidade_Maior <= 0) {
            printf("%s Perdeu!\n", pokedex[Pokemon_Velocidade_Maior].nome);
            break;
        }

        printf("%s tem %d HP restantes.\n", pokedex[Pokemon_Velocidade_Maior].nome, HP_Pokemon_Velocidade_Maior);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função para ler os dados do arquivo CSV e armazenar em um array de structs Pokemon
void arquivoR(Pokemon **pokemon, int *numAloc) {

    // Abre o arquivo CSV para leitura
    FILE *arquivo = fopen("pokedex.csv", "r");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Ignora a primeira linha (cabeçalho) do arquivo CSV
    fscanf(arquivo, "%*[^\n]\n");

    // Inicializa o array de Pokemon com capacidade inicial de 10
    int capacidade = 10; 
    *pokemon = malloc(capacidade * sizeof(Pokemon));
    if (*pokemon == NULL) {
        printf("Falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    
    // Inicializa o contador de elementos alocados
    *numAloc = 0;

    // Loop para ler os dados do arquivo CSV e armazenar no array de Pokemon
    while (fscanf(arquivo, "%d ,%29[^,] ,%14[^,] ,%14[^,] ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%14[^,] ,%f ,%f ,%d",
                  &(*pokemon)[*numAloc].numero, (*pokemon)[*numAloc].nome,
                  (*pokemon)[*numAloc].tipoUm, (*pokemon)[*numAloc].tipoDois,
                  &(*pokemon)[*numAloc].statusTotal, &(*pokemon)[*numAloc].hp,
                  &(*pokemon)[*numAloc].ataque, &(*pokemon)[*numAloc].defesa,
                  &(*pokemon)[*numAloc].atqSpec, &(*pokemon)[*numAloc].defSpec,
                  &(*pokemon)[*numAloc].velocidade, &(*pokemon)[*numAloc].geracao,
                  &(*pokemon)[*numAloc].lendario, (*pokemon)[*numAloc].cor,
                  &(*pokemon)[*numAloc].altura, &(*pokemon)[*numAloc].peso,
                  &(*pokemon)[*numAloc].taxadeCap) != EOF) {

        // Incrementa o contador de elementos alocados
        (*numAloc)++;

        // Verifica se a capacidade do array precisa ser aumentada
        if (*numAloc >= capacidade) {
            capacidade *= 2;
            
            // Realoca memória para o array de Pokemon
            *pokemon = realloc(*pokemon, capacidade * sizeof(Pokemon));
            if (*pokemon == NULL) {
                printf("Falha ao realocar memória.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);
}

// Função para listar todos os Pokémon presentes na Pokedex
void listarGeral(Pokemon *pokemon, int numAloc) {

    // Chama a função arquivoR para ler os dados do arquivo CSV e preencher a estrutura Pokemon
    arquivoR(&pokemon, &numAloc);

    // Loop para imprimir as informações de cada Pokémon na Pokedex
    for (int i = 0; i < numAloc; i++) {
        // Imprime os detalhes de cada Pokémon formatado
        printf("Pokémon: %d, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %.2f, %.2f, %d.\n",
            pokemon[i].numero, pokemon[i].nome, pokemon[i].tipoUm, pokemon[i].tipoDois,
            pokemon[i].statusTotal, pokemon[i].hp, pokemon[i].ataque, pokemon[i].defesa,
            pokemon[i].atqSpec, pokemon[i].defSpec, pokemon[i].velocidade, pokemon[i].geracao,
            pokemon[i].lendario, pokemon[i].cor, pokemon[i].altura, pokemon[i].peso,
            pokemon[i].taxadeCap);
    }

    // Libera a memória alocada para o array de Pokemon
    free(pokemon);
}


// Função para listar os Pokémon de uma geração específica
void listarGeracao(Pokemon *pokemon, int numAloc, int *geracaoDesejada) {
    // Chama a função arquivoR para ler os dados do arquivo CSV e preencher a estrutura Pokemon
    arquivoR(&pokemon, &numAloc);

    // Solicita ao usuário a geração desejada
    printf("Digite a geração que você deseja ver listada:");
    scanf("%d", geracaoDesejada);

    // Variável para verificar se há Pokémon na geração desejada
    int indefinido = 0;

    // Loop para percorrer os Pokémon e imprimir os da geração desejada
    for (int i = 0; i < numAloc; i++) {
        if (pokemon[i].geracao == *geracaoDesejada) {
            // Imprime os detalhes de cada Pokémon formatado
            printf("Pokémon: %d, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %.2f, %.2f, %d.\n",
                pokemon[i].numero, pokemon[i].nome, pokemon[i].tipoUm, pokemon[i].tipoDois,
                pokemon[i].statusTotal, pokemon[i].hp, pokemon[i].ataque, pokemon[i].defesa,
                pokemon[i].atqSpec, pokemon[i].defSpec, pokemon[i].velocidade, pokemon[i].geracao,
                pokemon[i].lendario, pokemon[i].cor, pokemon[i].altura, pokemon[i].peso,
                pokemon[i].taxadeCap);
            indefinido++;
        } 
    }

    // Se não houver Pokémon na geração desejada, imprime uma mensagem informativa
    if (indefinido) {
        printf("Não há uma geração correspondente.\n");
    } 
}

// Função para listar os Pokémon de um tipo específico
void listarTipo(Pokemon *pokemon, int numAloc, char *tipoDesejado) {
    // Chama a função arquivoR para ler os dados do arquivo CSV e preencher a estrutura Pokemon
    arquivoR(&pokemon, &numAloc);

    // Solicita ao usuário o tipo desejado
    printf("Digite o tipo que você deseja ver listado:");
    scanf("%s", tipoDesejado);

    // Loop para percorrer os Pokémon e imprimir os do tipo desejado
    for (int i = 0; i < numAloc; i++) {
        if (strcmp(pokemon[i].tipoUm, tipoDesejado) == 0 || strcmp(pokemon[i].tipoDois, tipoDesejado) == 0) {
            // Imprime os detalhes de cada Pokémon formatado
            printf("Pokémon: %d, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %.2f, %.2f, %d.\n",
                pokemon[i].numero, pokemon[i].nome, pokemon[i].tipoUm, pokemon[i].tipoDois,
                pokemon[i].statusTotal, pokemon[i].hp, pokemon[i].ataque, pokemon[i].defesa,
                pokemon[i].atqSpec, pokemon[i].defSpec, pokemon[i].velocidade, pokemon[i].geracao,
                pokemon[i].lendario, pokemon[i].cor, pokemon[i].altura, pokemon[i].peso,
                pokemon[i].taxadeCap);
        }
    }
}

// Função para inserir um novo Pokémon no arquivo CSV
void inserir(Pokemon *pokemon) {
    // Abre o arquivo CSV no modo de escrita no final (append)
    FILE *arquivo = fopen("pokedex.csv", "a");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Solicita ao usuário os dados do novo Pokémon
    printf("Digite o número, necessita ser maior que 750: ");
    scanf("%d", &pokemon->numero);
    
    // Solicita e valida o nome do Pokémon
    printf("Digite o nome do pokémon a ser inserido:");
    scanf("%s", pokemon->nome);

    // Solicita e valida o tipo do Pokémon
    printf("Digite o tipo do pokémon a ser inserido:");
    scanf("%s", pokemon->tipoUm);

    // Solicita e valida o segundo tipo do Pokémon
    printf("Digite o segundo tipo do pokémon a ser inserido:");
    scanf("%s", pokemon->tipoDois);

    // Solicita e valida o HP do Pokémon
    printf("Digite o HP do pokémon a ser inserido:");
    scanf("%d", &pokemon->hp);
    while (pokemon->hp > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->hp);
    }

    // Solicita e valida os atributos de ataque, defesa, ataque especial, defesa especial e velocidade
    // Certifica-se de que os valores não tornam o Pokémon overpower
    printf("Digite o ataque do pokémon a ser inserido:");
    scanf("%d", &pokemon->ataque);
    while (pokemon->ataque > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->ataque);
    }

    printf("Digite a defesa do pokémon a ser inserido:");
    scanf("%d", &pokemon->defesa);
    while (pokemon->defesa > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->defesa);
    }

    printf("Digite o ataque especial do pokémon a ser inserido:");
    scanf("%d", &pokemon->atqSpec);
    while (pokemon->atqSpec > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->atqSpec);
    }

    printf("Digite a defesa especial do pokémon a ser inserido:");
    scanf("%d", &pokemon->defSpec);
    while (pokemon->defSpec > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->defSpec);
    }

    printf("Digite a velocidade do pokémon a ser inserido:");
    scanf("%d", &pokemon->velocidade);
    while (pokemon->velocidade > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->velocidade);
    }

    // Calcula e preenche o status total do Pokémon
    pokemon->statusTotal = pokemon->hp + pokemon->ataque + pokemon->defesa + pokemon->atqSpec + pokemon->defSpec + pokemon->velocidade;

    // Preenche automaticamente a geração e se o Pokémon é lendário
    pokemon->geracao = 9;
    pokemon->lendario = 0;

    // Solicita e valida a cor do Pokémon
    printf("Digite a cor do pokémon a ser inserido:");
    scanf("%s", pokemon->cor);

    // Solicita e valida a altura do Pokémon
    printf("Digite a altura do pokémon a ser inserido:");
    scanf("%f", &pokemon->altura);

    // Solicita e valida o peso do Pokémon
    printf("Digite o peso do pokémon a ser inserido:");
    scanf("%f", &pokemon->peso);

    // Solicita e valida a taxa de captura do Pokémon
    printf("Digite a taxa de captura do pokémon a ser inserido:");
    scanf("%d", &pokemon->taxadeCap);
    while (pokemon->taxadeCap >= 255 && pokemon->taxadeCap <= 0) {
        printf("O valor digitado é inválido digite entre 0 a 255: ");
        scanf("%d", &pokemon->taxadeCap);
    }

    // Escreve os dados do novo Pokémon no arquivo CSV
    fprintf(arquivo, "\n%6d ,%11s ,%8s ,%8s ,%6d ,%4d ,%6d ,%6d ,%15d ,%15d ,%10d ,%7d ,%8d ,%7s ,%8f ,%7f ,%12d",
            pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, pokemon->statusTotal, pokemon->hp,
            pokemon->ataque, pokemon->defesa, pokemon->atqSpec, pokemon->defSpec, pokemon->velocidade, pokemon->geracao,
            pokemon->lendario, pokemon->cor, pokemon->altura, pokemon->peso, pokemon->taxadeCap);

    // Fecha o arquivo
    fclose(arquivo);
}

// Função para pesquisar um Pokémon no arquivo CSV
void pesquisar(Pokemon *pokemon) {
    // Abre o arquivo CSV no modo de leitura
    FILE *arquivo = fopen("pokedex.csv", "r");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    char pokemonPesquisado[30]; // Variável que será utilizada para inserir o nome do pokémon pesquisado
    int verificador = 0;       // Variável contadora para verificar se o pokémon está ou não registrado

    // Solicita ao usuário o nome do pokémon que deseja pesquisar
    printf("Digite o nome do pokémon que você deseja pesquisar: ");
    scanf("%s", pokemonPesquisado);

    // Ignora a primeira linha do arquivo (cabeçalho)
    fscanf(arquivo, "%*[^\n]\n");

    // Loop para percorrer o arquivo e encontrar o Pokémon pesquisado
    while (fscanf(arquivo, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d", &pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, &pokemon->statusTotal, &pokemon->hp, &pokemon->ataque, &pokemon->defesa, &pokemon->atqSpec, &pokemon->defSpec, &pokemon->velocidade, &pokemon->geracao, &pokemon->lendario, pokemon->cor, &pokemon->altura, &pokemon->peso, &pokemon->taxadeCap) != EOF){
        if (strcmp(pokemon->nome, pokemonPesquisado) == 0) {
            verificador = 1;
            break;
        } 
    }

    // Se o Pokémon foi encontrado, exibe suas informações
    if (verificador) {
        printf("Número: %d\n", pokemon->numero);
        printf("Nome: %s\n", pokemon->nome);
        printf("Tipos: %s e %s\n", pokemon->tipoUm, pokemon->tipoDois);
        printf("Status total: %d\n", pokemon->statusTotal);
        printf("Ataque: %d\n", pokemon->ataque);
        printf("Defesa: %d\n", pokemon->defesa);
        printf("Ataque especial: %d\n", pokemon->atqSpec);
        printf("Defesa especial: %d\n", pokemon->defSpec);
        printf("Velocidade: %d\n", pokemon->velocidade);
        printf("Altura: %.2f\n", pokemon->altura);
        printf("Peso: %.2f\n", pokemon->peso);
        printf("Taxa de captura: %d\n", pokemon->taxadeCap);
    } else {
        printf("O pokémon pesquisado ainda não foi capturado ou não existe.\n");
    } 
    
    // Fecha o arquivo
    fclose(arquivo);
}


// Função para excluir um Pokémon do arquivo CSV
void excluir(Pokemon *pokemon) {
    // Abre o arquivo original para leitura
    FILE *arquivoOriginal = fopen("pokedex.csv", "r");
    if (arquivoOriginal == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    } 

    // Abre um arquivo temporário para escrita
    FILE *arquivoTemporario = fopen("pokedextemp.csv", "w");
    if (arquivoTemporario == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        fclose(arquivoOriginal);
        exit(EXIT_FAILURE);
    }

    int pokemonRemovido;
    printf("Digite o número do pokémon a ser removido: ");
    scanf("%d", &pokemonRemovido);

    // Lê e escreve a primeira linha do arquivo (cabeçalho)
    char linha[1024];
    fgets(linha, sizeof(linha), arquivoOriginal);
    fprintf(arquivoTemporario, "%s", linha);

    // Loop para copiar todos os Pokémon do arquivo original para o arquivo temporário, exceto o Pokémon a ser removido
    while (fscanf(arquivoOriginal, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
                  &pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, &pokemon->statusTotal,
                  &pokemon->hp, &pokemon->ataque, &pokemon->defesa, &pokemon->atqSpec, &pokemon->defSpec,
                  &pokemon->velocidade, &pokemon->geracao, &pokemon->lendario, pokemon->cor,
                  &pokemon->altura, &pokemon->peso, &pokemon->taxadeCap) != EOF) {
        if (pokemon->numero != pokemonRemovido) {
            // Se o Pokémon não for o removido, escreve no arquivo temporário
            fprintf(arquivoTemporario, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%.2f ,%.2f ,%d\n",
                    pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, pokemon->statusTotal,
                    pokemon->hp, pokemon->ataque, pokemon->defesa, pokemon->atqSpec, pokemon->defSpec,
                    pokemon->velocidade, pokemon->geracao, pokemon->lendario, pokemon->cor,
                    pokemon->altura, pokemon->peso, pokemon->taxadeCap);
        }
    }

    // Fecha os arquivos
    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    // Remove o arquivo original e renomeia o arquivo temporário para o nome original
    if (remove("pokedex.csv") == 0) {
        if (rename("pokedextemp.csv", "pokedex.csv") != 0) {
            printf("Falha ao renomear o arquivo temporário.\n");
        }
    } else {
        printf("Falha ao renomear ao arquivo original.\n");
    }
}

// Função para alterar os dados de um Pokémon no arquivo CSV
void alterar(Pokemon *pokemon) {
    // Abre o arquivo original para leitura
    FILE *arquivoOriginal = fopen("pokedex.csv", "r");
    if (arquivoOriginal == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    // Abre um arquivo temporário para escrita
    FILE *arquivoTemporario = fopen("pokedextemp.csv", "w");
    if (arquivoTemporario == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    int pokemonDesejado;
    printf("Digite o número do pokémon que você deseja alterar: ");
    scanf("%d", &pokemonDesejado);

    // Loop para copiar todos os Pokémon do arquivo original para o arquivo temporário, realizando alterações no Pokémon desejado
    while (fscanf(arquivoOriginal, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
                  &pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, &pokemon->statusTotal,
                  &pokemon->hp, &pokemon->ataque, &pokemon->defesa, &pokemon->atqSpec, &pokemon->defSpec,
                  &pokemon->velocidade, &pokemon->geracao, &pokemon->lendario, pokemon->cor,
                  &pokemon->altura, &pokemon->peso, &pokemon->taxadeCap) != EOF) {
        fscanf(arquivoOriginal, "%*[^\n]\n");

        // Se o Pokémon desejado for encontrado, solicita novos dados e escreve no arquivo temporário
        if (pokemon->numero == pokemonDesejado) {  
            // Solicita novos dados para o Pokémon
            printf("Digite o número do pokémon (De preferência sendo igual o que você digitou para alterar): ");
            scanf("%d", &pokemon->numero);
            printf("Digite o nome do pokémon: ");
            scanf("%s", pokemon->nome);
            printf("Digite o primeiro tipo do pokémon: ");
            scanf("%s", pokemon->tipoUm);
            printf("Digite o segundo tipo do pokémon: ");
            scanf("%s", pokemon->tipoDois);
            printf("Digite o HP do pokémon: ");
            scanf("%d", &pokemon->hp);
           scanf("%d", &pokemon->ataque);
            printf("Digite a DEFESA do pokémon: ");
            scanf("%d", &pokemon->defesa);
            printf("Digite o ATAQUE ESPECIAL do pokémon: ");
            scanf("%d", &pokemon->atqSpec);
            printf("Digite o DEFESA ESPECIAL do pokémon: ");
            scanf("%d", &pokemon->defSpec);
            printf("Digite o HP do pokémon: ");
            scanf("%d", &pokemon->velocidade);
            printf("Digite a cor do pokémon: ");
            scanf("%s", pokemon->cor);

            // Define valores padrão para os atributos não solicitados
            pokemon->geracao = 10;
            pokemon->lendario = 0;
            pokemon->altura = 2;
            pokemon->peso = 80;
            pokemon->taxadeCap = 100;

            // Escreve os novos dados no arquivo temporário
            fprintf(arquivoTemporario, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%.2f ,%.2f ,%d\n",
                    pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, pokemon->statusTotal,
                    pokemon->hp, pokemon->ataque, pokemon->defesa, pokemon->atqSpec, pokemon->defSpec,
                    pokemon->velocidade, pokemon->geracao, pokemon->lendario, pokemon->cor,
                    pokemon->altura, pokemon->peso, pokemon->taxadeCap);
        } else {
            // Se o Pokémon não for o desejado, escreve no arquivo temporário sem alterações
            fprintf(arquivoTemporario, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%.2f ,%.2f ,%d\n",
                    pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, pokemon->statusTotal,
                    pokemon->hp, pokemon->ataque, pokemon->defesa, pokemon->atqSpec, pokemon->defSpec,
                    pokemon->velocidade, pokemon->geracao, pokemon->lendario, pokemon->cor,
                    pokemon->altura, pokemon->peso, pokemon->taxadeCap);
        }
    }

    // Fecha os arquivos
    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    // Remove o arquivo original e renomeia o arquivo temporário para o nome original
    remove("pokedex.csv");
    rename("pokedextemp.csv", "pokedex.csv");
}

int main() {
            Pokemon pokedex[MAX_POKEMONS];
            int NumeroPokemon1, NumeroPokemon2;
            int NivelPokemon1, NivelPokemon2;
            Vincular_Pokedex_Struct(pokedex, "pokedex.csv");


    
            // Declaração das estruturas necessárias
            RegistroCSV registro;
            Escolha escolha;
            Mochila mochila;
            Colecao colecao;
            int numLinhas = contarLinhas();
            // Inicializa a mochila e a coleção
            inicializarMochila(&mochila);
            inicializarColecao(&colecao);


    
            Pokemon *pokemon;
            int numAloc;
            char tipoDesejado[15];
            int geracaoDesejada;

            arquivoR(&pokemon, &numAloc);
            int numeroEscolhido;
            int listagem;
            int opcao;


    do {
    printf("Escolha uma opção:\n");
    printf("1. Batalha Pokémon\n");
    printf("2. Iniciar Jogo Pokémon\n");
    printf("3. Abrir Pekédex\n");
    printf("0. Sair\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            do{

            printf("Escolha o primeiro Pokémon (índice de 1 a 721): ");
            scanf("%d", &NumeroPokemon1);
            }while(NumeroPokemon1<1||NumeroPokemon1>721);

            printf("Escolha o nivel do primeiro Pokémon: ");
            scanf("%d", &NivelPokemon1);

            do{
            printf("Escolha o segundo Pokémon (índice de 1 a 721): ");
            scanf("%d", &NumeroPokemon2);
            }while(NumeroPokemon2<1||NumeroPokemon2>721);

            printf("Escolha o nivel do segundo Pokémon: ");
            scanf("%d", &NivelPokemon2);

            if (NumeroPokemon1 >= 1 && NumeroPokemon1 <= MAX_POKEMONS && NumeroPokemon2 >= 1 && NumeroPokemon2 <= MAX_POKEMONS) {

            BatalhaPokemon(pokedex, NumeroPokemon1 - 1, NumeroPokemon2 - 1, NivelPokemon1, NivelPokemon2); // Subtrai 1 para ajustar o índice do array.

            } else {
                printf("Índices de Pokémon inválidos!\n");
            }
        break;
        case 2:
            // Carrega os dados dos Pokémon disponíveis para escolha
            escolhaPokemon(&escolha, &mochila);

            // Inicia o jogo Pokémon, passando as estruturas necessárias
            jogarPokemon(&registro, &mochila, &colecao, numLinhas);

            // Retorna 0 indicando que o programa foi concluído com sucesso
        break;
        case 3:
            printf("POKÉDEX\n");
            printf("Digite o número correspondente para realizar a função desejada:\n" );
            printf("1 para LISTAR pokémons\n");
            printf("2 para INSERIR um pokémon\n");
            printf("3 para REMOVER um pokémon\n");
            printf("4 para PESQUISAR pokémons\n");
            printf("5 para ALTERAR pokémon\n");
            printf("6 para ENCERRAR o menu\n");
            printf("Número desejado: ");
            scanf("%d", &numeroEscolhido);

            switch (numeroEscolhido){
                case 1:
            printf("Escolha o tipo de listagem que deseja realizar.\n");
            printf("Digite 1 para listar TODOS os pokémons\n");
            printf("Digite 2 para listar pokémons por GERAÇÃO\n");
            printf("Digite 3 para listar pokémons por TIPO\n");
            printf("Número desejado: ");
            scanf("%d", &listagem);

            switch (listagem){
                case 1:
            listarGeral(pokemon, numAloc);
            break;
        
                case 2:
            listarGeracao(pokemon, numAloc, &geracaoDesejada);
            free(pokemon);  
            break;

                case 3:
            listarTipo(pokemon, numAloc, tipoDesejado);
            free(pokemon);  
            break;

        default:
            printf("O valor digitado não está associado a nenhuma opção disponível.");
            break;
        }
        break;
    
                case 2:
            inserir(pokemon);
            break;

                case 3:
            excluir(pokemon);
        break;

                case 4:
            pesquisar(pokemon);
        break;

                case 5:
            alterar(pokemon);
        break;

                case 6:
        exit(1);
        break;
       default:
    printf("O valor digitado não está associado a nenhuma opção disponível.");
    break;
    }
        break;
        case 0:
            printf("Saindo do programa. Até mais!\n");
            break;

            default:
            printf("Opção inválida. Tente novamente.\n");
    }
  } while (opcao != 0);

    return 0;
}

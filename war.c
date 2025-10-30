#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura para representar um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções para organizar o código
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirTerritorios(Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    int numTerritorios;
    int indiceAtacante, indiceDefensor;
    int opcao;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("--- Simulador de Batalhas WAR Estruturado ---\n");
    printf("Quantos territorios o mapa tera? ");
    scanf("%d", &numTerritorios);

    // Validação para garantir que há pelo menos 2 territórios para a batalha
    if (numTerritorios < 2) {
        printf("Erro: Sao necessarios pelo menos 2 territorios para jogar.\n");
        return 1; // Encerra o programa com código de erro
    }

    // 1. Alocação dinâmica de territórios: utilizando calloc
    // Aloca um vetor de 'Territorio' dinamicamente.
    // calloc inicializa a memória com zeros, o que é uma boa prática.
    Territorio* mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastra os territórios iniciais
    cadastrarTerritorios(mapa, numTerritorios);

    do {
        // Exibe o estado atual do mapa
        exibirTerritorios(mapa, numTerritorios);

        printf("\n--- Menu de Acoes ---\n");
        printf("1. Realizar um ataque\n");
        printf("0. Sair do jogo\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // Interface amigável para a seleção de territórios
            printf("\nEscolha o territorio atacante (pelo indice): ");
            scanf("%d", &indiceAtacante);
            printf("Escolha o territorio defensor (pelo indice): ");
            scanf("%d", &indiceDefensor);

            // Validações básicas das escolhas do usuário
            if (indiceAtacante < 0 || indiceAtacante >= numTerritorios ||
                indiceDefensor < 0 || indiceDefensor >= numTerritorios) {
                printf("\nErro: Indice de territorio invalido!\n");
                continue; // Volta para o início do loop
            }

            if (indiceAtacante == indiceDefensor) {
                printf("\nErro: O territorio de ataque e defesa nao podem ser o mesmo!\n");
                continue;
            }
            
            // Requisito: Validar para que o jogador não ataque um território da própria cor
            if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) == 0) {
                 printf("\nErro: Voce nao pode atacar um territorio que ja e seu!\n");
                 continue;
            }

            // 2. Simulação de ataques: utilizando ponteiros para acessar os territórios
            // Passa o endereço do território atacante e defensor para a função.
            printf("\n--- ATAQUE INICIADO ---\n");
            atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
            printf("--- ATAQUE FINALIZADO ---\n\n");
        }

    } while (opcao != 0);

    // 7. Gerenciamento de memória: libera a memória alocada
    liberarMemoria(mapa);
    printf("\nJogo encerrado e memoria liberada com sucesso!\n");

    return 0;
}

/**
 * @brief Cadastra os dados de N territórios em um vetor.
 * @param mapa Ponteiro para o vetor de territórios.
 * @param n Número de territórios a cadastrar.
 */
void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("\n--- Cadastro de Territorios ---\n");
    for (int i = 0; i < n; i++) {
        printf("Dados do Territorio %d:\n", i);
        printf("  Nome: ");
        scanf("%s", mapa[i].nome);
        printf("  Cor do exercito (ex: Azul, Verde): ");
        scanf("%s", mapa[i].cor);
        printf("  Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

/**
 * @brief Exibe os dados de todos os territórios cadastrados.
 * @param mapa Ponteiro para o vetor de territórios.
 * @param n Número de territórios a exibir.
 */
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n--- ESTADO ATUAL DO MAPA ---\n");
    for (int i = 0; i < n; i++) {
        // Acessa os campos da struct através do ponteiro
        printf("Indice: %d | Territorio: %-15s | Cor: %-10s | Tropas: %d\n",
               i, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
    }
    printf("--------------------------------\n");
}

/**
 * @brief Simula um ataque entre dois territórios.
 * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    // Simula a rolagem de dados de 1 a 6 para cada lado
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("Atacante '%s' (%s) rolou o dado: %d\n", atacante->nome, atacante->cor, dadoAtaque);
    printf("Defensor '%s' (%s) rolou o dado: %d\n", defensor->nome, defensor->cor, dadoDefesa);

    // 3. Atualização de dados: verifica o resultado da batalha
    if (dadoAtaque > dadoDefesa) {
        printf("\n>> VITORIA DO ATACANTE! <<\n");
        printf("O territorio '%s' foi conquistado!\n", defensor->nome);

        // O território defensor muda de dono (cor do exército)
        strcpy(defensor->cor, atacante->cor);

        // Metade das tropas do atacante (arredondado para baixo) se movem para o novo território
        int tropasMovidas = atacante->tropas / 2;
        if (tropasMovidas < 1) tropasMovidas = 1; // Garante que pelo menos 1 tropa se mova, se possível

        defensor->tropas = tropasMovidas; // O território conquistado fica com as tropas que se moveram
        atacante->tropas -= tropasMovidas; // O território atacante perde as tropas que se moveram
        
    } else {
        printf("\n>> VITORIA DA DEFESA! <<\n");
        printf("O ataque foi repelido!\n");
        
        // Se perder, o atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
            printf("O atacante '%s' perdeu 1 tropa na batalha.\n", atacante->nome);
        } else {
            printf("O atacante '%s' nao tinha tropas suficientes para perder.\n", atacante->nome);
        }
    }
}

/**
 * @brief Libera a memória alocada dinamicamente para o mapa.
 * @param mapa Ponteiro para o vetor de territórios que será liberado.
 */
void liberarMemoria(Territorio* mapa) {
    // Verifica se o ponteiro não é nulo antes de tentar liberar
    if (mapa != NULL) {
        free(mapa);
    }
}
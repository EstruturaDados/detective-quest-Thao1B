#include <stdio.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do tamanho máximo para o nome do cômodo
#define MAX_NOME 50

/**
 * @brief Estrutura que representa um cômodo (nó) da mansão.
 *
 * Uma Sala tem um nome e ponteiros para as salas conectadas à esquerda e à direita.
 */
typedef struct Sala {
    char nome[MAX_NOME];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/**
 * @brief Cria, de forma dinâmica, uma nova sala com o nome especificado.
 *
 * Aloca memória para uma nova estrutura Sala, copia o nome e inicializa
 * os ponteiros 'esquerda' e 'direita' como NULL.
 *
 * @param nome O nome do cômodo a ser criado.
 * @return Um ponteiro para a nova Sala criada dinamicamente.
 */
Sala* criarSala(const char* nome) {
    // Alocação dinâmica de memória para a nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    // Verifica se a alocação foi bem-sucedida
    if (novaSala == NULL) {
        perror("Erro ao alocar memória para a sala.");
        exit(EXIT_FAILURE);
    }
    
    // Copia o nome para o campo 'nome' da estrutura
    strncpy(novaSala->nome, nome, MAX_NOME - 1);
    novaSala->nome[MAX_NOME - 1] = '\0'; // Garantir terminação da string
    
    // Inicializa os ponteiros dos filhos como NULL
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * @brief Permite a navegação interativa do jogador pela árvore do mapa.
 *
 * O jogador pode escolher ir para a esquerda ('e'), para a direita ('d') ou sair ('s').
 * A exploração continua até o jogador chegar a uma sala sem caminhos (nó-folha)
 * ou escolher sair.
 *
 * @param hall O ponteiro para a sala inicial (raiz da árvore).
 */
void explorarSalas(Sala* hall) {
    Sala* salaAtual = hall;
    char escolha;
    
    printf("\n--- 🕵️‍♂️ Detective Quest: Explorando a Mansão ---\n");
    
    // Loop principal de exploração
    while (salaAtual != NULL) {
        printf("\nVocê está em: **%s**\n", salaAtual->nome);
        
        // 1. Verificar se é um nó-folha (sem caminhos)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Fim da linha! Este cômodo não tem mais saídas. A exploração terminou aqui.\n");
            break;
        }
        
        // 2. Apresentar opções
        printf("Para onde você quer ir?\n");
        if (salaAtual->esquerda != NULL) {
            printf("  [e] Ir para a **esquerda** (para a sala: %s)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  [d] Ir para a **direita** (para a sala: %s)\n", salaAtual->direita->nome);
        }
        printf("  [s] **Sair** da exploração\n");
        printf("Sua escolha: ");
        
        // 3. Capturar e processar a entrada
        if (scanf(" %c", &escolha) != 1) {
            // Limpa o buffer de entrada em caso de erro
            while(getchar() != '\n'); 
            continue;
        }
        
        // Processa a escolha do jogador
        switch (escolha) {
            case 'e':
            case 'E':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda; // Move para a esquerda
                } else {
                    printf("❌ Não há caminho para a esquerda a partir desta sala.\n");
                }
                break;
                
            case 'd':
            case 'D':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita; // Move para a direita
                } else {
                    printf("❌ Não há caminho para a direita a partir desta sala.\n");
                }
                break;
                
            case 's':
            case 'S':
                printf("🚪 Você decidiu sair da mansão. Exploração encerrada.\n");
                salaAtual = NULL; // Encerra o loop
                break;
                
            default:
                printf("❓ Escolha inválida. Use 'e' (esquerda), 'd' (direita) ou 's' (sair).\n");
                break;
        }
    }
    
    printf("\n--- Exploração finalizada. ---\n");
}

/**
 * @brief Função principal: monta o mapa inicial e dá início à exploração.
 *
 * Esta função cria a estrutura da árvore binária da mansão e chama a função
 * que permite a exploração interativa.
 */
int main() {
    // 1. Construção do Mapa da Mansão (Árvore Binária)
    
    // Nível 0 (Raiz)
    Sala* hallEntrada = criarSala("Hall de Entrada");
    
    // Nível 1
    hallEntrada->esquerda = criarSala("Sala de Estar");
    hallEntrada->direita = criarSala("Cozinha");
    
    // Nível 2
    hallEntrada->esquerda->esquerda = criarSala("Biblioteca");
    hallEntrada->esquerda->direita = criarSala("Escritório");
    hallEntrada->direita->esquerda = criarSala("Despensa"); // Nó-folha
    hallEntrada->direita->direita = criarSala("Jardim de Inverno");
    
    // Nível 3
    hallEntrada->esquerda->direita->esquerda = criarSala("Quarto Principal"); // Nó-folha

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 3
#define JOGADORES 100
#define NOME 16 // Aumentei o tamanho do campo de nome para 16 para considerar o caractere nulo ('\0')
#define ARQUIVO "ranking.txt"

typedef struct {
    char name[NOME];
    int wins;
    int losses;
    int dificuldade;
} Player;

void exibirMenu();
void jogar(Player *jogador, int *Ojogador);
void exibirSobre();
void clear_screen();
void save_ranking(Player *jogador, int Ojogador);
void load_ranking(Player *jogador, int *Ojogador);
void display_ranking(Player *jogador, int Ojogador);
void Adificuldade(Player *player);
int check_victory(char tabuleiro[TAMANHO][TAMANHO], char jogador_atual);

int main() {
    Player jogador[JOGADORES];
    int Ojogador = 0;
    int menu1;

    load_ranking(jogador, &Ojogador);

    clear_screen();
    printf("Bem-vindo ao Jogo da Velha!\n");

    do {
        exibirMenu();
        scanf("%d", &menu1);

        switch (menu1) {
            case 1:
                clear_screen();
                printf("Bem-vindo ao jogo da velha!\n");
                printf("Digite seu NickName: ");
                scanf("%s", jogador[Ojogador].name);
                jogador[Ojogador].wins = 0;
                jogador[Ojogador].losses = 0;
                Adificuldade(&jogador[Ojogador]);
                jogar(&jogador[Ojogador], &Ojogador);
                Ojogador++;
                break;
            case 2:
                display_ranking(jogador, Ojogador);
                break;
            case 3:
                exibirSobre();
                break;
            case 4:
                save_ranking(jogador, Ojogador);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (menu1 != 4);

    clear_screen();
    printf("Obrigado por jogar!\n");

    return 0;
}

void exibirMenu() {
    printf("\n===== MENU =====\n");
    printf("1. Jogar\n");
    printf("2. Ranking\n");
    printf("3. Sobre\n");
    printf("4. Sair\n");
    printf("================\n");
    printf("Escolha uma opcao: ");
}

void jogar(Player *jogador, int *Ojogador) {
    char tabuleiro[TAMANHO][TAMANHO];
    int i, j;
    int jogadas = 0;
    int vitoria = 0;
    char jogador_atual = 'X';


    // Inicializar tabuleiro
    for (i = 0; i < TAMANHO; i++) {
        for (j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = ' ';
        }
    }

    // Loop do jogo
    while (jogadas < TAMANHO * TAMANHO && !vitoria) {
        clear_screen();
        printf("Jogador: %s\n", jogador->name);
        printf("Dificuldade: %d\n\n", jogador->dificuldade);
        printf("===== JOGO DA VELHA =====\n\n");

        // Exibir tabuleiro
        printf("  1   2   3\n");
        for (i = 0; i < TAMANHO; i++) {
            printf("%d ", i + 1);
            for (j = 0; j < TAMANHO; j++) {
                printf(" %c ", tabuleiro[i][j]);
                if (j < TAMANHO - 1) {
                    printf("|");
                }
            }
            printf("\n");
            if (i < TAMANHO - 1) {
                printf("  ---+---+---\n");
            }
        }

        printf("\n");

        if (jogador_atual == 'X') {
            int linha, coluna;

            printf("Sua vez de jogar!\n");
            printf("Digite a linha (1-%d): ", TAMANHO);
            scanf("%d", &linha);
            linha--; 

            printf("Digite a coluna (1-%d): ", TAMANHO);
            scanf("%d", &coluna);
            coluna--; 
            
            
            if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO || tabuleiro[linha][coluna] != ' ') {
                printf("Posicao invalida. Tente novamente.\n");
                continue;
            }

            // Realizar jogada do jogador
            tabuleiro[linha][coluna] = jogador_atual;
        } else {
            printf("Vez da maquina jogar...\n");

            // Lógica da jogada da máquina de acordo com a dificuldade
            if (jogador->dificuldade == 1) {
                // Jogada aleatória fácil
                int i,j;
                //Primeira Jogada
                do {
                    i = rand() % TAMANHO;
                    j = rand() % TAMANHO;
                } while (tabuleiro[i][j] != ' ');
                tabuleiro[i][j] = jogador_atual;
                
                } else if (jogador->dificuldade == 2) {
                     // Jogada com lógica de dificuldade 2
                int block = 0;
                for (i = 0; i < TAMANHO; i++) {
                    for (j = 0; j < TAMANHO; j++) {
                        if (tabuleiro[i][j] == ' ') {
                            tabuleiro[i][j] = 'X';
                        if (check_victory(tabuleiro, 'X')) {
                    // Fazer jogada de bloqueio
                    tabuleiro[i][j] = 'O';
                    block = 1;
                    break;
                }
                tabuleiro[i][j] = ' ';
            }
        }
        if (block) {
            break;
        }
    }
    if (!block) {
    
    if (tabuleiro[1][1] == ' ') {
        tabuleiro[1][1] = 'O';
    } else {
        
        int diagonal[4][2] = {{0, 0}, {0, TAMANHO-1}, {TAMANHO-1, 0}, {TAMANHO-1, TAMANHO-1}};
        for (int k = 0; k < 4; k++) {
            int x = diagonal[k][0];
            int y = diagonal[k][1];
            if (tabuleiro[x][y] == ' ') {
                tabuleiro[x][y] = 'O'; 
                break;
            }
        }
    }
}


            } else {

                // (ainda precisa ser implementada a dificuldade 3)
                int linha, coluna;
                do {
                    linha = rand() % TAMANHO;
                    coluna = rand() % TAMANHO;
                } while (tabuleiro[linha][coluna] != ' ');

                // Realizar jogada da máquina
                tabuleiro[linha][coluna] = jogador_atual;
            }
        }

        // Verificar vitória
        if (check_victory(tabuleiro, jogador_atual)) {
            vitoria = 1;
            if (jogador_atual == 'X') {
                printf("Parabens, voce venceu!\n");
                jogador->wins++;
                        printf("  1   2   3\n");
        for (i = 0; i < TAMANHO; i++) {
            printf("%d ", i + 1);
            for (j = 0; j < TAMANHO; j++) {
                printf(" %c ", tabuleiro[i][j]);
                if (j < TAMANHO - 1) {
                    printf("|");
                }
            }
            printf("\n");
            if (i < TAMANHO - 1) {
                printf("  ---+---+---\n");
            }
        }

        printf("\n");
            } else {
                printf("A maquina venceu!\n");
                jogador->losses++;

                        printf("  1   2   3\n");
        for (i = 0; i < TAMANHO; i++) {
            printf("%d ", i + 1);
            for (j = 0; j < TAMANHO; j++) {
                printf(" %c ", tabuleiro[i][j]);
                if (j < TAMANHO - 1) {
                    printf("|");
                }
            }
            printf("\n");
            if (i < TAMANHO - 1) {
                printf("  ---+---+---\n");
            }
        }

        printf("\n");
            }
        }

        // Alternar jogador
        jogador_atual = (jogador_atual == 'X') ? 'O' : 'X';
        jogadas++;
    }

    // Verificar empate
    if (!vitoria) {
        clear_screen();
        printf("===== JOGO DA VELHA =====\n\n");

        // Exibir tabuleiro
        printf("  1   2   3\n");
        for (i = 0; i < TAMANHO; i++) {
            printf("%d ", i + 1);
            for (j = 0; j < TAMANHO; j++) {
                printf(" %c ", tabuleiro[i][j]);
                if (j < TAMANHO - 1) {
                    printf("|");
                }
            }
            printf("\n");
            if (i < TAMANHO - 1) {
                printf("  ---+---+---\n");
            }
        }

        printf("\n");

        printf("Empate! O jogo terminou sem vencedores.\n");
    }

    // Perguntar se quer jogar novamente
    char opcao;
    printf("\nDeseja jogar novamente? (S/N): ");
    scanf(" %c", &opcao);

    if (opcao == 'S' || opcao == 's') {
        jogar(jogador, Ojogador);
    }
}

void exibirSobre() {
    clear_screen();
    printf("===== SOBRE =====\n\n");
    printf("O Jogo da Velha e um jogo popular que envolve\n");
    printf("dois jogadores, X e O, que se revezam marcando espacos em\n");
    printf("uma grade de 3x3. O jogador que conseguir colocar tres\n");
    printf("marcas na horizontal, vertical ou diagonal vence o jogo.\n");
    printf("\nPressione qualquer tecla para continuar...\n");
    getchar();
    getchar();
}

void clear_screen() {
    system("cls");
}

void display_ranking(Player *jogador, int Ojogador) {
    clear_screen();
    printf("===== RANKING =====\n\n");
    printf("NICKNAME\tVITORIAS\tDERROTAS\n");
    printf("---------\t--------\t--------\n");

    for (int i = 0; i < Ojogador; i++) {
        printf("%s\t\t%d\t\t\t%d\n", jogador[i].name, jogador[i].wins, jogador[i].losses);
    }

    printf("\nPressione qualquer tecla para continuar...\n");
    getchar();
    getchar();
}

void load_ranking(Player *jogador, int *Ojogador) {
    FILE *file = fopen(ARQUIVO, "r");
    if (file != NULL) {
        while (!feof(file)) {
            if (fscanf(file, "%s %d %d", jogador[*Ojogador].name, &(jogador[*Ojogador].wins),
                       &(jogador[*Ojogador].losses)) != 3) {
                break;
            }
            (*Ojogador)++;
        }
        fclose(file);
    }
}

void save_ranking(Player *jogador, int Ojogador) {
    FILE *file = fopen(ARQUIVO, "w");
    if (file != NULL) {
        for (int i = 0; i < Ojogador; i++) {
            fprintf(file, "%s %d %d\n", jogador[i].name, jogador[i].wins, jogador[i].losses);
        }
        fclose(file);
        printf("Ranking salvo com sucesso!\n");
    } else {
        printf("Nao foi possível salvar o ranking.\n");
    }
}

void Adificuldade(Player *player) {
    printf("Escolha a dificuldade do jogo:\n");
    printf("1 - Facil\n");
    printf("2 - Medio\n");
    printf("3 - Dificil\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &(player->dificuldade));
}

int check_victory(char tabuleiro[TAMANHO][TAMANHO], char jogador_atual) {
    int i, j;
    int vitoria = 0;

    // Verificar linhas
    for (i = 0; i < TAMANHO; i++) {
        if (tabuleiro[i][0] == jogador_atual && tabuleiro[i][1] == jogador_atual && tabuleiro[i][2] == jogador_atual) {
            vitoria = 1;
            break;
        }
    }

    // Verificar colunas
    for (j = 0; j < TAMANHO; j++) {
        if (tabuleiro[0][j] == jogador_atual && tabuleiro[1][j] == jogador_atual && tabuleiro[2][j] == jogador_atual) {
            vitoria = 1;
            break;
        }
    }

    // Verificar diagonais
    if (tabuleiro[0][0] == jogador_atual && tabuleiro[1][1] == jogador_atual && tabuleiro[2][2] == jogador_atual) {
        vitoria = 1;
    }
    if (tabuleiro[0][2] == jogador_atual && tabuleiro[1][1] == jogador_atual && tabuleiro[2][0] == jogador_atual) {
        vitoria = 1;
    }

    return vitoria;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO 3
#define JOGADORES 100
#define NOME 15 //Temos QUE Colocar no Ranking para o Nickname ser no maximo 15 caractere
#define ARQUIVO "ranking.txt"


typedef struct {
    char name[NOME];
    int wins;
    int losses;
    int dificuldade; 
} Player;

void save_ranking(Player *players, int num_players);
void load_ranking(Player *players, int *num_players);
void display_ranking(Player *players, int num_players);
void display_sobre();
void display_menu();
void clear_screen();
void choose_dificuldade(Player *player) ;
void play_game(Player *player, int dificuldade);
int check_winner(char board[TAMANHO][TAMANHO]);





int main() {
    Player players[JOGADORES];
    int num_players = 0;
    int menu1;

    load_ranking(players, &num_players);

    clear_screen();
    printf("Bem-vindo ao Jogo da Velha!\n");

    do {
        display_menu();
        scanf("%d", &menu1);

        switch (menu1) {
            case 1:
                clear_screen();
                printf("Digite seu NickName: ");
                scanf("%s", players[num_players].name);
                players[num_players].wins = 0;
                players[num_players].losses = 0;
                choose_dificuldade(&players[num_players]);
                play_game(&players[num_players], players[num_players].dificuldade);
                num_players++;
                break;
            case 2:
                display_ranking(players, num_players);
                break;
            case 3:
                display_sobre();
                break;
            case 4:
                save_ranking(players, num_players);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (menu1 != 4);

    return 0;
}

void clear_screen() {
    system("cls");
}

void display_menu() {
    printf("===== MENU =====\n");
    printf("1. Jogar\n");
    printf("2. Ranking\n");
    printf("3. Sobre\n");
    printf("4. Sair\n");
    printf("================\n");
    printf("Escolha uma opcao: ");
}

int check_winner(char board[TAMANHO][TAMANHO]) {
    // Verificar linhas
    for (int linha = 0; linha < TAMANHO; linha++) {
        if (board[linha][0] != ' ' && board[linha][0] == board[linha][1] && board[linha][0] == board[linha][2]) {
            if (board[linha][0] == 'X')
                return 1; // Jogador venceu
            else
                return 2; // Máquina venceu
        }
    }

    // Verificar colunas
    for (int colunas = 0; colunas < TAMANHO; colunas++) {
        if (board[0][colunas] != ' ' && board[0][colunas] == board[1][colunas] && board[0][colunas] == board[2][colunas]) {
            if (board[0][colunas] == 'X')
                return 1; // Jogador venceu
            else
                return 2; // Máquina venceu
        }
    }

    // Verificar diagonais
    if ((board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) ||
        (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0])) {
        if (board[1][1] == 'X')
            return 1; // Jogador venceu
        else
            return 2; // Máquina venceu
    }

    // Verificar empate
    int empty_spots = 0;
    for (int linha = 0; linha < TAMANHO; linha++) {
        for (int colunas = 0; colunas < TAMANHO; colunas++) {
            if (board[linha][colunas] == ' ')
                empty_spots++;
        }
    }

    if (empty_spots == 0)
        return 3; // Empate

    return 0; // Jogo em andamento
}


void play_game(Player *player, int dificuldade) {
    char board[TAMANHO][TAMANHO];
    int linha, colunas;
    int turn = 0;
    int empty_spots = TAMANHO * TAMANHO;
    int continue_playing = 1;

    // Inicializar o tabuleiro
    for (linha = 0; linha < TAMANHO; linha++) {
        for (colunas = 0; colunas < TAMANHO; colunas++) {
            board[linha][colunas] = ' ';
        }
    }

    while (continue_playing) {
        while (1) {
            clear_screen();
            printf("===== JOGO DA VELHA =====\n\n");
            printf("Jogador: %s\n\n", player->name);

            // Exibir o tabuleiro
            printf("  1   2   3\n");
            for (linha = 0; linha < TAMANHO; linha++) {
                printf("%d ", linha + 1);
                for (colunas = 0; colunas < TAMANHO; colunas++) {
                    printf(" %c ", board[linha][colunas]);
                    if (colunas < TAMANHO - 1) {
                        printf("|");
                    }
                }
                printf("\n");
                if (linha < TAMANHO - 1) {
                    printf(" ---+---+---\n");
                }
            }

            int winner = check_winner(board);
            if (winner != 0) {
                if (winner == 1) {
                    printf("\nParabens! Voce venceu!\n");
                    player->wins++;
                } else if (winner == 2) {
                    printf("\nVoce perdeu! A maquina venceu!\n");
                    player->losses++;
                } else {
                    printf("\nEmpate!\n");
                }

                printf("\nDeseja jogar novamente?\n");
                printf("1. Sim\n");
                printf("2. Nao\n");
                printf("Escolha uma opcao: ");

                int menu1;
                scanf("%d", &menu1);

                if (menu1 == 1) {
                    // Limpar o tabuleiro para uma nova partida
                    for (linha = 0; linha < TAMANHO; linha++) {
                        for (colunas = 0; colunas < TAMANHO; colunas++) {
                            board[linha][colunas] = ' ';
                        }
                    }
                    turn = 0;
                    empty_spots = TAMANHO * TAMANHO;
                    continue_playing = 1;
                } else {
                    continue_playing = 0;
                }

                break;
            }

            if (turn % 2 == 0) {
                // Solicitar jogada do jogador
                int valid_move = 0;
                while (!valid_move) {
                    printf("\nDigite a linha (1-%d): ", TAMANHO);
                    scanf("%d", &linha);
                    printf("Digite a coluna (1-%d): ", TAMANHO);
                    scanf("%d", &colunas);
                    linha--;
                    colunas--;

                    if (linha >= 0 && linha < TAMANHO && colunas >= 0 && colunas < TAMANHO && board[linha][colunas] == ' ') {
                        valid_move = 1;
                    } else {
                        printf("\nJogada invalida. Tente novamente.\n");
                    }
                }

                board[linha][colunas] = 'X';
            } else {
                // Jogada da máquina
                int valid_move = 0;
                srand(time(NULL)); // aleatória

                if (dificuldade == 1) {
                    while (!valid_move) {
                        linha = rand() % TAMANHO;
                        colunas = rand() % TAMANHO;

                        if (board[linha][colunas] == ' ') {
                            valid_move = 1;
                        }
                    }
                } else if (dificuldade == 2) {
                    valid_move = 0;
                    // Tentar jogar na linha 2, coluna 2
                    if (board[1][1] == ' ') {
                        linha = 1;
                        colunas = 1;
                        valid_move = 1;
                    } else {
                        // Procurar por quinas disponíveis
                        int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
                        for (int i = 0; i < 4; i++) {
                            int corner_linha = corners[i][0];
                            int corner_colunas = corners[i][1];
                            if (board[corner_linha][corner_colunas] == ' ') {
                                linha = corner_linha;
                                colunas = corner_colunas;
                                valid_move = 1;
                                break;
                            }
                        }
                    }

                    // Jogar aleatoriamente se não houver quinas disponíveis
                    if (!valid_move) {
                        while (!valid_move) {
                            linha = rand() % TAMANHO;
                            colunas = rand() % TAMANHO;

                            if (board[linha][colunas] == ' ') {
                                valid_move = 1;
                            }
                        }
                    }
                    
                } else if (dificuldade == 3) {
                    // Estratégia para o modo Expert (dificuldade máxima)
                    

                    for (int i = 0; i < TAMANHO; i++) {
                        for (int j = 0; j < TAMANHO; j++) {
                            if (board[i][j] == ' ') {
                                linha = i;
                                colunas = j;
                                valid_move = 1;
                                break;
                            }
                        }

                        if (valid_move) {
                            break;
                        }
                    }
                }

                board[linha][colunas] = 'O';
            }

            turn++;
            empty_spots--;
        }
    }

    printf("\nPressione qualquer tecla para continuar...\n");
    getchar();
    getchar(); // Aguardar o usuário pressionar uma tecla
}

void choose_dificuldade(Player *player) {
    int dificuldade;

    printf("Escolha a dificuldade:\n");
    printf("1. Easy\n");
    printf("2. Hard\n");
    printf("3. Expert\n");
    printf("Digite a opcao: ");
    scanf("%d", &dificuldade);

    while (dificuldade < 1 || dificuldade > 3) {
        printf("Opcao invalida. Tente novamente: ");
        scanf("%d", &dificuldade);
    }

    player->dificuldade = dificuldade;
}

void display_ranking(Player *players, int num_players) {
    clear_screen();
    printf("===== RANKING =====\n\n");
    printf("NICKNAME\tVITORIAS\tDERROTAS\n");
    printf("---------\t--------\t--------\n");

    for (int i = 0; i < num_players; i++) {
        printf("%s\t\t%d\t\t\t%d\n", players[i].name, players[i].wins, players[i].losses);
    }

    printf("\nPressione qualquer tecla para continuar...\n");
    getchar();
    getchar();
}

void display_sobre() {
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

void load_ranking(Player *players, int *num_players) {
    FILE *file = fopen(ARQUIVO, "r");
    if (file != NULL) {
        while (!feof(file)) {
            if (fscanf(file, "%s %d %d", players[*num_players].name, &(players[*num_players].wins),
                       &(players[*num_players].losses)) == 3) {
                (*num_players)++;
            }
        }
        fclose(file);
    }
}

void save_ranking(Player *players, int num_players) {
    FILE *file = fopen(ARQUIVO, "w");
    if (file != NULL) {
        for (int i = 0; i < num_players; i++) {
            fprintf(file, "%s %d %d\n", players[i].name, players[i].wins, players[i].losses);
        }
        fclose(file);
    }
}

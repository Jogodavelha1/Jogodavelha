#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 3
#define JOGADORES 100
#define NOME 16 // Aumentei o tamanho do campo de nome para 16 para considerar o caractere nulo ('\0')
#define ARQUIVO "ranking.csv"

typedef struct {
    char name[NOME];
    char symbol;
    int wins;
    int losses;
    int dificuldade;
    int modo_jogo;
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
       
        clear_screen();
        printf("Bem-vindo ao jogo da velha (Jogador vs Jogador)!\n");
        printf("Digite o nome do primeiro jogador: ");
        scanf("%s", jogador[Ojogador].name);
        jogador[Ojogador].symbol = 'X';
        jogador[Ojogador].wins = 0;
        jogador[Ojogador].losses = 0;
        jogador[Ojogador].dificuldade = 0; 
        jogador[Ojogador].modo_jogo = 0; 
        Ojogador++;

        clear_screen();
        printf("Bem-vindo ao jogo da velha (Jogador vs Jogador)!\n");
        printf("Digite o nome do segundo jogador: ");
        scanf("%s", jogador[Ojogador].name);
        jogador[Ojogador].symbol = 'O';
        jogador[Ojogador].wins = 0;
        jogador[Ojogador].losses = 0;
        jogador[Ojogador].dificuldade = 0;
        jogador[Ojogador].modo_jogo = 0; 
        Ojogador++;

        jogar(&jogador[Ojogador - 2], &Ojogador - 1);
        break;    
            case 3:
                display_ranking(jogador, Ojogador);
                break;
            case 4:
                exibirSobre();
                break;
            case 5:
            save_ranking(jogador, Ojogador);
            break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (menu1 != 5);

    clear_screen();
    printf("Obrigado por jogar!\n");

    return 0;
}

void exibirMenu() {
    printf("\n===== MENU =====\n");
    printf("1. Jogar contra a Maquina\n");
    printf("2. Jogar contra outro Jogador\n");
    printf("3. Ranking\n");
    printf("4. Sobre\n");
    printf("5. Sair\n");
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

    if (jogador->modo_jogo == 0) {
        // Jogador vs Jogador
        int linha, coluna;
        printf("%s, sua vez! : ", jogador->name);
        
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
    }
    else {
        // Jogador vs Máquina
        if (jogador_atual == 'X') {
            printf("%s, sua vez!: ", jogador->name);
            int linha, coluna;

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
            } else if (jogador->dificuldade == 3) {
    int block = 0;
    int win = 0;
    int jogadaFeita = 0; // Variável para controlar se a máquina já fez uma jogada nesta rodada

    // Verificar se a máquina pode ganhar jogador->symbol
    if (!jogadaFeita) {
        for (i = 0; i < TAMANHO; i++) {
            for (j = 0; j < TAMANHO; j++) {
                if (tabuleiro[i][j] == ' ') {
                    tabuleiro[i][j] = 'O';
                    if (check_victory(tabuleiro, 'O')) {
                        // Fazer jogada de vitória
                        win = 1;
                        jogadaFeita = 1; // Definir como verdadeiro, pois a máquina já fez uma jogada
                        break;
                    }
                    tabuleiro[i][j] = ' ';
                }
            }
            if (win) {
                break;
            }
        }
    }

    // Verificar se a máquina precisa bloquear o jogador
    if (!win && !jogadaFeita) {
        for (i = 0; i < TAMANHO; i++) {
            for (j = 0; j < TAMANHO; j++) {
                if (tabuleiro[i][j] == ' ') {
                    tabuleiro[i][j] = 'X';
                    if (check_victory(tabuleiro, 'X')) {
                        // Fazer jogada de bloqueio
                        tabuleiro[i][j] = 'O';
                        block = 1;
                        jogadaFeita = 1; // Definir como verdadeiro, pois a máquina já fez uma jogada
                        break;
                    }
                    tabuleiro[i][j] = ' ';
                }
            }
            if (block) {
                break;
            }
        }
    }
    if (tabuleiro[0][0] == 'O' && tabuleiro[2][2] == 'X' && tabuleiro[2][0] == 'X' && tabuleiro[1][1] == 'X' && tabuleiro[0][2] == 'O' && tabuleiro[2][1] == 'O' && tabuleiro[1][0] == ' ' && tabuleiro[1][2] == ' ') {
        if (tabuleiro[1][0] == ' '){
        tabuleiro[1][0] = 'O';
        jogadaFeita = 1;
        
        }}
    if (tabuleiro[0][0] == 'X' && tabuleiro[2][2] == 'O' && tabuleiro[2][0] == 'X' && tabuleiro[1][1] == 'O' && tabuleiro[0][2] == ' ' && tabuleiro[2][1] == 'X' && tabuleiro[1][0] == 'O' && tabuleiro[1][2] == 'X') {
        if (tabuleiro[0][1] == ' '){
        tabuleiro[0][1] = 'O';
        jogadaFeita = 1;
        }
    }
    if (tabuleiro[0][0] == 'X' && tabuleiro[1][1] == 'O' && tabuleiro[2][1] == 'X' ) {
        if (tabuleiro[2][0] == ' '){
        tabuleiro[2][0] = 'O';
        jogadaFeita = 1;
        }
    }
    // Bloquear usuário quando ele pega duas diagonais
    if (!block && !win && !jogadaFeita) {
        if (tabuleiro[1][2] == 'X' && tabuleiro[2][0] == 'X' && tabuleiro[0][1] == 'X') {
            if (tabuleiro[2][2] == ' ') {
                tabuleiro[2][2] = 'O';
                jogadaFeita = 1;
            }
        } else if (tabuleiro[1][2] == 'X' && tabuleiro[2][0] == 'X') {
            jogadaFeita = 1;
            if (tabuleiro[2][2] == ' ') {
                tabuleiro[2][2] = 'O';
            }
        } else {
            // Verificar se o usuário pegou duas diagonais
            if (tabuleiro[0][0] == 'X' && tabuleiro[2][2] == 'X') {
                if (tabuleiro[0][1] == ' ') {
                    tabuleiro[0][1] = 'O';
                    jogadaFeita = 1;
                } else {
                    tabuleiro[1][2] = 'O';
                    jogadaFeita = 1;
                }
            } else if (tabuleiro[0][2] == 'X' && tabuleiro[2][0] == 'X') {
                if (tabuleiro[1][1] == ' ') {
                    tabuleiro[1][1] = 'O';
                    jogadaFeita = 1;
                } else {
                    tabuleiro[0][1] = 'O';
                    jogadaFeita = 1;
                }
            } else {
                // Fazer jogada padrão
                if (tabuleiro[1][1] == ' ') {
                    tabuleiro[1][1] = 'O';
                    jogadaFeita = 1;
                } else {
                    int diagonal[8][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}, {0, 1}, {1, 2}, {2, 1}, {1, 0}};
                    if (tabuleiro[0][0] == 'X' && tabuleiro[0][1] == ' ' && tabuleiro[1][0] == ' ')
                {
                    if (tabuleiro[1][2] == 'X' && tabuleiro[2][1] == 'X')
                    {
                        if (tabuleiro[2][0] == ' ')
                    {
                        tabuleiro[2][0] = 'O';
                        jogadaFeita = 1;
                    }
                    }
                }
                if (tabuleiro[2][1] == 'X' && tabuleiro[1][2] == 'X')
                {
                    if (tabuleiro[2][2] == ' ') {
                        tabuleiro[2][2] = 'O';
                        jogadaFeita = 1;
                }
                }
                else
                {
                    for (int k = 0; k < 4; k++) {
                        int x = diagonal[k][0];
                        int y = diagonal[k][1];
                        if (tabuleiro[x][y] == ' ') {
                            tabuleiro[x][y] = 'O';
                            jogadaFeita = 1;
                            break;
                        }
                    }
                }
            }
        }
    }}
    }



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
int compare_players(const void *a, const void *b) {
    const Player *player1 = (const Player *)a;
    const Player *player2 = (const Player *)b;

    // Comparar o número de vitórias (ordem decrescente)
    if (player1->wins > player2->wins) {
        return -1;
    } else if (player1->wins < player2->wins) {
        return 1;
    }

    // Se houver empate, comparar o número de derrotas (ordem crescente)
    if (player1->losses < player2->losses) {
        return -1;
    } else if (player1->losses > player2->losses) {
        return 1;
    }

    // Se houver empate novamente, comparar os nomes em ordem alfabética
    return strcmp(player1->name, player2->name);
}

void display_ranking(Player *jogador, int Ojogador) {
    if (Ojogador == 0) {
        printf("O ranking esta vazio.\n");
        return;
    }

    // Ordenar o vetor de jogadores
    qsort(jogador, Ojogador, sizeof(Player), compare_players);

    printf("===== RANKING =====\n\n");
    printf("NICKNAME\tVITORIAS\tDERROTAS\n");
    printf("---------\t--------\t--------\n");

    for (int i = 0; i < Ojogador; i++) {
        printf("%s\t\t%d\t\t\t%d\n", jogador[i].name, jogador[i].wins, jogador[i].losses);
    }
}

void load_ranking(Player *jogador, int *Ojogador) {
    FILE *file = fopen(ARQUIVO, "r+");
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

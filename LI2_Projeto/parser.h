#include "estado.h"

#define SIZE 10
#define TAM 50 

#define PLAYER "http://127.0.0.1/jogador.png"
#define ENEMY "http://127.0.0.1/inimigo.png"
#define WALL "http://127.0.0.1/pedra.png"
#define GOL "http://127.0.0.1/end.png"
#define GRASS "http://127.0.0.1/grass.png"
#define TREE "http://127.0.0.1/tree.png"
#define MORREU "http://127.0.0.1/morreu.png"

int score_atual, score1, score2, score3;

void parser();
ESTADO moveInimigo (ESTADO e, int indice);
ESTADO moveINIMIGOS (ESTADO e);
int posicao_valida(int x, int y);
int posicao_igual(POSICAO p, int x, int y);
int tem_jogador(ESTADO e, int x, int y);
int tem_inimigo(ESTADO e, int x, int y);
int tem_obstaculo(ESTADO e, int x, int y);
int tem_gol(ESTADO e, int x, int y);
int mov_impossivel(ESTADO e, int x, int y);
int movi_impossivel(ESTADO e, int x, int y);
int posicao_ocupada(ESTADO e, int x, int y);
ESTADO inicializar_inimigo(ESTADO e);
ESTADO inicializar_inimigos (ESTADO e, int num);
ESTADO inicializar_obstaculo(ESTADO e) ;
ESTADO inicializar_obstaculos (ESTADO e, int num);
ESTADO inicializar(int nivel);
void matar_jogador (ESTADO e);
void imprime_movimentos(ESTADO e);
void imprime_jogador(ESTADO e);
void imprime_inimigos(ESTADO e);
void imprime_obstaculos(ESTADO e);
void print_square (int X, int Y, int tam);
void print_image(int x, int y, int tam, char *name);
int retira_inimigo(ESTADO e);
ESTADO retira_pos(ESTADO e, int x, int y);
int score_board(ESTADO e);
void mata_monstros(ESTADO e);
int enemy_index(ESTADO e, int x, int y);
void imprime_movimento(ESTADO e,int dx, int dy);
void print_board();
int ler_score();
void put_score(int scores1, int scores2, int scores3);


















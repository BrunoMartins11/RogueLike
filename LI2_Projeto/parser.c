#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "estado.h"
#include <time.h>

int guarda_score=0;

/*ESTADO inicializar() {
	ESTADO e = {{0}};
	e.jog.x = 5;
	e.jog.y = 9;
	e.gol.x = 5;
	e.gol.y = 0;
	e.num_inimigos = 12;
	e.inimigo[0].x = (rand()%10);
	e.inimigo[0].y = (rand()%10);
	e.inimigo[1].x = (rand()%10);
	e.inimigo[1].y = (rand()%10);
	e.inimigo[2].x = (rand()%10);
	e.inimigo[2].y = (rand()%10);
	e.num_obstaculos = 21;
	e.obstaculo[0].x = 0;
	e.obstaculo[0].y = 1;
	e.obstaculo[1].x = 0;
	e.obstaculo[1].y = 2;
	return e;
}*/
int vida_jogador = 2;


ESTADO moveInimigo (ESTADO e, int indice) 
{
    int pos_X = e.inimigo[indice].x;
    int pos_Y = e.inimigo[indice].y;

    int x = 0, y = 0;
    
    do 
    {
        x = pos_X + rand() % 3 + (-1);
        y = pos_Y + rand() % 3 + (-1);

    } while (posicao_ocupada(e, x, y) == 1);

    e.inimigo[indice].x = x;
    e.inimigo[indice].y = y;

    return e;
}


ESTADO moveINIMIGOS (ESTADO e)
{
    	int i;
	ESTADO ne = e;

    for (i = 0 ; i < e.num_inimigos ; i++)
    {
        ne = moveInimigo(ne,i);
    }

    return ne;
}


/*----------------------------------------------------------------------------------------*/

int posicao_valida(int x, int y) {
	return x >= 0 && y >= 0 && x < SIZE && y < SIZE;
}

int posicao_igual(POSICAO p, int x, int y) {
	return p.x == x && p.y == y;
}

int tem_jogador(ESTADO e, int x, int y) {
	return posicao_igual(e.jog, x, y);
}

int tem_inimigo(ESTADO e, int x, int y) {
	int i;
	for ( i = 0; i < e.num_inimigos; i++)
		if ( posicao_igual(e.inimigo[i], x, y) )
			return 1;
	return 0;
}

int tem_obstaculo(ESTADO e, int x, int y) {
	int i;
	for ( i = 0; i < e.num_obstaculos; i++)
		if ( posicao_igual(e.obstaculo[i], x, y) )
			return 1;
	return 0;
}

int tem_gol(ESTADO e, int x, int y) {
	return posicao_igual(e.gol, x, y);
}

int mov_impossivel(ESTADO e, int x, int y){
	return tem_jogador(e, x, y) || tem_inimigo(e, x, y) || tem_obstaculo(e, x, y) || x < 0 || y < 0 || x >= SIZE || y >= SIZE;
}

int movi_impossivel(ESTADO e, int x, int y){
	return tem_jogador(e, x, y) || tem_obstaculo(e, x, y) || x < 0 || y < 0 || x >= SIZE || y >= SIZE;
}


int posicao_ocupada(ESTADO e, int x, int y) {
	return tem_jogador(e, x, y) || tem_inimigo(e, x, y) || tem_obstaculo(e, x, y) || tem_gol(e, x, y)
	                            || x < 0 || y < 0 || x >= SIZE || y >= SIZE;
}

ESTADO inicializar_inimigo(ESTADO e) {
	int x, y;
  do {
		x = rand() % SIZE;
		y = rand() % SIZE;
	} while (posicao_ocupada(e, x, y) );

	e.inimigo[(int)e.num_inimigos].x = x;
	e.inimigo[(int)e.num_inimigos].y = y;

  e.num_inimigos++;
	return e;
}

ESTADO inicializar_inimigos (ESTADO e, int num) {
	int i;
	for ( i = 0; i < num; i++)
		e = inicializar_inimigo(e);
	return e;
}

ESTADO inicializar_obstaculo(ESTADO e) {
	int x, y;
  do {
		x = rand() % SIZE;
		y = rand() % SIZE;
} while (posicao_ocupada(e, x, y) );

	e.obstaculo[(int)e.num_obstaculos].x = x;
	e.obstaculo[(int)e.num_obstaculos].y = y;

  e.num_obstaculos++;
	return e;
}

ESTADO inicializar_obstaculos (ESTADO e, int num) {
	int i;
	for ( i = 0; i < num; i++)
		e = inicializar_obstaculo(e);
	return e;
}

ESTADO inicializar(int nivel) {

	ESTADO e = {0};
	ler_score();
	e.nivel=nivel;
	e.score=score_atual;
	e.maxscore1=score1;
	e.maxscore2=score2;
	e.maxscore3=score3;
	e.gol.x = 0;
	e.gol.y = 0;
	e.jog.x = 9;
	e.jog.y = 9;
	e = inicializar_inimigos(e, 10 + nivel);
	e = inicializar_obstaculos(e, 20 + nivel);
	nivel++;
	return e;
}

void matar_jogador (ESTADO e){
	if (tem_inimigo(e, e.jog.x+1, e.jog.y)) vida_jogador--;
	if (tem_inimigo(e, e.jog.x, e.jog.y+1)) vida_jogador--;
	if (tem_inimigo(e, e.jog.x, e.jog.y-1)) vida_jogador--;
	if (tem_inimigo(e, e.jog.x-1, e.jog.y)) vida_jogador--;
	if (tem_inimigo(e, e.jog.x+1, e.jog.y+1)) vida_jogador--;
	if (tem_inimigo(e, e.jog.x+1, e.jog.y-1)) vida_jogador--;
	if (tem_inimigo(e, e.jog.x-1, e.jog.y+1)) vida_jogador--;
	if (tem_inimigo(e, e.jog.x-1, e.jog.y-1)) vida_jogador--;
	e.vida_jogador=vida_jogador;
	if (e.vida_jogador<=0){ 
		/**if(score_atual >= score1) score1=score_atual;*/
		score_atual=0;
		e =inicializar(0);
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(e));
		print_image(0,0,TAM*10,MORREU);
		printf("</a>\n");
		put_score(e.maxscore1, e.maxscore2, e.maxscore3);
	}
}


void imprime_movimentos(ESTADO e) {
	int dx, dy;

	for ( dx = -1; dx <= 1; dx++)
		for (dy = -1; dy <= 1; dy++)
			imprime_movimento(e, dx, dy);
}

void imprime_jogador(ESTADO e) {
	print_image(e.jog.x, e.jog.y, TAM, PLAYER);
	imprime_movimentos(e);
	matar_jogador(e);
}

/*ESTADO ler_estado(char *args) {
	if(strlen(args) == 0)
		return inicializar();
	return str2estado(args);
}*/

void imprime_inimigos(ESTADO e) {
	int i;
	for(i = 0; i < e.num_inimigos; i++)
		print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, ENEMY);

}

void imprime_obstaculos(ESTADO e) {
	int i;
	for(i = 0; i < e.num_obstaculos; i++)
		print_image(e.obstaculo[i].x, e.obstaculo[i].y, TAM, WALL);
}
/*--------------------------------------------------------------------------------------*/





void print_square (int X, int Y, int tam){
	char *color[]={"#444400", "#999900"};
	int idx = (X + Y) % 2;

	printf("<rect X=%d y=%d width=%d height=%d fill=\"%s\"/>\n", tam *X, tam *Y, tam, tam, color [idx]);
}


void print_image(int x, int y, int tam, char *name){
	printf("<image x=%d y=%d height=%d width=%d xlink:href=\"%s\"/>\n",x*tam,y*tam,tam,tam,name);
}


int retira_inimigo(ESTADO e) {
	int newnum_inimigos;
	newnum_inimigos= e.num_inimigos-1;
	return newnum_inimigos;
}

ESTADO retira_pos(ESTADO e, int x, int y){
	int r; 
	for(r=0; r < e.num_inimigos; r++){
		if((e.inimigo[r].x == x) && (e.inimigo[r].y == y)){
			e.inimigo[r].x = e.inimigo[e.num_inimigos-1].x;
			e.inimigo[r].y = e.inimigo[e.num_inimigos-1].y;
		}
	}
	
	return e;
}

int score_board(ESTADO e){
	score_atual= e.score;
	score1=e.maxscore1;
	score2=e.maxscore2;
	score3=e.maxscore3;
	if(score_atual >= score1)
		score1=score_atual;
	else{
			if(score_atual < score1 && score_atual >= score2)
				score2 = score_atual;
		 	else{
					if(score_atual < score2 && score_atual > score3)
						score3 = score_atual;}
			}
	e.maxscore1=score1;
	e.maxscore2=score2;
	e.maxscore3=score3;
	return score_atual;
}

void mata_monstros(ESTADO e){
	ESTADO ne=e;
	int jx = e.jog.x;
	int jy = e.jog.y;
	
	if(tem_inimigo(e,jx,jy+1)) {
		ne = retira_pos(e, jx, jy+1);
		ne.num_inimigos = retira_inimigo(e);
		ne.kills += 1;
		ne.score += 50;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(ne));
		print_image(jx, jy+1, TAM, ENEMY);
		printf("</a>\n");
	}
	
	if(tem_inimigo(e,jx+1,jy+1)) {
		ne = retira_pos(e, jx+1, jy+1);
		ne.num_inimigos = e.num_inimigos-1;
		ne.kills += 1;
		ne.score += 50;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(ne));
		print_image(jx+1, jy+1, TAM, ENEMY);
		printf("</a>\n");
	} 

	if(tem_inimigo(e,jx+1,jy)) {
		ne = retira_pos(e, jx+1, jy);
		ne.num_inimigos = e.num_inimigos-1;
		ne.kills += 1;
		ne.score += 50;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(ne));
		print_image(jx+1, jy, TAM, ENEMY);
		printf("</a>\n");
	} 

	
	if(tem_inimigo(e,jx+1,jy-1)){
		ne = retira_pos(e, jx+1, jy-1);
		ne.num_inimigos = e.num_inimigos-1;
		ne.kills += 1;
		ne.score += 50;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(ne));
		print_image(jx+1, jy-1, TAM, ENEMY);
		printf("</a>\n");
	}


	if(tem_inimigo(e, jx, jy-1)) {
		ne = retira_pos(e, jx, jy-1);
		ne.num_inimigos = e.num_inimigos-1;
		ne.kills += 1;
		ne.score += 50;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(ne));
		print_image(jx, jy-1, TAM, ENEMY);
		printf("</a>\n");
	} 


	if(tem_inimigo(e, jx-1, jy-1)){
		ne = retira_pos(e, jx-1, jy-1);
		ne.num_inimigos = e.num_inimigos-1;
		ne.kills += 1;
		ne.score += 50;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(ne));
		print_image(jx-1, jy-1, TAM, ENEMY);
		printf("</a>\n");
	}


	if(tem_inimigo(e, jx-1, jy)){
		ne = retira_pos(e, jx-1, jy);
		ne.num_inimigos = e.num_inimigos-1;
		ne.kills += 1;
		ne.score += 50;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(ne));
		print_image(jx-1, jy, TAM, ENEMY);
		printf("</a>\n");
	}


	if(tem_inimigo(e, jx-1, jy+1)) {
		ne = retira_pos(e, jx-1, jy+1);
		ne.num_inimigos = e.num_inimigos-1;
		ne.kills += 1;
		ne.score += 50;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(ne));
		print_image(jx-1, jy+1, TAM, ENEMY);
		printf("</a>\n");
	} 

}




int enemy_index(ESTADO e, int x, int y){
	int i, k;
	for(i=0;i<e.num_inimigos;i++){
		if(e.inimigo[i].x==x && e.inimigo[i].y==y)
			k=i;
			break;
	}
	return k;
}






void imprime_movimento(ESTADO e,int dx, int dy){
	ESTADO ne=e;
	int	x = e.jog.x + dx;
	int	y = e.jog.y + dy;
	

	if(x==e.gol.x && y==e.gol.y){
			ne.jog.x=x;
			ne.jog.y=y;
			ne = inicializar(++e.nivel);
			printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(ne));
			print_image(e.gol.x, e.gol.y, TAM, GOL);
			printf("</a>\n");
			}
	else{

		if(tem_inimigo(e, x, y)){
			mata_monstros(e);
			printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(ne));
			printf("</a>\n");
			}
		}

	if(mov_impossivel(e, x, y))
		return;
	
	ne.jog.x=x;
	ne.jog.y=y;
	ne=moveINIMIGOS(ne);

	if( x == e.gol.x && y == e.gol.y){
		ne = inicializar(++e.nivel);
		
	}

	ne.score = score_board(e);
	put_score(score1, score2, score3);
	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",estado2str(ne));
	print_image(x, y, TAM, GRASS);
	printf("</a>\n");
	}


void print_board(){
	int X, Y;
	for (Y=0;Y<SIZE;Y++)
		for (X=0; X<SIZE; X++)
			print_image(X, Y, TAM, GRASS);
}


void print_goal(ESTADO e) {
	print_image(e.gol.x, e.gol.y, TAM, GOL);
}




int ler_score() {
	int x;

  FILE * fp;

  fp = fopen("/var/www/html/scores/topscores.txt", "r");

  if (fp != NULL) {
    x=fscanf(fp, "%d,%d,%d", &score1, &score2, &score3);
    (void)x;

    fclose(fp);
  }

  return 0;
}

void put_score (int scores1, int scores2, int scores3) {

  FILE * fp;

  fp = fopen("/var/www/html/scores/topscores.txt", "w");

  if (fp == NULL) {
    perror("Nao existe");
    exit(1);
  }

  fprintf(fp, "%d,%d,%d", scores1, scores2, scores3);
  fclose(fp);

  return;
}


void parser(){
	ESTADO e;
	char *args;
	srand(time(NULL));
	args = getenv ("QUERY_STRING");
	if(strlen(args) == 0) e = inicializar(0);
	else e = str2estado(args);
	
	print_board();
	print_goal(e);
	imprime_inimigos(e);
	imprime_obstaculos(e);
	imprime_jogador(e);
}

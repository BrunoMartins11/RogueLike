#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O nº máximo de inimigos */
#define MAX_INIMIGOS		100

/** \brief O nº máximo de obstáculos */
#define MAX_OBSTACULOS		100



/** \brief Estrutura que armazena uma posição
*/
typedef struct posicao {
	char x;
	char y;
} POSICAO;


/**typedef struct inimigo {
	char num_enemy; 
	char vida_inimigo;
} INIMIGO;*/


/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {

	char nivel;
	/** A posição do jogador */
	POSICAO jog;
	/** Posiçao da porta objetivo*/
	POSICAO gol;
	/** O nº de inimigos */
	char num_inimigos;
	/** O nº de obstáculos */
	char num_obstaculos;
	/** Array com a posição dos inimigos */
	/**INIMIGO enemies[MAX_INIMIGOS];*/
	
	POSICAO inimigo[MAX_INIMIGOS];
	/** Array com a posição dos obstáculos */
	POSICAO obstaculo[MAX_OBSTACULOS];

	int score;

	int kills;

	char vida_jogador;

	int maxscore1;

	int maxscore2;

	int maxscore3;

} ESTADO;

/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/
char *estado2str(ESTADO e);

/**
\brief Função que converte uma string num estado 
@param argumentos Uma string contendo os argumentos passados à CGI
@returns O estado correspondente à string dos argumentos
*/
ESTADO str2estado(char *argumentos);

#endif

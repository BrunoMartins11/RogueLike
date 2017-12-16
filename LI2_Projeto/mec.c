#include <stdio.h>
#include "parser.h"


void print_header (){
	printf("content-type: text/html\n\n");
	printf("<head>\n");
	printf("<style type=\"text/css\">\n");
    printf("body {background-image: url(\"http://127.0.0.1/background.jpg\");}\n");
	printf("</style>\n");
	printf("</head>\n");
	printf("<body>\n");
	printf("<svg width=800 height=600>\n");
}


void print_background(){
	printf("<img src=\"fundo.jpg\" width=1000 height=800>");
	printf("</img>");
}


void print_table (){
	printf("<table width=400 border=1 bordercolor=green bgcolor=\"DBA901\" align=right>\n");
	printf("<tr>\n");
	printf("<td> ");
	printf("Top 3 scores ");
	printf("</td>\n");
	printf("</tr>\n");
	printf("<tr>\n");
	printf("<td> ");
	printf("Score Atual: %d ", score_atual);
	printf("</td>\n");
	printf("</tr>\n");
	printf("<tr>\n");
	printf("<td> ");
	printf("1st Place:  %d", score1);
	printf("</td>\n");
	printf("</tr>\n");
	printf("<tr>\n");
	printf("<td> ");
	printf("2nd Place: %d ", score2);
	printf("</td>\n");
	printf("</tr>\n");
	printf("<tr>\n");
	printf("<td> ");
	printf("3rd Place:  %d", score3);
	printf("</td>\n");
	printf("</tr>\n");
}

void print_footer(){
	printf("</svg>\n");
	printf("</body>\n");
}

int main(){
	print_header();
	/**print_background();*/
	parser();
	print_table();
	print_footer();
	return 0;
}

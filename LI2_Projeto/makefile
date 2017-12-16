CFLAGS=-Wall -Wextra -pedantic -O2 -g
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))
EXEC=mec

instalar: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)
	sudo cp $(EXEC) /usr/lib/cgi-bin
	sudo cp  jogador.png /var/www/html/
	sudo cp  inimigo.png /var/www/html/
	sudo cp  end.png /var/www/html/
	sudo cp  pedra.png /var/www/html/
	sudo cp  fundo.jpg /var/www/html/
	sudo cp  grass.png /var/www/html/
	sudo cp  tree.png /var/www/html/
	sudo cp  background.jpg /var/www/html/
	sudo cp  arvore.png /var/www/html/
	sudo cp  morreu.png /var/www/html/
	

limpar:
	rm $(EXEC) *.o

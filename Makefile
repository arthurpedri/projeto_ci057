    # AQUI VAI O NOME DO PROGRAMA EXECUTAVEL.
    # Substitua 'meuprog' abaixo pelo nome de seu programa
    PROG   = main
    # AQUI VAI A LISTA DOS MODULOS
    # Substitua 'modulo-1', 'modulo-2' pelo nome dos mÃ³dulos de seu programa
    # Para cada MÃ³dulo (par de arquivos '.c' e '.h') corresponde um arquivo 
    # '.o' na lista abaixo.
    OBJS   = $(PROG).o steamGames.o

    # Aqui vai o comando do compilador, com opcoes aplicaveis 
    # `a compilacao de qualquer modulo e `a geracao do codigo executavel
    CC     = gcc -g

%.o: %.c
	$(CC) -c $<

$(PROG):  $(OBJS)
	$(CC) -o $@ $^

limpa:
	@rm -f *~ *.bak

clean:   limpa
	@rm -f  $(PROG) *.o core a.out


#include <stdio.h>
#include <stdlib.h>
#include "steamGames.h"

int main (int argc, char *argv[])
{
/*	int a;*/
/*	int mudaA;*/
/*	int i;*/
/*	initnodoNull();*/
/*	ApAVL p = nodoNULL;*/
/*	for (i = 0; i < 5;i += 1)*/
/*	{*/
/*		scanf("%d", &a);*/
/*		p = insereAVL(p ,a ,&mudaA, a+1 );*/
/*		printf ("FInal do laço\n");*/
/*		imprimeAVL(p);*/
/*		printf("\n");*/
/*	}*/

/*	imprimeAVL(p);*/
/*	printf ("\n");*/

	int i;
	char c[15];
	initnodoNull234();
	Ap234 p = nodoNULL234;
	
	for (i = 0; i < 10; i += 1)
	{
		scanf("%s", c);
		p = insere234(p, c, i);
		imprime234(p);
		printf ("\n");
	}
	
	imprime234(p);
	//printf("qtdNome: %d, Nomes: %s, %s, %s", p->qtdNome, p->nome[0],p->nome[1],p->nome[2]);
	printf ("\n");

	return 0;
} 

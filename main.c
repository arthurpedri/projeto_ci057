#include <stdio.h>
#include <stdlib.h>
#include "steamGames.h"

int main (int argc, char *argv[])
{
	int a;
	int mudaA;
	int i;
	initnodoNull();
	printf ("%d", nodoNULL->codigo);
	ApAVL p = nodoNULL;
	for (i = 0; i < 5;i += 1)
	{
		scanf("%d", &a);
		p = insereAVL(p ,a ,&mudaA, a+1 );
	}

	imprimeAVL(p);
	return 0;
}

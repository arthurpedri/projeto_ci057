#include <stdio.h>
#include <stdlib.h>
#include "steamGames.h"

int main (int argc, char *argv[])
{
    initnodoNull();
    initnodoNull234();
    
    ApAVL avl = nodoNULL;
    Ap234 dtq = nodoNULL234;
    int i = 1, cint, *mudaA;
    char c[15], n[15], lixo[1000];
    
    FILE *registro;
    FILE *busca;
    
    registro = fopen(argv[1], "r");
    busca = fopen(argv[2], "r");
    
    fscanf (registro, "%s", c);
    cint = atoi(c);
    fscanf (registro, "%s", n);
    fgets (lixo, sizeof(lixo), registro);

    while (cint != 0)
    {
        avl = insereAVL(avl, cint, mudaA, i);
        dtq = insere234(dtq, n, i);
        fscanf (registro, "%s", c);
	cint = atoi(c);
        if (cint != 0)
        {
            fscanf (registro, "%s", n);
            fgets (lixo, sizeof(lixo), registro);
        }
	i++;
	printf("%d\n", i);
    }
    printf("Codigo:\n");
    imprimeAVL(avl);
    printf("\n\n");
    printf("Nome:\n");
    imprime234(dtq);
    printf("\n\n");
    
    char l[2], codestr[15], name[15], desc[300]; 
    int code, linha;    

    fscanf(busca, "%s", l);
    fscanf(busca, "%s", c);
    ApAVL auxAVL;
    Ap234 aux234;
    while (strcmp(l, "f") != 0)
    {
	if (strcmp(l, "c") == 0)
	{
	    cint = atoi(c);
	    auxAVL = buscaAVL(avl, cint);  
	    if (auxAVL != nodoNULL){
	    	rewind(registro);
	    	for (i=1;i < auxAVL->linhaRegistroAVL;i++)
	    	    fgets(lixo, sizeof(lixo), registro);
	    	fscanf (registro, "%s", codestr);
	    	code = atoi(codestr);
	    	fscanf (registro, "%s", name);
	    	fgets (desc, sizeof(desc), registro);
	    	printf("%d %s %s\n", code, name, desc);
	    }
	} 
	if (strcmp(l, "n") == 0)
	{
	   busca234 (dtq, c);
	   if (linhaVetor234 != 0) {
	   	rewind(registro);
		for (i=1; i < linhaVetor234;i++)
			fgets(lixo, sizeof(lixo), registro);
	   	fscanf (registro, "%s", codestr);
	   	code = atoi(codestr);
	   	fscanf (registro, "%s", name);
	   	fgets (desc, sizeof(desc), registro);
	   	printf("%s %d %s\n", name, code, desc);
	   }
	}
	fscanf(busca, "%s", l);
    	fscanf(busca, "%s", c);
    }   
} 

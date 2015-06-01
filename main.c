#include <stdio.h>
#include <stdlib.h>
#include "steamGames.h"

int main (int argc, char *argv[])
{
    initnodoNull();
    initnodoNull234();
    
    ApAVL avl = nodoNULL;
    Ap234 dtq = nodoNULL234;
    int i = 1, n, *mudaA;
    char c[15], lixo[1000];
    
    FILE *registro;
    FILE *busca;
    
    registro = fopen(argv[0], "r");
    // = fopen(argv[1], "r");
    
    fscanf (registro, "%d", c);
    fscanf (registro, "%s", n);
    fgets (lixo, 1000, registro);
    while (c != 0)
    {
        avl = insereAVL(avl, c, mudaA, i);
        dtq = insere234(dtq, n, i);
        fscanf (registro, "%d", c);
        if (!c)
        {
            fscanf (registro, "%s", n);
            fgets (lixo, 1000, registro);
        }
            
    }
    printf("Codigo:\n");
    imprimeAVL(avl);
    printf("\n\n");
    printf("Nome:\n");
    imprime234(dtq);
    printf("\n\n");
} 

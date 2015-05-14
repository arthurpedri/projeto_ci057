#include <stdio.h>
#include <stdlib.h>
#include "steamGames.h"

void initnodoNull ()
{
	nodoNULL = malloc(sizeof(tipoAVL));

}

ApAVL rotDir (ApAVL p)
{
	ApAVL q;
	q = p->esq;
	p->esq = q->dir;
	q->dir = p;
	return q;
}

ApAVL rotEsq (ApAVL p)
{
	ApAVL q;
	q = p->dir;
	p->dir = q->esq;
	q->esq = p;
	return q; 
}

ApAVL balanceiaAVL (ApAVL a) // Estava como ponteiro no Caderno. Não foi testado se é correto
{
	ApAVL f, neto;
	printf("%d, balanceia\n",a->codigo);
	if (a->bal == 2)
	{
		f = a->esq;
		if (f->bal == 1)
		{
			a = rotDir(a);
			a->bal = 0;
			f->bal = 0;
		}
		else
		{
			neto = f->dir;
			f = rotEsq(f);
			a = rotDir(a);
			if (neto->bal == 0)
				a->bal = f->bal = 0;
			else
				if (neto->bal > 0)
				{
					a->bal = 1;
					f->bal = 0;
				}
				else
				{
					a->bal = 0;
					f->bal = 1;
				}
			neto->bal = 0;
		}
	}	
	else
	{
		f=a->dir;
		if (f->bal == - 1)
		{
			a = rotEsq(a);
			printf("a->%d  f->%d\n", a->codigo, f->codigo);
			a->bal = 0;
			f->bal = 0;
			//a->esq->bal = 0;
		}
		else
		{
			neto = f->esq;
			f = rotDir(f);
			a = rotEsq(f);
			if (neto->bal == 0)
				a->bal = f->bal;
			else
			{
				if (neto->bal > 0)
				{
					a->bal = 0;
					f->bal = -1;
				}
				else
				{
					a->bal = 1; //Checar no caderno da Anna -- Olhei na página
					f->bal = 0; //Checar no caderno da Anna -- Olhei na página
				}
				neto->bal = 0; // Não tem isso no caderno, mas na página diz que tem.. 
			}
		}
	}
	printf("Final do Balanceia\n");
	imprimeAVL(a);
	printf ("\n");
	return a;
}

ApAVL criaNodoAVL (int codigo, int linha)
{
	ApAVL aux = malloc (sizeof(tipoAVL));
	if(!aux)
		return NULL;
	aux->codigo = codigo;
	aux->linhaRegistroAVL = linha;
	aux->bal = 0;
	aux->esq = nodoNULL;
	aux->dir = nodoNULL;
	return aux;
}

ApAVL insereAVL (ApAVL p, int codigo, int *mudaA, int linha)
{
	if (p == nodoNULL)
	{
		*mudaA = TRUE;
		return criaNodoAVL(codigo, linha);
	}
	if (codigo == p->codigo)
	{
		*mudaA = FALSE;
		return p;
	}	
	if (codigo < p->codigo)
	{
		p->esq = insereAVL(p->esq, codigo, mudaA, linha);
		if (*mudaA)
		{
			p->bal++;
			if (p->bal == 2)
				p = balanceiaAVL (p);
			if (p->bal == 0)
				*mudaA = FALSE;
		}
	}	
 		else
	{
		p->dir = insereAVL(p->dir, codigo, mudaA, linha);
		if (*mudaA) 
		{
			p->bal--;
			if (p->bal == -2)
				p = balanceiaAVL(p);
			if (p->bal == 0)
				*mudaA = TRUE;
		}
	}
	return p;
}
void imprimeAVL (ApAVL p)
{
	if (p==nodoNULL)	
		return;
	printf (" (%d %d", p->codigo, p->bal);
	imprimeAVL(p->esq);
	imprimeAVL(p->dir);
	printf (")");
	
}

ApAVL buscaAVL (ApAVL p, int codigo)
{
	if (p==nodoNULL)
		return nodoNULL;
	if (codigo == p->codigo)
		return p;
	if (codigo < p->codigo)
		return buscaAVL(p->esq, codigo);
	else
		return buscaAVL(p->dir, codigo);
} 	

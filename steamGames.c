#include <stdio.h>
#include <stdlib.h>
#include "steamGames.h"

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

ApAVL balanceiaAVL (ApAVL *a) // Estava como ponteiro no Caderno. Não foi testado se é correto
{
	ApAVL f, neto;
	if (*a->bal == 2)
	{
		f = *a->esq;
		if (f->bal == 1)
		{
			*a = rotDir(*a);
			*a->bal = 0;
			f->bal = 0;
		}
		else
		{
			neto = f->dir;
			f = rotEsq(f);
			*a = rotDir(*a);
			if (neto->bal == 0)
				*a->bal = f->bal = 0;
			else
				if (neto->bal > 0)
				{
					*a->bal = 1;
					f->bal = 0;
				}
				else
				{
					*a->bal = 0;
					f->bal = 1;
				}
			neto->bal = 0;
		}
	}	
	else
	{
		f=*a->dir;
		if (f->bal == - 1)
		{
			*a = rotEsq(*a);
			*a->bal = 0;
			f->bal = 0;
		}
		else
		{
			neto = f->esq;
			f = rotDir(f);
			*a = rotEsq(f);
			if (netp->bal == 0)
				*a->bal = f->bal;
			else
			{
				if (neto->bal > 0)
				{
					*a->bal = 0;
					f->bal = -1;
				}
				else
				{
					*a->bal = ; //Checar no caderno da Anna
					f->bal = ; //Checar no caderno da Anna
				}
			}
		}
	}
}

ApAVL criaNodoAVL (int codigo, int linha)
{
	ApAVL aux = malloc (sizeof(no));
	if(!aux)
		return NULL;
	aux->codigo = codigo;
	aux->linhaRegistroAVL = linha;
	aux->bal = 0;
	aux->esq = nodoNULL;
	aux->dir = nodoNULL;
	return aux;
}

ApAVL	insereAVL		(ApAVL p, int codigo, int *mudaA, int linha)
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
				balanceiaAVL (&p);
			if (p->bal == 0)
				*mudaA = FALSE;
		}
		else
		{
			p->dir = insereAVL(p->dir, codigo, mudaA, linha);
			if (*mudaA)
			{
				p->bal--;
				if (p->bal == -2)
					balanceiaAVL(&p);
				if (p->bal == 0)
					*mudaA = TRUE;
			}
		}
	}
	return p;
}
void imprimeAVL (ApAVL p)
{
	printf ("%d", p->codigo);
}

ApAVL buscaAVL (ApAVL p, int codigo) // Falta inserir o imprimeAVL da maneira que está na descrição
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

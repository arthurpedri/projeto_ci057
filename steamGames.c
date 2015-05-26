#include <stdio.h>
#include <stdlib.h>
#include "steamGames.h"

void initnodoNull ()
{
	nodoNULL = malloc(sizeof(tipoAVL));
	nodoNULL->codigo = 0;
	nodoNULL->linhaRegistroAVL = 0;
	nodoNULL->bal = 0;
	nodoNULL->esq = nodoNULL;
	nodoNULL->dir = nodoNULL;
}

void initnodoNull234 ()
{
	nodoNULL234 = malloc(sizeof(tipo234));
	for (int i = 0; i < 4; ++i)
		nodoNULL->Ap[i] = nodoNULL;
	nodoNULL234->nome = calloc(45, sizeof(char));
	nodoNULL234->linhaRegistro234 = calloc(3, sizeof(int));
	nodoNULL234->qtdNome = 0;
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
			a->dir->bal = 0;
			//f->bal = 0;
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
		if (f->bal == 0)
		{
			a = rotDir(a);
			a->bal = 1;
			f->bal = -1;
		}
		else
		{
			if (f->bal == -1)
			{
				a = rotEsq(a);
				a->esq->bal = 0;
				a->bal = 0;
			}
			else
			{
				neto = f->esq;
				f = rotDir(f);
				a = rotDir(a);
				if (neto->bal == 0)
					a->bal = f->bal = 0;
				else
				{
					if (neto->bal > 0)
					{
						a->bal = 0;
						f->bal = - 1;
					}
					else
					{
						a->bal = 1;
						f->bal = 0;
					}
				}	
				neto->bal = 0;
			}
		}
		/*if (f->bal == - 1)
		{
			a = rotEsq(a);
			//printf("a->%d  f->%d\n", a->codigo, f->codigo);
			a->bal = 0;
			//f->bal = 0;
			a->esq->bal = 0;
		}
		else
		{
			neto = f->esq;
			f = rotDir(f);
			printf("f =%d\n", f->codigo);
			a = rotEsq(a);
			printf("a =%d\n", a->codigo);
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
		}*/
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

// ------------ 2-3-4 ---------------- //

void busca234 (Ap234 ap, char *nome) {
	Ap234 q = ap;                 
	if (q!=nodoNULL) {
		for (i=0; i<qtdNome; i++){
			if (strcmp(q.nome[i], nome) == 0)
				return q;
			else if (strcmp (q.nome[i], nome) < 0)
				return busca234 (q.Ap[i],nome);
		}
		return busca234 (q.Ap[qtdNome], nome);
	}
}

Ap234 criaNodo234 (char *nome, int reg) {
	Ap234 novo = malloc (sizeof(tipo234));
	if (!novo) return NULL;
	novo->nome[0] = nome;
	for (int i = 0; i < 4; ++i)
		novo->Ap[i] = nodoNULL;
	novo->qtdNome = 0;
	novo->linhaRegistro234[0] = reg;
	return novo;
}

Ap234 insere234	(Ap234 ap, char *nome, int reg){
	if (ap == nodoNULL234){
		return criaNodo234(nome,reg);
	}
	// compara os nomes
	if (ap->qtdNome == 3)
	{
		//caso do pai ser raiz sozinha
		ap = split234(ap, nodoNULL234);
	}

	int i = 0;
	while ((strcmp(nome, ap->nome[i]) > 0) && (i < qtdNome))
		i++;

	if (ap->Ap[i]->qtdNome == 3)
	{
		ap = split234(ap, ap->Ap[i]);
	}
	return insere234(ap->Ap[i], nome, reg);
}

Ap234 split234 (Ap234 pai, Ap234 filho){  //errado com certyze
	Ap234 p1 = criaNodo234(pai->nome[0], pai->linhaRegistro234[0]);  
	p1->Ap[0] = pai->Ap[0];
    p1->Ap[1] = pai->Ap[1];
    Ap234 p2 = criaNodo234(pai->nome[2], pai->linhaRegistro234[2]);
    p2->Ap[0] = pai->Ap[2];
    p2->Ap[1] = pai->Ap[3];
    if (filho == nodoNULL234) // Se for Raiz
    {
    	Ap234 raiz = criaNodo234(pai->nome[1], pai->linhaRegistro234[1]);
    	raiz->Ap[0] = p1;
    	raiz->Ap[1] = p2;
    	pai = raiz;
    }
    else
    {
    	int i = 0;
    	int j = 0;
		while( (strcmp(filho->nome[1], pai->nome[i]) < 0) && (i < pai->qtdNome)) // Procurando a posição no pai
			i++;
		i--; // Ele vai sair sempre uma posição na frente
		
		
		for (j = pai->qtdNome - 1; j > i; j -= 1)
		{
			//Deslocar os nomes para direita
		}
    }

}

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
	int i;
	nodoNULL234 = malloc(sizeof(tipo234));
	for (i = 0; i < 4; ++i)
		nodoNULL234->Ap[i] = nodoNULL234;
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
	if (a->bal == 2)
	{
		f = a->esq;
		if (f->bal == 0)
		{
			a->bal = -1;
			f->bal = 1;
			a = rotDir(a);
		}
		else
		{
			if (f->bal == 1)
			{
				a->bal = 0;
				f->bal = 0;
				a = rotDir(a);
			}
			else
			{
				neto = f->dir;
				if (neto->bal == 0)
				{
					a->bal = 0;
					f->bal = 0;
				} 
				else
				{
					if (neto->bal > 0)
					{
						a->bal = -1;
						f->bal = 0;
					}
					else
					{
						a->bal = 0;
						f->bal = 1;
					}
					neto->bal = 0;	
				}
				f = rotEsq(f);
				a = rotDir(a);
			}
		}
	}	
	else 
	{
		f=a->dir;
		if (f->bal == 0)
		{
			a->bal = 1;
			f->bal = -1;
			a = rotEsq(a);
		}
		else
		{
			if (f->bal == -1)
			{
				f->bal = 0;
				a->bal = 0;
				a = rotEsq(a);
			}
			else
			{
				neto = f->esq;
				if (neto->bal == 0)
				{
					a->bal = 0;
					f->bal = 0;
				}
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
					neto->bal = 0;
				}	
				f = rotDir(f);
				a = rotEsq(a);
			}
		}
	}
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
		mudaA = TRUE;
		return criaNodoAVL(codigo, linha);
	}
	if (codigo == p->codigo)
	{
		mudaA = FALSE;
		return p;
	}	
	if (codigo < p->codigo)
	{
		p->esq = insereAVL(p->esq, codigo, mudaA, linha);
		if (mudaA)
		{
			p->bal++;
			if (p->bal == 2)
				p = balanceiaAVL (p);
			if (p->bal == 0)
				mudaA = FALSE;
		}
	}	
 		else
	{
		p->dir = insereAVL(p->dir, codigo, mudaA, linha);
		if (mudaA) 
		{
			p->bal--;
			if (p->bal == -2)
				p = balanceiaAVL(p);
			if (p->bal == 0)
				mudaA = FALSE;
		}
	}
	return p;
}
void imprimeAVL (ApAVL p)
{
	if (p==nodoNULL)	
		return;
	printf (" (%d", p->codigo);
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

void	imprime234		(Ap234 p)
{
	int i;
	if (p==nodoNULL234)	
		return;
	
	printf(" (%s", p->nome[0]);
	for (i = 1; i < p->qtdNome; i += 1)
	{
		printf(";%s", p->nome[i]);
	}

	for (i = 0; i <= p->qtdNome; i += 1)
	{
		imprime234(p->Ap[i]);
	}
		
	printf (")");

}



void busca234 (Ap234 ap, char *nome) {
	Ap234 q = ap;
	int i;                 
	if (q != nodoNULL234) {
		for (i=0; i< q->qtdNome; i++){
			if (strcmp(q->nome[i], nome) == 0){
				linhaVetor234 = q->linhaRegistro234[i];
				return;
			}
			else if (strcmp (q->nome[i], nome) < 0){
				busca234(q->Ap[i], nome);
				return;
			}
		}
		busca234(q->Ap[q->qtdNome], nome);
		return;
	}
	linhaVetor234 = 0;
	return;
}

Ap234 criaNodo234 (char *nome, int reg) {
	Ap234 novo = malloc (sizeof(tipo234));
	int i;
	if (!novo) return NULL;
	strcpy (novo->nome[0], nome);
	for (i = 0; i < 4; ++i)
		novo->Ap[i] = nodoNULL234;
	novo->qtdNome = 1;
	novo->linhaRegistro234[0] = reg;
	return novo;
}

Ap234 insere234	(Ap234 ap, char *nome, int reg){
	if (ap == nodoNULL234){
		return criaNodo234(nome,reg);
	}
	int i = 0;
	if (ap->qtdNome == 3) // É raiz
	{
		ap = split234(nodoNULL234, ap);
		i = 0;

		while ((strcmp(nome, ap->nome[i]) >= 0) && (i < ap->qtdNome))
			i++;

		ap->Ap[i] = insere234(ap->Ap[i], nome, reg);
	}
	else
	{
    	int flag = TRUE;
    	for (i = 0; i <= ap->qtdNome; i += 1) // Tem que saber se é folha.
    	{
    		if (ap->Ap[i] != nodoNULL234)
    			flag = FALSE;
    	}
    	
    	if(!flag) //Não é folha
    	{
    		i = 0;
    		while ((strcmp(nome, ap->nome[i]) >= 0) && (i < ap->qtdNome))// procura onde deve ser inserido
    			i++;
    
    		if (ap->Ap[i]->qtdNome == 3) // ve se onde vai ser inserido precisa ser quebrado
    		{
    			ap = split234(ap, ap->Ap[i]);
        		while ((strcmp(nome, ap->nome[i]) >= 0) && (i < ap->qtdNome))
        			i++;
    		}
    		
    		ap->Ap[i] = insere234(ap->Ap[i], nome, reg);
    	}
    	else // É folha
    	{
			int j;
			i = 0;
			while ((strcmp(nome, ap->nome[i]) >= 0) && (i < ap->qtdNome)) // Onde vai inserir
				i++;
			for (j = ap->qtdNome - 1; j + 1 > i; j -= 1) // Deslocar nomes
			{
				strcpy(ap->nome[j+1], ap->nome[j]);
				ap->linhaRegistro234[j+1] = ap->linhaRegistro234[j];
			}
			strcpy(ap->nome[i], nome);
			ap->linhaRegistro234[i] = reg;
			ap->qtdNome++;
    	}	
    }	
	return ap;
}

Ap234 split234 (Ap234 pai, Ap234 filho){  //errado com certyze
	Ap234 p1 = criaNodo234(filho->nome[0], filho->linhaRegistro234[0]);  
	p1->Ap[0] = filho->Ap[0];
    p1->Ap[1] = filho->Ap[1];
    Ap234 p2 = criaNodo234(filho->nome[2], filho->linhaRegistro234[2]);
    p2->Ap[0] = filho->Ap[2];
    p2->Ap[1] = filho->Ap[3];
    if (pai == nodoNULL234) // Se for Raiz
    {
    	Ap234 raiz = criaNodo234(filho->nome[1], filho->linhaRegistro234[1]);
    	raiz->Ap[0] = p1;
    	raiz->Ap[1] = p2;
    	pai = raiz;
    }
    else
    {
    	int i = 0;
    	int j = 0;
		while( (strcmp(filho->nome[1], pai->nome[i]) >= 0) && (i < pai->qtdNome)) // Procurando a posição no pai
			i++;
		
		
		for (j = pai->qtdNome - 1; j + 1 > i; j -= 1) // Deslocar nomes e registros
		{
			strcpy(pai->nome[j+1], pai->nome[j]);
			pai->linhaRegistro234[j+1]= pai->linhaRegistro234[j];
		}
		
		strcpy(pai->nome[i], filho->nome[1]); // insere nome
		pai->linhaRegistro234[i] = filho->linhaRegistro234[1]; // insere reg
		pai->qtdNome++;
		
		pai->Ap[i] = p1;
		pai->Ap[i+1] = p2; 	
		
    }
    free (filho);
    return pai;

}

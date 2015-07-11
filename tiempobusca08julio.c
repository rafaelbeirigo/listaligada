#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RAND_SEED 17
#define MAX (int)1e10
#define CANT_TESTE (int)1e6

FILE *f1;

struct Nodo{
    int chave;
    int  info;
    struct Nodo* prox;
};

typedef struct Nodo nodo;
void lst_imprime(nodo* l);
nodo* busca_enc(int x,nodo* l, nodo *(*ant));
nodo* insercao_enc(int x,nodo *l);
nodo* remocion_enc(int x,nodo *l);

nodo* cria(void)
{
    nodo *l;
    l=(nodo *)malloc(sizeof(nodo));
    l->chave=0;
    l->info=0;
    l->prox=NULL;

    return l;
}

int main(void)
{
    nodo *l,*pont,*ant;
    int i,n,qtd, num;
    time_t inicio_conta,fim_conta,total;
    FILE *f;
    
    srand(RAND_SEED);
    
    l=cria();
    
    for (qtd = 1; qtd <= MAX; qtd *= 2)
      {
        // completa a lista
        for (i = 0; i < (qtd / 2); ++i)
          l=insercao_enc(rand() % MAX,l);

        time(&inicio_conta);
        for (i = 1; i <= CANT_TESTE; ++i)
          {
            num = rand() % MAX;
            l=insercao_enc(num,l);
            l=remocion_enc(num,l);
          }
        time(&fim_conta);
        total = fim_conta - inicio_conta;
        printf("qtd: %9d   total: %9d \n",qtd,total);

        f = fopen("resultadolistasimple08julio.txt", "a");
        fprintf(f, "%d\t%d\n", qtd, total);
        fclose(f);
      }
    getchar();
    return 0;
}

nodo* busca_enc(int x,nodo* l,nodo *(*ant))
{
    nodo *pont,*ptr;
    //int x;
    *ant=l;
    pont=NULL;
    ptr=l->prox;
    while(ptr!=NULL)
    {
        if (ptr->chave<x)
        {
            *ant=ptr;
            ptr=ptr->prox;
        }
        else
        {
            if(ptr->chave==x)
            {
                pont=ptr;
            }
            ptr=NULL;
        }
    }

    return pont;
}

nodo* insercao_enc(int x,nodo *l)
{
    nodo *ant,*pt,*pont;
    pont=busca_enc(x,l,&ant);
    if(pont==NULL)
    {
        pt=(nodo*)malloc(sizeof(nodo));
        pt->chave=x;
        pt->prox=ant->prox;
        ant->prox=pt;
    }
    else
    {
//        printf("%d elemento ja esta na tabela\n", x);
    }

    return l;
}

nodo* remocion_enc(int x,nodo *l)
{
    nodo *ant,*pont;
    int valor_recuperado;
    pont=busca_enc(x,l,&ant);
    if(pont!=NULL)
    {
        ant->prox=pont->prox;
        free(pont);
    }
//    else
//        printf("%d nodo no si encuentra en la tabela\n",x);
    return l;
}

void lst_imprime(nodo* l)
{
    nodo* p;
    for (p=l->prox;p!=NULL;p=p->prox)
        printf("chave=%d\n",p->chave);
    printf("\n");
}

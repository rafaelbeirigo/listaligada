#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND_SEED 17
#define MAX (int)1e10
#define CANT_TESTE (int)1e4
#define INTERVALO (int)1e4

typedef struct no {
  int info;
  int chave;
  struct no *ant;
  struct no *post;
} no;

typedef struct listadupla {
  no *cab;
} listadupla;

no * novoNo();
listadupla * novalistadupla();
void insere(listadupla *l, int chave);
void imprime(listadupla *l);
void imprimereverso(listadupla *l);
no * busca(listadupla *l, int chave);
void deleta(listadupla *l, int chave);

int main() {
  listadupla *l;
  int i, n;
  time_t inicio, fim, total;
  FILE *f;

  l = novalistadupla();
  
  for (n = 0; n <= MAX; ++n) {
    insere(l, n);

    if (n % INTERVALO == 0) {
      time(&inicio);
      for (i = 1; i <= CANT_TESTE; ++i) {
        deleta(l, n);
        insere(l, n);
      }
      time(&fim);
      total = fim - inicio;
      printf("n: %9d   total: %9d \n", n, total);

      f = fopen("resultadolistaduplaparan.txt", "a");
      fprintf(f, "%d\t%d\n", n, total);
      fclose(f);
    }
  }

  return 0;
}

listadupla * novalistadupla() {
  listadupla *l;

  l = (listadupla *)malloc(sizeof(listadupla));
  l->cab = (no *)malloc(sizeof(no));

  l->cab->chave = l->cab->info = -1;
  l->cab->ant = l->cab->post = l->cab;

  return l;
}

no * novoNo() {
  no *pNovo;

  pNovo = (no *)malloc(sizeof(no));

  pNovo->chave = 0;
  pNovo->info = 0;
  pNovo->ant = NULL;
  pNovo->post = NULL;
  
  return pNovo;
}

no * busca_dup(listadupla *l, int x) {
  no *ptlista, *ultimo, *pont, *ret;

  ptlista = l->cab;

  ultimo = ptlista->ant;

  if (x == ultimo->chave) {
    return ultimo;
  }
  else {
    if (x < ultimo->chave) {
      pont = ptlista->post;
      while (pont->chave < x)
        pont = pont->post;
      return pont;
    }
  }

  return ptlista;
}

void insere(listadupla *l, int x) {
  no *pont, *anterior, *pt, *ptlista;

  ptlista = l->cab;
  
  pont = busca_dup(l, x);

  if (pont == ptlista || pont->chave != x) {
    anterior = pont->ant;
    pt = novoNo();

    pt->chave = x;
    pt->ant = anterior;
    pt->post = pont;

    anterior->post = pt;
    pont->ant = pt;
  }
}

void deleta(listadupla *l, int x) {
  no *pont, *anterior, *posterior, *ptlista;

  ptlista = l->cab;
  
  pont = busca_dup(l, x);

  if (pont != ptlista && pont->chave == x) {
    anterior = pont->ant;
    posterior = pont->post;

    anterior->post = posterior;
    posterior->ant = anterior;
    
    free(pont);
  }
}

void imprime(listadupla *l) {
  no *pAux;
  
  for (pAux = l->cab->post; pAux != l->cab; pAux = pAux->post)
    printf("%3d", pAux->chave);
  printf("\n");
}

void imprimereverso(listadupla *l) {
  no *pAux;
  
  for (pAux = l->cab->ant; pAux != l->cab; pAux = pAux->ant)
    printf("%3d", pAux->chave);
  printf("\n");
}

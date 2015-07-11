#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND_SEED 17
#define QTD_TESTE (int)1e2

typedef struct no {
  int info;
  int chave;
  struct no *ant;
  struct no *post;
} no;

typedef struct listadupla {
  no *pri;
} listadupla;

no * novoNo(int chave);
listadupla * novalistadupla();
void insere(listadupla *l, int chave);
void imprime(listadupla *l);
no * busca(listadupla *l, int chave);
void deleta(listadupla *l, int chave);

int main() {
  listadupla *l;
  int i, num, qtd;
  time_t inicio, fim, total;
  FILE *f;

  srand(RAND_SEED);

  l = novalistadupla();

  for (qtd = 1; qtd <= (int)1e9; qtd *= 2) {
    for (i = 0; i < qtd; ++i)
      insere(l, rand() % qtd);

    time(&inicio);
    for (i = 0; i < QTD_TESTE; ++i) {
      num = rand() % qtd;
      insere(l, num);
      deleta(l, num);
    }
    time(&fim);
    total = fim - inicio;

    printf("qtd: %d   total: %d\n", qtd, total);

    f = fopen("results.txt", "a");
    fprintf(f, "%d\t%d\n", qtd, total);
    fclose(f);
  }

  return 0;
}

listadupla * novalistadupla() {
  listadupla *l;

  l = (listadupla *)malloc(sizeof(listadupla));
  l->pri = (no *)malloc(sizeof(no));

  l->pri->chave = l->pri->info = -1;
  l->pri->ant = l->pri->post = l->pri;

  return l;
}

no * novoNo(int chave) {
  no *pNovo;

  pNovo = (no *)malloc(sizeof(no));

  pNovo->chave = chave;
  pNovo->ant = NULL;
  pNovo->post = NULL;
  
  return pNovo;
}

no * busca(listadupla *l, int chave) {
  no *pAnt, *pUlt;

  pUlt = l->pri->ant;
  if (pUlt == l->pri || pUlt->chave < chave)
    return pUlt;

  for (pAnt = l->pri;
       pAnt->post != l->pri && pAnt->post->chave <= chave;
       pAnt = pAnt->post);
    
  return pAnt;
}

void insere(listadupla *l, int chave) {
  no *pNovo;
  no *pAnt;

  pAnt = busca(l, chave);

  if (pAnt != l->pri && pAnt->chave == chave) return;
    
  pNovo = novoNo(chave);

  pNovo->ant = pAnt;
  pNovo->post = pAnt->post;

  pAnt->post->ant = pNovo;
  pAnt->post = pNovo;
}

void deleta(listadupla *l, int chave) {
  no *pDel, *pAnt, *pPost;

  pDel = busca(l, chave);
  
  if (pDel == l->pri || pDel->chave != chave) return;
    
  pAnt = pDel->ant;
  pPost = pDel->post;

  pAnt->post = pPost;
  pPost->ant = pAnt;

  free(pDel);
}

void imprime(listadupla *l) {
  no *pAux;
  
  for (pAux = l->pri->post; pAux != l->pri; pAux = pAux->post)
    printf("%3d", pAux->chave);
  printf("\n");
}

void imprimereverso(listadupla *l) {
  no *pAux;
  
  for (pAux = l->pri->ant; pAux != l->pri; pAux = pAux->ant)
    printf("%3d", pAux->chave);
  printf("\n");
}

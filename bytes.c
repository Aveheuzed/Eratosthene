#include <stdlib.h>
#include <stdio.h>

#define USLI unsigned long int
#define USC unsigned char

#define LEN_PREM_BLOCK 256 // max : 256 (must fit in an USC)

static inline void nouveau_premier(USLI *const totprem, const USLI p) {
  (*totprem)++;
  printf("%lu\n",p);
}

static inline void flush(USC *const nombres, const USLI bornesup, const USLI premiers[], USC *const nb_prem) {
  USLI prod, inombres;
  const USLI stop_inombres=bornesup/premiers[*nb_prem-1];
  USC iprem;
  for (inombres=bornesup/premiers[0]; inombres>stop_inombres; inombres--) {
    if (!nombres[inombres]) {
      for (iprem=0; iprem<(*nb_prem); iprem++) {
        prod = premiers[iprem]*inombres;
        if (prod<bornesup) {
          nombres[prod]=1;
        }
      }
    }
  }
  for (; inombres>=premiers[0]; inombres--) { //fastpath : no "if"
    if (!nombres[inombres]) {
      for (iprem=0; iprem<*nb_prem; iprem++) {
        nombres[premiers[iprem]*inombres]=1;
        }
      }
    }
  *nb_prem=0;
}

int main() {
  USLI bornesup, maxsearch=1, totprem=0;
  USLI i, p;
  USLI running_prem[LEN_PREM_BLOCK];
  printf("Borne supérieure (exclue) : ");
  scanf("%lu", &bornesup);
  USC *const nombres = calloc(bornesup, sizeof(USC));
  if (nombres == NULL) {
    printf("Pas assez de mémoire !\n");
    exit(EXIT_FAILURE);
  }
  USC n_prem_block=0;

  while ((++maxsearch)*maxsearch <= bornesup);

  for (p=2; p<maxsearch; p++) {
    if ((n_prem_block && (running_prem[0]*running_prem[0] <= p)) ||
        (n_prem_block == LEN_PREM_BLOCK))
      flush(nombres, bornesup, running_prem, &n_prem_block);

    if (!nombres[p]) {
      nouveau_premier(&totprem, p);
      running_prem[n_prem_block++] = p;
    }
  }

  if (n_prem_block) flush(nombres, bornesup, running_prem, &n_prem_block);

  for (; p<bornesup; p++) {
    if (!nombres[p]) nouveau_premier(&totprem, p);
  }

  free(nombres);
  printf("Il y a %lu nombres premiers inférieurs à %lu\n",
  totprem, bornesup);
}

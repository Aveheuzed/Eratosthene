#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


static inline void nouveau_premier(uintmax_t *const totprem, const uintmax_t p) {
  (*totprem)++;
  printf("%lu\n",p);
}

static inline void flush(uint8_t *const nombres, const uintmax_t bornesup, const uintmax_t premiers[], uint8_t *const nb_prem) {
  uintmax_t prod, inombres;
  const uintmax_t stop_inombres=bornesup/premiers[*nb_prem-1];
  uint8_t iprem;
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
  uintmax_t bornesup, maxsearch=1, totprem=0;
  uintmax_t i, p;
  uintmax_t running_prem[UINT8_MAX];
  printf("Borne supérieure (exclue) : ");
  scanf("%lu", &bornesup);
  uint8_t *const nombres = calloc(bornesup, sizeof(uint8_t));
  if (nombres == NULL) {
    printf("Pas assez de mémoire !\n");
    exit(EXIT_FAILURE);
  }
  uint8_t n_prem_block=0;

  while ((++maxsearch)*maxsearch <= bornesup);

  for (p=2; p<maxsearch; p++) {
    if ((n_prem_block && (running_prem[0]*running_prem[0] <= p)) ||
        (n_prem_block == UINT8_MAX))
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

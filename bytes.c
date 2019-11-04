#include <stdlib.h>
#include <stdio.h>

#define USLI unsigned long int
#define USC unsigned char

static inline void nouveau_premier(USLI *const totprem, const USLI p) {
  (*totprem)++;
  printf("%lu\n",p);
}

int main() {
  USLI bornesup, maxsearch=1, totprem=0;
  USLI i, p;
  printf("Borne supérieure (exclue) : ");
  scanf("%lu", &bornesup);
  USC *const nombres = calloc(bornesup, sizeof(USC));
  if (nombres == NULL) {
    exit(1);
  }

  while ((++maxsearch)*maxsearch <= bornesup);
  maxsearch--;

  for (p=2; p<maxsearch; p++) {
    if (!nombres[p]) {
      nouveau_premier(&totprem, p);
      for (i=bornesup/p; i>=p; i--){
        if (!nombres[i]) {
          nombres[p*i]++;
          // on sait maintenant qu'on ne passe qu'une unique fois sur chaque nombre
          // non premier, d'où le ++ au lieu du =1 (supposé plus lent)
        }
      }
    }
  }
  for (; p<bornesup; p++) {
    if (!nombres[p]) nouveau_premier(&totprem, p);
  }
  free(nombres);
  printf("Il y a %lu nombres premiers inférieurs à %lu\n",
  totprem, bornesup);
}

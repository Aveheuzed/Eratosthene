#include <stdlib.h>
#include <stdio.h>

#define USLI unsigned long int
#define USC unsigned char


int main() {
  USLI bornesup, maxsearch=1, p, totprem=0, i;
  USC *nombres = NULL;
  printf("Borne supérieure (exclue) : ");
  scanf("%lu", &bornesup);
  nombres = malloc(bornesup*sizeof(USC));
  if (nombres == NULL) {
    exit(1);
  }

  do {
    maxsearch ++;
  } while (maxsearch*maxsearch <= bornesup);
  maxsearch --;

  for (i=0; i<bornesup; i++) {
    nombres[i] = 0;
  }

  for (p=2; p<=maxsearch; p++) {
    if (nombres[p]) {
      continue;
    }
    for (i=p*p; i<bornesup; i+=p){
      nombres[i] = 1;
    }
  }
  for (p=2; p<bornesup; p++) {
    if (nombres[p] == 0) {totprem++;printf("%lu\n",p);}
  }
  free(nombres);
  printf("Il y a %lu nombres premiers inférieurs à %lu\n",
  totprem, bornesup);
}

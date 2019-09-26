#include <stdlib.h>
#include <stdio.h>

#define usli unsigned long int
#define usc unsigned char


int main() {
  usli bornesup, maxsearch=0, p, totprem=0;
  usc *nombres = NULL;
  printf("Borne supérieure (exclue) : ");
  scanf("%ld", &bornesup);
  do {
    maxsearch ++;
  } while (maxsearch*maxsearch <= bornesup);
  maxsearch --;
  nombres = malloc(bornesup*sizeof(usc));
  if (nombres == NULL) {
    exit(1);
  }
  for (int i=0; i<maxsearch; i++) {
    nombres[i] = 0;
  }

  for (p=2; p<maxsearch; p++) {
    if (nombres[p]) {
      continue;
    }
    for (int i=p*p; i<bornesup; i+=p){
      nombres[i] = 1;
    }
  }
  for (p=2; p<bornesup; p++) {
    if (nombres[p] == 0) {totprem++;}
  }
  free(nombres);
  printf("Il y a %ld nombres premiers inférieurs à %ld\n",
  totprem, bornesup);
}

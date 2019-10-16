#include <stdlib.h>
#include <stdio.h>

#define USLI unsigned long int
#define TYPEOFTABLE unsigned int //USLI pose problème, je sais pas pq...
#define BITSPERSLOT (sizeof(TYPEOFTABLE)*8)

static inline void write1(TYPEOFTABLE table[], const USLI base, const TYPEOFTABLE offset) {
  table[base] |= (1<<offset);
}

static inline TYPEOFTABLE read(TYPEOFTABLE table[], const USLI base, const TYPEOFTABLE offset) {
  return (table[base]) &(1<<offset);
}

static inline USLI eval_tablesize(USLI bornesup) {
  USLI result = bornesup / BITSPERSLOT;
  if (bornesup%BITSPERSLOT) {result++;}
  return result;
}


int main() {
  USLI bornesup, maxsearch=1, /*p,*/ totprem=0, i, q, m;
  TYPEOFTABLE *nombres = NULL;

  TYPEOFTABLE r, p;

  printf("Borne supérieure (exclue) : ");
  scanf("%lu", &bornesup);
  USLI imax = eval_tablesize(bornesup); //nombre d'éléments de la table

  nombres = malloc(imax*sizeof(TYPEOFTABLE));
  if (nombres == NULL) {
    printf("Pas assez de mémoire !\n");
    exit(1);
  }

  for (i=0; i<imax; i++) {
    nombres[i] = 0;
  }
  write1(nombres, 0, 0); write1(nombres, 0, 1);
  for (q=0; q<imax; q++) {
    for (r=0; r<BITSPERSLOT; r++) {
      if (!read(nombres, q, r)) {
        totprem++;
        printf("%lu\n",BITSPERSLOT*q+r);

        // (q*BITSPERSLOT+r)**2
        m = q*q*BITSPERSLOT + 2*q*r + (r*r)/BITSPERSLOT;
        p = (r*r)%BITSPERSLOT;

        while (m<imax) {
          write1(nombres, m, p);
          p += r;
          m += q; // p += q*BITSPERSLOT+r
          m += p/BITSPERSLOT;
          p %= BITSPERSLOT;
        }
      }
    }
  }
  printf("Il y a %lu nombres premiers inférieurs à %lu\n",
  totprem, BITSPERSLOT*imax);
}
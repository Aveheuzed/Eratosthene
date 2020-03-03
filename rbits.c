#include <stdlib.h>
#include <stdio.h>

#define USLI unsigned long int
#define USC unsigned char

#define TYPEOFTABLE unsigned int //USLI pose problème, je sais pas pq...
#define BITSPERSLOT (sizeof(TYPEOFTABLE)*8)

typedef struct nombre nombre;
struct nombre {
  USLI byte;
  USC bit;
};

static inline void write1(TYPEOFTABLE *const table, const USLI byte, const TYPEOFTABLE mask) {
  table[byte] |= mask;
}

static inline TYPEOFTABLE read(TYPEOFTABLE *const table, const USLI byte, const TYPEOFTABLE mask) {
  return (table[byte]) & mask;
}

static inline USLI eval_tablesize(const USLI bornesup) {
  USLI result = bornesup / BITSPERSLOT;
  return ++result; // pour gérer l'éventuel reste de la division
}

USLI imax, totprem=0;

static inline USLI convert(const nombre nbr) {
  return (nbr.bit*imax)+(nbr.byte);
}

static inline void nouveau_premier(const nombre p) {
  totprem++;
  printf("%lu\n",convert(p));
}

int main() {
  USLI bornesup/*, totprem=0*/;
  USC maxsearch=1;
  nombre p,i;

  printf("Borne supérieure (exclue) : ");
  scanf("%lu", &bornesup);
  imax = eval_tablesize(bornesup); //nombre d'éléments de la table

  TYPEOFTABLE mask, mask2;
  TYPEOFTABLE *const nombres = calloc(imax, sizeof(TYPEOFTABLE));
  if (nombres == NULL) {
    printf("Pas assez de mémoire !\n");
    exit(EXIT_FAILURE);
  }

  while ((++maxsearch)*maxsearch*imax <= BITSPERSLOT);

  write1(nombres, 0, 1); write1(nombres, 1, 1); // stand for 0 and 1
  for (p.bit=0, mask=1; p.bit<=maxsearch; p.bit++, mask<<=1) {
    for (p.byte=0; p.byte<imax; p.byte++) {
      if (!read(nombres, p.byte, mask)) {
        nouveau_premier(p);

        i.bit = p.bit*p.bit*imax + 2*p.byte*p.bit + (p.byte*p.byte)/imax;
        mask2 = 1<<i.bit;
        i.byte = (p.byte*p.byte)%imax;

        while (i.bit<BITSPERSLOT) {
          write1(nombres, i.byte, mask2);
          i.byte += p.byte;
          i.bit += p.bit + i.byte/imax;
          mask2 <<= p.bit + i.byte/imax;
          i.byte %= imax;
        }
      }
    }
  }
  for(; p.bit<BITSPERSLOT; p.bit++, mask<<=1) {
    for(p.byte=0;p.byte<imax;p.byte++) {
      if (!read(nombres, p.byte, mask)) {
        nouveau_premier(p);
      }
    }
  }
  free(nombres);
  printf("Il y a %lu nombres premiers inférieurs à %lu\n",
  totprem, BITSPERSLOT*imax);
}

#include <stdlib.h>
#include <stdio.h>

#define USLI unsigned long int
#define USC unsigned char

#define TYPEOFTABLE unsigned int //USLI pose problème, je sais pas pq...
#define BITSPERSLOT (sizeof(TYPEOFTABLE)*8)

typedef struct nombre nombre;
struct nombre {
  USLI base;
  USC offset;
};

static inline void write1(TYPEOFTABLE *const table, const nombre nbr) {
  table[nbr.base] |= (1<<nbr.offset);
}

static inline TYPEOFTABLE read(const TYPEOFTABLE *const table, const nombre nbr) {
  return (table[nbr.base]) & (1<<nbr.offset);
}

static inline USLI eval_tablesize(const USLI bornesup) {
  USLI result = bornesup / BITSPERSLOT;
  return ++result; // pour gérer l'éventuel reste de la division
}

static inline USLI convert(const nombre nbr) {
  return (nbr.base*BITSPERSLOT)+(nbr.offset);
}

static inline void nouveau_premier(USLI *const totprem, const nombre p) {
  (*totprem)++;
  printf("%lu\n",convert(p));
}

int main() {
  USLI bornesup, totprem=0, maxsearch=1;
  nombre p,i;

  printf("Borne supérieure (exclue) : ");
  scanf("%lu", &bornesup);
  USLI imax = eval_tablesize(bornesup); //nombre d'éléments de la table

  TYPEOFTABLE *const nombres = calloc(imax, sizeof(TYPEOFTABLE));
  if (nombres == NULL) {
    printf("Pas assez de mémoire !\n");
    exit(EXIT_FAILURE);
  }

  while ((++maxsearch)*maxsearch*BITSPERSLOT <= imax);

  write1(nombres, (nombre) {0, 0}); write1(nombres, (nombre) {0, 1});
  for (p.base=0; p.base<=maxsearch; p.base++) {
    for (p.offset=0; p.offset<BITSPERSLOT; p.offset++) {
      if (!read(nombres, p)) {
        nouveau_premier(&totprem, p);

        i.base= p.base*p.base*BITSPERSLOT + 2*p.base*p.offset + (p.offset*p.offset)/BITSPERSLOT;
        i.offset = (p.offset*p.offset)%BITSPERSLOT;

        while (i.base<imax) {
          write1(nombres, i);
          i.offset += p.offset;
          i.base += p.base;
          i.base += i.offset/BITSPERSLOT;
          i.offset %= BITSPERSLOT;
        }
      }
    }
  }
  for(;p.base<imax;p.base++) {
    for(p.offset=0; p.offset<BITSPERSLOT; p.offset++) {
      if (!read(nombres, p)) {
        nouveau_premier(&totprem, p);
      }
    }
  }
  free(nombres);
  printf("Il y a %lu nombres premiers inférieurs à %lu\n",
  totprem, BITSPERSLOT*imax);
}

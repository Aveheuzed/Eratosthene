#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


typedef struct nombre nombre;
struct nombre {
  uintmax_t base;
  uint8_t offset;
};

static inline void write1(uint32_t *const table, const nombre nbr) {
  table[nbr.base] |= (1<<nbr.offset);
}

static inline uint32_t read(const uint32_t *const table, const nombre nbr) {
  return (table[nbr.base]) & (1<<nbr.offset);
}

static inline uintmax_t eval_tablesize(const uintmax_t bornesup) {
  uintmax_t result = bornesup / 32;
  return ++result; // pour gérer l'éventuel reste de la division
}

static inline uintmax_t convert(const nombre nbr) {
  return (nbr.base*32)+(nbr.offset);
}

static inline void nouveau_premier(uintmax_t *const totprem, const nombre p) {
  (*totprem)++;
  printf("%lu\n",convert(p));
}

int main() {
  uintmax_t bornesup, totprem=0, maxsearch=1;
  nombre p,i;

  printf("Borne supérieure (exclue) : ");
  scanf("%lu", &bornesup);
  uintmax_t imax = eval_tablesize(bornesup); //nombre d'éléments de la table

  uint32_t *const nombres = calloc(imax, sizeof(uint32_t));
  if (nombres == NULL) {
    printf("Pas assez de mémoire !\n");
    exit(EXIT_FAILURE);
  }

  while ((++maxsearch)*maxsearch*32 <= imax);

  write1(nombres, (nombre) {0, 0}); write1(nombres, (nombre) {0, 1});
  for (p.base=0; p.base<=maxsearch; p.base++) {
    for (p.offset=0; p.offset<32; p.offset++) {
      if (!read(nombres, p)) {
        nouveau_premier(&totprem, p);

        i.base= p.base*p.base*32 + 2*p.base*p.offset + (p.offset*p.offset)/32;
        i.offset = (p.offset*p.offset)%32;

        while (i.base<imax) {
          write1(nombres, i);
          i.offset += p.offset;
          i.base += p.base;
          i.base += i.offset/32;
          i.offset %= 32;
        }
      }
    }
  }
  for(;p.base<imax;p.base++) {
    for(p.offset=0; p.offset<32; p.offset++) {
      if (!read(nombres, p)) {
        nouveau_premier(&totprem, p);
      }
    }
  }
  free(nombres);
  fprintf(stderr, "Il y a %lu nombres premiers inférieurs à %lu\n",
  totprem, 32*imax);
}

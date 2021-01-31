#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


typedef struct nombre nombre;
struct nombre {
  uintmax_t byte;
  uint8_t bit;
};

static inline void write1(uint32_t *const table, const uintmax_t byte, const uint32_t mask) {
  table[byte] |= mask;
}

static inline uint32_t read(uint32_t *const table, const uintmax_t byte, const uint32_t mask) {
  return (table[byte]) & mask;
}

static inline uintmax_t eval_tablesize(const uintmax_t bornesup) {
  uintmax_t result = bornesup / 32;
  return ++result; // pour gérer l'éventuel reste de la division
}

uintmax_t imax, totprem=0;

static inline uintmax_t convert(const nombre nbr) {
  return (nbr.bit*imax)+(nbr.byte);
}

static inline void nouveau_premier(const nombre p) {
  totprem++;
  printf("%lu\n",convert(p));
}

int main() {
  uintmax_t bornesup/*, totprem=0*/;
  uint8_t maxsearch=1;
  nombre p,i;

  printf("Borne supérieure (exclue) : ");
  scanf("%lu", &bornesup);
  imax = eval_tablesize(bornesup); //nombre d'éléments de la table

  uint32_t mask, mask2;
  uint32_t *const nombres = calloc(imax, sizeof(uint32_t));
  if (nombres == NULL) {
    printf("Pas assez de mémoire !\n");
    exit(EXIT_FAILURE);
  }

  while ((++maxsearch)*maxsearch*imax <= 32);

  write1(nombres, 0, 1); write1(nombres, 1, 1); // stand for 0 and 1
  for (p.bit=0, mask=1; p.bit<=maxsearch; p.bit++, mask<<=1) {
    for (p.byte=0; p.byte<imax; p.byte++) {
      if (!read(nombres, p.byte, mask)) {
        nouveau_premier(p);

        i.bit = p.bit*p.bit*imax + 2*p.byte*p.bit + (p.byte*p.byte)/imax;
        mask2 = 1<<i.bit;
        i.byte = (p.byte*p.byte)%imax;

        while (i.bit<32) {
          write1(nombres, i.byte, mask2);
          i.byte += p.byte;
          i.bit += p.bit + i.byte/imax;
          mask2 <<= p.bit + i.byte/imax;
          i.byte %= imax;
        }
      }
    }
  }
  for(; p.bit<32; p.bit++, mask<<=1) {
    for(p.byte=0;p.byte<imax;p.byte++) {
      if (!read(nombres, p.byte, mask)) {
        nouveau_premier(p);
      }
    }
  }
  free(nombres);
  fprintf(stderr, "Il y a %lu nombres premiers inférieurs à %lu\n",
  totprem, 32*imax);
}

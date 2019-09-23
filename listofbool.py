#!/usr/bin/env python3
from time import perf_counter_ns

import numpy as np

bornesup = int(input("Borne supérieure de recherche (exclue) : "))
maxsearch = int(bornesup**0.5)

nombres = np.zeros(bornesup, dtype='bool') # False pour "pas barré"
p = 2

a = perf_counter_ns()

while p < maxsearch :
    nombres[p**2::p] = True
    p += 1
    p = np.argmin(nombres[p:])+p

b = perf_counter_ns()

print(f"Il y a {bornesup-nombres.sum()-2:_} nombres premiers < {bornesup:_}")
# -2 parce qu'on a inclus 0 et 1 dans le comptage
print(f"Temps d'exécution : {b-a:_} ns")
del nombres

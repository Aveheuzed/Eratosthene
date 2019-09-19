#!/usr/bin/env python3
from time import perf_counter_ns

def ceil(D, d) :
    # returns ceil(D/d), without using floats
    q,r = divmod(D, d)
    if not r :
        return q
    return q+1

bornesup = int(input("Borne supérieure de recherche (exclue) : "))
maxsearch = int(bornesup**0.5)

nombres = [False,] * bornesup # False pour "pas barré"
p = 2

a = perf_counter_ns()

while p < maxsearch :
    nombres[p**2::p] = (True,) * ceil(bornesup-p**2,p)
    p = nombres.index(False, p+1)

b = perf_counter_ns()

print(f"Il y a {nombres.count(False)-2:_} nombres premiers < {bornesup:_}")
# -2 parce qu'on a inclus 0 et 1 dans le comptage
print(f"Temps d'exécution : {b-a:_} ns")
del nombres

#!/usr/bin/env python3
from time import perf_counter

def ceil(D, d) :
    # returns ceil(D/d), without using floats
    q,r = divmod(D, d)
    if not r :
        return q
    return q+1

bornesup = int(input("Borne supérieure de recherche (exclue) : "))
maxsearch = int(bornesup**0.5)

a = perf_counter()

nombres = [False,] * bornesup # False pour "pas barré"
p = 2

while p < maxsearch :
    nombres[p**2::p] = (True,) * ceil(bornesup-p**2,p)
    p = nombres.index(False, p+1)


print(f"Il y a {nombres.count(False)-2:_} nombres premiers < {bornesup:_}")
b = perf_counter()
# -2 parce qu'on a inclus 0 et 1 dans le comptage
print(f"Temps d'exécution : {b-a:_.2} s")
del nombres

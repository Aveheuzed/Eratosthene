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

nombres = 0 # bits à 0 pour "pas barré"

a = perf_counter()

p = 2
while p < maxsearch :
   bigmask = 0
   for shiftnp in (1<<(n*p) for n in range(p, ceil(bornesup,p)) if not (nombres & (1<<n))) :
       bigmask |= shiftnp
   nombres |= bigmask

   p += 1
   while nombres & 1<<p :
       p += 1

b = perf_counter()

nprem = 0
i = 2
nombres >>= 2
while i < bornesup :
    if not (nombres & 1) :
        nprem += 1
    nombres >>= 1
    i += 1
print(f"Il y a {nprem:_} nombres premiers < {bornesup:_}")
print(f"Temps d'exécution : {b-a:_.2} s")
del nombres

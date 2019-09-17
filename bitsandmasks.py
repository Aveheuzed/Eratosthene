#!/usr/bin/env python3
from time import clock

bornesup = int(input("Borne supérieure de recherche (exclue) : "))
maxsearch = int(bornesup**0.5)

a = clock()

nombres = 0 # bits à 0 pour "pas barré"

p = 2
while p < maxsearch:
    if nombres & 1<<p :
        p += 1
        continue
    bigmask = 0
    for n in range(p, bornesup) :
        if n*p >= bornesup :
            break
        if nombres & (1<<n) :
            continue
        bigmask |= 1<<(n*p)
    nombres |= bigmask
    p += 1

b = clock()
print(b-a)
#print(bin(nombres))
#print(*[x for x in range(2, bornesup) if not (nombres & 1<<x)], sep="\n")

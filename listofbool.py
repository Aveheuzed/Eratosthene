#!/usr/bin/env python3
from time import clock

bornesup = int(input("Borne supérieure de recherche (exclue) : "))
maxsearch = int(bornesup**0.5)

a = clock()

nombres = [False,] * bornesup # False pour "pas barré"

p = 2
while p < maxsearch:
    if nombres[p] :
        p += 1
        continue
    for n, barred in enumerate(nombres[p:], p) :
        if n*p >= bornesup :
            break
        if barred :
            continue
        nombres[n*p] = True
    p += 1

b = clock()
print(b-a)
#print(*[i for i,x in enumerate(nombres[2:], 2) if not x], sep="\n")

#!/usr/bin/env python3

"""Alexis Masson, octobre 2019"""


from random import sample


def _ceil(D, d) :
    # returns math.ceil(D/d), without using floats
    q,r = divmod(D, d)
    if not r :
        return q
    return q+1

def tous_premiers(bornesup:int)->tuple :
    """Recherche et renvoie le tuple des nombres premiers, ordonnés,
    strictement inférieurs à bornesup"""
    maxsearch = int(bornesup**0.5)
    nombres = [False,] * bornesup # False pour "pas barré"
    p = 2

    while p < maxsearch :
        pp = p*p
        nombres[pp::p] = (True,) * _ceil(bornesup-pp,p)
        p = nombres.index(False, p+1)

    # Approche bibliothèque standard, pour le fun :
    #return tuple(itertools.filterfalse(functools.partial(operator.getitem, nombres), range(2, bornesup)))
    return tuple(i for i,x in enumerate(nombres) if not x)[2:]

def premiers_aleatoires(n:int, bornesup:int)->list :
    """Renvoie une liste de n nombres premiers distincts inférieurs à bornesup"""
    return sample(tous_premiers(bornesup), n)


__all__ = ["tous_premiers", "premiers_aleatoires"]

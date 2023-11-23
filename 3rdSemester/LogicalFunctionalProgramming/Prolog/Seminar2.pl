suma([], 0).
suma([H|T], S):-
    suma(T, TS),
    S is H+TS.

sumaC([], C, C).
sumaC([H|T], C, R):-
    C1 is C+H,
    sumaC(T, C1, R).


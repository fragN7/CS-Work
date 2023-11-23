%list_min(L: list, Min: number)
%   list_min(l2...ln, min1, min) if min1 < l1
%   list_min(l2...ln, l1, min) otherwise
%list_min(i, i, o), (i, i, i)

list_min([H|T], Min) :-
    list_min(T, H, Min).

list_min([], Min, Min).
list_min([H|T], Min0, Min) :-
    Min1 is min(H, Min0),
    list_min(T, Min1, Min).

%position(L: list, I: number, R: number, RES: list)
%   insert i in res, position(l2...ln, I + 1, R, RES)  if l1 = R
%   position(l2...ln, I + 1, R, RES)  otherwise
%
%position(i, i, i, o), (i, i, i, i)

position([H|T], I, R, RES) :- 
    H =:= R,
    I1 is I + 1,
    position(T, I1, R, [I1|RES]).

position([H|T], I, R, RES) :-
    H =\= R,
    I1 is I + 1,
    position(T, I1, R, RES).

%get_result(L:list, RList: list)
%get_result(i, o) (i, i)

get_result(L, RList) :-
    R is 10000,
    list_min(L, R),
    position(L, 1, R, RList).

test_get_result():-
    get_result([10, -14, 12, 13, -14], [2, 5]),
    get_result([1, 2, 3, 4, 5], [1]),
    get_result([1, 2, 3, 2, 1, 2, 3, 2], [1, 5]),
    get_result([1, 1, 1, 1, 1], [1, 2, 3, 4, 5]).



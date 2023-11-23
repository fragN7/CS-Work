predecesor([], _, []) :-!.
predecesor([0], 1, [9]) :-!.
predecesor([N], 0, [NR]) :-
    NR is N - 1,!.
predecesor([0|T], 1, [9|R]) :-
    predecesor(T, 1, R), !.
predecesor([H|T], 0, [HR|R]) :-
    predecesor(T, C, R),
    HR is H - C.

lead([],[]).
lead([H|T],[H|T]) :-
    H =\= 0.
lead([0|T],T2) :-
    lead(T,T2).

%Mathematical model:
%[] if n == 0
%List if Head is not 0
%l2....ln otherwise
%
%lead(List, List)
%lead(i,o)

main_predecesor(L,R):-
    predecesor(L, _, R1),
    lead(R1, R).


%Mathematical model:
%predecesor(n, c):
%   [] if n == 0
%   [9] if n == 1 and l1 == 0
%   [l1 - 1] if n == 1 and l1 != 0
%   9 + predecesor(l2....ln, 1) if c == 1 and l1 == 0
%   (l1 - c) + predecesor(l2....ln, c), otherwise
%
%predecesor(List, Number, List)
%predecesor(i, i, o)

test_predecesor() :-
    main_predecesor([1, 3, 6, 0, 0], [1, 3, 5, 9, 9]),
    main_predecesor([1, 2, 3],[1, 2, 2]),
    main_predecesor([1, 0], [9]),
    main_predecesor([2], [1]),
    main_predecesor([1],  []).

heter_list([], []).
heter_list([H|T], [HR|R]):-
    is_list(H), !,
    main_predecesor(H, HR),
    heter_list(T, R).
heter_list([H|T], [H|R]):-
    heter_list(T, R).

get_lists([], []).
get_lists([H|T], R):-
    is_list(H), !,
    get_lists(T, H).

new_output(L, LIS):-
    heter_list(L, R),
    get_lists(R, LIS).

%new_heter_list([H|T], _, _):-
%    not(is_list(H)), !,
%    new_heter_list(T, _, H).

%Mathematical model:
%heter_list(l1....ln, list):
%    [] if list empty
%    consecutive(l1, [], []) + heter_list(l2....ln) if l1 is list
%    l1 + heterlist(l2....ln) otherwise
%
%heter_list(List, List)
%heter_list(i, o)


test_heter_list() :-
    heter_list([1, [2, 3], 4, 5, [6, 7, 8], 9], [1, [2, 2], 4, 5, [6, 7, 7], 9]).












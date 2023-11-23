paranthesis('(').
paranthesis(')').


%check(l1....ln, c):
%    check(l2....ln, c+1) if l1 = '('
%    check(l2....ln, c-1) if l1 = ')' and c > 0
%
%check(L: list, C: number)
%check(i, i)


check([], 0).
check([H|T], C) :-
    H == '(',
    C1 is C + 1,
    check(T, C1).

check([H|T], C) :-
    H == ')',
    C > 0,
    C1 is C - 1,
    check(T, C1).

%combinations(n, i, c):
%    c, if i = n
%    combinations(n, i + 1, paranthesis(x) + c), otherwise
%
%combinations(N: number, I: number, C: list, R: list)
%combinations(i, i, i, o)


combinations(N, N, C, C) :- !.
combinations(N, I, C, R) :-
    paranthesis(X),
    N1 is I + 1,
    combinations(N, N1, [X|C], R).

%solution(N: number, R: list)
%solution(i, o)

solution(N, R) :-
    combinations(N, 0, [], R),
    check(R, 0).

%allsolutions(N: number, R: list)
%allsoultions(i, o)

allsolutions(N, R) :-
    findall(R1, solution(N, R1), R).

test_allsolutions() :-
    allsolutions(2, ['(', ')']),
    allsolutions(1, []),
    allsolutions(0, []).

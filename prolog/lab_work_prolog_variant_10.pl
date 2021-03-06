
%  -------- 10.Два лікарські препарати взаємозамінні , якщо вони мають одні й ті самі
% показання та протипоказання до застосування.
% ?Drug1, ?Drug2
is_equivalent(D1, D2):-
   cures(D1, Disease1),
   cures(D2, Disease2),
   equal(Disease1, Disease2),
   contraindicates(D1, ContraDiase1),
   contraindicates(D1, ContraDiase2),
   equal(ContraDiase1, ContraDiase2),
   D1 \= D2,
   !.

% ?Name, ?Disease
contraindicates(drug1, [disease4]).
contraindicates(drug3, [disease4]).
contraindicates(drug2, [disease1]).
contraindicates(drug4, [disease5]).

% ?Name, ?Disease
cures(drug1, [disease1, disease2, disease3]).
cures(drug2, [disease3]).
cures(drug3, [disease1, disease2, disease3]).
cures(drug4, [disease1, disease2, disease3, disease4]).



% ?List1, ?List2
isSubset([], _).
isSubset([H|T], Y) :-
    member(H, Y),
    select(H,Y,Z),
    isSubset(T,Z).

% ?List1, ?List2
equal(List1, List2) :-
    isSubset(List1, List2),
    isSubset(List2, List1).


% -------- ЗАВДАННЯ No 2 Представлення родинних зв’язків
% 10.Вітчим.

% ?Who ?Whom 
is_felt(Person, Child):-
    dif(Person, Child),
	is_parent(SomeMother, Child),
    is_female(SomeMother),
    (marriage(Person, SomeMother) ; marriage(SomeMother, Person)),
	not(is_parent(Person, Child)),
    !.
    

% ?ParentName, ?ChildName
is_parent(person2, vasia).
is_parent(person1, vasia).

is_parent(person4, petia).
is_parent(petia_father, petia).

% ?ParentName, 
is_female(person2).
is_female(person4).

% ?Person1, ?Person2
marriage(person2, somefelt).
marriage(person4, petia_father).


% -------- ЗАВДАННЯ No 3 Арифметичні операції. Організація циклу

% ?Variable, ?Result
public_func(X, Result) :-
    func(X, 1, Result).

% ?Variable, ?Counter, ?Result
func(X, N, Result) :-
    X > 100, N =< 5,
    N1 is N + 1,
    func(X, N1, Result1),
    Result is (N * X - 2) + Result1.
func(_, 6, 0).
func(_, _, 5).

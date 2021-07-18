% Завдання

% 1 Представлення фраз Пролог-програми
% 2 Представлення родинних відношень
% 3 Арифметичні операції. Организація циклу
% 4 Розрахунок значень арифметичних функцій у заданому інтервалі значень Х
% 5 Обробка списків
% 6 Перестановка частин списків
% 7 Обробка матриці
% 8 Контрольна робота
% 9 Використання предикатів збору
% 10 Обробка записів БД типу recorded database


% ЗАВДАННЯ No 1 Представлення фраз Пролог-програми

% 2. Двоє дітей одного віку можуть ходити 
% в одну групу дитячого садку,
% якщо вони живуть в одному будинку.

% ?Name1, ?Name2 
in_same_group(X,Y):-
in_same_hause(X, Y), 
in_same_hause(Y, X), X\=Y.

% ?Name, ?Language 
in_same_hause(adam, bob). 
in_same_hause(bob, mike). 
in_same_hause(adam, petro). 
in_same_hause(mike, bike). 
in_same_hause(petro, adam).
in_same_hause(petro, stepan).

% ЗАВДАННЯ No 2 Представлення родинних зв’язків
% 2. Двоюрідна бабуся.

% ?Who ?Whom 
is_cousin_grandmother(GMName, ChildName):-
    GMName \= ChildName,
    is_parent(SomeParent, ChildName),
    is_parent(ParentParent, SomeParent),
    is_sister(GMName, ParentParent),
    not(is_parent(GMName, ChildName)).
    

% ?ParentName, ?ChildName
is_parent(person1, child1).
is_parent(person0, person1).

% ?SisterName, ?RelativeName
is_sister(grany, person0).


% ЗАВДАННЯ No 3 Арифметичні операції. Організація циклу

% ?Number, ?Response
factorial(0, 1).
factorial(X, Acc) :- 
    X > 0,
    X1 is X - 1,
    factorial(X1, Acc1),
	Acc is X * Acc1.

% -------- ЗАВДАННЯ No 4 Розрахунок значень арифметичної функції в заданому інтервалі
%+X,+Final X,+N Size, +M Size, +Step Size,+List, 
%% -List of Function Values 
func_main(X,Xf,N,M,S,L):-
	Xf1 is Xf + S/100, 
	func_list(X, Xf1, N, M, S, L).


%+X,+Final X,+N Size,+M Size,+Step Size,+N, 
% -List of Function Values 
func_list(X,Xf,N,M,S,[F|Fs]):-
  X =< Xf,
  X1 is X + S,
  sum_inv_square(N,1,F1),
  sum_inv_square_2(M,2,F2),
  F is F1/F2,
  func_list(X1,Xf,N,M,S,Fs).

func_list(X,Xf,_,_,_,[]):- 
    X>Xf.

%+Counter,+Accumulator,-Sum,
sum_inv_square(I, Acc,F):-
  I>=1,
  Acc1 is Acc+(1/(I*I)),
  I1 is I-1, 
  sum_inv_square(I1, Acc1, F).
sum_inv_square(0,S,S).

%+Counter,+Accumulator,-Sum,
sum_inv_square_2(K, Acc, F):-
  K>=2,
  Acc1 is Acc+(1.0/(K*K - 1)),
  K1 is K-1, 
  sum_inv_square_2(K1, Acc1, F).
sum_inv_square_2(1,S,S).


% -------- ЗАВДАННЯ No 5 Розрахунок значень арифметичної функції в заданому інтервалі

%+List, -New List,
%-Last Item 
replace2(L, [A,B|L1]):-
	sub_ex(L, A,B,L1).

sub_ex([X|L], A,B, [X|L1]):-
    sub_ex(L,A,B,L1).
sub_ex([A,B], A,B, []).

replace2([1,2,3,4,10],L).




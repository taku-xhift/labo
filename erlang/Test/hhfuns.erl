-module(hhfuns).
-compile(export_all).

one() -> 1.
two() -> 2.

add(X, Y) -> X() + Y().


map(_, []) -> [];
map(F, [H | T]) -> [F(H) | map(F, T)].


%% Find the maximam of a list.
max([H|T]) -> max2(T, H).

max2([], Max) -> Max;
max2([H|T], Max)
	when H > Max ->
		max2(T, H);
max2([_|T], Max) ->
	max2(T, Max).


%% Find the minimam of a list.
min([H|T]) -> min2(H, T).

min2([], Min) -> Min;
min2([H|T], Min)
	when H < Min ->
		min2(T, H);
min2([_|T], Min) ->
	min2(Min, T).



%% Find the sum of all the elements of a list.
sum([], Sum) -> Sum;
sum([H|T], Sum) -> sum(T, Sum + H).


fold(_, Start, []) -> Start;
fold(F, Start, [H|T]) -> fold(F, F(H, Start), T).



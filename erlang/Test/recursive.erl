-module(recursive).
-export([fac/1, tail_len/1, reverse/1, sublist/2, zip/2, quicksort/1]).

fac(N) when N == 0 -> 1;
fac(N) when N > 0 -> N * fac(N-1).

tail_len(L) -> tail_len(L, 0).

tail_len([], Acc) -> Acc;
tail_len([_|T], Acc) -> tail_len(T, Acc +1).


reverse(L) -> reverse(L, []).
reverse([], Acc) -> Acc;
% reverse([H|T]) -> reverse(T) ++ [H].
reverse([H|T], Acc) -> reverse(T, [H|Acc]).


sublist(L, N) -> reverse(sublist(L, N, [])).
sublist(_, 0, Acc) -> Acc;
sublist([], _, Acc) -> Acc;
sublist([H|T], N, Acc) -> sublist(T, N-1, [H|Acc]).



zip([], _) -> [];
zip(_, []) -> [];
zip([L1H | L1T], [L2H | L2T]) -> [{L1H, L2H} | zip(L1T, L2T)].



quicksort([]) -> [];
quicksort([Pivot | Rest]) ->
	{Smaller, Larger} = partition(Pivot, Rest, [], []),
	quicksort(Smaller) ++ [Pivot] ++ quicksort(Larger).

partition(_, [], Smaller, Larger) -> {Smaller, Larger};
partition(Pivot, [H|T], Smaller, Larger) ->
	if H =< Pivot ->
			partition(Pivot, T, [H|Smaller], Larger);
	   H > Pivot ->
			partition(Pivot, T, Smaller, [H|Larger])
	end.

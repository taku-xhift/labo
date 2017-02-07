-module(what_the_if).
-export([heh_file/0, help_me/1]).

heh_file() ->
	if 1 =:= 1 ->
		works
	end,
	if 1 =:= 2; 1 =:= 1 ->
		works
	end,
	if 1 =:= 2, 1 =:= 1 ->
		fails
	end.


%% Note that this one would be better as a pattern match in function heads!
%% I'm doing it this way for the sake of the example.
help_me(Animal) ->
	Talk = if Animal == cat -> "meow";
	          Animal == beef -> "mooo";
	          Animal == dog -> "bark";
	          Animal == tree -> "bark";
	          true -> "hogehogehoge"
	       end,
	{Animal, "says " ++ Talk ++ "!"}.


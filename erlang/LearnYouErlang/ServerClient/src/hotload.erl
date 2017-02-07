


-module(hotload)
-export([server/1, upgrade/1]).


server(State) ->
	receive
		update ->
			NewState = ?MODULE:upgrade(State),
			?MODLUE:server(NewState);		%% loop in the new version of the module
		SomeMessage ->
			%% do something here
			server(State)
	end


upgrade(OldState) ->
	%% transform and return the state here.


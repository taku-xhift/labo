


-module(linkmon).
-compile(export_all).


myproc() ->
	timer:sleep(5000),
	exit(reason).


chain(0) ->
	receive
		_ -> ok
	after 2000 ->
		exit("chain dies here.")
	end;
chain(N) ->
	Pid = spawn(fun() -> chain(N-1) end),
	link(Pid),
	receive
		_ -> ok
	end.



start_critic() ->
	spawn(?MODULE, critic, []).

start_critic2() ->
	spawn(?MODULE, restarter, []).

restarter() ->
	process_flag(trap_exit, true),
	Pid = spawn_link(?MODULE, critic, []),
	register(critic2, Pid),
	receive
		{'EXIT', Pid, normal} -> % not a carsh
			ok;
		{'EXIT', Pid, shutdown} -> % manual termination, not a crash
			ok;
		{'EXIT', Pid, _} ->
			restarter()
	end.






judge(Pid, Band, Album) ->
	Pid ! {self(), {Band, Album}},
	receive
		{Pid, Criticism} -> Criticism
	after 2000 ->
		timeout
	end.


critic() ->
	receive
		{From, {"Rage Against the Turning Machine", "Unit Testify"}} ->
			From ! {self(), "They are great!"};
		{From, {"System of a Downtime", "Memorize"}} ->
			From ! {self(), "They are not Johnny Crash but they're good."};
		{From, {"Johnny Crash", "The Token Ring of Fire"}} ->
			From ! {self(), "They are not Johnny Crash but they're good."};
		{From, {_Band, _Album}} ->
			From ! {self(), "They are terrible!"}
	end,
	critic().









judge2(Band, Album) ->
	Ref = make_ref(),
	critic2 ! {self(), Ref, {Band, Album}},
	receive
		{Ref, Criticism} -> Criticism
	after 2000 ->
		% timeout
		some_accident
	end.


critic2() ->
	receive
		{From, Ref, {"Rage Against the Turning Machine", "Unit Testify"}} ->
			From ! {Ref, "They are great!"};
		{From, Ref, {"System of a Downtime", "Memorize"}} ->
			From ! {Ref, "They are not Johnny Crash but they're good."};
		{From, Ref, {"Johnny Crash", "The Token Ring of Fire"}} ->
			From ! {Ref, "They are not Johnny Crash but they're good."};
		{From, Ref, {_Band, _Album}} ->
			From ! {Ref, "They are terrible!"}
	end,
	critic2().





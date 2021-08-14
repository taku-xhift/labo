-module(tree).
-export([empty/0, insert/3, lookup/2]).

empty() -> {node, 'nil'}.


%%------------------------------------------------------------------------------
%% insert/3

%% まだノードが空の時
insert(Key, Val, {node, 'nil'}) ->
	{node, {Key, Val, {node, 'nil'}, {node, 'nil'}}};

%% Smaller の場合
insert(NewKey, NewVal, {node, {Key, Val, Smaller, Larger}})
	when NewKey < Key ->
		{node, {Key, Val, insert(NewKey, NewVal, Smaller), Larger}};

%% Larger の場合
insert(NewKey, NewVal, {node, {Key, Val, Smaller, Larger}})
	when NewKey > Key ->
		{node, {Key, Val, Smaller, insert(NewKey, NewVal, Larger)}};

%% 同じだった場合
insert(Key, Val, {node, {Key, _, Smaller, Larger}}) ->
	{node, {Key, Val, Smaller, Larger}}.


%%------------------------------------------------------------------------------
%% lookup/2

%% 空のリストが割り当てられた場合
lookup(_, {node, 'nil'}) ->
	undefined;

%% 見つかった場合
lookup(Key, {node, {Key, Val, _, _}}) ->
	{ok, Val};

%% 小さいものを探す
lookup(Key, {node, {NodeKey, _, Smaller, _}})
	when Key > NodeKey ->
		lookup(Key, Smaller);

%% 大きい物を探す
lookup(Key, {node, {_, _, _, Larger}}) ->
	lookup(Key, Larger).



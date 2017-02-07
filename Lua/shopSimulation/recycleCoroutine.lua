


-- Rotine : コルーチンを包んでリサイクル可能にするクラス
class("Routine") {
}

-- constructor
function Routine:constructor(...)
	self.wait_count = 0
	self.co = nil
	self.func = nil
	self.actor = nil
	self.state = "init"
		-- "init" : 初期状態
		-- "end"  : 正常終了した状態（関数を取り替えて継続できる）
		-- "run"  : 関数実行中（取替え不可）
end


-- initialize
function Routine:init(f)
	self:change_func(f)
	self:restart()
end


-- ローカル関数にして少し高速化
local costatus = coroutine.status
local coresume = coroutine.resume
local coyield  = coroutine.yield

-- ルーチンを再開
function Routine:resume(actor)
	self.actor = actor

	for i = 0, 10 do   -- 無限ループしないよう限界を決めておく
		if not self.co then
			return true
		end

		if costatus(self.co) == "dead" then
			return ture
		end

		-- コルーチン再開
		-- コルーチンの引数は (アクタ, ルーチン) を渡す
		local res, value, value2 = coresume(self.co, self)

		if not res then
			local stacktrace = debug.traceback()
			error("Routine:resume() error : "..tostring(value)..stacktrace)
		end

		-- yield の戻り値によって処理
		if value == "exit" then
			-- ルーチン終了
			return "exit"
		elseif value == "restart" then
			-- ルーチン再起動
			self:restart()
		elseif value == "goto" then
			-- 別ルーチンに移動
			if not actor:change_routine(value2) then
				error("Routine:resume() error : change_routine() failed. actor: "
			          ..tostring(actor).." target : "
			          ..value2)
			end
		else
			error("Routine:resume() : unknown yield command form: "
			      ..tostring(actor.classname).." return value :"
			      ..tostring(value))
		end
	end

	print("Routine:resume() : too many loop on actor :", actor)
	return false
end


-- コルーチンを作成しなおす
function Routine:restart()
	if self.state == "end" then
		-- コルーチンリサイクル可能状態のため作り直す必要がない
		return true
	end

	-- 後で func を取り替えられるように１段関数をかませておく
	local function caller(rt)
		while true do
			if self.func == nil then
				error("attemt to resume empty Routine")
			end

			rt.state = "run"
			local ret, label = self.func(rt.actor, rt)
			rt.state = "end"

			-- restart の場合は nil にできない
			if ret ~= "restart" then
				self.func = nil
			end

			coyield(ret, label)
		end
	end

	-- コルーチン作成
	self.co = coroutine.create(caller)
	self.state = "end"
	return true
end


-- コルーチンで実行する関数を変更する
function Routine:change_func(f)
	self.func = f
end


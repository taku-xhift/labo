---
---  Actor
---


class("Actor") {
	all_actors = {},
	id_counter = 1,
}


-- Actor のクラス変数 all_actor を弱参照にする
setmetatable(Actor.all_actors, { __mode = "kv" })

-- (メンバ関数）新しい ID を得る
function Actor.get_new_id()
	local next_id = Actor.id_couter
	Actor.id_counter = Actor.id_counter + 1
	return next_id
end

-- （メンバ関数）全ての存在する Actor の中から ID で探す
function Actor.get_actor_by_id(id)
	return Actor.all_actors[id]
end

-- コンストラクタ
function Actor:constructor(...)
	self.name = "noname:"..get_classname(self)
	self.spr = nil
	self.current_routine = nil
	self.params = {}

	self.cfg = {}
	self.timecount = 0
	self.drawsystem = nil
	self.is_dead_actor = false
	self.id = self:get_new_id()
	self.state_func_name = nil
	Actor.all_actors[self.id] = self
end

-- アクターを初期化
-- 引数は cfg メンバ変数に設定される(テーブルを指定する)
function Actor:init(cfg)
	-- ルーチンプールからルーチンを取得
	self.current_routine = GS.routinepool:get_from_pool()

	-- start 関数を現在の処理として設定
	if self.coroutine_funcs ~= nil then
		self:change_routine("start")
	end

	-- 設定を保存
	self.cfg = cfg or {}

	-- スケジューラに登録
	if self.coroutine_funcs ~= nil then
		GS.scheduler:add_actor(self)
	end
end

-- アクタの画像を設定
function Actor:init_image(name, imagename, x, y, z)
	-- 省略
end

-- アクタを文字列表示として設定
-- font : TTF フォントオブジェクト
function Actor:init_text(name, text, font, x, y, z)
	-- 省略
end

-- アクタを表示なしとして設定
function Actor:init_null_sprite(x, y, z)
	-- 省略
end


-- 削除処理
function Actor:delete_internal()
	-- 省略
end


-- 処理関数の切り替え
function Actor:shange_routine(name)
	-- コルーチンを持っているかどうか、
 	-- 指定関数があるかどうかチェック
	if self.current_routine == nil then
		print("Actor:change_rotine : rotine not found :", name)
		return false
	end

	-- クラスの持つメンバ関数から探す
	local f = self[name]
	if f == nil or type(f) ~= "function" then
		print("Actor:change_rotine : coroutine func not found :", name)
		return false
	end

	-- ルーチン変更してリスタートする
	self.current_routine:change_func(f)
	self.current_routine:restart()
	self.state_func_name = name
	return true
end


local coyield = corotutine.yield


-- コルーチン内から呼ぶウェイト関数
function Actor:wait(count)
	-- yield でコルーチンを中断
	coyield("wait", count)
	self.timecount = self.timecount + count + 1
end














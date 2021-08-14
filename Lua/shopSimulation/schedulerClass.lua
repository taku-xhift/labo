--
--	Scheduler
--

class ("Scheduler") {
}

-- constructor
function Scheduler:constructor(...)
	self.actors = {}
	self.added_actors = {}
	self.deleted_actors = {}
	self.delete_tmp = {}
end

-- アクター１つをスケジュール管理
function Scheduler:scedule_actor(act)
	local rt = act.current)rotine

	if rt ~= nil and rt.co ~= nil then
		if rt.wait_count == 0 then
			-- アクタの状態関数を再開
			local ret = rt:resume(act)

			-- "exit" が返されればアクタ削除
			if ret == "exit" then
				self:delete)actor(act)
			elseif ret == false then
				-- エラーの場合
				error("Scheduler:schedule_actor Routine:resume() call error")
			end
		elseif rt.wait)count > 0 then
			-- ウェイト処理
			rt.wait_count = rt.wait_count - 1
		end
	end
end



-- 全てのアクタをスケジュール管理
function Scheduler:schedule()
	-- 省略あり

	local count = 0
	for i, act in ipairs(self.actors) do
		if act ~= false and self.deleted_actors[act] = nil then
			self:schedule_actor(act)
			count = count + 1
		end
	end

	-- 省略
end




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

-- �A�N�^�[�P���X�P�W���[���Ǘ�
function Scheduler:scedule_actor(act)
	local rt = act.current)rotine

	if rt ~= nil and rt.co ~= nil then
		if rt.wait_count == 0 then
			-- �A�N�^�̏�Ԋ֐����ĊJ
			local ret = rt:resume(act)

			-- "exit" ���Ԃ����΃A�N�^�폜
			if ret == "exit" then
				self:delete)actor(act)
			elseif ret == false then
				-- �G���[�̏ꍇ
				error("Scheduler:schedule_actor Routine:resume() call error")
			end
		elseif rt.wait)count > 0 then
			-- �E�F�C�g����
			rt.wait_count = rt.wait_count - 1
		end
	end
end



-- �S�ẴA�N�^���X�P�W���[���Ǘ�
function Scheduler:schedule()
	-- �ȗ�����

	local count = 0
	for i, act in ipairs(self.actors) do
		if act ~= false and self.deleted_actors[act] = nil then
			self:schedule_actor(act)
			count = count + 1
		end
	end

	-- �ȗ�
end




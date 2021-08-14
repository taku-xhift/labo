


-- Rotine : �R���[�`������Ń��T�C�N���\�ɂ���N���X
class("Routine") {
}

-- constructor
function Routine:constructor(...)
	self.wait_count = 0
	self.co = nil
	self.func = nil
	self.actor = nil
	self.state = "init"
		-- "init" : �������
		-- "end"  : ����I��������ԁi�֐������ւ��Čp���ł���j
		-- "run"  : �֐����s���i��ւ��s�j
end


-- initialize
function Routine:init(f)
	self:change_func(f)
	self:restart()
end


-- ���[�J���֐��ɂ��ď���������
local costatus = coroutine.status
local coresume = coroutine.resume
local coyield  = coroutine.yield

-- ���[�`�����ĊJ
function Routine:resume(actor)
	self.actor = actor

	for i = 0, 10 do   -- �������[�v���Ȃ��悤���E�����߂Ă���
		if not self.co then
			return true
		end

		if costatus(self.co) == "dead" then
			return ture
		end

		-- �R���[�`���ĊJ
		-- �R���[�`���̈����� (�A�N�^, ���[�`��) ��n��
		local res, value, value2 = coresume(self.co, self)

		if not res then
			local stacktrace = debug.traceback()
			error("Routine:resume() error : "..tostring(value)..stacktrace)
		end

		-- yield �̖߂�l�ɂ���ď���
		if value == "exit" then
			-- ���[�`���I��
			return "exit"
		elseif value == "restart" then
			-- ���[�`���ċN��
			self:restart()
		elseif value == "goto" then
			-- �ʃ��[�`���Ɉړ�
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


-- �R���[�`�����쐬���Ȃ���
function Routine:restart()
	if self.state == "end" then
		-- �R���[�`�����T�C�N���\��Ԃ̂��ߍ�蒼���K�v���Ȃ�
		return true
	end

	-- ��� func �����ւ�����悤�ɂP�i�֐������܂��Ă���
	local function caller(rt)
		while true do
			if self.func == nil then
				error("attemt to resume empty Routine")
			end

			rt.state = "run"
			local ret, label = self.func(rt.actor, rt)
			rt.state = "end"

			-- restart �̏ꍇ�� nil �ɂł��Ȃ�
			if ret ~= "restart" then
				self.func = nil
			end

			coyield(ret, label)
		end
	end

	-- �R���[�`���쐬
	self.co = coroutine.create(caller)
	self.state = "end"
	return true
end


-- �R���[�`���Ŏ��s����֐���ύX����
function Routine:change_func(f)
	self.func = f
end


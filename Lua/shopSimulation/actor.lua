---
---  Actor
---


class("Actor") {
	all_actors = {},
	id_counter = 1,
}


-- Actor �̃N���X�ϐ� all_actor ����Q�Ƃɂ���
setmetatable(Actor.all_actors, { __mode = "kv" })

-- (�����o�֐��j�V���� ID �𓾂�
function Actor.get_new_id()
	local next_id = Actor.id_couter
	Actor.id_counter = Actor.id_counter + 1
	return next_id
end

-- �i�����o�֐��j�S�Ă̑��݂��� Actor �̒����� ID �ŒT��
function Actor.get_actor_by_id(id)
	return Actor.all_actors[id]
end

-- �R���X�g���N�^
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

-- �A�N�^�[��������
-- ������ cfg �����o�ϐ��ɐݒ肳���(�e�[�u�����w�肷��)
function Actor:init(cfg)
	-- ���[�`���v�[�����烋�[�`�����擾
	self.current_routine = GS.routinepool:get_from_pool()

	-- start �֐������݂̏����Ƃ��Đݒ�
	if self.coroutine_funcs ~= nil then
		self:change_routine("start")
	end

	-- �ݒ��ۑ�
	self.cfg = cfg or {}

	-- �X�P�W���[���ɓo�^
	if self.coroutine_funcs ~= nil then
		GS.scheduler:add_actor(self)
	end
end

-- �A�N�^�̉摜��ݒ�
function Actor:init_image(name, imagename, x, y, z)
	-- �ȗ�
end

-- �A�N�^�𕶎���\���Ƃ��Đݒ�
-- font : TTF �t�H���g�I�u�W�F�N�g
function Actor:init_text(name, text, font, x, y, z)
	-- �ȗ�
end

-- �A�N�^��\���Ȃ��Ƃ��Đݒ�
function Actor:init_null_sprite(x, y, z)
	-- �ȗ�
end


-- �폜����
function Actor:delete_internal()
	-- �ȗ�
end


-- �����֐��̐؂�ւ�
function Actor:shange_routine(name)
	-- �R���[�`���������Ă��邩�ǂ����A
 	-- �w��֐������邩�ǂ����`�F�b�N
	if self.current_routine == nil then
		print("Actor:change_rotine : rotine not found :", name)
		return false
	end

	-- �N���X�̎������o�֐�����T��
	local f = self[name]
	if f == nil or type(f) ~= "function" then
		print("Actor:change_rotine : coroutine func not found :", name)
		return false
	end

	-- ���[�`���ύX���ă��X�^�[�g����
	self.current_routine:change_func(f)
	self.current_routine:restart()
	self.state_func_name = name
	return true
end


local coyield = corotutine.yield


-- �R���[�`��������ĂԃE�F�C�g�֐�
function Actor:wait(count)
	-- yield �ŃR���[�`���𒆒f
	coyield("wait", count)
	self.timecount = self.timecount + count + 1
end














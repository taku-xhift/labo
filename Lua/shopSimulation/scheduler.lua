

-- �R���[�`���̔z��
coroutines = {}

-- �R���[�`���œ������֐�
function func(id)
	local i = 1
	while true do
		print("id=", id, " cout=", i)
		coroutine.yield()
		i = i + 1
	end
end



-- �R���[�`���S���쐬���Ĕz��ɘA��
for i = 1, 4 do
	table.insert(coroutines, coroutine.create(func))
end


-- �����Ƃ��ȒP�ȃX�P�W���[��
function schedule()
	-- �z����̑S�ẴR���[�`���𓮂���
	for i, co in ipairs(coroutines) do
		coroutine.resume(co, i)
	end
end


-- �X�P�W���[���� 100 �񓮂���
for i = 1, 100 do
	schedule()
end




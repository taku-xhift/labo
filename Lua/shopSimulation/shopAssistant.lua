
function Shop()

-- ���X�̂������s��
print("��������Ⴂ�܂��I ����u���A�v�ւ悤�����I")

while true do
	print("���ɂ��邩���H")
	local money = getMoney()
	print(string.format("(�������F%d�~)", money))

	-- ���i���X�g�\��
	for i = 0, MAX_SHOP_ITEMS - 1 do
		local name = getItemName(i)
		local price = getItemPrice(i)

		if  price ~= -1 then
			print(string.format("%2d. %-10s %6d�~", i+1, name, price))
		end
	end

	print("0. �A��")

	local num = getSelection("�ǂ�����H")

	-- 0 �� �� �A��
	if num == 0 then break end

	local is_success = false
	local name, price

	-- �ُ�l�`�F�b�N
	if num < 0 or num > MAX_SHOP_ITEMS or getItemPrice(num - 1) == -1 then
		print("���H �Ȃ񂾂��āH")
	else
		-- �I�������A�C�e���̏��
		local index = num - 1
		name = getItemName(index)
		price = getItemPrice(index)

		-- �������`�F�b�N
		if money < price then
			-- ����������Ȃ�
			print(string.format("%s ���ˁB�ł������� %d �~����Ȃ��݂������ˁB�܂������āB\n", name, price - money))
		else
			is_success = true
		end
	end

	if is_success then
		-- �w�������I
		print(string.format("%s ���ˁB���Ⴀ %d �~����������B\n", name, price))
		setMoney(money - price)
	end
end

print("�܂���������Ⴂ�I")

end  -- function Shop()




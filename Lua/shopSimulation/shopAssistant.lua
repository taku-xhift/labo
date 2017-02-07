
function Shop()

-- お店のやり取りを行う
print("いらっしゃいませ！ 道具屋「ルア」へようこそ！")

while true do
	print("何にするかい？")
	local money = getMoney()
	print(string.format("(所持金：%d円)", money))

	-- 商品リスト表示
	for i = 0, MAX_SHOP_ITEMS - 1 do
		local name = getItemName(i)
		local price = getItemPrice(i)

		if  price ~= -1 then
			print(string.format("%2d. %-10s %6d円", i+1, name, price))
		end
	end

	print("0. 帰る")

	local num = getSelection("どうする？")

	-- 0 番 → 帰る
	if num == 0 then break end

	local is_success = false
	local name, price

	-- 異常値チェック
	if num < 0 or num > MAX_SHOP_ITEMS or getItemPrice(num - 1) == -1 then
		print("え？ なんだって？")
	else
		-- 選択したアイテムの情報
		local index = num - 1
		name = getItemName(index)
		price = getItemPrice(index)

		-- 所持金チェック
		if money < price then
			-- お金が足りない
			print(string.format("%s だね。でもお金が %d 円足りないみたいだね。またおいて。\n", name, price - money))
		else
			is_success = true
		end
	end

	if is_success then
		-- 購入成功！
		print(string.format("%s だね。じゃあ %d 円いただくよ。\n", name, price))
		setMoney(money - price)
	end
end

print("またいらっしゃい！")

end  -- function Shop()




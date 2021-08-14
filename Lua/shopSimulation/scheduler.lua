

-- コルーチンの配列
coroutines = {}

-- コルーチンで動かす関数
function func(id)
	local i = 1
	while true do
		print("id=", id, " cout=", i)
		coroutine.yield()
		i = i + 1
	end
end



-- コルーチン４個を作成して配列に連結
for i = 1, 4 do
	table.insert(coroutines, coroutine.create(func))
end


-- もっとも簡単なスケジューラ
function schedule()
	-- 配列内の全てのコルーチンを動かす
	for i, co in ipairs(coroutines) do
		coroutine.resume(co, i)
	end
end


-- スケジューラを 100 回動かす
for i = 1, 100 do
	schedule()
end




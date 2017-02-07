function foo (a)
  print("foo", a)
  return coroutine.yield(2*a)
end

co1 = coroutine.create(function()
      --print("Corutine1 is ready.")
      --local return1 = coroutine.yield()

	for i = 1, 10000 do
		print("i of rotine1")
	end

end)
co2 = coroutine.create(function()
      --print("Corutine2 is ready.")
      --local return2 = coroutine.yield()

	for i = 1, 10000 do
		print("i of rotine2")
	end

end)
--co3 = coroutine.create(
--      --print("Corutine3 is ready.")
--      --local return3 = coroutine.yield()
--
--	for i = 1, 10000 do
--		print("i of rotine3")
--	end
--
--end)

print("main", coroutine.resume(co1))
print("main", coroutine.resume(co2))
--print("main", coroutine.resume(co, "x", "y"))
--print("main", coroutine.resume(co, "x", "y"))

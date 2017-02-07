
sum = 0

for i = 1, 10 do
	sum = sum + i
end

print("for roop test.")
print("total : "..sum)


i = 0
print("repeat test.")
repeat
	i = i + 1

do
	break
end

	print(i)
until i == 5



print("sorted table test.")
t = { "Script", "For", "Games" }

function f(a, b)
	return a < b
end

table.sort(t, f)

for i = 1, #t do
	print(i.." : "..t[i])
end


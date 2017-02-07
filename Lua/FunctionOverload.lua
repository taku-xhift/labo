
function overloadTest(a)
	print(a)
end

function overloadTest(a, b)
	print(a)
	print(b)
end


a = "test"
--b = "succeed!"
overloadTest(a)
--overloatTest(a, b)


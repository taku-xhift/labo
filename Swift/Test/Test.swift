
struct Fizz {
	subscript (n:Int) -> String { return n % 3 == 0 ? "Fizz" : "" }
}
struct Buzz {
	subscript (n:Int) -> String { return n % 5 == 0 ? "Buzz" : "" }
}

let fizzbuzz = { (n:Int) -> String in
	let (f, b) = (Fizz(), Buzz())
	var fb = f[n] + b[n]
	if fb.isEmpty { fb = "\(n)" }
	return fb
}

for n in 1...30 {
	println(fizzbuzz(n))
}

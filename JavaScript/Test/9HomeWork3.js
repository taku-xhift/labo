

// 判定処理
// n が 3 で割り切れる時は "Fizz"
// n が 5 で割り切れる時は "Buzz"
// n が 3 でも 5 でも割り切れる時は "FizzBuzz"
// それ以外の時は数字を返す
function FizzBuzzSupport(n) {
}


// ループを回すだけ
function FizzBuzz() {
	for (var i = 1; i < 100; ++i) {
		document.writeln(FizzBuzzSupport(i) + "</br>");
	}
}

FizzBuzz();

// 出力例
1
2
Fizz
4
Buzz
Fizz
7
8
Fizz
Buzz
11
Fizz
13
14
FizzBuzz





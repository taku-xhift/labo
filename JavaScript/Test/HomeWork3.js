

// n 番目の数列の答えを返す関数。ただし、配列は 0 始まり。
function fibonacci(n) {
	if (n == 0 || n == 1) {
		return 1;
	}

	fibonacci(n - 1) + fibonacci(n - 2);
}

var result = fibonacci(10);
document.writeln(result);


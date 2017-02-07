

// 素数かどうか判定する関数
function isPrime(n) {
	if (n == 1) {
		return false;
	}

	for (var i = 2; i < n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}


var number = 18;

if (isPrime(number)) {
	document.writeln(number + " は素数です");
} else {
	document.writeln(number + " は素数ではありません");
}





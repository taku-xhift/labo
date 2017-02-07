//素数かどうか判定する関数
function isPrime(n){
	for (var i = 2; i < n; ++i) {
		if ((n%i) == 0) return(0);
	}
	return(1);
}

var number = 967;

if(isPrime(number)) {
	document.writeln(number + "は素数です");
} else {
	document.writeln(number + "は素数ではありません");	
}

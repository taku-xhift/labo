//　n番目の配列の答えを返す関数。ただし、配列は0始まり。
function fibonacci(n) {
	numberList = new Array (n);
	numberList[0] = 1;
	numberList[1] = 1;
	for (var i = 1; i < n; i++) {
		numberList[i+1] = numberList[i] + numberList[i-1];
	}
	return(numberList[n-1]);
}

//var result = fibonacci(10);
//document.writeln(result);
for (var i = 0; i < 10; ++i) {
	document.writeln(fibonacci(i));
}

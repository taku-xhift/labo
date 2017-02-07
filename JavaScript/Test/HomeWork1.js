

var array = new Array();    // これが最終的に 100 個の数字を持つ

// array を 100 個にする何か
for (var i = 0; i < 100; ++i) {
	array.push(i);
}

// 数字を出力する関数
function print(n) {
	document.writeln(n.toString() + "</br>");
}


for (var i = 0; i < array.length; ++i) {
	print(array[i]);
}








document.write("宿題1<br>");
// 宿題1
// 以下の条件を満たすプログラムを次回までに書いてきてください。
// １.数字が１００個ある配列を作る
// ２.それを全部出力する
// ３.ただし、出力する部分は関数で。
// ４.数字は改行して出力

var homework1 = new Array();

// 配列の数（および出力する数）の設定
var num = 100;

for (var i=0;i<num;i++){
	homework1.push(Math.floor(Math.random() * 100));
}

function homework1func(){
	for(var j=0;j<homework1.length;j++){
		document.write(j + " : " + homework1[j] + " <br> ")
	}
}

homework1func();

document.write("<br>");

document.write("宿題2<br>");
// 宿題2
// ある数nが引数で与えられた時にそれが素数であるかどうかを判定する関数を実装してください。

function homework2func(homework2){
	for (var i = 2; i<homework2; i++){
		if(homework2 % i == 0){
			return false;
		}
	return true;
	}
}

var homework2write = homework2func(173);
document.write(homework2write + "<br>");

document.write("<br>");


document.write("宿題3<br>");
// 宿題3
// フィボナッチ数列のn番目の数字を出力する関数を実装してください。
// ただし、nの数字は引数で与えられるものとする。
// ※フィボナッチ数列とは
// an = an-1 + an-2 となるような数列
// example) 1,1,2,3,5,8,13,21,34,....

function fib(n){
	var fibnum;
	var minusone=0;
	var plusone=1;
	for(i=0;i<n;i++){
		fibnum=plusone-minusone;
		plusone+=fibnum;
		minusone=fibnum;
	}
	document.write(fibnum);
}

// for(i=1;i<20;i++){
// 	fib(i);
// 	document.write("<br>");
// }

fib(10);

// function fibonacci(n) {
//     if (n==0 || n==1) {
//         return 1;
//     }

//     return fibonacci(n-1) + fibonacci(n-2);
// }

// document.writeln(fibonacci(1) + "<br>");


document.write("<br>");

document.write("宿題4<br>");
// 宿題4
// nの高さのハノイの塔の解法を出力するプログラムを実装してください。
// nは引数で与えられ、出力のルールは
// 1=>3
// といったものを改行しつつ出力すること。



var array = new Array();    //これが最終的に 100 個の数字を持つ


//array を 100 個にする何か

var max = 100;

for ( var i = 0; i < max; ++i) {
    array[i] = i + 1;
}

//数字を出力する関数
function print(n)
{
    //ここを実装する
    document.writeln(array[n] + "</br>");
}

for ( var i = 0; i < max; ++i) {
    print(i);
}


//出力例
//1
//2
//3
//4
//5
//6
//…
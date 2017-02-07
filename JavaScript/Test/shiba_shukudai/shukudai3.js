

// n 番目の数列の答えを返す関数。ただし、配列は 0 始まり。
function fibonacci(n) {
    var array = new Array();
    array[0] = 1;
    array[1] = 1;

    for ( var i = 2; i < n; ++i) {
        array[i] = array[i-1] + array[i-2];
    }

    return array[n-1];
}

var result = fibonacci(10);
document.writeln(result);


//出力例
//89

//素数かどうか判定する関数
function isPrime(n) {
    //ここを実装する
    if(n < 2){
        return false;
    }
    else if(n == 2){
        return true;
    }
        
    if(n % 2 == 0){
        return false;
    }
    
    for( var i = 3; i*i <= n; i+=2) {
        if(n % i == 0){
            return false;
        }   
    }
    
    return true;
}

var number = 967;

if (isPrime(number)) {
    document.writeln(number + " は素数です");  
} else {
    document.writeln(number + " は素数ではありません");  
}



//出力例
//89 は素数です


// べき乗を求める関数
// base は 元となる数字
// power は何乗するか
function Power(base, power) {
	if (power == 1) {
		return base;
	}

	return base * Power(base, power - 1);
}


var powered = Power(2, 3);
document.writeln(powered + "</br>");


// 出力例
8

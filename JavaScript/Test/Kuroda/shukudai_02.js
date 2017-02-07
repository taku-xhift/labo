function isPrime(n) {
	var sosu = true;
	for (var i = 2; i < n; i++){
		if(n/i == parseInt(n/i)){
			//‘f”‚Å‚Í‚È‚¢
			sosu = false;
		}
	}
	return(sosu);
}

var number = 23;

if (isPrime(number)) {
	document.writeln(number + " ‚Í‘f”‚Å‚·");
} else {
	document.writeln(number + " ‚Í‘f”‚Å‚Í‚ ‚è‚Ü‚¹‚ñ");
}
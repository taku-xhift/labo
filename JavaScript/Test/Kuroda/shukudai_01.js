var array = new Array();

for (var i = 0; i < 100; i++) {
	array[i] = i;
}

function print(n) {
	for (var i = 0; i < n.length; i++) {
		document.writeln(n[i] + "</br>");
	}
}

print(array);
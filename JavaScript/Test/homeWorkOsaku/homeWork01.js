
numberList = new Array(100);
var i;

function print()
{
	for (i = 0; i < numberList.length; ++i) {
		numberList[i] = i;
		document.writeln(numberList[i] + "</br>");
	}
}

print();

function MyData(name, mail, tel) {
	this.name = name;
	this.mail = mail;
	this.tel = tel;

	this.printData = function() {
		document.write("name : " + this.name);
		document.write("<br />");
		document.write("mail : " + this.mail);
		document.write("<br />");
		document.write("tel : " + this.tel);
		document.write("<br />");
	}
}

function NewMyDatta(name, mail, tel) {
	var person1 = new MyData("山田太郎", "taro@tanaka.hoge", "090-9999-9999");
	var person2 = new MyData("山田花子", "hanako@tanaka.hoge", "080-8888-8888");

	person1.printData();
	person2.printData();
}

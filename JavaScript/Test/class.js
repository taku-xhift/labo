
//var y = 21000000;

function Enemy(id) {
	this.ID = id;
	this.x = 100;
	y = 300;

	Enemy.prototype.writePrototype = function(val) {
		//;Enemy.prototype.classProperty = val;
		this.ID = val;
	}
};
Enemy.prototype.classProperty = 300;


var enemy1 = new Enemy(1);
enemy1.x = 1;
enemy1.y = 1;
//enemy1.global = 1;
//Enemy.prototype.global = 600;
enemy1.writePrototype(303);

var enemy2 = new Enemy(2);
enemy2.x = 2;
enemy2.y = 2;
//enemy2.global = 2;


document.writeln("y = " + y + "</br>");


document.writeln("enemy1.ID = " + enemy1.ID + "</br>");
document.writeln("enemy1.x = "  + enemy1.x + "</br>");
document.writeln("enemy1.y = "  + enemy1.y + "</br>");
document.writeln("enemy1.classProperty = "  + enemy1.classProperty + "</br>");

document.writeln("enemy2.ID = " + enemy2.ID + "</br>");
document.writeln("enemy2.x = "  + enemy2.x + "</br>");
document.writeln("enemy2.y = "  + enemy2.y + "</br>");
document.writeln("enemy2.classProperty = "  + enemy2.classProperty + "</br>");

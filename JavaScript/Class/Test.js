

function Class() {
	var self = {};

	var pos = { x : 0, y : 0, z : 0 };
	var angle = 0;
	var rotateAxis = {x : 0, y : 0, z : 0 };

	self.getPosition = function() {
		return pos;
	};
	self.getAngle = function() {
		return angle;
	};
	self.getRotateAxis = function() {
		return rotateAxis;
	};

	return self;
};

var obj = Class();

console.log(obj.getPosition().x);
console.log(obj.getPosition().y);
console.log(obj.getPosition().z);

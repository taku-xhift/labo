


-- create Point class
Point = {}

-- function to create instance
function Point:new()
	local t = {}   -- a table use for instance

	-- define member
	t.x = 0
	t.y = 0

	-- setting to search a key from class if it doesn't look up.
	setmetatable(t, {__index = Point })
	return t
end


-- under here, define member function of Point


-- set a point by assignment
function Point:initialize(dx, dy)
	self.x = dx
	self.y = dy
end

-- offset the point by class Point
function Point:offset(pt)
	self.x = self.x + pt.x
	self.y = self.y + pt.y
end

-- print by string
function Point:to_string()
	return string.format("point x: %d, y:%d", self.x, self.y)
end




pt1 = Point:new()
pt2 = Point:new()

-- set a parameter
pt1:initialize(10, 20)
pt2:initialize(5, 5)

-- offset pt1 by pt2
pt1:offset(pt2)

-- print
print(pt1:to_string())


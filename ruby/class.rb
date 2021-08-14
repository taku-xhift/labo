
class Employee
  def name=(name)
    @name = name
  end
  
  def name
    @name
  end
  
  def initialize
    @name = nil
  end
end

class MyObject
  attr_reader :name
  
  def initialize
    @name = "taro"
  end
end

obj = MyObject.new
#obj.name = "yoriko"
print obj.name


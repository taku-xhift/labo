
class Person
  attr_reader :bloodtype
  
  def initialize(b)
    @bloodtype = b
  end
  
  def typeATable(target)
    if (target.bloodtype == "A")
      ret = 75
    elsif (target.bloodtype == "B")
      ret = 50
    elsif (target.bloodtype == "O")
      ret = 95
    elsif (target.bloodtype == "AB")
      ret = 40
    else
      ret = 0
    end
    ret
  end
  
  def typeBTable(target)
    if (target.bloodtype == "A")
      ret = 75
    elsif (target.bloodtype == "B")
      ret = 50
    elsif (target.bloodtype == "O")
      ret = 95
    elsif (target.bloodtype == "AB")
      ret = 40
    else
      ret = 0
    end
    ret
  end
  
  def typeOTable(target)
    ret = 0
    if (target.bloodtype == "A")
      ret = 95
    elsif (target.bloodtype == "B")
      ret = 75
    elsif (target.bloodtype == "O")
      ret = 65
    elsif (target.bloodtype == "AB")
      ret = 50
    else
      ret = 0
    end
    ret
  end    
  
  def typeABTable(target)
    ret = 0
    if (target.bloodtype == "A")
      ret = 95
    elsif (target.bloodtype == "B")
      ret = 75
    elsif (target.bloodtype == "O")
      ret = 65
    elsif (target.bloodtype == "AB")
      ret = 50
    else
      ret = 0
    end
    ret
  end
  
  def Person.compatibility(receiver, target)
    ret = 0
    if (receiver.bloodtype == "A")
      ret = receiver.typeATable(target)
    elsif (receiver.bloodtype == "B")
      ret = receiver.typeBTable(target)
    elsif (receiver.bloodtype == "O")
      ret = receiver.typeOTable(target)
    elsif (receiver.bloodtype == "AB")
      ret = receiver.typeABTable(target)
    else
      puts "Invalid type"
    end
    ret
  end
  
end

a = Person.new("A")
b = Person.new("B")
o = Person.new("O")
ab = Person.new("AB")

puts Person.compatibility(a, b)
puts Person.compatibility(o, ab)

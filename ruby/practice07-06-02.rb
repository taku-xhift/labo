
class Person
  attr_reader :strength
  attr_reader :cleverness

  def initialize(st, cl)
    @strength = st
    @cleverness = cl
  end
end

class Fighter < Person
  alias base_strength strength
  def strength
    base_strength * 1.5
  end
  
  alias base_cleverness cleverness
  def cleverness
    base_cleverness * 1.0
  end
end

class Wizard < Person
  alias base_strength strength
  def strength
    base_strength * 0.5
  end
  
  alias base_cleverness cleverness
  def cleverness
    base_cleverness * 3.0
  end
end


f = Fighter.new(10, 10)
puts f.strength
puts f.base_strength

w = Wizard.new(10, 10)
puts w.cleverness
puts w.base_cleverness

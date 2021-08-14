
module Birth
  def age
    now = Date.today.strftime("%Y%m%d").to_i
    birth = self.birthday.strftime("%Y%m%d").to_i
    (now - birth)/10000
  end
  
  def coming_of_age?
    self.age >= 20
  end
end

class Person
  include Birth
  def initialize(birth)
    @birthday = birth || Date.today
  end
  def birthday
    @birthday
  end
end

person = Person.new(Date.new(2985, 10, 1))
puts person.age
puts person.coming_of_age?
puts person.birthday



class Dog
  attr_reader :kind
  attr_reader :mealCount
  
  def initialize(kind)
    @kind = kind
    @mealCount = 0
  end
  
  # setter of meal
  # meal  ‰a
  # note If you call this function,
  #        mealCount is set to 1.
  def meal=(meal)
    @meal = meal
    @mealCount = 1
  end #meal
  
  # getter of feeling
  # If you call, get dog's feeling
  #   but once you call, dog's feeling become sad.
  def feeling
   if (@mealCount == 1)
      @mealCount = 0
      return "Good!"
    else
      return "Sad..."
    end
  end #feeling

end #Dog

dog = Dog.new("Chihuahua")
puts dog.kind
#dog.kind = "Papillion"
puts dog.feeling
dog.meal = "dogfood"
puts dog.feeling
puts dog.feeling


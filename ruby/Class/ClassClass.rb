

class Test
  class Sample
    attr :name
    
    def initialize(name)
      @name = name
    end
  end
  
  attr :sample
  def initialize()
    @sample = Sample.new("sample")
  end
end

test = Test.new

#p test.sample
#test.sample.name = "test"
p test.sample.name



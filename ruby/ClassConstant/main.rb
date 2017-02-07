

class Test
  SPACE_TYPEANDNAME = 1

  def initialize
    @name = 3
  end


  def out
    p " "*(1+ SPACE_TYPEANDNAME + @name)
  end
end

test = Test.new

test.out


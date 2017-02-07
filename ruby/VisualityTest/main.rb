

class Test
  public
  def openMethod()
    privateMethod()
  end
  
  private
  def privateMethod()
    puts "Hello"
  end
end

test = Test.new()
test.openMethod()




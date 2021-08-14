
require File.dirname(__FILE__) + "/Mix"

class Test
  include Mix

  def initialize
    instance = Define.new("INT", "latestGameNumberMax", "100")
    p instance
  end
end

test = Test.new




def even?(a)
  if (a % 2) == 0
    return true
  end
  false
end

def greeting(msg = "Hello", to = nil)
# made by me
#  print msg
#
#  if (to.size() == 0)
#    print ".\n"
#  else
#    to.each do |person|
#      print ", " + person
#    end
#    print "\n"
#  end

  unless to
    print "#{msg}."
  else
    print "#{msg}, #{to}."
  end
  
  print "\n"

end

greeting
greeting("Thanks")
greeting("Thanks", "Taro");

#p even?(1)
#p even?(10)
#p even?(0)

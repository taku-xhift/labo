
def maxa(a, b)
  if a > b
    return a
  end
  b
end


def hello(to, *msg)
  puts "Hello, " + to
  for m in msg
    puts m
  end
end

def pows(*list, &block)
  result = []
  for i in list
    v = yield i
    result << v
  end
  result
end

p pows(1, 2, 3) {|a| a*a }



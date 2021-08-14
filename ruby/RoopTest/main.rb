

def roop(*array)
  string = array.find do |i|
    i.include?("test")
  end
  #puts array
  puts array.size()
  puts string
end

array = Array.new()
#array << "test"
#array << "sample"
#array << "good"
#array << "bad"
array.push("test")
array.push("sample")
array.push("good")
array.push("bad")
strings = array.find do |i|
  i =~ /b../
end
puts strings

#roop(array)


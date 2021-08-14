


hash = {"Test" => "test", "Sample" => "sample"}
array = ["Test", "Sample"]

p "\hash.each do |value|"
hash.each do |value|
  p value
end
p "array.each do |value|"
array.each do |value|
  p value
end

p "hash.each_value {|value|"
hash.each_value {|value|
  p value
}
#p "array.each_value {|value|"
#array.each_value {|value|
#  p value
#}

p "hash.each_pair {|key, value|"
hash.each_pair {|key, value|
  p key
  p value
}
#p "array.each_pair {|key, value|"
#array.each_pair {|key, value|
#  p value
#}

p "hash.each_key {|value|"
hash.each_key {|value|
  p value
}
#p "array.each_key {|value|"
#array.each_key {|value|
#  p value
#}

p "hash.each_with_index {|value|"
hash.each_with_index {|value, index|
  p value
  p index
}
p "array.each_with_index {|value|"
array.each_with_index {|value, index|
  p value
  p index
}



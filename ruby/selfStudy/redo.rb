
array = [1, 2, 3, 4, 5]
sum = 0
array.each do |num|
  sum += num
  if sum %3 == 0
    redo
  end
end

puts sum # => 26

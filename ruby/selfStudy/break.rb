array = [1, 2, 3, -1, 1, 2, 3]
sum = 0
array.each do |num|
  if num < 0
    break
  end
  sum += num
end

puts sum # => 6



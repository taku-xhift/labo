
fruit = "apple"

thread = Thread.new(fruit) do |fruit|
  500000.times do |i|
    case i%3
    when 0
      fruit = "banana"
    when 1
      fruit = "orange"
    when 2
      fruit = "strawberry"
    end
#    sleep 1
  end
end

puts fruit
sleep 2
puts fruit
sleep 2
puts fruit


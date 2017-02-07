
require 'date'

def chg_month(list, &block)
  result = []
  unless block
    list.each do |i|
      next unless 0 < i && i < 13
      n = Date::MONTHNAMES[i]
      result << n  if n
    end
  else
    list.each do |i|
      next unless 0 < i && i < 13
      n = block.call(i)
      result << n  if n
    end
  end
  result
end

array = chg_month([2, 3, 5, 7, 8, 9, 1, 10, 4, 13])
puts array
array = chg_month([2, 3, 5, 7, 8, 9, 1, 10, 4, 13]) {|m| "#{m} ŒŽ" }
puts array



class MyArray
  def initialize(ary)
    @ary = ary
  end
  
  def each1
    i = 0
    while i < @ary.size
      yield(@ary[i])
      i += 1
    end
  end
  
  def each2(&block)
    i = 0
    while i < @ary.size
      block.call(@ary[i])
      i += 1
    end
  end
  
  def omit_block1
    if defined? yield
      puts "block exist"
    else
      puts "block no exist"
    end
  end
  
  def omit_block2(&block)
    if block
      puts "block exist"
    else
      puts "block no exist"
      end
  end
  
  def select1
    array = []
    each1 do |i|
      array << i if yield(i)
    end
  end
  
  def select2(&block)
    array = []
    each2 do |i|
      array << i if block.call(i)
    end
  end
  
end
require 'date'

def chg_month(list, &block)
  i = 0
  array = []
  if block
    list.each do |i|
#      if ((0 < list[i] ) && (list[i] < 13))
#       array << block.call(list[i])
      #      end
      next unless  i >= 1 && i <= 12
      array << block.call(i)
    end
  else
    while i < list.size
      array << Date::MONTHNAMES[list[i]]
      i += 1
    end
  end
  array
end

array = chg_month([2, 3, 5, 7, 8, 9, 1, 10, 4, 13])
puts array
array = chg_month([2, 3, 5, 7, 8, 9, 1, 10, 4, 13]) {|m| "#{m} ŒŽ" }
puts array




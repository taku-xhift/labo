
class MyDate
  
  def initialize(year, month, day)
    @year = year
    @month = month
    @day = day
  end
  
  def <=>(target)
    ret = @year - target.year
    ret = @month - target.month  if ret == 0
    ret = @day - target.day  if ret == 0
    ret
  end
  
protected
  def year
    @year
  end
  def month
    @month
  end
  def day
    @day
  end
end

date1 = MyDate.new(2009, 1, 10)
date2 = MyDate.new(2009, 1, 15)

puts date1 <=> date2


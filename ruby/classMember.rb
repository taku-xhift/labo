
class Employee
  @@corp_name = "PONDA"
  def corp_name
    @@corp_name
  end
end

emp1 = Employee.new
puts emp1.corp_name

emp2 = Employee.new
puts emp2.corp_name

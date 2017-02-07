
require 'date'

# 型チェック
def check_type(type, instance, nullable =false)

    if (instance.nil?)
        unless (nullable)
            raise ArgumentError.new("non-nil constraint vioration")
        end
    else
        unless (instance.kind_of?(type))
            raise(ArgumentError::new("type mismatch: #{instance.class} for #{type}"))
        end
    end

    return instance
end

# 「学生」クラス
class Student

    attr :id
    attr :fname
    attr :lname
    attr :birthday

    # 初期化
    def initialize(id, lname, fname, birthday)
        @id       =check_type(Integer, id,       false);
        @lname    =check_type(String,  lname,    false);
        @fname    =check_type(String,  fname,    false);
        @birthday =check_type(Date,    birthday, false);
    end
end # class Stundent


#student = Student.new(1, "Mike", "Manchester", Date::today)
student = Student.new(1, "Mike", "Manchester", Time.now)


p student



module TypeChecker
  # �^�`�F�b�N
  def check_type(type, instance, nullable = false)
    
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
end

module Mix

  include TypeChecker

  attr_accessor :name

  def initialize
    @name = "sample"
  end

  # define �̏ڍ׏��
  class Define
    include TypeChecker

    attr_reader :type
    attr_reader :name
    attr_reader :data
    attr_reader :comment

    # constructor
    # [type_]
    #       �^���Bstring �^
    # [name_]
    #       �ϐ����Bstring �^
    # [data_]
    #       �ϐ����Bstring �^
    # [comment_]
    #       �R�����g�Bsting �^
    def initialize(type_, name_, data_, comment_ = "")
#      $log.info(__LINE__.to_s + ", " + __FILE__)
#      $log.debug(type_)
#      $log.debug(type_.class)
#      $log.debug(name_)
#      $log.debug(name_.class)
#      $log.debug(data_)
#      $log.debug(data_.class)
      @type    = check_type(String, type_,    false);
      @name    = check_type(String, name_,    false);
      @data    = check_type(String, data_,    false);
      @comment = check_type(String, comment_, true);
    end
  end


  class ClassClass

    include TypeChecker

    def initialize
      @name = "name"
      out(@name)
    end
  end

end


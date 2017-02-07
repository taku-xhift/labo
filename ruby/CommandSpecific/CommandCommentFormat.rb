#! D:/PersonalTool/xyzzy/labolatory/ruby/CommandSpec/

# 他のメソッドで使用するようなモジュール郡
# Mix-in して使うことを想定

require File.dirname(__FILE__) + "/OrderHash"


module TypeChecker

  # 型チェック
  # [type_]
  #     欲しい型。クラス型
  # [instance_]
  #     型チェックを行いたいインスタンス。任意型
  # [nullable_ = false]
  #     nil チェックをしないかどうか。boolean 型(正確ではないが…)
  def check_type(type_, instance_, nullable_ = false)
    if (instance_.nil?)
      unless (nullable_)
        raise ArgumentError.new("non-nil constraint vioration")
      end
    else
      unless (instance_.kind_of?(type_))
        @log.fatal(__LINE__.to_s + ", " + __FILE__)
        @log.fatal(type_)
        @log.fatal(instance_.class)
        @log.fatal("type mismatch: #{instance_.class} for #{type_}")
        raise(ArgumentError::new("In this file -> " + @fileName + ", " +"type mismatch: #{instance_.class} for #{type_}"))
      end
    end

    instance_
  end

end


module CommandCommentFormat

  include TypeChecker

  # 初期化。Mix-in された先で必ず使うと思われるもの。
  def initialize(fileName_)
    super()
    @fileName = fileName_           # 今回解析するファイル名
    @struct = OrderHash.new         # 構造体のハッシュ
    @enum = OrderHash.new           # enum のハッシュ
    @define = OrderHash.new         # define のハッシュ
    @commandStruct = OrderHash.new  # COMMAND のハッシュ。keyList 完成のために保存しているだけ。
    @returnValue = OrderHash.new    # Return_Value の一覧保存先。
    @includeFiles = OrderHash.new   # include するファイル。key で headder と source に分かれている

    #@log = Logger.new(logFileName(@fileName))
    #@log.level = Logger::DEBUG
    #@log.level = Logger::FATAL

    @includeFiles[headderFileName(@fileName)] = []
    @includeFiles[structHeadderFileName(@fileName)] = []
    @includeFiles[converterHeadderFileName(@fileName)] = []
    @includeFiles[converterSourceFileName(@fileName)] = []
    @includeFiles[commandCreaterHeadderFileName(@fileName)] = []
    @includeFiles[commandCreaterSourceFileName(@fileName)] = []

  end

  Regexp_ParseDefine = /(?:DEFINE\s+)(\w*)(?:\s*)(\w*)(?::)(?:\s*)(\w*)/
  Regexp_ParseStruct = /(?:^STRUCT\s+)(\w+)(?:\s*)(?:.*)/
  Regexp_ParseEnum = /(?:^ENUM\s+)(\w*)(?:\s*)(\w*)(?:\s*)/
  Regexp_ParseCommandStruct = /(?:^COMMAND\s+)(\w*)(?:\s*)(?:.*)/

  STRING_ENUM = "ENUM"          # 定数。ENUM を文字列定義したもの
  STRING_STRING = "STRING"      # 定数。STRING  を文字列定義したもの
  STRING_INT = "INT"            # 定数。INT     を文字列定義したもの
  STRING_FLOAT = "FLOAT"        # 定数。FLOAT   を文字列定義したもの
  STRING_CHAR = "CHAR"          # 定数。CHAR    を文字列定義したもの
  STRING_INTARRAY = "INTARRAY"  # 定数。FLOAT   を文字列定義したもの
  STRING_FLOATARRAY = "FLOATARRAY"          # 定数。CHAR    を文字列定義したもの

  STRING_HEADDER = "headder"    # 定数。headder を文字列定義したもの
  STRING_SOURCE = "source"      # 定数。source  を文字列定義したもの

  SPACE_TYPEANDNAME = 4
  SPACE_NAMEANDCOMMENT = 4




  # 構造体のメンバ情報
  class Member
    include TypeChecker

    attr_reader :ownType     # メンバの型情報。string 型
    attr_reader :ownName     # メンバ名。string 型
    attr_reader :comment     # メンバのコメント。string 型

    # constructor
    # [type]
    #       型情報。string 型
    # [name]
    #       変数名。string 型
    # [comment]
    #       コメント。sting 型
    def initialize(type_, name_, comment_)
        @ownType = check_type(String, type_,    false);
        @ownName = check_type(String, name_,    false);
        @comment = check_type(String, comment_, false);
    end
  end

  # 構造体の情報
  class Structure
    include TypeChecker

    attr_reader :ownName    # 構造体名。string 型
    attr_reader :comment    # 構造体に対するコメント。string 型
    attr_reader :member     # 構造体に所属するメンバの配列。Member 型

public

    # constructor
    # [name]
    #       変数名。string 型
    # [comment]
    #       コメント。sting 型
    def initialize(name_, comment_ = "")
      @ownName = check_type(String, name_,    false);
      @comment = check_type(String, comment_, true);
      @member  = Array.new
    end

    # adder. メンバを追加するだけ
    # [member_]
    #       メンバ。Member 型
    def addMember(member_)
      if hasMember?(member_)
        @log.fatal(__LINE__.to_s + ", " + __FILE__)
        @log.fatal(member_)
        @log.fatal("In this file -> " + @fileName + ", " +"The member is already Registered!! -> " + member_.ownName)
        raise AlreadyRegisteredError, "In this file -> " + @fileName + ", " +"The member is already Registered!! -> " + member_.ownName
      end

      @member << check_type(Member, member_, false);
    end

    # 既に同じ名前のメンバがいるかどうか？
    # [member_]
    #       メンバ。Member 型
    def hasMember?(member_)
      returnValue = false
      @member.each do |value|
        if value.ownName == member_.ownName
          returnValue = true
          break
        end
      end
      returnValue
    end
  end

  # enum の情報
  class Enumerate
    include TypeChecker

    attr_reader :ownName    # enum 名。string 型
    attr_reader :ownType    # enum の型。string 型
    attr_reader :comment    # enum に対するコメント。string 型
    attr_reader :member     # enum に所属するメンバの配列。Member 型

    # constructor
    # [name_]
    #       変数名。string 型
    # [type_]
    #       変数名。string 型
    # [comment_]
    #       コメント。sting 型
    def initialize(name_, type_, comment_ = "")
      @ownName = check_type(String, name_,    false);
      @ownType = check_type(String, type_,    false);
      @comment = check_type(String, comment_, true);
      @member  = Array.new
    end

    # adder. メンバを追加するだけ
    # [member_]
    #       メンバ。Member 型
    def addMember(member_)
      @member << check_type(Member, member_, false);
    end
  end

  # define の詳細情報
  class Define
    include TypeChecker

    attr_reader :ownType
    attr_reader :ownName
    attr_reader :data
    attr_reader :comment

    # constructor
    # [type_]
    #       型情報。string 型
    # [name_]
    #       変数名。string 型
    # [data_]
    #       変数名。string 型
    # [comment_]
    #       コメント。sting 型
    def initialize(type_, name_, data_, comment_ = "")
      @ownType = check_type(String, type_,    false);
      @ownName = check_type(String, name_,    false);
      @data    = check_type(String, data_,    false);
      @comment = check_type(String, comment_, true);
    end
  end


  # 構造体のメンバデータを
  #     Structure の配列を返す関数
  # [line_]
  #     ファイルから読み取ったメンバ情報。String 型
  def createStructMember(line_)
    temp = nil

    # よくあるミスの防止
    if line_ =~ /;/
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Instead of \";\", use \":\". -> " + line_)
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"Instead of \";\", use \":\". -> " + line_
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"; の代わりに : を使用してください -> " + line_
    end

    # [min...max] の構文を C 用 [max] に修正
    # ついでに min の文字数文だけスペースを補完
    if line_ =~ /(.*\[)(.*\.\.\.*)(.*\]:)(.*)/
      line_ = $1 + $3 + " " * $2.size + $4 + "\n"
    end

    # " INT id: (コメント)" の様な文字列から必要要素を取り出す
    line_ =~ /(?:\s*)(\w*)(?:\s*)(.*)(?::)(?:\s*)(?:\(|（)(.*)(?:\)|）)/
    if $1 != nil && $2 != nil && $3 != nil
      temp = Member.new($1, $2, $3)
    elsif $1 == nil && $2 == nil && $3 == nil
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"There is some syntax error!! -> " + line_ + "\n")
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"There is some syntax error!! -> " + line_ + "\n"
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"どこか構文エラーがあります -> " + line_ + "\n"
    elsif $1 == nil
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Can't find a type!! -> " + line_ + "\n")
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"Can't find a type!! -> " + line_ + "\n"
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"型が見つかりませんでした -> " + line_ + "\n"
    elsif $2 == nil
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Can't find a member!! -> " + line_ + "\n")
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"Can't find a member!! -> " + line_ + "\n"
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"メンバ名が見つかりませんでした -> " + line_ + "\n"
    elsif $3 == nil
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Can't find a comment!! -> " + line_ + "\n")
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"Can't find a comment!! -> " + line_ + "\n"
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"コメントが見つかりませんでした -> " + line_ + "\n"
    end
    temp
  end


  # 構造体のメンバデータを
  #     Structure の配列を返す関数
  # [line_]
  #     ファイルから読み取ったメンバ情報。String 型
  def createEnumerateMember(type_, line_)
    temp = nil

    # よくあるミスの防止
    if line_ =~ /;/
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Instead of \";\", use \":\". -> " + line_)
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"Instead of \";\", use \":\". -> " + line_
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"; の代わりに : を使用してください -> " + line_
    end
    unless line_ =~ /:/
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Can't find \":\". -> " + line_)
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"Can't find \":\". -> " + line_
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +": が使用されていません -> " + line_
    end

    # "	"win": (コメント)" の様な文字列から必要要素を取り出す
    line_ =~ /(?:\s*)(?:\")(\w*)(?:\")(?:\s*)(?::)(?:\s*)(?:\(|（)(.*)(?:\)|）)/
    if $1 != nil && $2 != nil
      temp = Member.new(type_.chomp.strip, $1.chomp.strip, $2.chomp.strip)
    elsif $1 == nil && $2 == nil && $3 == nil
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"There is some syntax error!! -> " + line_ + "\n")
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"There is some syntax error!! -> " + line_ + "\n"
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"どこか構文エラーがあります -> " + line_ + "\n"
    elsif $1 == nil
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Can't find a type!! -> " + line_ + "\n")
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"Can't find a type!! -> " + line_ + "\n"
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"型が見つかりませんでした -> " + line_ + "\n"
    elsif $2 == nil
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Can't find a member!! -> " + line_ + "\n")
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"Can't find a member!! -> " + line_ + "\n"
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"メンバ名が見つかりませんでした -> " + line_ + "\n"
    elsif $3 == nil
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Can't find a comment!! -> " + line_ + "\n")
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"Can't find a comment!! -> " + line_ + "\n"
      raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"コメントが見つかりませんでした -> " + line_ + "\n"
    end
    temp
  end


  # 構造体のメンバデータを
  #     Structure の配列を返す関数
  # [name_]
  #     構造体名。String 型
  # [comment_]
  #     構造体の詳細情報が入ったコメント。String 型
  # [memberArray_]
  #     メンバ情報。Member 型
  def createStruct(name_, comment_, *memberArray_)
    data = Structure.new(name_.chomp.strip, comment_)
    if memberArray_
      memberArray_.each do |i|
        data.addMember(i)
      end
    end
    data
  end


  # enum のデータを Enumerate で返す関数
  # [name_]
  #     enum 名。String 型
  # [type_]
  #     enum の型。String 型
  # [comment_]
  #     enum の詳細情報が入ったコメント。String 型
  # [memberArray_]
  #     メンバ情報。Member 型
  def createEnumerate(name_ ,type_, comment_ = "", *memberArray_)
    data = Enumerate.new(name_.chomp.strip, type_, comment_)
    if memberArray_
      memberArray_.each do |i|
        data.addMember(i)
      end
    end
    data
  end


  # 行情報から Define を作成する
  # [line_]
  #     define 情報を含んだ列。string 型
  # [comment_]
  #     コメント情報を含んだ列。string 型
  def createDefine(line_, comment_)
    if comment_ == nil
      comment_ = ""
    end

    # よくあるミスの防止
    if line_ =~ /;/
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Instead of \";\", use \":\". -> " + line)
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"Instead of \";\", use \":\". -> " + line
      raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"; の代わりに : を使用してください -> " + line
    end

    returnData = nil

    # " INT id: (コメント)" の様な文字列から必要要素を取り出す
    # "DEFINE INT latestGameNumberMax:    100" のようなものを解析する
    line_ =~ Regexp_ParseDefine
    if $1 != nil && $2 != nil && $3 != nil
      @log.info(__LINE__.to_s + ", " + __FILE__)
      @log.debug($1)
      @log.debug($2)
      @log.debug($3)
      @log.debug(comment_)
      returnData = Define.new($1.chomp.strip, $2.chomp.strip, $3.chomp.strip, comment_.chomp.strip)
    elsif $1 != nil
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Can't find a type!! -> " + line_ + "\n")
      raise TypeUnDefindError, "In this file -> " + @fileName + ", " +"Can't find a type!! -> " + line_ + "\n"
      raise TypeUnDefindError, "In this file -> " + @fileName + ", " +"型が見つかりませんでした!! -> " + line_ + "\n"
    elsif $2 != nil
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Can't find a name!! -> " + line_ + "\n")
      raise TypeUnDefindError, "In this file -> " + @fileName + ", " +"Can't find a name!! -> " + line_ + "\n"
      raise TypeUnDefindError, "In this file -> " + @fileName + ", " +"定義名が見つかりませんでした -> " + line_ + "\n"
    elsif $3 != nil
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Can't find a data!! -> " + line_ + "\n")
      raise TypeUnDefindError, "In this file -> " + @fileName + ", " +"Can't find a data!! -> " + line_ + "\n"
      raise TypeUnDefindError, "In this file -> " + @fileName + ", " +"データが見つかりませんでした -> " + line_ + "\n"
    end

    returnData
  end


  # @(コマンド)に対応したコメントを追加していく
  # [hashData]
  #     コマンド情報
  def createCommandComment(hashData_)
    # Hash をループでまわさないのは、C でコメントとして読む際に
    # 毎回ランダムに生成されていたのでは読みづらいため
    string = ""
    if hashData_.has_key?("@COMMAND")
      string << " * @note   command"
      string << hashData_["@COMMAND"].chomp
      string << " を実装\n"
    end
    if hashData_.has_key?("@BRIEF")
      string << " * @BRIEF"
      string << hashData_["@BRIEF"]
    end
    if hashData_.has_key?("@PURPOSE")
      string << " * @PURPOSE"
      string << hashData_["@PURPOSE"]
    end
    if hashData_.has_key?("@USER")
      string << " * @USER"
      string << hashData_["@USER"]
    end
    if hashData_.has_key?("@ERROR")
      string << " * @ERROR"
      string << hashData_["@ERROR"]
    end
    if hashData_.has_key?("@RETVAL")
      string << " * @RETVAL"
      string << hashData_["@RETVAL"]
    end
    string
  end


  # ファイルのヘッダ部分を作成する
  # [commandHash]
  #     日付、著者情報などを記載
  #     ファイルヘッダに書き足したい情報を入れる
  def createFileHeadder(commandHash)
    string  = "/**\n"
    string << " * @file\n"
    string << createCommandComment(commandHash)
    string << " *\n"
    string << " * @version 0.01"
    if commandHash.has_key?("AUTHOR")
      string << ", "
      string << commandHash["AUTHOR"].chomp
    end
    if commandHash.has_key?("DATE")
      string << ", "
      string << commandHash["DATE"].chomp
    end
    string << "\n"
    string << " *      (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.\n"
    string << "*/\n"
    string << "\n"
    string
  end


  # include guard の作成
  # [writeFileName]
  #     書き込み予定のファイルの名前
  def createIncludeGuard(writeFileName)
    defineString = writeFileName.upcase.sub(/\./, "_").sub(/_HPP/, "_HPP_INCLUDED")
    string = "#ifndef " + defineString + "\n"
    string = string + "#define " + defineString + "\n"
    string
  end

  # 関数用ののコメントを作成する。doxygen にのっとった形になる。
  # [hashData_]
  #     コマンドをキーにしたコメント情報
  def createFunctionComment(hashData_)
    string = "/**----------------------------------------------------\n"
    string << createCommandComment(hashData_)
    string << " *---------------------------------------------------*/\n"
    string
  end

  # マーカーを作成する
  # [name_]
  #     マーカーの名前
  def createMarker(name_)
    string = <<EOS
//---------------------------------------------------------
//  #{name_}
//---------------------------------------------------------
EOS
    string
  end


  # [fileLines]
  #     読み取ったファイル情報。Array-String 型
  def parse(fileLines)
    # 受け取ったファイル情報を解析開始
    fileLines.each do |line|
      case line
      when /　/
        @log.fatal(__LINE__.to_s + ", " + __FILE__)
        @log.fatal("In this file -> " + @fileName + ", " + "Use Twobyte space!!")
        raise UseDoubleByteSpaceError, "In this file -> " + @fileName + ", " + "Use Twobyte space!!"
      when /@BRIEF/
        @log.info(__LINE__.to_s + ", " + __FILE__)
        #@tempArray.clear
        if @command.has_key?("@BRIEF") && @command.has_key?("@COMMAND")
          # BRIEF１度も出力しないままで、COMMAND が解析データに含まれている
          #     => ヘッダ部分の出力だと思われる
          @log.info("has COMMAND")
          temp = createFileHeadder(@command)
          @headderBaffer << temp
          #TODO
          @command.clear
        end
        @command["@BRIEF"] = $'
      when /@COMMAND/
        @command["@COMMAND"] = $'
      when /@PURPOSE/
        @command["@PURPOSE"] = $'
      when /@USER/
        @command["@USER"] = $'
      when /@AUTHOR/
        @command["@AUTHOR"] = $'
      when /@DATE/
        @command["@DATE"] = $'
      when /@ERROR/
        @command["@ERROR"] = $'
      when /@INCLUDE/
        $' =~ /(?:\s*)(.*)/
        includeFile = $1
        @includeFiles[headderFileName(@fileName)] << headderFileName(includeFile)
        includeCheck(includeFile, @struct, @commandStruct, @enum, @define)
      when /@RETVAL/
        @command["@RETVAL"] = $'
      when /@UPDATE/
        @command["@UPDATE"] = $'
      when /^ENUM\s+/
        @log.info(__LINE__.to_s + ", " + __FILE__)
        # 次のような文字列を期待している
        # ENUM STRING Result {
        # (ENUM ) までは既に正規表現でマッチしているのでその他の部分を解析
        $' =~ /(\w*)(?:\s*)(\w*)(?:\s*)/
        @log.debug($2)
        @command["ENUM"] = [$1, $2]
      when /^STRUCT\s+/
        line =~ Regexp_ParseStruct
        @command["STRUCT"] = $1
      when /^DEFINE\s+/
        @log.info(__LINE__.to_s + ", " + __FILE__)
        @log.debug(@define)
        define = createDefine(line, @command["@BRIEF"])
        unless @define.has_key?(define.ownName)
          @define[define.ownName] = define
        else
          @log.fatal(__LINE__.to_s + ", " + __FILE__)
          @log.fatal("In this file -> " + @fileName + ", " +"The object is aready registered!! -> " + line)
          raise AlreadyRegisteredError, "In this file -> " + @fileName + ", " +"The object is aready registered!! -> " + line
          raise AlreadyRegisteredError, "In this file -> " + @fileName + ", " +"そのオブジェクトは既に定義されています -> " + line
        end
        @command.clear
      when /^RETURN_VALUE\s+/
      when /^COMMAND\s+/
        string = $'.sub(/\{/, "").strip
        @command["COMMAND"] = string
      when /\}$/
        if @command.has_key?("STRUCT")
          @log.info(__LINE__.to_s + ", " + __FILE__)
          raise AlreadyRegisteredError, "In this file -> " + @fileName + ", " +"The structure is already registered!!" if (@struct.has_key?(@command["STRUCT"]) || @enum.has_key?(@command["STRUCT"]))

          array = Array.new
          @tempArray.each do |i|
            array << createStructMember(i)
          end
          @struct[@command["STRUCT"]] = createStruct(@command["STRUCT"], createFunctionComment(@command), *array)
          @tempArray.clear
          @command.clear
        elsif @command.has_key?("COMMAND")
          @log.info(__LINE__.to_s + ", " + __FILE__)
          array = Array.new
          @tempArray.each do |i|
            array << createStructMember(i)
          end

          if @commandStruct.has_key?(@command["COMMAND"])
            array.each do |element|
              unless @commandStruct[@command["COMMAND"]].hasMember?(element)
                @commandStruct[@command["COMMAND"]].addMember(element)
              end
            end
          else
            @commandStruct[@command["COMMAND"]] = createStruct(@command["COMMAND"], createFunctionComment(@command), *array)
          end
          @tempArray.clear
          @command.clear
        elsif @command.has_key?("ENUM")
          @log.info(__LINE__.to_s + ", " + __FILE__)
          raise AlreadyRegisteredError, "In this file -> " + @fileName + ", " +"The structure is already registered!!" if (@struct.has_key?(@command["ENUM"]) || @enum.has_key?(@command["ENUM"]))

          array = Array.new
          @tempArray.each do |i|
            array << createEnumerateMember(@command["ENUM"][0], i)
          end
          @enum[@command["ENUM"][1]] = createEnumerate(@command["ENUM"][1], @command["ENUM"][0], createFunctionComment(@command), *array)
          @log.info(__LINE__.to_s + ", " + __FILE__)
          @log.debug(@command["ENUM"][1])
          @log.debug(@enum[@command["ENUM"][1]])
          @log.debug(createFunctionComment(@command))
          @tempArray.clear
          @command.clear
        end
      when /^\#/
      when /^\n/
      else
        @log.info(__LINE__.to_s + ", " + __FILE__)
        @log.info("There is some valid data.")
        @log.debug(line)
        @tempArray << line
      end
    end
  end



  # include して structName と define を集めてくる
  #    但し、渡された struct_ と define_ に既に同じ名前の要素があれば例外発生
  # [fileName_]
  #     マーカーの名前。string
  # [struct_]
  #     構造体の出力先。hash
  # [define_]
  #     define の出力先。hash
  def includeCheck(fileName_, struct_, commandStruct_, enum_, define_)
    unless File.exist?(fileName_)
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Don't exist such file!! -> " + fileName_)
      raise NoFileError, "In this file -> " + @fileName + ", " +"Don't exist such file!! -> " + fileName_
    end

    f = File.open(fileName_, "r") do |f|
      # ファイルを読み取り
      line = f.readlines()

      # 文字列のエンコード
      encordedStrings = String.new
      line.each do |i|
        fileLines << i.toutf8
      end

      case strings
      when /(?:^@include)(?:\s+)(\w+)/
        includeCheck($1, struct_, define_)
      when Regexp_ParseStruct
        name = $1
        if struct_.has_key?(name) || enum_.has_key?(name) || define_.has_key?(name)
          @log.fatal(__LINE__.to_s + ", " + __FILE__)
          @log.fatal("In this file -> " + @fileName + ", " +"The Struct is already registered!! -> " + name)
          raise AlreadyRegisteredError, "In this file -> " + @fileName + ", " +"The Struct is already registered!! -> " + name
        else
          struct_[name] = nil
        end
      when Regexp_ParseDefine
        #DEFINE INT latestGameNumberMax:    100 のような形
        type = $1
        name = $2
        data = $3
        if struct_.has_key?(name) || enum_.has_key?(name) || define_.has_key?(name)
          @log.fatal(__LINE__.to_s + ", " + __FILE__)
          @log.fatal("In this file -> " + @fileName + ", " +"The Struct is already registered!! -> " + name)
          raise AlreadyRegisteredError, "In this file -> " + @fileName + ", " +"The Define is already registered!! -> " + name
        else
          define_[name] = nil
        end
      when Regexp_ParseEnum
        #ENUM STRING Result { のような形
        type = $1
        name = $2
        if struct_.has_key?(name) || enum_.has_key?(name) || define_.has_key?(name)
          @log.fatal(__LINE__.to_s + ", " + __FILE__)
          @log.fatal("In this file -> " + @fileName + ", " +"The Struct is already registered!! -> " + name)
          raise AlreadyRegisteredError, "In this file -> " + @fileName + ", " +"The Define is already registered!! -> " + name
        else
          enum_[name] = nil
        end
      end
    end
  end


  # include 文字列を作成する
  # [file_]
  #     include するファイル名。String 型
  def createIncludeString(file_)
#      @log.fatal(__LINE__.to_s + ", " + __FILE__)
#      @log.fatal(file_)

    string = ""
    case file_
    when "exception", "iostream", "new", "ostream", "sstream", "string", "algorithm", "bitset", "functional", "list", "map", "numeric", "set", "vector", "cassert", "assert.h", "malloc.h", "stdio.h", "cstdio", "stdlib.h", "cstdlib", "limits.h", "climits", "string.h", "cstring"
      string = "#include \<#{file_}\>\n"
    else
      string = "#include \"#{file_}\"\n"
    end
  end


  # struct の作成
  # [structName_]
  #     構造体につける名前。String 型
  # [struct_]
  #     構造体情報。Structure 型
  def createStructBaffer(structName_, data_, comment_)
    string = ""

    # 文字列調整用
    maxTypeSize = "Boolean".length
    maxNameSize = "isDefault".length
    data_.member.each do |member|
      @log.info(__LINE__.to_s + ", " + __FILE__)
      @log.debug(member.ownName.length)
      @log.debug(member.ownName.length.class)
      @log.debug(maxNameSize)
      @log.debug(maxNameSize.class)
      if member.ownType == STRING_INT || member.ownType == STRING_FLOAT || member.ownType == STRING_CHAR || member.ownType == STRING_STRING
        maxTypeSize = member.ownType.length+2 if maxTypeSize < member.ownType.length+2 # +2 は we とつける分
      elsif @enum.has_key?(member.ownType)
        maxTypeSize = @enum[member.ownType].ownType.length+2 if maxTypeSize < @enum[member.ownType].ownType.length+2 # +2 は we とつける分
      else
        maxTypeSize = member.ownType.length if maxTypeSize < member.ownType.length
      end
      maxNameSize = member.ownName.length if maxNameSize < member.ownName.length
    end

    string << comment_
    string << "typedef struct {\n"

    data_.member.each do |member|
      if @struct.has_key?(member.ownType)
        # 最低１個はスペースが入るので +1 されている
        string << "	" + member.ownType + " "*(maxTypeSize+1 +(SPACE_NAMEANDCOMMENT) -member.ownType.length) + member.ownName + ";" + " "*(maxNameSize+1 +(SPACE_NAMEANDCOMMENT) -member.ownName.length) + "/**< " + member.comment + " */\n"
      elsif @enum.has_key?(member.ownType)
        # 最低１個はスペースが入るので +1 されている。-2 は we とつく分。
        string << "	we" + @enum[member.ownType].ownType.capitalize + " "*(maxTypeSize+1 +(SPACE_NAMEANDCOMMENT) -@enum[member.ownType].ownType.length-2) + member.ownName + ";" + " "*(maxNameSize+1 +(SPACE_NAMEANDCOMMENT) -member.ownName.length) + "/**< " + member.comment + " */\n"
      else
        string << "	we" + member.ownType.capitalize + " "*(maxTypeSize+1 +(SPACE_NAMEANDCOMMENT) -member.ownType.length-2) + member.ownName + ";" + " "*(maxNameSize+1 +(SPACE_NAMEANDCOMMENT) -member.ownName.length) + "/**< " + member.comment + " */\n"
      end
    end
    string << "	Boolean" + " "*(maxTypeSize+1 +(SPACE_NAMEANDCOMMENT) -"Boolean".length) + "isDefault;" + " "*(maxNameSize+1 +(SPACE_NAMEANDCOMMENT) -"isDefault".length) + "/**< 変更済みかどうかをチェックするためのメンバ */\n"
    string << "} " + structName_ + ";\n"
    string
  end


  # struct の作成
  # [structName_]
  #     構造体につける名前。String 型
  # [struct_]
  #     構造体情報。Structure 型
  # [comment_]
  #     コメント情報。String 型
  def createDirectionStructBaffer(structName_, data_, comment_)
    string = ""
    useListString = "useList\[" + data_.member.size.to_s + "\]"

    # 文字列調整用
    maxTypeSize = "weInt".length
    maxNameSize = useListString.length
    data_.member.each do |member|
      @log.info(__LINE__.to_s + ", " + __FILE__)
      @log.debug(member.ownName.length)
      @log.debug(member.ownName.length.class)
      @log.debug(maxNameSize)
      @log.debug(maxNameSize.class)
      if member.ownType == STRING_INT || member.ownType == STRING_FLOAT || member.ownType == STRING_CHAR || member.ownType == STRING_STRING
        maxTypeSize = member.ownType.length+2 if maxTypeSize < member.ownType.length+2 # +2 は we とつける分
      elsif @enum.has_key?(member.ownType)
        maxTypeSize = @enum[member.ownType].ownType.length+2 if maxTypeSize < @enum[member.ownType].ownType.length+2 # +2 は we とつける分
      else
        maxTypeSize = member.ownType.length if maxTypeSize < member.ownType.length
      end
      maxNameSize = member.ownName.length if maxNameSize < member.ownName.length
    end

    string << comment_
    string << "typedef struct {\n"

    data_.member.each do |member|
      if @struct.has_key?(member.ownType)
        # 最低１個はスペースが入るので +1 されている
        string << "	" + member.ownType + " "*(maxTypeSize+1 +(SPACE_NAMEANDCOMMENT) -member.ownType.length) + member.ownName + ";" + " "*(maxNameSize+1 +(SPACE_NAMEANDCOMMENT) -member.ownName.length) + "/**< " + member.comment + " */\n"
      elsif @enum.has_key?(member.ownType)
        # 最低１個はスペースが入るので +1 されている。-2 は we とつく分。
        string << "	we" + @enum[member.ownType].ownType.capitalize + " "*(maxTypeSize+1 +(SPACE_NAMEANDCOMMENT) -@enum[member.ownType].ownType.length-2) + member.ownName + ";" + " "*(maxNameSize+1 +(SPACE_NAMEANDCOMMENT) -member.ownName.length) + "/**< " + member.comment + " */\n"
      else
        string << "	we" + member.ownType.capitalize + " "*(maxTypeSize+1 +(SPACE_NAMEANDCOMMENT) -member.ownType.length-2) + member.ownName + ";" + " "*(maxNameSize+1 +(SPACE_NAMEANDCOMMENT) -member.ownName.length) + "/**< " + member.comment + " */\n"
      end
    end
    string << "	weInt" + " "*(maxTypeSize+1 +(SPACE_NAMEANDCOMMENT) -"weInt".length) + useListString + ";" + " "*(maxNameSize+1 +(SPACE_NAMEANDCOMMENT) -useListString.length) + "/**< 使用するかかどうかをチェックするためのメンバ */\n"
    string << "} " + structName_ + ";\n"
    string
  end



###########################################################
#  CreateHPP.rb
###########################################################

  # define の作成
  # [define_]
  #     define が書かれた文字列のデータ
  def createDefineBaffer(define_)
    @log.info(__LINE__.to_s + ", " + __FILE__)
    @log.debug(define_.ownType)
    string = ""
    if define_.ownType =~ /(CHAR|INT|FLOAT|STRING)/
      string = "\#define " + define_.ownName + " " + define_.data + " "*(SPACE_NAMEANDCOMMENT) + "/**< " + define_.comment + " */\n"
    else
      string = "\#define " + define_.ownName + " " + define_.data + " "*(SPACE_NAMEANDCOMMENT) + "/**< " + define_.comment + " */\n"
    end
    string
  end


  # enum の作成
  # [data_]
  #     enum 情報。Enumerate 型
  def createEnumBaffer(data_)
    string = ""

    maxNameSize = 0
    data_.member.each do |member|
      maxNameSize = member.ownName.length if maxNameSize < member.ownName.length
    end

    string << data_.comment
    if data_.ownType == "INT"
      string << "typedef struct {\n"
      data_.member.each do |member|
        string << "	" + member.ownName + "," + " "*(maxNameSize+1 +(SPACE_NAMEANDCOMMENT) -member.ownName.length) + "/**< " + member.comment + " */\n"
      end
      string << "} " + data_.ownName + ";\n"
    else
      data_.member.each do |member|
        string << "static const we" + member.ownType.capitalize + " enum_" + data_.ownName + "_" + member.ownName + " = \"" + member.ownName + "\";" + " "*((SPACE_NAMEANDCOMMENT)+2*(maxNameSize-member.ownName.length)) + "/**< " + member.comment + " */\n"
      end
    end
    string
  end


  # 構造体作成関数の実装部作成。コメント文は他に託す。
  # [structName_]
  #     作成する構造体の名前。文字列
  # [structData_]
  #     作成する構造体のメンバ情報が含まれた配列。
  def structCreaterImplementation(structName_, structData_)
    @log.info(__LINE__.to_s + ", " + __FILE__)
    @log.debug(structName_)
    @log.debug(structData_)

    string = structCreaterDeclaration(structName_).chomp.sub(/;/, "\n")
    string << "{\n"
    string << "	#{structName_} data;\n\n"
    string << "	int i = 0;\n"

    structData_.member.each do |member|
      if member.ownName =~ /(?:\[)(.+)(?:\])/
        string << "	for (i = 0; i < #{$1}; ++i) {\n"
        string << "		data.#{member.ownName.sub(/\[.+\]/, "\[i\]")} = "
      else
        string << "	data.#{member.ownName} = "
      end

      # 型に合わせて初期化の値を変える
      # enum の場合だけ冗長な気もするが…
      if member.ownType == "INT"
        string << "INT_MAX"
      elsif member.ownType == "FLOAT"
        string << "FLT_MAX"
      elsif member.ownType == "CHAR"
        string << "\'\\0\'"
      elsif member.ownType == "STRING"
        string << "\'\\0\'"
      else
        if @struct.has_key?(member.ownType)
          string << "create#{@struct[member.ownType].ownName}()"
        elsif @enum.has_key?(member.ownType)
          if @enum[member.ownType].ownType == "INT"
            string << "INT_MAX"
          elsif @enum[member.ownType].ownType == "FLOAT"
            string << "FLT_MAX"
          elsif @enum[member.ownType].ownType == "CHAR"
            string << "\'\\0\'"
          elsif @enum[member.ownType].ownType == "STRING"
            string << "\'\\0\'"
          end
        else
          @log.fatal(__LINE__.to_s + ", " + __FILE__)
          @log.fatal("In this file -> " + @fileName + ", " +"Undefined Type!! -> " + member.ownType)
          raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"Undefined Type!! -> " + member.ownType
          raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"定義されていない型があるようです -> " + member.ownType
        end

      end

      string << ";\n"

      if $&
        string << "	}\n"
      end
    end

    string << "	data.isDefault = FALSE;\n"
    string << "\n"
    string << "	return data;\n"
    string << "}\n"

    string
  end


###########################################################
#  Converter.rb
###########################################################

  # ストレージの宣言部を作成する
  def createStorageDeclaration(structName_)
    string = <<EOS
/**----------------------------------------------------
 * @brief storage
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_#{structName_}(const #{structName_}& data_, const char* key_);
EOS
    string
  end

  # ストレージの宣言部を作成する
  def createStorageArrayDeclaration(structName_)
    string = <<EOS
/**----------------------------------------------------
 * @brief storage
 * @param[in]   data_   格納するデータ
 * @param[in]   key_    キー
 * @return      data_ を一定書式に倣って格納したデータのアドレス
 *---------------------------------------------------*/
ReciprocateData* storage_#{structName_}Array(const std::vector<#{structName_}>& data_, const char* key_);
EOS
    string
  end


  # コンバートの宣言部を作成する
  def createConvertDeclaration(structName_, isImplementation)
    string = <<EOS
/**----------------------------------------------------
 * @brief converter
 * @param[in]   reciprocateData_    解析が必要なデータ
 * @para[in]    node_               配列の場合は欲しいデータの番号を指定。
 * @return      解析の結果得られたデータ。
 *                  配列ならば node_ の先頭で指定されたデータ。
 *---------------------------------------------------*/
EOS
    if isImplementation
      string << "#{structName_} convertTo#{structName_}(const ReciprocateData* reciprocateData_, std::vector<int> node_ /*= std::vector<int>()*/);\n"
    else
      string << "#{structName_} convertTo#{structName_}(const ReciprocateData* reciprocateData_, std::vector<int> node_ = std::vector<int>());\n"
    end
    string
  end


  # 基データから受け渡し構造体に変化するモジュールを作成する
  # [structData_]
  #     メンバの型とキー名(メンバ名)が配列になった配列
  def storageImplementation(structData_)
    string = ""

    string << createStorageDeclaration(structData_.ownName).chomp.sub(/;/, "\n")
    string <<  "{\n"
    string << "	ReciprocateData* container = createReciprocateData();\n"
    string << "	container->type = DATATYPE_STRUCT;\n"
    string << "    container->num = #{structData_.member.size};\n"
    string << "	container->key = key_;\n"
    string << "\n"
    string << "	container->value = reinterpret_cast<void**>(calloc(container->num, sizeof(void**)));\n"

    structData_.member.each_with_index {|item, index|
      # 配列かどうかの確認を行う
      if item.ownName =~ /\[/ && (item.ownName =~ /^CHAR/) == nil
      # 一つ目は、自分のメンバに配列アクセス情報を持っているかどうかの確認
      # ２つめは、定数でサイズが指定された配列の場合
      # に備えてのマッチング
      # なお、両方ともそのサイズ情報を $1 番目に持っています
        item.ownName =~ /(\w+)(?:\[)(.+)(?:\])/
        memberName = $1
        arraySize = $2

        if item.ownType == STRING_CHAR
          string << "	container->value[#{index}] = storage_String(data_.#{item.ownName.sub(/\[.*\]/, "")}, key_#{structData_.ownName}_#{item.ownName.sub(/\[.*\]/, "")});\n"
        elsif (item.ownType == STRING_STRING || item.ownType == STRING_CHAR || item.ownType == STRING_INT || item.ownType == STRING_FLOAT || item.ownType == STRING_INTARRAY || item.ownType == STRING_FLOATARRAY)
          string << "	container->value[#{index}] = storage_#{item.ownType.capitalize}Array(std::vector<we#{item.ownType.capitalize}> (&data_.#{memberName}[0], &data_.#{memberName}[#{arraySize.sub(/^this->/, "data.")}]), #{createKeyName(structData_.ownName, memberName)});\n"
        else
          string << "	container->value[#{index}] = storage_#{item.ownType}Array(std::vector<#{item.ownType}> (&data_.#{memberName}[0], &data_.#{memberName}[#{arraySize.sub(/^this->/, "data.")}]),  #{createKeyName(structData_.ownName, memberName)});\n"
        end
      else
        # 普通のデータだった場合
        if item.ownType == STRING_STRING || item.ownType == STRING_CHAR
          string << "	container->value[#{index}] = storage_String(&data_.#{item.ownName.sub(/\[.*\.\.\..*\]/, "")}, key_#{structData_.ownName}_#{item.ownName.sub(/\[.*\.\.\..*\]/, "")});\n"
        elsif item.ownType == STRING_INT
          string << "	container->value[#{index}] = storage_Int(data_.#{item.ownName.sub(/\[.*\.\.\..*\]/, "")}, key_#{structData_.ownName}_#{item.ownName.sub(/\[.*\.\.\..*\]/, "")});\n"
        elsif item.ownType == STRING_FLOAT
          string << "	container->value[#{index}] = storage_Float(data_.#{item.ownName.sub(/\[.*\.\.\..*\]/, "")}, key_#{structData_.ownName}_#{item.ownName.sub(/\[.*\.\.\..*\]/, "")});\n"
        elsif item.ownType == STRING_INTARRAY
          string << "	container->value[#{index}] = storage_IntArray(data_.#{item.ownName.sub(/\[.*\.\.\..*\]/, "")}, key_#{structData_.ownName}_#{item.ownName});\n"
        elsif item.ownType == STRING_FLOATARRAY
          string << "	container->value[#{index}] = storage_FloatArray(data_.#{item.ownName.sub(/\[.*\.\.\..*\]/, "")}, key_#{structData_.ownName}_#{item.ownName.sub(/\[.*\.\.\..*\]/, "")});\n"
        else
          if @enum.has_key?(item.ownType)
              string << "	container->value[#{index}] = storage_#{@enum[item.ownType].ownType.capitalize}(data_.#{item.ownName.sub(/\[.*\.\.\..*\]/, "")}, key_#{structData_.ownName}_#{item.ownName.sub(/\[.*\.\.\..*\]/, "")});\n"
          elsif @struct.has_key?(item.ownType)
            string << "	container->value[#{index}] = storage_#{item.ownType}(data_.#{item.ownName.sub(/\[.*\.\.\..*\]/, "")}, key_#{structName_}_#{item.ownName.sub(/\[.*\.\.\..*\]/, "")});\n"
          else
            @log.fatal(__LINE__.to_s + ", " + __FILE__)
            @log.fatal(@enum)
            @log.fatal(@struct)
            @log.fatal(structData_)
            @log.fatal(item.ownType)
            @log.fatal(item.ownName)
            raise TypeUnDefinedError, "The type is not defined."
            raise TypeUnDefinedError, "型定義エラー"
          end
        end
      end
    }    # structData_.each_with_index {|item, index|

    string << "\n"
    string << "	return container;\n"
    string << "}\n"

    string
  end


  # 基データから受け渡し構造体に変化するモジュールを作成する
  # [structData_]
  #     メンバの型とキー名(メンバ名)が配列になった配列
  def storageArrayImplementation(structData_)
    string = ""

    string << createStorageArrayDeclaration(structData_.ownName).chomp.sub(/;/, "\n")
    string <<  "{\n"
    string << "	ReciprocateData* container = createReciprocateData();\n"
    string << "	container->type = DATATYPE_STRUCTARRAY;\n"
    string << "    container->num = data_.size();\n"
    string << "	container->key = key_;\n"
    string << "\n"
    string << "	container->value = reinterpret_cast<void**>(calloc(container->num, sizeof(void**)));\n"

	string << "	for (int i = 0; i < container->num; ++i) {\n"
	string << "		container->value[i] = storage_#{structData_.ownName}(data_.at(i), key_);\n"
	string << "	}\n"

    string << "\n"
    string << "	return container;\n"
    string << "}\n"

    string
  end



  # 基データから受け渡し構造体に変化するモジュールを作成する
  # [structData_]
  #     構造体情報。Structure 型
  def converterImplementation(structData_)
    @log.info(__LINE__.to_s + ", " + __FILE__)
    @log.debug(structData_.ownName)
    @log.debug(structData_)

    string = createConvertDeclaration(structData_.ownName, true).chomp.sub(/;/, "\n")
    string << "{\n"
    string << "	#{structData_.ownName} data;\n"
    string << "	const void* value = NULL;\n"
    string << "\n"
    string << "	if (reciprocateData_->type != DATATYPE_STRUCT\n"
    string << "		&& reciprocateData_->type != DATATYPE_STRUCTARRAY)\n"
    string << "	{\n"
    string << "		// 渡されているデータが不正なものの可能性がある\n"
    string << "		userAssert(0, \"Probably reciprocateData_ is invalid!!\");\n"
    string << "		return create#{structData_.ownName}();\n"
    string << "	}\n"
    string << "\n"
    string << "	if (reciprocateData_->type == DATATYPE_STRUCTARRAY) {\n"
    string << "		if (node_.empty()) {\n"
    string << "			// 配列でない可能性がある。もしくは指定のミス\n"
    string << "			userAssert(0, \"node_ is empty!!\");\n"
    string << "			return create#{structData_.ownName}();\n"
    string << "		}\n"
    string << "	}\n"
    string << "\n"

    structData_.member.each_with_index {|item, index|
      # 配列か、かつ文字列をしまうだけの型でないかどうかの確認
      @log.info(__LINE__.to_s + ", " + __FILE__)
      @log.debug(item.ownName)
      @log.debug(item.ownName)

      if item.ownName =~ /\[/ && (item.ownType =~ /#{STRING_CHAR}/) == nil
        @log.info(__LINE__.to_s + ", " + __FILE__)
        # 一つ目は、自分のメンバに配列アクセス情報を持っているかどうかの確認
        # ２つめは、定数でサイズが指定された配列の場合
        # に備えてのマッチング
        # なお、両方ともそのサイズ情報を $1 番目に持っています
        if (item.ownName =~ /(\w*)(?:\[.*\.\.\..*)(?:\{)(.*)(?:\})(?:\])/) != nil || (item.ownName =~ /(\w*)(?:\[)(?:.*\.\.\.)(\w*)(?:\])/) != nil
          temp = $1
          string << "	for (int i = 0; i < #{$2.sub(/^this->/, "data.")}; ++i) {\n"
          string << "		std::vector<int> localNode(node_);\n"
          string << "		localNode.push_back(i);\n"
          string << "\n"
          string << "		value = getKeyValue(*reciprocateData_, key_#{structData_.ownName}_#{item.ownName.sub(/\[.+\]/, "")}, localNode);\n"
          string << "		if (value == NULL) {\n"
          string << "			userAssert(0, \"The key is not found!!\");\n"
          string << "			return create#{structData_.ownName}();\n"
          string << "		}\n"
        elsif (item.ownName =~ /(\w*)(?:\[.*)(?:\{)(.*)(?:\})(?:\])/) != nil || (item.ownName =~ /(\w*)(?:\[)(\w*)(?:\])/) != nil
          string << "	for (int i = 0; i < #{$2.sub(/^this->/, "data.")}; ++i) {\n"
          string << "		std::vector<int> localNode(node_);\n"
          string << "		localNode.push_back(i);\n"
          string << "\n"
          string << "		value = getKeyValue(*reciprocateData_, key_#{structData_.ownName}_#{item.ownName.sub(/\[.+\]/, "")}, localNode);\n"
          string << "		if (value == NULL) {\n"
          string << "			userAssert(0, \"The key is not found!!\");\n"
          string << "			return create#{structData_.ownName}();\n"
          string << "		}\n"
        else
          @log.info(__LINE__.to_s + ", " + __FILE__)
          @log.fatal(structData_.ownName)
          @log.fatal(item.ownType)
          @log.fatal(item.ownName)
          raise SyntaxFormatError, "Wrong in Assignment of Array element."
          raise SyntaxFormatError, "配列の要素数の表現が間違っています"
        end  # if item[NAMEOFMEMBER] =~ /\[/ && (item[NAMEOFMEMBER] =~ /CHAR/) == nil
      else
        @log.info(__LINE__.to_s + ", " + __FILE__)
        # 普通の処理
        string << "	{\n"
        string << "		value = getKeyValue(*reciprocateData_, key_#{structData_.ownName}_#{item.ownName.sub(/\[.+\]/, "")}, node_);\n"
        string << "		if (value == NULL) {\n"
        string << "			userAssert(0, \"The key is not found!!\");\n"
        string << "			return create#{structData_.ownName}();\n"
        string << "		}\n"
      end

      # 以下、型に合わせて全て違う処理。
      # 構造体や enum だった場合のチェック。
      if @enum.has_key?(item.ownType)
        if @enum[item.ownType].ownType == STRING_CHAR
          string << "		strcpy(data.#{item.ownName.sub(/\[.+\]/, "[i]")}, reinterpret_cast<const we#{@enum[item.ownType].ownType.capitalize}>(value));\n"
        elsif @enum[item.ownType].ownType == STRING_STRING
          string << "		data.#{item.ownName.sub(/\[.+\]/, "[i]")} = reinterpret_cast<const we#{@enum[item.ownType].ownType.capitalize}>(value);\n"
        else
          string << "		data.#{item.ownName.sub(/\[.+\]/, "[i]")} = reinterpret_cast<const we#{@enum[item.ownType].ownType.capitalize}*>(value);\n"
        end
      elsif @struct.has_key?(item.ownType)
        string << "		data.#{item.ownName.sub(/\[.+\]/, "[i]")} = *reinterpret_cast<const #{item.ownType}*>(value);\n"
      elsif item.ownType == STRING_CHAR
        string << "		strcpy(data.#{item.ownName.sub(/\[.+\]/, "")}, reinterpret_cast<const weString>(value));\n"
      elsif item.ownType == STRING_STRING
        string << "		data.#{item.ownName.sub(/\[.+\]/, "[i]")} = reinterpret_cast<const we#{@enum[item.ownType].ownType.capitalize}>(value);\n"
      else
        string << "		data.#{item.ownName.sub(/\[.+\]/, "[i]")} = *reinterpret_cast<const we#{item.ownType.capitalize}*>(value);\n"
      end

      string << "	}\n"
      string << "\n"
    }

    string << "	data.isDefault = false;\n"
    string << "\n"
    string << "	return data;\n"
    string << "}\n"

    string
  end

  # 適切な初期値を取得する
  # [ownType_]
  #     自分の方情報。String 型
  # [parentName_]
  #     親の型情報。String 型
  def initialEntry(ownType)
    string = ""
    if @struct.has_key?(ownType)
      string << "create#{ownType}()\n"
    elsif @enum[ownType].ownType == STRING_INT
      string = "INT_MAX\n"
    elsif @enum[ownType].ownType == STRING_FLOAT
      string = "return FLT_MAX\n"
    elsif @enum[ownType].ownType == STRING_CHAR
      string = "\'\\0\'\n"
    elsif @enum[ownType].ownType == STRING_STRING
      string = "\'\\0\'\n"
    else
      @log.fatal(__LINE__.to_s + ", " + __FILE__)
      @log.fatal("In this file -> " + @fileName + ", " +"Invalid Type is selected!!")
      @log.fatal("In this file -> " + @fileName + ", " +"無効な型が指定されています!!")
      raise TypeUnDefindError, "In this file -> " + @fileName + ", " +"Invalid Type is selected!!"
      raise TypeUnDefindError, "In this file -> " + @fileName + ", " +"無効な型が指定されています!!"
    end
    string
  end

###########################################################
#  CreateCommandCreater.rb
###########################################################
  # 構造体の初期化関数の名前を決定する
  # [commandName_]
  #     コマンドの名前
  def createInitializerName(commandName_)
    string = "#{commandName_}Direction create#{commandName_}Direction();"
    string
  end

  # コマンド発行の宣言部を作成する
  # [commandName_]
  #       コマンドの名前
  def createDirectionInitializerDeclaration(commandName_)
    string = <<EOS
/**----------------------------------------------------
 * @brief 初期化されたコマンドの取得関数
 * @note    UseList の管理も行うので、直接代入せず、このモジュールを通すこと
 * @return      初期化されたコマンド
 *---------------------------------------------------*/
EOS
    string << createInitializerName(commandName_)
    string
  end


  # コマンド発行の宣言部を作成する
  # [commandName_]
  #         コマンドの名前。String 型
  # [data_]
  #         構造体情報。Structure 型
  def createDirectionInitializerImplementation(commandName_, data_)
    string = "#{createDirectionInitializerDeclaration(commandName_).chomp.sub(/;/, "\n")}"
    string << "{\n"
    string << "	#{commandName_}Direction direction;\n"
    string << "\n"

    data_.member.each do |member|

      @log.info(__LINE__.to_s + ", " + __FILE__)
      @log.debug(member)

      case member.ownType
      when STRING_STRING, STRING_CHAR
        string << "	direction\." + member.ownName + " = \'\\0\';\n"
      when STRING_INT
        string << "	direction\." + member.ownName + " = INT_MAX;\n"
      when STRING_FLOAT
        string << "	direction\." + member.ownName + " = FLT_MAX;\n"
      else
        if @struct.has_key?(member.ownType)
          string << "	direction\." + member.ownName + " = create" + member.ownType + "\(\);\n"
        elsif @enum.has_key?(member.ownType)
          case @enum[member.ownType].ownType
          when STRING_STRING, STRING_CHAR
            string << "	direction\." + member.ownName + " = \'\\0\';\n"
          when STRING_INT
            string << "	direction\." + member.ownName + " = INT_MAX;\n"
          when STRING_FLOAT
            string << "	direction\." + member.ownName + " = FLT_MAX;\n"
          end
        else
          @log.fatal(__LINE__.to_s + ", " + __FILE__)
          @log.fatal("In this file -> " + @fileName + ", " +"Can't find a type!! -> " + member.ownType + "\n")
          raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"Can't find a type!! -> " + member.ownType + "\n"
          raise TypeUnDefinedError, "In this file -> " + @fileName + ", " +"型が見つかりませんでした -> " + member.ownType + "\n"
        end
      end
    end

    string << <<EOS

	for (int i = 0; i < sizeof(direction.useList)/sizeof(direction.useList[0]); ++i) {
		direction.useList[i] = USELIST_UNUSE;
	}

	return direction;
}
EOS

    string
  end


  # コマンド発行の宣言部を作成する
  # [commandName_]
  #       コマンドの名前。String 型
  # [member_]
  #       構造体のメンバ。Member 型
  def createDirectionSetterDeclaration(commandName_, member_)
    string = <<EOS
/**----------------------------------------------------
 * @brief パラメータセットモジュール
 * @note    UseList の管理も行うので、直接代入せず、このモジュールを通すこと
 * @param[in]   #{member_.ownName}    #{member_.comment}
 *---------------------------------------------------*/
EOS
    if member_.ownName.size > 1
      if (member_.ownName =~ /\[/) != nil
        if @struct.has_key?(member_.ownType)
          string << "void set#{member_.ownName.upcase[0].chr}#{member_.ownName[1..member_.ownName.length].sub(/\[.+\]/, "")}_#{commandName_}Direction(#{commandName_}Direction* command_, #{member_.ownType}* #{member_.ownName.sub(/\[.+\]/, "")}_);\n"
        elsif @enum.has_key?(member_.ownType)
          string << "void set#{member_.ownName.upcase[0].chr}#{member_.ownName[1..member_.ownName.length].sub(/\[.+\]/, "")}_#{commandName_}Direction(#{commandName_}Direction* command_, we#{@enum[member_.ownType].ownType.capitalize}* #{member_.ownName.sub(/\[.+\]/, "")}_);\n"
        elsif member_.ownType == STRING_CHAR
          string << "void set#{member_.ownName.upcase[0].chr}#{member_.ownName[1..member_.ownName.length].sub(/\[.+\]/, "")}_#{commandName_}Direction(#{commandName_}Direction* command_, weString #{member_.ownName.sub(/\[.+\]/, "")}_);\n"
        else
          string << "void set#{member_.ownName.upcase[0].chr}#{member_.ownName[1..member_.ownName.length].sub(/\[.+\]/, "")}_#{commandName_}Direction(#{commandName_}Direction* command_, const we#{member_.ownType.capitalize}* #{member_.ownName.sub(/\[.+\]/, "")}_);\n"
        end
      else
        if @struct.has_key?(member_.ownType)
          string << "void set#{member_.ownName.upcase[0].chr}#{member_.ownName[1..member_.ownName.length].sub(/\[.+\]/, "")}_#{commandName_}Direction(#{commandName_}Direction* command_, #{member_.ownType}* #{member_.ownName.sub(/\[.+\]/, "")}_);\n"
        elsif @enum.has_key?(member_.ownType)
          string << "void set#{member_.ownName.upcase[0].chr}#{member_.ownName[1..member_.ownName.length].sub(/\[.+\]/, "")}_#{commandName_}Direction(#{commandName_}Direction* command_, we#{@enum[member_.ownType].ownType.capitalize} #{member_.ownName.sub(/\[.+\]/, "")}_);\n"
        else
          string << "void set#{member_.ownName.upcase[0].chr}#{member_.ownName[1..member_.ownName.length].sub(/\[.+\]/, "")}_#{commandName_}Direction(#{commandName_}Direction* command_, const we#{member_.ownType.capitalize} #{member_.ownName.sub(/\[.+\]/, "")}_);\n"
        end
      end
    else
      string << "void set#{member_.ownName.capitalize}_#{commandName_}Direction(#{commandName_}Direction* command_, we#{member_.ownType.capitalize} #{member_.ownName}_);\n"
    end

    string
  end



  # コマンド発行の宣言部を作成する
  # [memberNumber]
  #       何番目のメンバーかを示すデータ
  # [commandName_]
  #       コマンドの名前。String 型
  # [member_]
  #       構造体のメンバ。Member 型
  def createDirectionSetterImplementation(memberNumber, commandName_, member_)
    string = createDirectionSetterDeclaration(commandName_, member_).chomp.sub(/;/, " \{\n")
	if (member_.ownName =~ /(?:\[)(.+)(?:\])/) != nil
	  string << "	for (int i = 0; i < #{$1}; ++i) {\n"
      if @struct.has_key?(member_.ownType)
        string << "		command_->#{member_.ownName.sub(/\[.+\]/, "\[i\]")} = #{member_.ownName.sub(/\[.+\]/, "")}_\[i\];\n"
      elsif member_.ownType == STRING_CHAR
        string << "		strcpy(command_->#{member_.ownName.sub(/\[.+\]/, "")}, #{member_.ownName.sub(/\[.+\]/, "")}_);\n"
      else
        string << "		command_->#{member_.ownName.sub(/\[.+\]/, "\[i\]")} = #{member_.ownName.sub(/\[.+\]/, "")}_\[i\];\n"
      end
      string << "	}\n"
	else
      if @struct.has_key?(member_.ownType)
        string << "	command_->#{member_.ownName.sub(/\[.+\]/, "")} = *#{member_.ownName.sub(/\[.+\]/, "")}_;\n"
      else
        string << "	command_->#{member_.ownName.sub(/\[.+\]/, "")} = #{member_.ownName.sub(/\[.+\]/, "")}_;\n"
      end
	end

    string << "	command_->useList[#{memberNumber}] = USELIST_USE;\n"
    string << "}\n"

    string
  end



  # コマンド発行の宣言部を作成する
  # [commandName_]
  #       コマンドの名前
  def createCommandCreateDeclaration(commandName_)
    string = <<EOS
/**----------------------------------------------------
 * @brief コマンド作成関数
 * @note    取得したコマンドは自分で解放関数を使って解放すること
 * @param[in]   指示
 * @return      作成されたコマンド
 *---------------------------------------------------*/
ReciprocateData* commandCreate_#{commandName_}(#{commandName_}Direction* direction_);
EOS
    string
  end


  # コマンド発行の宣言部を作成する
  # [commandName_]
  #       コマンドの名前。String 型
  # [struct_]
  #       構造体のメンバ。Struct 型
  def createCommandCreateImplementation(commandName_, struct_)
    string = createCommandCreateDeclaration(commandName_).chomp.sub(/;/, " \{\n")
	string << "	ReciprocateData* command = reinterpret_cast<ReciprocateData*>(calloc(#{struct_.member.size}, sizeof(ReciprocateData)));\n"
    string << "	command->type = DATATYPE_STRUCT;\n"

    string << "	command->key = key_#{commandName_};\n"
    string << "\n"
    string << "	// 要素数を数える\n"
    string << "	int useCount = 0;\n"
    string << "\n"
    string << "	for (int i = 0; i < sizeof(direction_->useList)/sizeof(direction_->useList[0]); ++i) \{\n"
    string << "		if (direction_->useList[i] == USELIST_USE) \{\n"
    string << "			++useCount;\n"
    string << "		\}\n"
    string << "	\}\n"
    string << "	command->num = useCount;\n"
    string << "\n"

    struct_.member.each_with_index do |member, index|
      string << "	if (direction_->useList[#{index}] == USELIST_USE) {\n"
      string << "		command->value = reinterpret_cast<void**>(calloc(1, sizeof(void**)));\n"

      if (member.ownName =~ /\[/) != nil
        if member.ownType == STRING_CHAR
          string << "		command->value[useCount-1] = storage_String(direction_->#{member.ownName.sub(/\[.+\]/, "")}, key_#{commandName_}_#{member.ownName.sub(/\[.+\]/, "")});\n"
        elsif @struct.has_key?(member.ownType)
          string << "		command->value[useCount-1] = storage_#{@enum[member.ownType].ownType}Array(direction_->#{member.ownName.sub(/\[.+\]/, "")}, key_#{commandName_}_#{member.ownName.sub(/\[.+\]/, "")});\n"          
        elsif @enum.has_key?(member.ownType)
          string << "		command->value[useCount-1] = storage_#{@enum[member.ownType].ownType.capitalize}Array(direction_->#{member.ownName.sub(/\[.+\]/, "")}, key_#{commandName_}_#{member.ownName.sub(/\[.+\]/, "")});\n"
        else
        end
      else
        if @struct.has_key?(member.ownType)
          string << "		command->value[useCount-1] = storage_#{@struct[member.ownType].ownName}(direction_->#{member.ownName}, key_#{commandName_}_#{member.ownName});\n"
        elsif @enum.has_key?(member.ownType)
          string << "		command->value[useCount-1] = storage_#{@enum[member.ownType].ownType.capitalize}(direction_->#{member.ownName}, key_#{commandName_}_#{member.ownName});\n"
        else
          string << "		command->value[useCount-1] = storage_#{member.ownType.capitalize}(direction_->#{member.ownName}, key_#{commandName_}_#{member.ownName});\n"
        end
      end
      string << "		--useCount;\n"
      string << "	}\n"
      string << "\n"
    end
          
#    case member.ownType
#      when STRING_CHAR
#        string << "		command->value[useCount-1] = storage_String(&direction_->#{member.ownName.sub(/\[.+\]/, "")}, key_#{commandName_}_#{member.ownName.sub(/\[.+\]/, "")});\n"
#      when STRING_STRING
#        string << "		command->value[useCount-1] = storage_String(direction_->#{member.ownName}, key_#{commandName_}_#{member.ownName.sub(/\[.+\]/, "")});\n"
#      when STRING_INT
#        string << "		command->value[useCount-1] = storage_Int(direction_->#{member.ownName}, key_#{commandName_}_#{member.ownName.sub(/\[.+\]/, "")});\n"
#      when STRING_FLOAT
#        string << "		command->value[useCount-1] = storage_Float(direction_->#{member.ownName}, key_#{commandName_}_#{member.ownName.sub(/\[.+\]/, "")});\n"
#      else
#        if @enum.has_key?(member.ownType)
#          string << "		command->value[useCount-1] = storage_#{@enum[member.ownType].ownType.capitalize}(direction_->#{member.ownName}, key_#{commandName_}_#{member.ownName});\n"
#        elsif @struct.has_key?(member.ownType)
#          string << "		command->value[useCount-1] = storage_#{@struct[member.ownType].ownName}(direction_->#{member.ownName}, key_#{commandName_}_#{member.ownName});\n"
#        else
#          @log.fatal(__LINE__.to_s + ", " + __FILE__)
#          @log.fatal("In this file -> " + @fileName + ", " +"Invalid Type is selected!!")
#          @log.fatal("In this file -> " + @fileName + ", " +"無効な型が指定されています!!")
#          raise TypeUnDefindError, "In this file -> " + @fileName + ", " +"Invalid Type is selected!!"
#          raise TypeUnDefindError, "In this file -> " + @fileName + ", " +"無効な型が指定されています!!"
#        end
#      end
#      string << "		--useCount;\n"
#      string << "	}\n"
#      string << "\n"
#    end

    string << "\n"
    string << "	if (useCount != 0) \{\n"
    string << "		// 正しい数が処理されなかった\n"
    string << "		// 。の後に何か付け加えないとなぜかエラーが発生するので付け加えている\n"
    string << "		userAssert(0, \"正しい数が処理されませんでした。プログラム上のバグがあるのかもしれません。あ\");\n"
    string << "		return NULL;\n"
    string << "	\}\n"
    string << "\n"
    string << "	return command;\n"
    string << "\}\n"

    string
  end


  # インターフェース構造体を作成する
  # [commandName_]
  #         コマンド名。String 型
  # [data_]
  #         構造体情報。Structure 型
  def createDirectionStructure(commandName_, data_)
    string = ""
    string << "/**\n"
    string << " * @brief チーム情報をＤＢから取得するための検索指示\n"
    string << " *          \n"
    string << " * @note    パラメータのうち、片方だけが指定されていればそれで検索する\n"
    string << " *              同時に成り立たないものの優先度はメンバの上から順。\n"
    string << " */\n"

    string = createDirectionStructBaffer(commandName_+"Direction", data_, string)
  end

  # key 名を作成する
  # [structName_]
  #     構造体の名前
  # [memberName_]
  #     構造体に所属するメンバ名
  # 構造体定義ファイルは C 用に書く
  def createKeyName(structName_, memberName_)
    "key_" + structName_ + "_" + memberName_
  end


  # ログファイルの名前を取得する
  # [fileName]
  #     仕様書ファイルの名前。
  # 構造体定義ファイルは C 用に書く
  def logFileName(fileName_)
    @ownDirectory + "/Log/" + fileName_.sub(/.txt/, ".log")
  end


  # 自動で出力するファイル名の先頭につける文字列
  def leadingString
    "Auto_"
  end


  # ヘッダファイルの名前を取得する
  # [fileName]
  #     仕様書ファイルの名前。
  # 構造体定義ファイルは C 用に書く
  def headderFileName(fileName_)
    leadingString + fileName_.sub(/.txt/, ".h")
  end


  # ヘッダファイルの名前を取得する
  # [fileName]
  #     仕様書ファイルの名前。
  # 構造体定義ファイルは C 用に書く
  def structHeadderFileName(fileName_)
    leadingString + fileName_.sub(/.txt/, ".c")
  end


  # key 定義ファイルを作成する
  # [fileName]
  #     仕様書ファイルの名前。
  # 構造体定義ファイルは C 用に書く
  def structDefineFileName(fileName_)
    leadingString + fileName_.sub(/.txt/, "_Define.h")
  end


  # コンバーターのヘッダファイルの名前を取得する
  # [fileName]
  #     仕様書ファイルの名前
  # コンバーターファイルは非公開予定なので C++ 用に出力
  def converterHeadderFileName(fileName_)
    leadingString + "Converter_" + fileName_.sub(/.txt/, ".hpp")
  end


  # コンバーターのソースファイルの名前を取得する
  # [fileName]
  #     仕様書ファイルの名前
  # コンバーターファイルは非公開予定なので C++ 用に出力
  def converterSourceFileName(fileName_)
    leadingString + "Converter_" + fileName_.sub(/.txt/, ".cpp")
  end


  # コマンドクリエイターのヘッダファイルの名前を取得する
  # [fileName]
  #     仕様書ファイルの名前
  # コンバーターファイルは非公開予定なので C++ 用に出力
  def commandCreaterHeadderFileName(fileName_)
    leadingString + "CommandCreater_" + fileName_.sub(/.txt/, ".hpp")
  end


  # コマンドクリエイターのソースファイルの名前を取得する
  # [fileName]
  #     仕様書ファイルの名前
  # コンバーターファイルは非公開予定なので C++ 用に出力
  def commandCreaterSourceFileName(fileName_)
    leadingString + "CommandCreater_" + fileName_.sub(/.txt/, ".cpp")
  end


  # Reciprocater のヘッダファイルの名前を取得する
  # [fileName]
  #     仕様書ファイルの名前
  # コンバーターファイルは非公開予定なので C++ 用に出力
  def reciprocaterHeadderFileName(fileName_)
    leadingString + "Reciprocater_" + fileName_.sub(/.txt/, ".hpp")
  end


  # Reciprocater のソースファイルの名前を取得する
  # [fileName]
  #     仕様書ファイルの名前
  # コンバーターファイルは非公開予定なので C++ 用に出力
  def reciprocaterSourceFileName(fileName_)
    leadingString + "Reciprocater_" + fileName_.sub(/.txt/, ".cpp")
  end


  # 構造体作成関数の宣言部作成。コメント文は他に託す。
  # [structName_]
  #     作成する構造体の名前。文字列
  def structCreaterDeclaration(structName_)
    string = "#{structName_} create#{structName_}();\n"
    string
  end


end


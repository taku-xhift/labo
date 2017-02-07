#! D:/PersonalTool/xyzzy/laboratory/ruby/SpecConverter
 
# 仕様書を解析し、Ｃ言語用のソースコードを出力する
# Author::    Takuya Shishido
# Copyright:: (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.


require File.dirname(__FILE__) + "/CommandCommentFormat"
require File.dirname(__FILE__) + "/Exception"

require "kconv"     # String の拡張(Encode を可能に)
require "logger"    # log 出力用


###########################################################
#  define
###########################################################
DEFINE = "Define"
Headder = "Headder"
Converter = "Converter"
Command = "Command"
Log = "Log"


# データ定義ファイルのヘッダファイルを作成する
# 内部では、ファイルヘッダ、構造体宣言等を書き込むようになっている
class SpecConverter

  include CommandCommentFormat

  public

  # initlizer
  # [fileName]
  #     仕様書ファイル名
  def initialize(fileName_, ownDirectoryName_)
    super(fileName_)
    @ownDirectory = ownDirectoryName_
    @command = {}                   # コマンドデータをハッシュで持っているもの
    @headderBaffer = ""             # ヘッダ部分を保存しておくバッファ
    @tempArray = Array.new          # 用途が判明していない行データ。配列で行を保存していく

    @log = Logger.new(logFileName(@fileName))
    @log.level = Logger::DEBUG

    # log ファイルの初期化
    f = File.open(logFileName(@fileName), "w") do |f|
      f.puts("")
    end

    # 書き込み先のファイルの初期化
    f = File.open(@ownDirectory + "/" + Headder + "/" + headderFileName(@fileName), "w") do |f|
      f.puts("")
    end
    f = File.open(@ownDirectory + "/" + Headder + "/" + structHeadderFileName(@fileName), "w") do |f|
      f.puts("")
    end
    f = File.open(@ownDirectory +  "/" + DEFINE + "/" + structDefineFileName(@fileName), "w") do |f|
      f.puts("")
    end
    f = File.open(@ownDirectory + "/" + Converter + "/" + converterHeadderFileName(@fileName), "w") do |f|
      f.puts("")
    end
    f = File.open(@ownDirectory + "/" + Converter + "/" + converterSourceFileName(@fileName), "w") do |f|
      f.puts("")
    end
    f = File.open(@ownDirectory + "/" + Command + "/" + commandCreaterHeadderFileName(@fileName), "w") do |f|
      f.puts("")
    end
    f = File.open(@ownDirectory + "/" + Command + "/" + commandCreaterSourceFileName(@fileName), "w") do |f|
      f.puts("")
    end

    @includeFiles[headderFileName(@fileName)] << "../../Define/LeagueModeDefineData.h"
    @includeFiles[structHeadderFileName(@fileName)] << "limits.h"
    @includeFiles[structHeadderFileName(@fileName)] << headderFileName(@fileName)

    @includeFiles[converterHeadderFileName(@fileName)] << "vector"
    @includeFiles[converterHeadderFileName(@fileName)] << "../../Structure/ReciprocateData.h"
    @includeFiles[converterHeadderFileName(@fileName)] << "../../Structure/Command/" + headderFileName(@fileName)
    @includeFiles[converterSourceFileName(@fileName)] << "cstring"
    @includeFiles[converterSourceFileName(@fileName)] << "malloc.h"
    @includeFiles[converterSourceFileName(@fileName)] << "cassert"
    @includeFiles[converterSourceFileName(@fileName)] << "../../Define/Command/" + structDefineFileName(@fileName)
    @includeFiles[converterSourceFileName(@fileName)] << "../../Structure/ReciprocateData.h"
    @includeFiles[converterSourceFileName(@fileName)] << "../Storage.hpp"
    @includeFiles[converterSourceFileName(@fileName)] << "../Parse.hpp"
    @includeFiles[converterSourceFileName(@fileName)] << "../UtilityFunction.hpp"
    @includeFiles[converterSourceFileName(@fileName)] << converterHeadderFileName(@fileName)

    @includeFiles[commandCreaterHeadderFileName(@fileName)] << commandCreaterHeadderFileName(@fileName)
    @includeFiles[commandCreaterHeadderFileName(@fileName)] << "../Converter/" + converterHeadderFileName(@fileName)
    @includeFiles[commandCreaterHeadderFileName(@fileName)] << "../../Structure/Command/" + headderFileName(@fileName)
    @includeFiles[commandCreaterHeadderFileName(@fileName)] << "../../Define/Command/" + structDefineFileName(@fileName)
    @includeFiles[commandCreaterHeadderFileName(@fileName)] << "../../Define/LeagueModeDefineData.h"
    @includeFiles[commandCreaterHeadderFileName(@fileName)] << "../../Structure/ReciprocateData.h"
    @includeFiles[commandCreaterHeadderFileName(@fileName)] << "../storage.hpp"
    @includeFiles[commandCreaterSourceFileName(@fileName)] << commandCreaterHeadderFileName(@fileName)
    @includeFiles[commandCreaterSourceFileName(@fileName)] << "../../Structure/Command/" + headderFileName(@fileName)
    @includeFiles[commandCreaterSourceFileName(@fileName)] << "../UtilityFunction.hpp"
    @includeFiles[commandCreaterSourceFileName(@fileName)] << "../Converter/" + converterHeadderFileName(@fileName)


    ready
    pusher
  end


  # 書き込み準備
  def ready
    fileLines = Array.new

    f = File.open(@fileName, "r") do |f|
      # ファイルを読み取り
      strings = f.readlines()

      # 文字列のエンコード
      encordedStrings = String.new
      strings.each do |i|
        fileLines << i.toutf8
      end
    end

    parse(fileLines)
  end


  # 出力
  def pusher
    # 各スレッドにて発生した例外を捕捉
#    begin
#      threadHeadder = Thread::start do
#        pushToHeadderFile
#      end
#      threadSource = Thread::start do
#        pushToSourceFile
#      end
#      threadDefine = Thread::start do
#        pushToDefineFile
#      end
#      threadConverterHeadder = Thread::start do
#        pushToConverterHeadderFile
#      end
#      threadConverterSource = Thread::start do
#        pushToConverterSourceFile
#      end
#      threadCommandHeadder = Thread::start do
#        pushToCommandHeadderFile
#      end
#      threadCommandSource = Thread::start do
#        pushToCommandSourceFile
#      end
#      threadHeadder.join
#      threadSource.join
#      threadDefine.join
#      threadConverterHeadder.join
#      threadCommandHeadder.join
#      threadCommandSource.join
#    rescue
#      p $!  # => "unhandled exception"
#    end
        pushToHeadderFile
        pushToSourceFile
        pushToDefineFile
        pushToConverterHeadderFile
        pushToConverterSourceFile
        pushToCommandHeadderFile
        pushToCommandSourceFile
  end


  # key に関してだけファイルを出力するモジュール
  def pushToDefineFile
    f = File.open(@ownDirectory +  "/" + DEFINE + "/" + structDefineFileName(@fileName), "a") do |f|
      f.puts(@headderBaffer + "\n")
      f.puts(createIncludeGuard(structDefineFileName(@fileName)) + "\n\n")

      tempArray = Array.new
      @struct.each_pair {|key, value|
        value.member.each do |i|
          memberName = i.ownName
          @log.info(__LINE__.to_s + ", " + __FILE__)
          @log.debug(memberName)

          # 配列だった場合に要素数を示す部分を削除する
          if (memberName =~ /(.+)(?:\[)(?:.+)(?:\])(?:.*)/) != nil
            memberName = $1
          end

          if tempArray.assoc(createKeyName(key, memberName)) == nil
            tempArray << [createKeyName(key, memberName), memberName]
          end
        end

        # 構造体名のキーを作成する
        if tempArray.assoc(createKeyName(key, "").chop) == nil
          tempArray << [createKeyName(key, "").chop, key]
        end
      }

      @commandStruct.each_pair {|key, value|
        value.member.each do |i|
          memberName = i.ownName
          @log.info(__LINE__.to_s + ", " + __FILE__)
          @log.debug(memberName)
          @log.debug(@commandStruct)

          # 配列だった場合に要素数を示す部分を削除する
          if (memberName =~ /(.+)(?:\[)(?:.+)(?:\])(?:.*)/) != nil
            memberName = $1
          end

          if tempArray.assoc(createKeyName(key, memberName)) == nil
            tempArray << [createKeyName(key, memberName), memberName]
          end
        end

        # コマンド名のキーを作成する
        if tempArray.assoc(createKeyName(key, "").chop) == nil
          tempArray << [createKeyName(key, "").chop, key]
        end
      }

      

      tempArray.each do |value|
        f.puts("static const char* " + value[0] + " = \"" + value[1] + "\";\n")
      end

      f.puts("\n")
      f.puts("#endif    // " + structDefineFileName(@fileName) + "\n")
      f.puts("\n")
    end
  end


  # ファイルに出力する
  def pushToHeadderFile
    # 追記モードで再度ファイルオープン
    f = File.open(@ownDirectory + "/" + Headder + "/" + headderFileName(@fileName), "a") do |f|
      f.puts(@headderBaffer + "\n")
      f.puts(createIncludeGuard(headderFileName(@fileName)) + "\n\n")

      f.puts(createMarker("include"))
      @includeFiles[headderFileName(@fileName)].each do |file|
        f.puts(createIncludeString(file))
      end
      f.puts("\n\n")

      f.puts(createMarker("define"))
      @define.each_pair {|key, value|
        next unless value
        f.puts(createDefineBaffer(value))
      }
      f.puts("\n\n")

      f.puts("#ifdef __cplusplus\n")
      f.puts("extern \"C\" \{\n")
      f.puts("#endif\n")
      f.puts("\n")

      @enum.each_pair {|key, value|
        next unless value
        #f.puts(createEnumBaffer(value) + "\n")
      }
      f.puts("\n\n")

      @struct.each_pair {|key, value|
        next unless value
        f.puts(createStructBaffer(value.ownName, value, value.comment) + "\n\n")
      }
      f.puts("\n\n")

      @struct.each_key {|key|
        string = ""
        string << <<EOS
/**----------------------------------------------------
 * @brief 初期化関数
 * @return    初期パラメータが代入された構造体
 *---------------------------------------------------*/
EOS
        f.puts(string)
        f.puts(structCreaterDeclaration(key) + "\n\n")
      }

      f.puts("#ifdef __cplusplus\n")
      f.puts("\}\n")
      f.puts("#endif\n")
      f.puts("\n")


      # 最後にインクルードガード用の endif
      f.puts("#endif    // " + headderFileName(@fileName).upcase.sub(/.HPP/, "_HPP_INCLUDED\n\n"))

      # 処理が終わっていないデータが残っていればそれは構文エラー
      # 今は開発段階なので無視する
      # 2010.06.28 まだ出力していないデータもあるのでまだ使用しない。
      @tempArray.clear
      @command.clear
      unless @tempArray == [] && @command == {}
        @log.fatal(__LINE__.to_s + ", " + __FILE__)
        @log.fatal(@tempArray)
        @log.fatal(@command)
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"Remain some data to be done!!"
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"何か未処理のデータが残っています。構文が間違っていないかチェックしてください"
      end

    end
  end


  # ソースファイル出力用
  def pushToSourceFile
    # 追記モードで再度ファイルオープン
    f = File.open(@ownDirectory + "/" + Headder + "/" + structHeadderFileName(@fileName), "a") do |f|
      # ファイルヘッダ
      f.puts(@headderBaffer + "\n")

      f.puts(createMarker("include"))
      @includeFiles[structHeadderFileName(@fileName)].each do |file|
        f.puts(createIncludeString(file))
      end
      f.puts("\n\n")

      # 構造体作成関数の実装部分
      @struct.each_pair {|key, value|
        string = <<EOS
/**----------------------------------------------------
 * @brief 初期化関数
 * @return    初期パラメータが代入された構造体
 *---------------------------------------------------*/
EOS
        f.puts(string)
        f.puts(structCreaterImplementation(key, value) + "\n\n")
      }

      # 処理が終わっていないデータが残っていればそれは構文エラー
      # 今は開発段階なので無視する
      # 2010.06.28 まだ出力していないデータもあるのでまだ使用しない。
      @tempArray.clear
      @command.clear
      unless @tempArray == [] && @command == {}
        @log.fatal(__LINE__.to_s + ", " + __FILE__)
        @log.fatal(@tempArray)
        @log.fatal(@command)
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"Remain some data to be done!!"
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"何か未処理のデータが残っています。構文が間違っていないかチェックしてください"
      end

    end
  end


  # ファイルに出力する
  def pushToConverterHeadderFile
    # 追記モードで再度ファイルオープン
    f = File.open(@ownDirectory + "/" + Converter + "/" + converterHeadderFileName(@fileName), "a") do |f|
      f.puts(@headderBaffer)
      f.puts(createIncludeGuard(converterHeadderFileName(@fileName)) + "\n")

      f.puts(createMarker("include"))
      @includeFiles[converterHeadderFileName(@fileName)].each do |file|
        f.puts(createIncludeString(file))
      end
      f.puts("\n\n")

      @struct.each_value do |struct|
        f.puts(createStorageDeclaration(struct.ownName))
        f.puts("\n\n")
      end

      @struct.each_value do |struct|
        f.puts(createStorageArrayDeclaration(struct.ownName))
        f.puts("\n\n")
      end

      @struct.each_value do |struct|
        f.puts(createConvertDeclaration(struct.ownName, false))
        f.puts("\n\n")
      end

      # 最後にインクルードガード用の endif
      f.puts("#endif    // " + converterHeadderFileName(@fileName).upcase.sub(/.HPP/, "_HPP_INCLUDED\n\n"))

      # 処理が終わっていないデータが残っていればそれは構文エラー
      # 今は開発段階なので無視する
      # 2010.06.28 まだ出力していないデータもあるのでまだ使用しない。
      @tempArray.clear
      @command.clear
      unless @tempArray == [] && @command == {}
        @log.fatal(__LINE__.to_s + ", " + __FILE__)
        @log.fatal(@tempArray)
        @log.fatal(@command)
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"Remain some data to be done!!"
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"何か未処理のデータが残っています。構文が間違っていないかチェックしてください"
      end

    end
  end

  # ファイルに出力する
  def pushToConverterSourceFile
    # 追記モードで再度ファイルオープン
    f = File.open(@ownDirectory + "/" + Converter + "/" + converterSourceFileName(@fileName), "a") do |f|
      f.puts(@headderBaffer + "\n")

      f.puts(createMarker("include"))
      @includeFiles[converterSourceFileName(@fileName)].each do |file|
        f.puts(createIncludeString(file))
      end
      f.puts("\n\n")

      @struct.each_value {|value|
        f.puts(storageImplementation(value))
        f.puts("\n\n")
      }

      @struct.each_value {|value|
        f.puts(storageArrayImplementation(value))
        f.puts("\n\n")
      }

      @struct.each_value {|value|
        f.puts(converterImplementation(value))
        f.puts("\n\n")
      }

      # 処理が終わっていないデータが残っていればそれは構文エラー
      # 今は開発段階なので無視する
      # 2010.06.28 まだ出力していないデータもあるのでまだ使用しない。
      @tempArray.clear
      @command.clear
      unless @tempArray == [] && @command == {}
        @log.fatal(__LINE__.to_s + ", " + __FILE__)
        @log.fatal(@tempArray)
        @log.fatal(@command)
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"Remain some data to be done!!"
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"何か未処理のデータが残っています。構文が間違っていないかチェックしてください"
      end

    end
  end



  # ファイルに出力する
  def pushToCommandHeadderFile
    # 追記モードで再度ファイルオープン
    f = File.open(@ownDirectory + "/" + Command + "/" + commandCreaterHeadderFileName(@fileName), "a") do |f|
      f.puts(@headderBaffer + createIncludeGuard(commandCreaterHeadderFileName(@fileName)) + "\n")

      f.puts(createMarker("include"))
      @includeFiles[commandCreaterHeadderFileName(@fileName)].each do |file|
        f.puts(createIncludeString(file))
      end
      f.puts("\n\n")

      f.puts("#ifdef __cplusplus")
      f.puts("extern \"C\" \{");
      f.puts("#endif")
      f.puts("\n\n")

      @commandStruct.each_pair {|key, value|
        f.puts(createDirectionStructure(key, value))
        f.puts("\n\n")
      }

      @commandStruct.each_pair {|key, value|
        f.puts(createDirectionInitializerDeclaration(key))
        f.puts("\n\n")
      }

      @commandStruct.each_pair {|key, value|
        # 構造体のメンバ全てに関してセッタを出力する
        value.member.each do |member|
          f.puts(createDirectionSetterDeclaration(key, member))
          f.puts("\n\n")
        end
      }

      @commandStruct.each_pair {|key, value|
        f.puts(createCommandCreateDeclaration(key).chomp)
        f.puts("\n\n")
      }


      f.puts("#ifdef __cplusplus")
      f.puts("\}")
      f.puts("#endif")
      f.puts("\n")

      # 最後にインクルードガード用の endif
      f.puts("#endif    // " + converterHeadderFileName(@fileName).upcase.sub(/.HPP/, "_HPP_INCLUDED\n\n"))

      # 処理が終わっていないデータが残っていればそれは構文エラー
      # 今は開発段階なので無視する
      # 2010.06.28 まだ出力していないデータもあるのでまだ使用しない。
      @tempArray.clear
      @command.clear
      unless @tempArray == [] && @command == {}
        @log.fatal(__LINE__.to_s + ", " + __FILE__)
        @log.fatal(@tempArray)
        @log.fatal(@command)
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"Remain some data to be done!!"
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"何か未処理のデータが残っています。構文が間違っていないかチェックしてください"
      end

    end
  end

  # ファイルに出力する
  def pushToCommandSourceFile
    # 追記モードで再度ファイルオープン
    f = File.open(@ownDirectory + "/" + Command + "/" + commandCreaterSourceFileName(@fileName), "a") do |f|
      f.puts(@headderBaffer + "\n")

      f.puts(createMarker("include"))
      @includeFiles[commandCreaterSourceFileName(@fileName)].each do |file|
        f.puts(createIncludeString(file))
      end
      f.puts("\n\n")

      @commandStruct.each_pair {|key, value|
        f.puts(createDirectionInitializerImplementation(key, value))
        f.puts("\n\n")
      }

      @commandStruct.each_pair {|key, value|
        value.member.each_with_index {|member, index|
          f.puts(createDirectionSetterImplementation(index, key, member))
          f.puts("\n\n")
        }
      }

      @commandStruct.each_pair {|key, value|
        f.puts(createCommandCreateImplementation(key, value))
        f.puts("\n\n")
      }

      # 処理が終わっていないデータが残っていればそれは構文エラー
      # 今は開発段階なので無視する
      # 2010.06.28 まだ出力していないデータもあるのでまだ使用しない。
      @tempArray.clear
      @command.clear
      unless @tempArray == [] && @command == {}
        @log.fatal(__LINE__.to_s + ", " + __FILE__)
        @log.fatal(@tempArray)
        @log.fatal(@command)
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"Remain some data to be done!!"
        raise SyntaxFormatError, "In this file -> " + @fileName + ", " +"何か未処理のデータが残っています。構文が間違っていないかチェックしてください"
      end

    end
  end


end


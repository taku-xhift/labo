#! D:/PersonalTool/xyzzy/laboratory/ruby/CommandSpec/

# 仕様書からＣ言語用のソースコードを出力するスクリプト
# Author::    Takuya Shishido
# Copyright:: (c) 2010 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
# License::   Konami



###########################################################
#  require
###########################################################
# ディレクトリを再帰的に抽出する
require 'find'

require 'pp'

require "SpecConverter.rb"


###########################################################
#  entry Point
###########################################################
currentDirectory = Dir::getwd
begin
  Dir::mkdir(Log)
rescue
end
begin
  Dir::mkdir(DEFINE)
rescue
end
begin
  Dir::mkdir(Headder)
rescue
end
begin
  Dir::mkdir(Converter)
rescue
end
begin
  Dir::mkdir(Command)
rescue
end

Dir::chdir("../")

dir_entries = Dir.glob("./" + "**/*")

find_entries = Array.new
Find.find(Dir::getwd) do |path|
  unless path =~ /svn|#{currentDirectory}/
    if path =~ /.txt/
      path =~ /(?:.*\/)(.*.txt)/
      find_entries.push($1)
    end
  end
end

find_entries.each do |file|
#  begin
#    object = SpecConverter.new(file, currentDirectory)
#  rescue
#    pp $!
#    raise "Some Error is happen!! -> " + file
#  end
  object = SpecConverter.new(file, currentDirectory)
end

# １ファイルずつコマンドラインで指定する場合
#object = SpecConverter.new(ARGV[0])


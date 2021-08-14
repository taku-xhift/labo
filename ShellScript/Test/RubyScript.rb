
# Makefile の一部を書き換え、
# C++ のインラインコードをコンパイルできるようにする


###########################################################
#  require
###########################################################
require "logger"    # log 出力用


###########################################################
#  global object
###########################################################
$log = Logger.new("log.log")
$log.level = Logger::DEBUG

strings = []

# ファイルを一通り読み込んでくる
File.open(ARGV[0], "r") do |f|
  while line = f.gets
  $log.debug(line)
    strings << line
  end
end

# ファイルの最後にある LD_RUN_PATH を探し
# c++ 用ライブラリを追加する
strings.reverse_each do |i|
  if i =~ /LD_RUN_PATH/
  $log.debug(i)
    i.chomp! << " " << ARGV[1] << "\n"
    p "added c++ library"
    p ARGV[1]
    break
  end
end

# 変更点書き込み
File.open(ARGV[0], "w") do |f|
  strings.each do |line|
  $log.debug(line)
    f << line
  end
end


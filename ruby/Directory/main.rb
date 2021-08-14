
#array = nil
#
#Dir::glob("../CommandSpecific/**/*.txt").each {|f|
#  #p "#{f}: #{File::stat(f).size} bytes"
#  array = File::stat(f)
#}
#
#p array.class
#


# ディレクトリを再帰的に抽出する
require 'find'
require 'pp'

#root = "D:/PersonalTool/xyzzy/laboratory/Ruby/CommandSpecific/"
root = File.dirname(__FILE__) + "./CommandSpecific"


# Dir.globの場合、エントリの配列が返る
puts "--- Dir.glob ---"
dir_entries = Dir.glob(root + "/" + "**/*")
pp dir_entries

# Find.findは、走査を行う。findをrequireして使う。
puts "--- Find.find ---"
find_entries = Array.new
Find.find(root) do |path|
  unless path =~ /svn/
    if path =~ /.txt/
      path =~ /(?:.*\/)(.*.txt)/
      find_entries.push($1)
    end
  end
end
pp find_entries


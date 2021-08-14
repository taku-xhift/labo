
#array = nil
#
#Dir::glob("../CommandSpecific/**/*.txt").each {|f|
#  #p "#{f}: #{File::stat(f).size} bytes"
#  array = File::stat(f)
#}
#
#p array.class
#


# �f�B���N�g�����ċA�I�ɒ��o����
require 'find'
require 'pp'

#root = "D:/PersonalTool/xyzzy/laboratory/Ruby/CommandSpecific/"
root = File.dirname(__FILE__) + "./CommandSpecific"


# Dir.glob�̏ꍇ�A�G���g���̔z�񂪕Ԃ�
puts "--- Dir.glob ---"
dir_entries = Dir.glob(root + "/" + "**/*")
pp dir_entries

# Find.find�́A�������s���Bfind��require���Ďg���B
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



thread = Thread.new do
  puts "thread �J�n"
  sleep 5
  puts "thread �I��"
end

puts "thread �͏I�����Ă��܂����H"
thread.join
puts "�v���O�����͏I�����܂���"



puts "�v���O�����J�n"

thread = Thread.new do
  puts "�X���b�h�J�n"
  sleep 5
  puts "�X���b�h�I��"
end


puts "�X���b�h�͏I����Ă��܂����H"
thread.join
puts "�v���O�����I��"



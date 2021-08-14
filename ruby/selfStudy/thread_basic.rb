
puts "プログラム開始"

thread = Thread.new do
  puts "スレッド開始"
  sleep 5
  puts "スレッド終了"
end


puts "スレッドは終わっていますか？"
thread.join
puts "プログラム終了"



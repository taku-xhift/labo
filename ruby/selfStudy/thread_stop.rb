
thread = Thread.new do
  puts "thread 開始"
  sleep 5
  puts "thread 終了"
end

puts "thread は終了していますか？"
thread.join
puts "プログラムは終了しました"


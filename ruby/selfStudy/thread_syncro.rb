
num = 0
mutex = Mutex.new

thread1 = Thread.new do
  10000.times do
    mutex.lock
    num = num + 1
    mutex.unlock
  end
end

thread2 = Thread.new do
  10000.times do
    mutex.lock
    num = num + 1
    mutex.unlock
  end
end

thread3 = Thread.new do
  10000.times do
    mutex.lock
    num = num + 1
    mutex.unlock
  end
end

thread1.join
thread2.join
thread3.join

puts num


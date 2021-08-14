
require 'thread'

class Store
  def initialize
    @mutex = Mutex.new
    @sleepingTime = 5
    puts "�������ł��B"
  end
  
  def run
    @mutex.lock
    sleep @sleepingTime
    @mutex.unlock
    puts "�J�X���܂����B"
  end
  
  def enter(name)
    while @mutex.locked?
      puts "#{name} �͓��X�҂��ł��B"
      sleep 1
    end
    puts "#{name} �͓��X���܂����B"
  end
end

store = Store.new
th1 = Thread.start{store.run}
th2 = Thread.start{store.enter("musashi")}
th3 = Thread.start{store.enter("kojiro")}

th1.join
th2.join
th3.join



require 'thread'

class Store
  def initialize
    @mutex = Mutex.new
    @sleepingTime = 5
    puts "€”õ’†‚Å‚·B"
  end
  
  def run
    @mutex.lock
    sleep @sleepingTime
    @mutex.unlock
    puts "ŠJ“X‚µ‚Ü‚µ‚½B"
  end
  
  def enter(name)
    while @mutex.locked?
      puts "#{name} ‚Í“ü“X‘Ò‚¿‚Å‚·B"
      sleep 1
    end
    puts "#{name} ‚Í“ü“X‚µ‚Ü‚µ‚½B"
  end
end

store = Store.new
th1 = Thread.start{store.run}
th2 = Thread.start{store.enter("musashi")}
th3 = Thread.start{store.enter("kojiro")}

th1.join
th2.join
th3.join


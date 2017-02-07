begin
  t = Thread.new do
    Thread.pass    # メインスレッドが確実にjoinするように
    raise "unhandled exception"
  end
  t.join
rescue
  p $!  # => "unhandled exception"
end

begin
  t = Thread.new do
    Thread.pass    # ���C���X���b�h���m����join����悤��
    raise "unhandled exception"
  end
  t.join
rescue
  p $!  # => "unhandled exception"
end

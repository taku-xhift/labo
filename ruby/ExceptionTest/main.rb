

class SampleException < StandardError;
end


def out(data)
  raise SampleException, "testException"
  p data
end


begin
out(2)
rescue #SampleException
  p 3
end
out(2)


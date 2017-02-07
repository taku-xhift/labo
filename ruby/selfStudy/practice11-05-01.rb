
require "net/http"
require "kconv"

def search(key)
  Net::HTTP.start("www.google.co.jp", 80) do |http|
    contents = http.get("/search?q=#{key}" )
    puts contents.body.tosjis
  end
end

keyword = "ruby"
search(keyword)

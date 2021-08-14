
require "net/http"
require "kconv"

Net::HTTP.start("search.yahoo.co.jp", 80) do |http|
  contents = http.post("/search", "p=ruby")
  puts contents.body.tosjis
end


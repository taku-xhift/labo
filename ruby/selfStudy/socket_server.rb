
require "socket"

port_number = 12344

# localhost のポートオープン
con = TCPServer.open(port_number)
puts "waiting connect"

# 接続受付
receive = con.accept

# 受信したデータを表示
while data = receive.gets
  puts data
end

# 接続を閉じる
receive.close
con.close



require 'socket'

host = "localhost"
port_number = 12344

# localhost のポート 12345 へ接続
con = TCPSocket.open(host, port_number)

# 文字列を送信
con.write("successful")

# 接続を閉じる
con.close



require "socket"

port_number = 12344

# localhost �̃|�[�g�I�[�v��
con = TCPServer.open(port_number)
puts "waiting connect"

# �ڑ���t
receive = con.accept

# ��M�����f�[�^��\��
while data = receive.gets
  puts data
end

# �ڑ������
receive.close
con.close



require 'socket'

host = "localhost"
port_number = 12344

# localhost �̃|�[�g 12345 �֐ڑ�
con = TCPSocket.open(host, port_number)

# ������𑗐M
con.write("successful")

# �ڑ������
con.close


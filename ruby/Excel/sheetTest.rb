require 'spreadsheet'

xls = Spreadsheet.open('test.xls', 'rb') #Excel�t�@�C���̓ǂݍ���
sheet = xls.worksheet(0) #0�Ԗڂ܂�1�Ԏn�߂�sheet��ǂݍ���

#�ǂݍ��݂̊J�n��'�O'����n�܂�B
puts sheet[0,0] #���ۂ�Excel�ł́A1�s�ڂ�2��ڂ̒l��ǂݍ���
#sheet[4,6] #���ۂ�Excel�ł́A5�s�ڂ�6��ڂ̒l��ǂݍ���

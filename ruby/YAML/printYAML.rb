###
### print-yaml.rb
###
### �g�����F ruby print-yaml.rb file.yaml [file2.yaml ...]
###
require 'yaml'
require 'pp'

str  = ARGF.read()      # ���͂����ׂēǂݍ���
data = YAML.load(str)   # �p�[�X����
pp data                 # �f�[�^��\������


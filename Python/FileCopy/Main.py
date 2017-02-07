# -*- coding: utf-8 -*-

import sys
import io

my_encoding = 'utf-8'

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding=my_encoding)



class KeyPair:
	def __init__(self, key, word):
		self.key = key
		self.word = word

	def get_key(self):
		return self.key
	def get_word(self):
		return self.word


key_pair_list = [
	KeyPair("brief", "fffffffffffff"),
]



if __name__ == "__main__":
	contents = open('AI.cpp', mode='r', encoding=my_encoding).read()

	for key in key_pair_list:
		contents = contents.replace(key.get_key(), key.get_word())
	print(contents)



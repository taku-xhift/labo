

def replace(string):
	temp = string
	temp = temp.replace('Hello', 'World')
	print(temp)
	return temp

src = 'Hello'

result = replace(src)

print('src = ' + src)
print('result = ' + result)

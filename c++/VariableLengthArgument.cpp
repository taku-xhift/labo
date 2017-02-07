


#include <iostream>
#include <cstdarg>

const int bufSize = 0x100;

int print(const char* format, ...) {
	char	buf[bufSize];
	va_list	argp;
	va_start( argp, format );

	//const int result = sprintf(buf, format, *argp);
	const int result = vsnprintf_s(
			buf, sizeof(buf),
			bufSize,
			format,
			argp
			);
	printf("%s", buf);

	return result;
}

int main() {
	const int result = print("sample %d\n", 100);
	std::cout << "result => " << result << std::endl;
}






#include <iostream>
//#include <crtdbg.h>

int main()
{
	int* integer = new int;
	float* floating = new float;

	*integer = 3;
	*floating = 3.0f;

	delete (integer, floating);
//	delete (integer);
	delete (floating);

	std::cout << *integer << std::endl;

//	_CrtDumpMemoryLeaks();	// ���̎��_�ŊJ������Ă��Ȃ��������̏��̕\��
	return 0;
}






#include <iostream>
#include <math.h>


float getGausianRandom(float average, float sigma)
{
	// �����_���Ȑ������Q�쐬
	int random = rand()%100000;
	float x = static_cast<float>(random)/100000.0f;
	random = rand()%100000;
	float y = static_cast<float>(random)/100000.0f;

	// �K�E�X���z�ɉ������m���Ń����_���Ȑ����P�쐬
	double result = .0;
	result = sqrt((-2 * log(y))) * (cos(2 * M_PI * x));

	// ���ϒl�ƕ��U���g���ă����_���l���v�Z
	float returnData = static_cast<float>((result * sigma) + average);

	return returnData;
}


int main() {
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
	std::cout << getGausianRandom(1.0f, .10f) << std::endl;
}


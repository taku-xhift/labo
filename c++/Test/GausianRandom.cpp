
#include <iostream>
#include <math.h>


float getGausianRandom(float average, float sigma)
{
	// ランダムな数字を２つ作成
	int random = rand()%100000;
	float x = static_cast<float>(random)/100000.0f;
	random = rand()%100000;
	float y = static_cast<float>(random)/100000.0f;

	// ガウス分布に応じた確立でランダムな数を１つ作成
	double result = .0;
	result = sqrt((-2 * log(y))) * (cos(2 * M_PI * x));

	// 平均値と分散を使ってランダム値を計算
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


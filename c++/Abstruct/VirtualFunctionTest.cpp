


#include <iostream>


class Virtual
{
public:

	virtual int getter()
	{
		return 1;
	}
};



class Main : public Virtual
{
public:

	int getter()
	{
		int local = 1;

		// �p�����Ƃ̊֐����Ăяo������
		local += Virtual::getter();
		//local += __super::getter();

		return local;
	}
};



int main()
{
	Main main1;

	// 2 �Əo��Ί��Ғʂ�
	std::cout << main1.getter() << std::endl;

	return 0;
}



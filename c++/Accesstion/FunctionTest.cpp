//
// �����ł͌p����ł̊֐��̌Ăяo�����ɂ��Č��؂���B
//     ���؎��R    �p����ł̌p�����Ƃ̊֐��̌Ăяo���ɂ���
//     ���_        �X�R�[�v�𖾊m�����邱�ƂŌp�����Ƃ̊֐��Ɠ����̊֐������L���Ă����ꍇ��
//                     ��������Ƃ����Ăт킯���ł��邱�Ƃ��Ċm�F�����B



#include <iostream>


class Super
{
public:
	Super()
	{
		std::cerr << "Constructor of Super." << ::std::endl;
	}

	void init()
	{
		this->check1 = 1.0f;
		this->check2 = 1.0f; 
		this->class
	}


	float   check1;
	float   check2;
};


class Child    : public Super
{
public:
	Child()
	{
		::std::cerr << "Constructor of Child." << ::std::endl;
	}

	void init()
	{
		this->check1 = 2.0f;
		this->check2 = 2.0f;
		this->check3 = 2.0f;
		this->check4 = 2.0f;

		Super::init();
	}


	float check3;
	float check4;

};




int main()
{
	//Super super;
	Child child;


	child.init();


	::std::cerr << child.check1 << ::std::endl;
	::std::cerr << child.check2 << ::std::endl;
	::std::cerr << child.check3 << ::std::endl;
	::std::cerr << child.check4 << ::std::endl;


	return 0;
}






// �q���N���X�̕ۑ����@�ɂ��Ă̎���

// ���_
// �N���X�̃����o�Ƃ��ĕۑ����邱�Ƃ͉\�����A
// Super class �������o�Ƃ��ĕۑ�����ꍇ�ɂ͂������A
// �q���̃N���X�^�Ń����o�������Ă����ꍇ�ɂ�
// Super class �̕ۑ����@���Ȃ��̂Œ��ӂ��K�v�B

// �p�̓f�[�^�̌`���ς��\��������ꍇ�ɂ�
// �e�̃N���X�^�Ńf�[�^�������Ă����Ƃ����B

//---------------------------------------------
//  ���_
//---------------------------------------------
// �e�N���X�^�Ńf�[�^��ێ����Ă���ƁA�Ⴆ�΃f�[�^�����o�������ꍇ��
// �q�N���X��n���Ċi�[�����Ƃ��Ă����o�������e�N���X���q�����o���Ȃ�



#include <iostream>

class Super
{

};

class Child : public Super
{

};


class Save
{
public:
	Child child;
	Super super;

	//void cout(Child &child)
	//{
	//	::std::cerr << "Success!" << ::std::endl;
	//}

	void cout(Super &super)
	{
		::std::cerr << "Success!" << ::std::endl;
	}
};




int main()
{
	Save save;
	Child child;
	Super super;

	//save.child = super;
	save.super = child;
//	save.child = super;

	//save.cout(super);
	save.cout(child);

	return 0;
}



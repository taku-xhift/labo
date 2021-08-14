
/*
 * @note
 *      �����o�֐��|�C���^�̓f�[�^��ۑ�����̂�
 *      �ǂ̃N���X�̊֐��|�C���^�Ȃ̂���ۑ����Ȃ��Ă͂����Ȃ��̂�
 *      �S�ẴN���X�̊֐���ۑ�����悤�ȃO���[�o�������o����邱�Ƃ͂ł��Ȃ��B
 *
 *      �֐��|�C���^���g���āA����{�^������������
 *      �f�[�^���v�����g�����悤�ȃ��\�b�h����肽�������B
 *      ����������͔��ɖʓ|���������������̂ŁA�p���B
 *      �ȉ��́A���s�������́B
 * 
 *      �R�[���o�b�N�̃R���e�i���čl�����̕��������̂����B�B
*/

#include <iostream>
#include <vector>

//std::vector<void*> fpContainer;


void out() {
	std::cout << "Out of Global." << std::endl;
}

void (*userFunc)(void) = out;


class Test
{
public:

	void out() {
		std::cout << "Out of Test." << std::endl;
	}

	Test()
	{
		userFunc = (&Test::out);
	}
};


int main()
{
	out();

	return 0;
}



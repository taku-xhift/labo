/*
	HeaderFile �Ɗ֐��̊֌W���ɂ��ă`�F�b�N�B
	���_���炢���ƁA�悭�킩��Ȃ��B
	Header �ɐ錾�������ă\�[�X�t�@�C���ɒ��g��������
	�Ȃ��F������Ȃ������킩��Ȃ��B
	���Ƃŕ����Č���Ƃ�����������Ȃ��B
*/



#include <iostream>

#include "VoidArray.hpp"



int main()
{
	VoidArray voidArray;
	voidArray.voidData = 2.3f;

	std::cout << voidArray.value<int> () << std::endl;

	return 0;
}



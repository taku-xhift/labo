
#ifndef VOIDARRAY_HPP
#define VOIDARRAY_HPP


class VoidArray
{
public:

	template<typename T> T &value() throw();
	//{
	//	//// �擾�����\��̃f�[�^����Ɉړ����Ă�����
	//	//this->offset += sizeof(T);

	//	//// offset �����Z�����O�̃f�[�^�̃|�W�V������ԋp
	//	//return *(*T)(this->pointer + this->offset - sizeof(T));
	//	return *(T*)(this->voidData);
	//}

	float voidData;
	float offset;
	float pointer;
};


#endif 




#include <iostream>


// ��O�x�[�X�N���X
class LibrariesException    : public ::std::exception
{
public:

	// ::std::exception ��������p���� virtual �֐�
	virtual const char* what() const throw()
	{
		return "Libraries Exception";
	}
};

// ��O�x�[�X�N���X���p�����Ă��������p�̃x�[�X�N���X
class PhysicsException    : public LibrariesException
{
public:

	// LibrariesException �� Virtual �֐��������p�����֐�
	virtual const char* what() const throw()
	{
		return "Physics Exception";
	}


	// ������߂Ă����Œ�`�����������g�p���邽�߂̗�O�֐��B
	//     ����͏���������Ă��Ȃ��\��������ꍇ�ɕ�������o�͂��邽�߂̊֐��ł��B
	//     �g���Ă����ʂ� ExceptionTest::initializedCheck() �����ŁA
	//     ���̊֐��� private �ɂȂ��Ă���̂ŁA���[�U�[�������m�邱�Ƃ͂���܂���B
	void initializedCheck() const throw(PhysicsException)
	{
		std::cout << "InitializeError!! (You should check parameter what is initalized.)" << std::endl;
		throw PhysicsException();
	}
};


// ����͂���̊֐����g���ė�O�N���X�̗������Ă��܂��B
class ExceptionTest
{
private:

	// ���̊֐��ɌĂ΂��֐��ł��B
	//     ���g�͏���������Ă��邩�ǂ������`�F�b�N���邽�߂̊֐��ł��B
	//     ��O�Ƃ��� PhysicsException �� throw ���܂��B
	void initialaizedCheck(int i) throw(PhysicsException)
	{
		if (i == NULL) {
			throw PhysicsException();
		}
	}


public:
	// ����͏�̊֐��𗘗p���Ċ�������֐��ł��B
	//     initializedCheck �����Ă���a���v�Z���Ԃ��܂��B
	int AdditionalReturner (int a, int b) throw(PhysicsException)
	{
		int Int;

		try {
			this->initialaizedCheck(a);
			this->initialaizedCheck(b);
		} catch (PhysicsException& pe) {
			pe.initializedCheck();
			//throw PhysicsException();    // initializedCheck() ������ throw ����ׂ����͋c�_�̗]�n������Ǝv���܂��B
		}

		Int = a + b;

		return Int;
	}
};


int main()
{
	// �����������Ɏg�����߂̃p�����[�^�Q
	int sum = 0;
	int parameter = 0;
	ExceptionTest exceptionTest;


	// �������炪�`�F�b�N���邽�߂̃e�X�g�t�B�[���h�B
	try {
		// ����̓��[�U�[�Ɍ��J���Ă���֐��B
		//     ������ initializedCheck �������Ă��邱�Ƃ̓��[�U�[�͒m��Ȃ��Ă����B
		sum = exceptionTest.AdditionalReturner(parameter, parameter);

		// �オ��O���o���Ă��Ȃ���Ώo�́B
		std::cout << sum << std::endl;

	} catch (LibrariesException& le) {

		// �L���b�`�͗�O�x�[�X�N���X�ŁA���ʂ� Virtual �֐����Ăяo�������Ń`�F�b�N�͂ł���B
		//     ����ł����� PhysicsException ���G���[��f���Ă��邱�Ƃ��`�F�b�N�ł���B
		std::cout << le.what() << std::endl;
	}

	return 0;
}


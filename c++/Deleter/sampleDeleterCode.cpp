

class X
{
public:

	~X()
	{
		std::cout << "X::~X" << std::endl;
	}
};

class B
{
public:

	~B() // virtual �łȂ����Ƃɒ��ӁI�I
	{
		std::cout << "B::~B" << std::endl;
	}
};

class D : public B
{
public:

	~D()
	{
		std::cout << "D::~D" << std::endl;
	}
};

int main()
{
	{
		boost::shared_ptr< void > px( new X() ); // void * �̂悤�Ɍ����邯��ǁc�c
	} // �����ł����� X::~X ������I

	{
		boost::shared_ptr< B > pb( new D() ); // �f�X�g���N�^�����z�łȂ����N���X�̃X�}�|��
		// �h���N���X�̃|�C���^�����D���v���H
	} // ������ D::~D ���Ă΂�܂��I
}




#include <iostream>


// �Q�ƁF http://ja.wikibooks.org/wiki/More_C%2B%2B_Idioms/%E5%AE%89%E5%85%A8%E3%81%AA_bool(Safe_bool)

class safe_bool_base
{
public:

	typedef void (safe_bool_base::*bool_type)() const;
	void this_type_does_not_support_comparisons() const {}

protected:

	safe_bool_base() {}
	safe_bool_base(const safe_bool_base&) {}
	safe_bool_base& operator=(const safe_bool_base&) { return *this; }
	~safe_bool_base() {}
};


// ���z�֐��Ȃ��ł̃e�X�g���̂���
template <typename T> 
class safe_bool
	: private safe_bool_base
{
	// main ���ŃA�N�Z�X����ᔽ�������N�������߂ɁA
	// private �p�����Aprotected �p���ł��邱�Ƃ����ɏd�v
public:
	operator bool_type() const {
		return (static_cast<const T*>(this))->boolean_test()
			? &safe_bool_base::this_type_does_not_support_comparisons : 0;
	}
protected:
	~safe_bool() {}
};

template <typename T> 
bool operator==(const safe_bool<T>& lhs, bool b) {
	if (b)
	{
		if (lhs) return true;
		else return false;
	}
	else
	{
		if (lhs) return false;
		else return true;
	}
}

template <typename T> 
bool operator==(bool b, const safe_bool<T>& rhs) {
	if (b)
	{
		if (rhs) return true;
		else return false;
	}
	else
	{
		if (rhs) return false;
		else return true;
	}
}


template <typename T, typename U> 
void operator==(const safe_bool<T>& lhs,const safe_bool<U>& rhs) {
	lhs.this_type_does_not_support_comparisons();  
}

template <typename T,typename U> 
void operator!=(const safe_bool<T>& lhs,const safe_bool<U>& rhs) {
	lhs.this_type_does_not_support_comparisons();
}


class Testable_without_virtual : 
	public safe_bool <Testable_without_virtual> // CRTP �C�f�B�I��
{
public:
	bool boolean_test() const {
		// �^�U�l�ɕω����郍�W�b�N�������Ŏ��s
		return false;
	}

	bool operator==(const Testable_without_virtual&) const {
		return true;
	}
};

int main (void)
{
	Testable_without_virtual p1, p2;
	if (p1 == false) 
	{
		std::cout << "p1 == false\n";
	}
	if (p1 == p2) {
		std::cout << "operator ==" << std::endl;
	} // ���Ғʂ�A�R���p�C���ł��Ȃ�
	//int i = p1;
	//std::cout << i << std::endl;
	//if (t1 != t2) {} // ���Ғʂ�A�R���p�C���ł��Ȃ�
	
	return 0;
}


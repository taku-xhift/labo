


#include <iostream>


#define accessorR(type, name)                                               \
	public:                                                                 \
		const type& name() const throw() { return this->name##_; }          \
	private:                                                                \
		type name##_;


#define accessorW(type, name)                                               \
	public:                                                                 \
		void name(const type& value) throw() { this->name##_ = value; }     \
	private:                                                                \
		type name##_;


#define accessorRW(type, name)                                              \
	public:                                                                 \
		const type& name() const throw() { return this->name##_; }          \
		void name(const type& value) throw() { this->name##_ = value; }     \
	private:                                                                \
		type name##_;



#define accessorRCopy(type, name)                                           \
	public:                                                                 \
		type name() const throw() { return this->name##_; }                 \
	private:                                                                \
		type name##_;


#define accessorWCopy(type, name)                                           \
	public:                                                                 \
		void name(type value) throw() { this->name##_ = value; }            \
	private:                                                                \
		type name##_;


#define accessorRWCopy(type, name)                                          \
	public:                                                                 \
		type name() const throw() { return this->name##_; }                 \
		void name(type value) throw() { this->name##_ = value; }            \
	private:\
		type name##_;



//! \breif read only �ȃ����o��ǉ�����
//! \note   char �z���p
//! \param[in]  type    �^
//! \param[in]  name    �ϐ����B������ _ �������ŕt�������
#define accessorRCharArray(name, size)                                      \
	public:                                                                 \
		const char* const name() const throw() { return this->name##_; }    \
	private:                                                                \
		char name##_[size];



//! \breif write only �ȃ����o��ǉ�����
//! \note   char �z���p
//! \param[in]  type    �^
//! \param[in]  name    �ϐ����B������ _ �������ŕt�������
#define accessorWCharArray(name, size)                                      \
	public:                                                                 \
		void name(const char* const value) throw() {                        \
			memmove(this->name##_, value, sizeof(name##_));                 \
			this->name##_[size-1] = '\0';                                   \
		}                                                                   \
	private:                                                                \
		char name##_[size];



//! \breif read write ���ɉ\�ȃ����o��ǉ�����
//! \note   char �z���p
//! \param[in]  type    �^
//! \param[in]  name    �ϐ����B������ _ �������ŕt�������
#define accessorRWCharArray(name, size)                                     \
	public:                                                                 \
		const char* const name() const throw() { return this->name##_; }    \
		void name(const char* const value) throw() {                        \
			memmove(this->name##_, value, sizeof(name##_));                 \
			this->name##_[size-1] = '\0';                                   \
		}                                                                   \
	private:                                                                \
		char name##_[size];





class Test {
public:
	static const int ArraySize = 0xff;

	Test() throw() : integer_(0) {}

	accessorRWCopy(int, integer);
	accessorRWCharArray(string, ArraySize);
};



int main() {
	Test test;
	test.integer(3);
	test.string("sample");
	std::cerr << test.integer() << std::endl;
	std::cerr << test.string() << std::endl;
}


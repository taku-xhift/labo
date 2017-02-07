


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



//! \breif read only なメンバを追加する
//! \note   char 配列専用
//! \param[in]  type    型
//! \param[in]  name    変数名。末尾に _ が自動で付加される
#define accessorRCharArray(name, size)                                      \
	public:                                                                 \
		const char* const name() const throw() { return this->name##_; }    \
	private:                                                                \
		char name##_[size];



//! \breif write only なメンバを追加する
//! \note   char 配列専用
//! \param[in]  type    型
//! \param[in]  name    変数名。末尾に _ が自動で付加される
#define accessorWCharArray(name, size)                                      \
	public:                                                                 \
		void name(const char* const value) throw() {                        \
			memmove(this->name##_, value, sizeof(name##_));                 \
			this->name##_[size-1] = '\0';                                   \
		}                                                                   \
	private:                                                                \
		char name##_[size];



//! \breif read write 共に可能なメンバを追加する
//! \note   char 配列専用
//! \param[in]  type    型
//! \param[in]  name    変数名。末尾に _ が自動で付加される
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


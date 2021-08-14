
#ifndef NONCOPYABLE_HPP_INCLUDED
#define NONCOPYABLE_HPP_INCLUDED


//! \brief private 継承することでコピー禁止にする
class NonCopyable
{
protected:

	NonCopyable() throw() {}

	~NonCopyable() {}

private:

	//! \brief inhibition of copy
	NonCopyable(const NonCopyable&) throw();

	//! \brief inhibition of substitution
	const NonCopyable& operator=(const NonCopyable&) throw();

};


#endif


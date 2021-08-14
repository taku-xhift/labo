
#ifndef NONCOPYABLE_HPP_INCLUDED
#define NONCOPYABLE_HPP_INCLUDED


//! \brief private �p�����邱�ƂŃR�s�[�֎~�ɂ���
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


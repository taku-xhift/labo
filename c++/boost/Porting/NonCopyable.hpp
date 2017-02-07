/**
 * @file
 * @brief boost ÇÃ noncopyable ÇÃà⁄êA
 * @note    See http://www.boost.org/libs/utility for documentation.
 *
 * @author Takuya Shishido
 * @date   2011.02.17 18:14:56
 *
 * @version 0.01, Shishido Takuya, 2011.02.17 18:14:56
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef NONCOPYABLE_HPP_INCLUDED
#define NONCOPYABLE_HPP_INCLUDED


//! \brief private åpè≥Ç∑ÇÈÇ±Ç∆Ç≈ÉRÉsÅ[ã÷é~Ç…Ç∑ÇÈ
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


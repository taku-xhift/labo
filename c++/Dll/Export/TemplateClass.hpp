/**
 * @file TemplateClass.hpp
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2012.01.07 00:29:13
 *
 * @version 1.00, Shishido Takuya, 2012.01.07 00:29:14
 *      (c) 2012 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef MODE_TEMPLATECLASS_HPP_INCLUDED
#define MODE_TEMPLATECLASS_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------


namespace mode {


template<typename T>
class TemplateClass
{
public:

	//! \brief constructor
	TemplateClass() throw() {}


	//! \brief destructor
	~TemplateClass() throw() {}

	const T& getT() const { return this->t_; }
	void setT(const T& t) { this->t_ = t; }

private:

	T t_;

};    // class TemplateClass

}    // namespace mode


#endif


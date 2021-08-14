
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


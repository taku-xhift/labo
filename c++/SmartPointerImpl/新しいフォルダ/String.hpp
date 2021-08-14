//! \file
//! \brief String class.
//!         This class is for practice.
//!
//! \author Shishido Takuya
//! \date 2009-06-24
//!
//! \version 0.01, Shishido Takuya, 2009-06-24
//!
//! (c) 2009 Uehara seminar

#ifndef STRING_HPP
#define STRING_HPP


//-----------------------------------------
// include files
//-----------------------------------------
#include "SmartPointer.hpp"


class String
{
public:

	//! brief constructor
	String(const char *value = "");

	//! brief operators
	char operator[] (int index) const;
	char& operator[] (int index);

//	const char* getValue() {
//		return value;
//	}

private:

	//! brief Use for SmartPointer
	struct StringValue : public RCObject
	{
		//! brief constructor
		StrinfValue(const char *initValue);

		//! brief copy constructor
		StrinfValue(const StringValue& rhs);

		//! brief initialize
		void init(const char *initValue);

		//! brief destructor
		~StringValue();
	};

	SmartPointer<String Value> value;    //!< SmartPointer member

};


#endif    // String_HPP


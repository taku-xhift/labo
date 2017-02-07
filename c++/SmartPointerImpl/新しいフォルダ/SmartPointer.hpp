//! \file
//! \brief SmartPointer
//!
//! \author Shishido Takuya
//! \date 2009-06-24
//!
//! \version 0.01, Shishido Takuya, 2009-06-24
//!
//! (c) 2009 Uehara seminar

#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP


#include <iostream>


//! breif Counter Class of Reference.
class RCObject
{
public:

	//! brief constructor
	RCObject();

	//! brief copy constructor
	RCObject(const RCObject& rhs);

	//! breif operator=
	RCObject& operator=(const RCObject& rhs);

	//! breif destructor
	virtual ~RCObject() = 0;

	//! brekf Add counter of Reference.
	void addReference();

	//! breif Remover.
	void removeReference();

	//! breif Set mard as Unshareable.
	void markUnshareable();

	//! breif Return this object can share.
	//! retval true  Can share.
	//! retval false Cannot share.
	bool isShareable() const;

	//! breif Return this object is already shared.
	//! retval true  shared
	//! retval false Not shared
	bool isShared() const;


private:

	size_t refCount;    //!< Couter of reference.
	bool shareable;     //!< Check member of shareable.
};





//! breif SmartPointer
template<typename T>
class SmartPointer
{
public:

	//! brief constructor
	SmartPointer(T *realPtr = NULL);

	//! breif copy constructor
	SmartPointer(const SmartPointer& rhs);

	//! brief destructor
	~SmartPointer();

	//! brief operator=
	SmartPointer& operator=(const SmartPointer& rhs);

	//! breif access operators
	T* operator->() const;
	T& operator*() const;

private:

	T *pointee;    //!< Real pointer

	//! breif initialize function
	void init();

};


#endif    // SMARTPOINTER_HPP


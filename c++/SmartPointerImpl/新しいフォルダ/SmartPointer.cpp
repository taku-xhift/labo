


#include "SmartPointer.hpp"


RCObject::RCObject()
: refCount(0)
, shareable(true)
{
}

RCObject::RCObject(const RCObject &rhs)
: refCount(0)
, shareable(true)
{
}

RCObject& RCObject::operator=(const RCObject &rhs)
{
	return *this;
}

RCObject::~RCObject()
{
}

void RCObject::addReference()
{
	++this->refCount;
}

void RCObject::removeReference()
{
	if (this->refCount) {
		delete this;
	}
}

void RCObject::markUnshareable()
{
	this->shareable = false;
}

bool RCObject::isShareable() const
{
	return this->shareable;
}

bool RCObject::isShared() const
{
	return (this->refCount > 1);
}




/*

	SmartPointer functions.

*/

template<typename T>
SmartPointer<T>::SmartPointer(T *realPtr /* = NULL*/)
	: pointee(realPtr)
{
	this->init();
}


template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T> &rhs)
: pointee(rhs.pointee)
{
	this->init();
}


template<typename T>
SmartPointer<T>::~SmartPointer()
{
	if (this->pointee) {
		this->pointee->removeReference();
	}
}


template<typename T>
SmartPointer<T>& SmartPointer<T>::operator =(const SmartPointer<T> &rhs)
{
	if (this->pointee != rhs.pointee) {
		T* oldPointee = this->pointee;
		this->pointee = rhs.pointee;

		this->init();

		if (oldPointee) {
			oldPointee->removeReference();
		}
	}

	return *this;
}


template<typename T>
T* SmartPointer<T>::operator->() const
{
	return this->pointee;
}

template<typename T>
T& SmartPointer<T>::operator*() const
{
	return *this->pointee;
}


template<typename T>
void SmartPointer<T>::init()
{
	if (this->pointee == NULL) {
		return;
	}

	if (this->pointee->isShared() == false) {
		this->pointee = new T(*this->pointee);
	}

	this->pointee->addReference();
}







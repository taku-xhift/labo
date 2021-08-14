

#ifndef MANAGER_HPP
#define MANAGER_HPP


//#include <iostream>
#include <typeinfo>
#include "StateMachine.hpp"


class StateManager
{
private:
	friend class State;
	friend class InitState;
	friend class RoopState;
	friend class ReleaseState;
	friend class ErrorState;

public:

	StateManager()
	{
		this->initState = new InitState(const_cast<StateManager*>(this));
		this->roopState = new RoopState(const_cast<StateManager*>(this));
		this->releaseState = new ReleaseState(const_cast<StateManager*>(this));
		this->errorState = new ErrorState(const_cast<StateManager*>(this));

		this->nowState = this->initState;
	}

	~StateManager()
	{
		delete this->errorState;
		delete this->releaseState;
		delete this->roopState;
		delete this->initState;
	}

	void setState(State* state_)
	{
		this->nowState = state_;
	}

	const char* run() {
		this->nowState->run();
		return this->nowState->getStateName();
	}

	const char* getNowStateName() {
		return typeid(this->nowState).name();
	}


	State* getNowState() { return this->nowState; }
	State* getInitState() { return this->initState; }
	State* getRoopState() { return this->roopState; }
	State* getReleaseState() { return this->releaseState; }
	State* getErrorState() { return this->errorState; }

private:

	State* nowState;
	State* initState;
	State* roopState;
	State* releaseState;
	State* errorState;
};


#endif    // MANAGER_HPP



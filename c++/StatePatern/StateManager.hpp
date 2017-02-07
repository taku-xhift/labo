/*!
 * @file
 * @brief GameManager that control gameScene.
 *
 * @author Takuya Shishido
 * @date 2009-10-17
 *
 * @version 0.01, Shishido Takuya, 2009-10-17
 *      (c) 2009 Uehara seminar
*/


#ifndef MANAGER_HPP
#define MANAGER_HPP


//#include <iostream>
#include <typeinfo>
#include "StateMachine.hpp"


class StateManager
{
private:

	static StateManager* uniqueInstance;

public:

	static StateManager* getInstance()
	{
		if (uniqueInstance == NULL) {
			uniqueInstance = new StateManager();
		}
		return uniqueInstance;
	}

	static void destroyInstance()
	{
		if (StateManager::uniqueInstance != NULL) {
			delete StateManager::uniqueInstance;
		}
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

	StateManager()
	{
		this->initState = new InitState(*this);
		this->roopState = new RoopState(*this);
		this->releaseState = new ReleaseState(*this);
		this->errorState = new ErrorState(*this);

		this->nowState = this->initState;
	}

	StateManager(const StateManager&);
	StateManager& operator =(const StateManager&);


	State* nowState;
	State* initState;
	State* roopState;
	State* releaseState;
	State* errorState;
};


#endif    // MANAGER_HPP



/*!
 * @file
 * @brief StateMachine to control GameManager
 *
 * @author Takuya Shishido
 * @date 2009-10-17
 *
 * @version 0.01, Shishido Takuya, 2009-10-17
 *      (c) 2009 Uehara seminar
*/


#include "StateMachine.hpp"
#include "Manager.hpp"


namespace {
	const char* init = "init";
	const char* roop = "roop";
	const char* error = "error";
	const char* release = "release";
	void printOutStateMessage();
}

void printOutStateMessage(StateManager& manager, State& state)
{
	std::cout << "change State." << std::endl;
	std::cout << "From " << state.getStateName() << " to " << manager.getNowStateName() << "." << std::endl;
}


void State::printStateChangeLog() {
	std::cin >> this->input;

	if (this->input == init) {
		manager.setState(manager.getInitState());
		printOutStateMessage(this->manager, *this);
	}

	else if (this->input == roop) {
		manager.setState(manager.getRoopState());
		printOutStateMessage(this->manager, *this);
	}

	else if (this->input == release) {
		manager.setState(manager.getRoopState());
		printOutStateMessage(this->manager, *this);
	}

	else if (this->input == error) {
		manager.setState(manager.getErrorState());
		printOutStateMessage(this->manager, *this);
	}

	else {
		std::cout << "Invalid input!!!" << std::endl;
	}
}



void InitState::run()
{
	this->printStateChangeLog();
//	this->getNextState();
}

const char*InitState::getStateName()
{
	return typeid(InitState).name();
}

void RoopState::run()
{
	this->printStateChangeLog();
//	this->getNextState();
}
const char* RoopState::getStateName()
{
	return typeid(RoopState).name();
}

void ErrorState::run()
{
	this->printStateChangeLog();
//	this->getNextState();
}
const char* ErrorState::getStateName()
{
	return typeid(ErrorState).name();
}

void ReleaseState::run()
{
	this->printStateChangeLog();
//	this->getNextState();
}
const char* ReleaseState::getStateName()
{
	return typeid(ReleaseState).name();
}




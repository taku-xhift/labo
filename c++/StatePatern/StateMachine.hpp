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


#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <iostream>
#include <typeinfo>
#include <string>


class StateManager;

/**
 * The Super class which decide a GameManager's action.
 *
 * This class is planned to fit design pattern of "State Pattern".
 *      So, if you control GameManager, you have to create a class
 *      which is inherit this class.
 * @author Takuya Shishido
 * @date 2009-10-17
 * @version 0.01
*/
class State
{

public:

	/**
	 * constructor.
	 *
	 * @param[in]    manager_    GameManager object.
	*/
	State(StateManager& manager_)
		: manager(manager_)
	{
	}

	/**
	 * destroctor
	 *
	 * This function is virtual function.
	 *      Because, this class is planned as super class.
	*/
	virtual ~State()
	{
	}

	/**
	 * Function to get class Name.
	 *
	 * To let a child say his name, I set this function as pure virtual.
	 * @return Child class's name.
	*/
	virtual const char* getStateName() = 0;//     { return typeid(State).name(); }

	/**
	 * Executional Function.
	 *
	 * For keeping a expansibility, I define as pure virtual.
	*/
	virtual void run() = 0;


	/**
	 * Print a log to debug a state change.
	*/
	void printStateChangeLog();

	/**
	 * getter
	 *
	 * getter of next state.
	 * @return next state.
	*/
	const char* getNextState()
	{
		return "next";
	}

private:

	StateManager& manager;  //!< GameManager's reference.
	std::string input;      //!< Data of user's input.
//	State nextState;
};


/**
 * A class which deicde a initialize method of GameManager.
 *
 * @author  Takuya Shishido
 * @date    2009-10-17
 * @version 0.01
*/
class InitState : public State
{
public:

	/**
	 * constructor
	 *
	 * @param[in]    manager_    GameManager's Instance
	*/
	InitState(StateManager& manager_) : State(manager_)
	{
		
	}

	/**
	 * Execution of GameManager's inialize method.
	 *
	 * initialize method of GameManger conformed to State Patern.
	*/
	void run();

	/**
	 * Getter.
	 *
	 * Getter of StateName.
	*/
	const char* getStateName();
};

class RoopState : public State
{
public:
	RoopState(StateManager& manager_) : State(manager_)
	{
		
	}

	void run();
	const char* getStateName();
};

class ErrorState : public State
{
public:
	ErrorState(StateManager& manager_) : State(manager_)
	{
	}

	void run();
	const char* getStateName();
};



class ReleaseState : public State
{
public:
	ReleaseState(StateManager& manager_) : State(manager_)
	{
	}

	void run();
	const char* getStateName();
};


#endif   // STATEMACHINE_HPP


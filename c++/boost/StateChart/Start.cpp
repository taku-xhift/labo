


#include <iostream>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/transition.hpp>


namespace sc = boost::statechart;


struct greeting;
struct bye;
struct say_good_bye;
struct machine;


struct machine
	: sc::state_machine<machine, greeting>
{
	machine() {
		std::cerr << typeid(machine).name() << "::" << __FUNCTION__ << std::endl;
	}
};


struct greeting
	: sc::simple_state<greeting, machine>
{
	typedef sc::transition<say_good_bye, bye> reactions;

	greeting() {
		std::cerr << typeid(greeting).name() << "::" << __FUNCTION__ << std::endl;
	}
};


struct bye
	: sc::simple_state<bye, machine>
{
	bye() {
		std::cerr << typeid(greeting).name() << "::" << __FUNCTION__ << std::endl;
		std::cerr << "bye" << std::endl;
	}
};


struct say_good_bye
	: sc::event<say_good_bye>
{
	
};


int main() {
	machine the_machine;
	std::cerr << "before initiate()" << std::endl;
	the_machine.initiate();
	the_machine.process_event(say_good_bye());
}



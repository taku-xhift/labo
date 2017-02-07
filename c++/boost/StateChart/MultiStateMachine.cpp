

#include <iostream>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>


using namespace std;
namespace sc = boost::statechart;

namespace states
{
	struct main;

	struct on;
	struct off;

	struct enable;
	struct disable;

	struct mode1;
	struct mode2;
	struct mode3;
}

struct machine : sc::state_machine< machine, states::main >
{
	machine() { initiate(); }

	void print_states();

	void operator()() const throw();
};

namespace events
{
	struct go_to_next_mode
		: sc::event< go_to_next_mode >
	{};

	struct toggle_on_off
		: sc::event<toggle_on_off>
	{};
}

namespace states
{
	struct StateBase
	{
		virtual void update() const throw() = 0;
	};

	struct main
		: sc::simple_state< main, machine,
			boost::mpl::list< on, enable, mode1 > >
	{
		typedef
			sc::custom_reaction<events::toggle_on_off>
				reactions;

		sc::result react(const events::toggle_on_off&) {
			const bool is_on        = !!state_downcast<const on*>();
			const bool is_enable    = !!state_downcast<const enable*>();
			const bool is_mode3     = !!state_downcast<const mode3*>();

			if (is_on) {
				if (is_enable && is_mode3) {
					std::cerr << "if (is_enable && is_mode3) {\n";
					return transit<disable>();
				} else {
					std::cerr << "nif (is_enable && is_mode3) {\n";
					return transit<off>();
				}
			} else {
				return transit<on>();
			}
		}
	};


	struct      on : sc::simple_state<      on, main::orthogonal< 0 > > , public StateBase { virtual void update() const throw() { std::cerr << typeid(*this).name() <<  "on" << "\n"; } };
	struct     off : sc::simple_state<     off, main::orthogonal< 0 > > , public StateBase { virtual void update() const throw() { std::cerr << typeid(*this).name() <<  "off" << "\n"; } };

	struct  enable : sc::simple_state<  enable, main::orthogonal< 1 > > , public StateBase { virtual void update() const throw() { std::cerr << typeid(*this).name() <<  "enable" << "\n"; } };
	struct disable : sc::simple_state< disable, main::orthogonal< 1 > > , public StateBase { virtual void update() const throw() { std::cerr << typeid(*this).name() <<  "disable" << "\n"; } };

	struct   mode1 : sc::simple_state<   mode1, main::orthogonal< 2 > > , public StateBase 
	{
		typedef
			sc::transition< events::go_to_next_mode, mode2 >
				reactions;
		virtual void update() const throw() { std::cerr << typeid(*this).name() <<  "mode1" << "\n"; }
	};

	struct   mode2 : sc::simple_state<   mode2, main::orthogonal< 2 > > , public StateBase 
	{
		typedef
			sc::transition< events::go_to_next_mode, mode3 >
				reactions;
		virtual void update() const throw() { std::cerr << typeid(*this).name() <<  "mode2" << "\n"; }
	};
	struct   mode3 : sc::simple_state<   mode3, main::orthogonal< 2 > > , public StateBase 
	{
		typedef
			sc::transition< events::go_to_next_mode, mode1 >
				reactions;
		virtual void update() const throw() { std::cerr << typeid(*this).name() <<  "mode3" << "\n"; }
	};
}

void machine::print_states()
{
	for( state_iterator i = this->state_begin(); i != this->state_end(); ++ i )
	{
		#define print_if_same_type( state_name )                    \
			if( typeid( * i ) == typeid( states::state_name ) ) {   \
				cout << #state_name << " ";                         \
			}

		print_if_same_type( on );
		print_if_same_type( off );
		print_if_same_type( enable );
		print_if_same_type( disable );
		print_if_same_type( mode1 );
		print_if_same_type( mode2 );
		print_if_same_type( mode3 );

		#undef print_if_same_type
	}

	cout << endl;
}

void machine::operator()() const throw() {
	for (state_iterator i = this->state_begin(); i != this->state_end(); ++i) {
		//const states::StateBase& state = state_cast<const states::StateBase&>();
		//state.update();
		i->update();
	}
	std::cerr << "Sleeping..." << std::endl;
	//sleep(1);
}



int main()
{
	machine the_machine;

	the_machine.print_states();
	std::cerr << std::endl;

	std::cerr << "go next\n";
	the_machine.process_event( events::go_to_next_mode() );
	the_machine.print_states();
	std::cerr << std::endl;

//	std::cerr << "toggle" << std::endl;
//	the_machine.process_event( events::toggle_on_off() );
//	the_machine.print_states();
//	std::cerr << std::endl;

	std::cerr << "go next\n";
	the_machine.process_event( events::go_to_next_mode() );
	the_machine.print_states();
	std::cerr << std::endl;

	std::cerr << "toggle" << std::endl;
	the_machine.process_event( events::toggle_on_off() );
	the_machine.print_states();
	std::cerr << std::endl;


	for (int i = 0; i < 1; ++i) {
		the_machine();
	}
}


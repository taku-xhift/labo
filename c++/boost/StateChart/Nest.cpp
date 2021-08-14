
#include <iostream>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/deferral.hpp>
#include <boost/statechart/event.hpp>

using namespace std;
namespace sc = boost::statechart;

namespace states
{
	struct power_on;
		struct bit_0;
		struct bit_1;

	struct power_off;
}

// ��ԃ}�V���Bpower_off �ŏ������B
struct machine : sc::state_machine< machine, states::power_off >
{
	machine() { initiate(); }
};

// �C�x���g�̒�`
namespace events
{
	struct push_power_button : sc::event< push_power_button > {};

	struct push_flip_button : sc::event< push_flip_button > {};
}

// ��Ԃ̒�`
namespace states
{
	// power_on �� machine �̏�Ԃ̂ЂƂB������ bit_0 ��������ԁB
	struct power_on
		: sc::simple_state< power_on, machine, bit_0 >
	{
		typedef sc::transition<
			events::push_power_button, power_off
		> reactions;
	};

	// bit_0 �� power_on �̓�����Ԃ̂ЂƂB
	struct bit_0
		: sc::simple_state< bit_0, power_on >
	{
		typedef sc::transition<
			events::push_flip_button, bit_1
		> reactions;

		bit_0() { cout << " bit_0" << endl; }
	};

	// bit_1 �� power_on �̓�����Ԃ̂ЂƂB
	struct bit_1 :
		sc::simple_state< bit_1, power_on >
	{
		typedef sc::transition<
			events::push_flip_button, bit_0
		> reactions;

		bit_1() { cout << " bit_1" << endl; }
	};

	// power_off �� machine �̏�Ԃ̂ЂƂB
	struct power_off
		: sc::simple_state< power_off, machine >
	{
//		typedef boost::mpl::list<
//			// push_power_button �C�x���g�� power_on �ɂȂ�B
//			sc::transition< events::push_power_button, power_on >,
//			// push_flip_button �C�x���g�͉���������B
//			sc::deferral< events::push_flip_button >
//		> reactions;
		typedef sc::transition<
			events::push_power_button, power_on
		> reactions;
	};
}



int main()
{
	// power_off �ŏ������B
	machine the_machine;

	// flip_button �C�x���g�� power_off �ł͖��������B
	the_machine.process_event( events::push_flip_button() );

	// power_on :: bit_0 �ɂȂ�B
	std::cerr << "power_on" << std::endl;
	the_machine.process_event( events::push_power_button() );

	// flip_button �C�x���g���󗝁Bpower_on :: bit_1 �ɑJ�ځB
	std::cerr << "flip_button" << std::endl;
	the_machine.process_event( events::push_flip_button() );

	// power_off �ɂȂ�B
	std::cerr << "power_off" << std::endl;
	the_machine.process_event( events::push_power_button() );

	// ���������� power_on�B
	std::cerr << "repower_on" << std::endl;
	the_machine.process_event( events::push_power_button() );
}



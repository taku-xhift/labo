
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

// 状態マシン。power_off で初期化。
struct machine : sc::state_machine< machine, states::power_off >
{
	machine() { initiate(); }
};

// イベントの定義
namespace events
{
	struct push_power_button : sc::event< push_power_button > {};

	struct push_flip_button : sc::event< push_flip_button > {};
}

// 状態の定義
namespace states
{
	// power_on は machine の状態のひとつ。内部は bit_0 が初期状態。
	struct power_on
		: sc::simple_state< power_on, machine, bit_0 >
	{
		typedef sc::transition<
			events::push_power_button, power_off
		> reactions;
	};

	// bit_0 は power_on の内部状態のひとつ。
	struct bit_0
		: sc::simple_state< bit_0, power_on >
	{
		typedef sc::transition<
			events::push_flip_button, bit_1
		> reactions;

		bit_0() { cout << " bit_0" << endl; }
	};

	// bit_1 は power_on の内部状態のひとつ。
	struct bit_1 :
		sc::simple_state< bit_1, power_on >
	{
		typedef sc::transition<
			events::push_flip_button, bit_0
		> reactions;

		bit_1() { cout << " bit_1" << endl; }
	};

	// power_off は machine の状態のひとつ。
	struct power_off
		: sc::simple_state< power_off, machine >
	{
//		typedef boost::mpl::list<
//			// push_power_button イベントで power_on になる。
//			sc::transition< events::push_power_button, power_on >,
//			// push_flip_button イベントは延期させる。
//			sc::deferral< events::push_flip_button >
//		> reactions;
		typedef sc::transition<
			events::push_power_button, power_on
		> reactions;
	};
}



int main()
{
	// power_off で初期化。
	machine the_machine;

	// flip_button イベントは power_off では無視される。
	the_machine.process_event( events::push_flip_button() );

	// power_on :: bit_0 になる。
	std::cerr << "power_on" << std::endl;
	the_machine.process_event( events::push_power_button() );

	// flip_button イベントを受理。power_on :: bit_1 に遷移。
	std::cerr << "flip_button" << std::endl;
	the_machine.process_event( events::push_flip_button() );

	// power_off になる。
	std::cerr << "power_off" << std::endl;
	the_machine.process_event( events::push_power_button() );

	// もういちど power_on。
	std::cerr << "repower_on" << std::endl;
	the_machine.process_event( events::push_power_button() );
}






#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>


namespace sc = boost::statechart;


namespace states {
	struct Enable;
	struct Disable;
}


class CarCounter
	: public sc::state_machine<CarCounter, states::Disable>
{
public:
	CarCounter()
		: count_(0)
	{
		this->initiate();
	}

	int& count()                { return this->count_; }
	const int& count() const    { return this->count_; }
private:

	int count_;
};


namespace events
{
	struct ToggleEnableDisable
		: sc::event<ToggleEnableDisable>
	{
		
	};

	struct GoThroughCar
		: sc::event<GoThroughCar>
	{
		
	};
}


namespace states {
	struct Disable
		: sc::simple_state<Disable, CarCounter>
	{
		typedef sc::transition<
			events::ToggleEnableDisable, Enable
		> reactions;
	};


	struct Enable
		: sc::simple_state<Enable, CarCounter>
	{
		typedef boost::mpl::list<
			sc::transition<events::ToggleEnableDisable, Disable>,
			sc::custom_reaction<events::GoThroughCar>
		> reactions;

		sc::result react(const events::GoThroughCar& e) {
			++this->context<CarCounter>().count();
			return discard_event();
		}
	};
}


int main() {
	// initiaize with Disable
	CarCounter cc;

	for (int i = 0; i < 50; ++i) {
		switch (i) {
		case 0:
		case 20:
		case 25:
		case 50:
			cc.process_event(events::ToggleEnableDisable());
			// no break;
		default:
			cc.process_event(events::GoThroughCar());
			break;
		}
	}

	std::cerr << cc.count() << std::endl;
}


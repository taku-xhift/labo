


#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>


namespace bsc = boost::statechart;


namespace states {
	struct Base;
	struct Init;
	struct Main;
}


struct Viewer
	: bsc::state_machine<Viewer, states::Init>
{
	void Init() {
		std::cerr << "Viewer::Init\n";
	}

	void Main() {
		std::cerr << "Viewer::Main\n";
	}

//	states::Base* getState() throw();
	void Update() {
		const states::Base* state = state_cast<states::Base*>();
		//state();
	}
};



namespace events {
	struct Init
		: bsc::event<Init>
	{};

	struct Main
		: bsc::event<Main>
	{};
}


namespace states {

	struct Base {
		virtual void operator()() throw() = 0;
	};

	struct Init
		: bsc::simple_state<states::Init, Viewer>
		, Base
	{
		typedef
			bsc::transition<events::Main, states::Main>
				reactions;

		Init() throw() {
			std::cerr << "Init\n";
		}


		void operator()() throw() {
			Viewer& viewer = this->context<Viewer>();
			viewer.Init();
		}
	};


	struct Main
		: bsc::simple_state<states::Main, Viewer>
		, Base
	{
		typedef
			bsc::transition<events::Init, states::Init>
				reactions;

		Main() throw() {
			std::cerr << "Main\n";
		}


		void operator()() throw() {
			Viewer& viewer = this->context<Viewer>();
			viewer.Main();
		}
	};
}


//states::Base* Viewer::getState() throw() {
//	// Œ»Ý‚Ìó‘Ô‚ð•\Ž¦
//	for (Viewer::state_iterator i = this->state_begin(); i != this->state_end(); ++i) {
//		if (typeid(*i) == typeid(states::Init)) { return &(*i); }
//		if (typeid(*i) == typeid(states::Main)) { return &(*i); }
//	}
//}


int main() {
	Viewer viewer;
	viewer.initiate();

	viewer.process_event(events::Init());
	viewer.process_event(events::Main());
	viewer.process_event(events::Init());
}



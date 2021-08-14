#include <iostream>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/in_state_reaction.hpp>
#include <boost/mpl/list.hpp>

using namespace std;
//using namespace boost::statechart;


// ���
struct Locked;
struct Unlocked;


// �C�x���g
struct Coin   : boost::statechart::event<Coin>
{
};

struct Pass   : boost::statechart::event<Pass>
{
};


// ��ԃ}�V��
struct Gate   : boost::statechart::state_machine<Gate, Locked>
{
};


// Locked ��Ԃ̒�`
struct Locked    : boost::statechart::simple_state<Locked, Gate>
{
	void Alarm( const Pass& )
	{
		std::cout << "ALARM!!!" << std::endl;
	}

	typedef boost::mpl::list<
		boost::statechart::transition          < Coin, Unlocked >,
		boost::statechart::in_state_reaction   < Pass, Locked, &Locked::Alarm >
	> reactions;
};

// Unlocked ��Ԃ̒�`
struct Unlocked    : boost::statechart::simple_state<Unlocked, Gate>
{
	void Thankyou( const Coin& )
	{
		std::cout << "Thank you : )" << std::endl;
	}

	typedef boost::mpl::list<
		boost::statechart::in_state_reaction < Coin, Unlocked, &Unlocked::Thankyou>,
		boost::statechart::transition       < Pass, Locked >
	> reactions;
};

int main()
{

	Gate gate;

	gate.initiate();
	gate.process_event( Coin() );
	gate.process_event( Pass() );
	gate.process_event( Pass() );   // ALARM!!!
	gate.process_event( Coin() );
	gate.process_event( Coin() );   // Thank you

}



#include <boost/shared_ptr.hpp>
#include <iostream>

namespace ReseedEngine
{
	namespace Input
	{
		class Input
		{
		public:
			~Input()
			{
				::std::cerr << "Input destruactor is Called." << ::std::endl;
			}

			void callOut()
			{
				::std::cerr << "callOut By InputManager." << ::std::endl;
			}
		};


		class InputManager
		{
		public:
			~InputManager()
			{
				::std::cerr << "InputManager destructor is Called." << ::std::endl;
			}

			Input input;
		};
	}
}





int main()
{
	ReseedEngine::Input::InputManager inputManager;
	boost::shared_ptr<ReseedEngine::Input::Input> input_(new ReseedEngine::Input::Input());
	
	inputManager.input = (*input_);

	inputManager.input.callOut();

	return 0;
}



#include <iostream>


class Virtual
{
public:

	virtual int getter()
	{
		return 1;
	}
};



class Main : public Virtual
{
public:

	int getter()
	{
		int local = 1;

		// Œp³‚à‚Æ‚ÌŠÖ”‚ğŒÄ‚Ño‚µ‚½‚¢
		local += Virtual::getter();
		//local += __super::getter();

		return local;
	}
};



int main()
{
	Main main1;

	// 2 ‚Æo‚ê‚ÎŠú‘Ò’Ê‚è
	std::cout << main1.getter() << std::endl;

	return 0;
}



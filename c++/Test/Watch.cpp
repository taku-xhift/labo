
#include <iostream>

using namespace std;

void printHour(int hour, int minutes);

int main()
{
	int hour = 12;
	int minutes = 60;

/*  cout<<"           *            "<<endl;
    cout<<"	      *         *       "<<endl;
    cout<<"                        "<<endl;
    cout<<"   *               *    "<<endl;
    cout<<"                        "<<endl;
    cout<<"  *        *        *   "<<endl;
    cout<<"                        "<<endl;
    cout<<"   *               *    "<<endl;
    cout<<"                        "<<endl;
    cout<<"      *         *       "<<endl;
    cout<<"           *            "<<endl;
    cout<<"                        "<<endl;
    cout<<"           *            "<<endl;
    cout<<"      *    ^    *       "<<endl;
    cout<<"        \\  |  /         "<<endl;
    cout<<"   *     \\ | /     *    "<<endl;
    cout<<"          \\|/           "<<endl;
    cout<<"  *  <---- * -----> *   "<<endl;
    cout<<"          /|\\           "<<endl;
    cout<<"   *     / | \\     *    "<<endl;
    cout<<"        /  |  \\         "<<endl;
    cout<<"      *    '    *       "<<endl;
    cout<<"           *            "<<endl;
    cout<<"                        "<<endl;
    cout<<"           *            "<<endl;
    cout<<"      *         *       "<<endl;
    cout<<"                        "<<endl;
    cout<<"   * -_         _- *    "<<endl;
    cout<<"       ``-. .-``        "<<endl;
    cout<<"  *        *        *   "<<endl;
    cout<<"       ..-` `-..        "<<endl;
    cout<<"   * -`         `- *    "<<endl;
    cout<<"                        "<<endl;
    cout<<"      *         *       "<<endl;
    cout<<"           *            "<<endl;
    cout<<"                        "<<endl;
    cout<<"           *            "<<endl;
    cout<<"      *         *       "<<endl;
    cout<<"        \\  |  /         "<<endl;
    cout<<"   * -_  \\ | /  _- *    "<<endl;
    cout<<"       ``-.|.-``        "<<endl;
    cout<<"  *  ----- * -----  *   "<<endl;
    cout<<"       ..-`|`-..        "<<endl;
    cout<<"   * -`  / | \\  `- *    "<<endl;
    cout<<"        /  |  \\         "<<endl;
    cout<<"      *         *       "<<endl;
    cout<<"           *            "<<endl;*/

	while (true){
		cout<<"Insert Hour [1-12] : "<<endl;
		cin>>hour;
		if (hour == 0){
			break;
		}

		cout<<"Insert Minutes [0,5,10,...,60] :"<<endl;
		cin>>minutes;
		if (minutes > 60 || hour > 12 | minutes%5 != 0){
			cout<<"Bir hata saptandi!"<<endl;
			continue;
		}
		printHour(hour,minutes);
	}
}

void printHour(int hour, int minutes) {
	cout<<"                        "<<endl;
	cout<<"           *            "<<endl;
	cout<<"      *         *       "<<endl;
	cout<<"        "<<((minutes==55)?("\\"):(" "))
		<<"  "<<((minutes==60 || minutes == 0)?("|"):(" "))<<"  "
		<<((minutes==5)?("/"):(" "))<<"         "<<endl;
	cout<<"   * "<<((minutes == 50)?("-_"):("  "))<<"  "
		<<((hour == 11 || minutes == 55)?("\\"):(" "))
			<<" "<<((hour == 12 || minutes == 60 || minutes == 0)?("|"):(" "))
			<<" "<<((hour == 1 || minutes == 5)?("/"):(" "))<<"  "
			<<((minutes == 10)?("_-"):("  "))<<" *    "<<endl;
	cout<<"       "<<((hour == 10 || minutes == 50)?("``-"):("   "))<<""
		<<((hour == 10 || hour == 11 || minutes == 50 || minutes == 55)?("."):(" "))
		<<""<<((hour == 12 || minutes == 60 || minutes == 0)?("|"):(" "))<<""
		<<((hour == 1 || hour == 2 || minutes == 5 || minutes == 10)?("."):(" "))
		<<""<<((hour == 2 || minutes == 10)?("-``"):("   "))<<"        "<<endl;
	cout<<"  *  "<<((minutes==45)?("-"):(" "))<<""
		<<((hour==9 || minutes == 45)?("----"):("    "))<<" * "
		<<((hour == 3 || minutes == 15)?("----"):("    "))<<""
		<<((minutes==15)?("-"):(" "))<<"  *   "<<endl;
	cout<<"       "<<((hour == 8 || minutes == 40)?("..-"):("   "))
		<<""<<((hour == 7 || hour == 8 || minutes == 40 || minutes == 35)?("`"):(" "))
		<<""<<((hour == 6 || minutes == 30)?("|"):(" "))<<""
		<<((hour == 4 || hour == 5 || minutes == 20 || minutes == 25)?("`"):(" "))
		<<""<<((hour == 4 || minutes == 20)?("-.."):("   "))<<"        "<<endl;
	cout<<"   * "<<((minutes==40)?("-`"):("  "))<<"  "
		<<((hour == 7 || minutes == 35)?("/"):(" "))<<" "
		<<((hour == 6 || minutes == 30)?("|"):(" "))<<" "
		<<((hour == 5 || minutes == 25)?("\\"):(" "))<<"  "
		<<((minutes==20)?("`-"):("  "))<<" *    "<<endl;
	cout<<"        "<<((minutes==35)?("/"):(" "))<<"  "
		<<((minutes==30)?("|"):(" "))<<"  "<<((minutes==25)?("\\"):(" "))
		<<"         "<<endl;
	cout<<"      *         *       "<<endl;
	cout<<"           *            "<<endl;
}

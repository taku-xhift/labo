


#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <array>


using namespace std;


struct People {
	People(int number, string name)
		: number_(number)
		, name_(name)
	{
	}

	int number_;
	string name_;
	vector<int> feeling_;
};


struct Team {
	int teamPower_;
	vector<int> member_;

	Team()
		: teamPower_(0)
	{
		
	}

	bool operator<(const Team& other) const {
		return this->teamPower_ < other.teamPower_;
	}
};


static set<Team> teamPowerList;
static vector<People> peopleList;


class PickTeam {
public:
	static void CulcTeamPower(int teamSize, vector<int> member, const vector<People>& peopleList) {
		if ((teamSize - member.size()) == 0) {
			// ここに入ってきている時点で member は最大限に入っている
			Team team;
			team.member_ = member;

			// ここはチームメイト組合せすべての相性の和を求める
			for (int i = 0; i < member.size(); ++i) {
				for (int j = i+1; j < member.size(); ++j) {
					if (i == j) {
						continue;
					}

					team.teamPower_ += peopleList[member[i]].feeling_[member[j]];
				}
			}

			teamPowerList.insert(team);
			return;
		}

		vector<int> temp;
		const int roopEndNum = peopleList.size() - (teamSize - member.size());
		for (int i = *member.rbegin() +1; i <= roopEndNum; ++i) {
			temp = member;
			temp.push_back(i);
			CulcTeamPower(teamSize, temp, peopleList);
		}
	}

	static vector <string> pickPeople(int teamSize, vector <string> people) {
		string name;
		stringstream ss;

		vector<People> peopleList;
		int tempFeeling;

		for (int i = 0; i < people.size(); ++i) {
			ss << people[i];
			ss >> name;

			People temp(i, name);

			for (int j = 0; j < people.size(); ++j) {
				ss >> tempFeeling;
				temp.feeling_.push_back(tempFeeling);
			}

			peopleList.push_back(temp);

			temp.feeling_.clear();
			ss.str("");
			ss.clear();
		}

		vector<int> member;
		for (int i = 0; i <= people.size() - teamSize; ++i) {
			member.push_back(i);
			CulcTeamPower(teamSize, member, peopleList);
			member.clear();
		}

		set<Team>::const_reverse_iterator ite = teamPowerList.rbegin();

		vector<string> ret;
		for (int i = 0; i < teamSize; ++i) {
			ret.push_back(peopleList[ite->member_[i]].name_);
		}

		sort(ret.begin(), ret.end());

		return ret;
	}

	static void test() {
		{
			array<string, 3> arg =
				{"ZDYSSJ 0 223 -215", "LTWJF 223 0 -588", "BLLIJSAB -215 -588 0"};
			auto ret = pickPeople(2, vector<string>(arg.begin(), arg.end()));
			for (int i = 0; i < ret.size(); ++i) {
				cerr << ret[i] << ", ";
			}
			cerr << "\n";
		}
	}
};




int main() {
	PickTeam::test();
}



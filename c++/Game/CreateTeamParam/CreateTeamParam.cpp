

#pragma warning(disable:4996)
#pragma warning(disable:4290)

#include <algorithm>
#include <limits>
#include <Personal/StreamObject.hpp>
#include "Define.hpp"
#include "Utility.hpp"
#include "DataType.hpp"
#include "Functor.hpp"
#include <stdlib.h>
#include <time.h>


int main() {
	unsigned int count = 0;
	unsigned int select = std::numeric_limits<unsigned int>::max();
	so::out << "Select a League!!\n";
	so::out << count << ": Liga Espanola\n";
	so::out << ++count << ": Premier League\n";
	so::out << ++count << ": Serie A\n";
	so::out << ++count << ": League 1\n";
	so::out << ++count << ": Eledivisie\n";
	so::out << so::endl;

	std::cin >> select;

	switch (select) {
		case 0: {
			so::out << "Liga Espanola is selected!!\n";
			fileName = LigaData;
			break;
		}
		case 1: {
			so::out << "Premier League is selected!!\n";
			fileName = PremierData;
			break;
		}
		case 2: {
			so::out << "Serie A is selected!!\n";
			fileName = SerieAData;
			break;
		}
		case 3: {
			so::out << "League 1 is selected!!\n";
			fileName = League1Data;
			break;
		}
		case 4: {
			so::out << "Eledivisie is selected!!\n";
			fileName = EledivisieData;
			break;
		}
		default: {
			so::out << "exit...\n";
			return 0;
		}
	}
	so::out << so::endl;

	so::out.fileName(fileName + "_" + so::out.fileName());
	srand((unsigned)time( NULL ));

	int testTimes = 5;

	std::vector<Team> teamList = readParamFile(fileName);

	SeasonResult result(teamList, 2);

	for (int i = 0; i < testTimes; ++i) {
		while (!result.isAllScheduleFinished()) {
			result.stepADay();
		}
		result.finishSeazon();
	}

	std::sort(teamList.begin(), teamList.end(), SortByAllSeasonPointsGreater());
	std::for_each(teamList.begin(), teamList.end(), Print());

	so::out << result << so::endl;

	std::cerr << "\n\n" << std::endl;
	std::cerr << "Reported to " << so::out.fileName() << " !!!\n\n" << std::endl;
}





#include <stdio.h>
#include "BallSelection.h"


int main() {
	int i = 0;
	BallSearchCondition searchCondition;

	searchCondition.location_ = BALL_LOCATION_NORMAL;
	getBallDataListByCondition(&searchCondition);

	for (i = 0; i < searchCondition.validSize_; ++i) {
		printf("%s\n", getBallDataByID(searchCondition.ballList_[i])->name_);
	}
}


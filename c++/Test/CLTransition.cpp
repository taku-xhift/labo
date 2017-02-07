


#include <iostream>


struct OneMatch {
	OneMatch() : isFinished_(false) {}

	bool isFinished_;
};


struct DayResult {
	DayResult() : isFinished_(false) {}

	bool isAllGameFinished() const throw() {
		for (int i = 0; i < this->results_.size(); ++i) {
			if (results_.at(i).isFinished_ == false) {
				return false;
			}
		}
		return true;
	}

	std::vector<OneMatch> results_;
};


struct Tournament {
	Tournament() {}
	Tournament(bool isHomeAway) {
		if (isHomeAway) {
			this->results_.resize(2);
		} else {
			this->results_.resize(1);
		}
	}

	bool isAllGameFinished() const throw() {
		for (int i = 0; i < this->results_.size(); ++i) {
			if (results_.at(i).isFinished_ == false) {
				return false;
			}
		}
		return true;
	}

	std::vector<DayResult> results_;
};


struct CLGroupStage {
	bool isAllGameFinished() const throw() {
		for (int i = 0; i < 6; ++i) {
			if (this->results_[i].isFinished_ == false) {
				return false;
			}
		}
		return true;
	}

	bool getFinished(int day) throw() {
		return this->results_[day].results_[0].isFinished_;
	}

	void setFinish(int day, bool value) throw() {
		for (int i = 0; i < this->results_[day].results_.size(); ++i) {
			this->results_[day].results_[i].isFinished_ = true;
		}
	}

	DayResult results_[6];
};


struct CL {
	Tournament playOff_;
	CLGroupStage group_[8];
	Tournament final_[4];

	CL() {
		this->playOff_  = Tournament(true);
		this->final_[0] = Tournament(true);
		this->final_[1] = Tournament(true);
		this->final_[2] = Tournament(true);
		this->final_[3] = Tournament(false);
	}

	bool isAllGroupStageFinished() const throw() {
		for (int i = 0; i < 6; ++i) {
			if (this->group_[i].isFinished_ == false) {
				return false;
			}
		}
		return true;
	}

	void stepADay() {
		if (!this->playOff.isAllGameFinished()) {
			if (this->playOff_.results_[0].isFinished_) {
				this->playOff_.results_[1].isFinished_ = true;
			} else {
				this->playOff_.results_[0].isFinished_ = true;
			}
		} else if (!this->isAllGroupStageFinished()) {
			int day = 0;
			for (; day < 6; ++i) {
				if (!this->group_[0].getFinished(day)) {
					break;
				}
			}

			for (int i = 0; i < 8; ++i) {
				this->group_[i].setFinish(day, true);
			}
		} else if (!this->final_[0].isAllGameFinished()) {
			if (this->playOff_.results_[0].isFinished_) {
				this->playOff_.results_[1].isFinished_ = true;
			} else {
				this->playOff_.results_[0].isFinished_ = true;
			}
		} else if (!this->final_[1].isAllGameFinished()) {
			if (this->playOff_.results_[0].isFinished_) {
				this->playOff_.results_[1].isFinished_ = true;
			} else {
				this->playOff_.results_[0].isFinished_ = true;
			}
		} else if (!this->final_[2].isAllGameFinished()) {
			if (this->playOff_.results_[0].isFinished_) {
				this->playOff_.results_[1].isFinished_ = true;
			} else {
				this->playOff_.results_[0].isFinished_ = true;
			}
		} else {
			this->playOff_.results_[0].isFinished_ = true;
		}

		this->readyToNext();
	}

	void readyToNext() {
		
	}
};


int main() {
	
}






#include <iostream>
#include <vector>


struct Matrix
{
	//! \param  rows 行
	//! \param  cols 列
	Matrix(int rows, int cols) {
		for (int i = 0; i < rows; ++i) {
			this->para_.push_back(std::vector<double> (cols));
		}
	}


	void Print() const {
		for (auto rows : this->para_) {
			for (auto elem : rows) {
				std::cout << elem << ", ";
			}

			std::cout << "\n";
		}
	}

	Matrix Transpose() const {
		Matrix ret(this->para_.at(0).size(), this->para_.size());

		for (int i = 0; i < ret.para_.size(); ++i) {
			for (int j = 0; j < ret.para_.at(0).size(); ++j) {
				ret.para_.at(i).at(j) = this->para_.at(j).at(i);
			}
		}

		return ret;
	}

	std::vector<std::vector<double>> para_;
};





int main() {
	Matrix mat(2, 4);

	for (int i = 0; i < mat.para_.size(); ++i) {
		for (int j = 0; j < mat.para_.at(i).size(); ++j) {
			mat.para_.at(i).at(j) = i * mat.para_.at(i).size() + j;
		}
	}

	mat.Print();

	std::cout << "\n";

	Matrix transeposed = mat.Transpose();

	transeposed.Print();
}



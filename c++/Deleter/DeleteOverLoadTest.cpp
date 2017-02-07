/**
 * @file
 * @brief Delete を define しつつ smart_ptr でも管理できる様に
 *          ファンクタ deleter を作ってみた
 *          けど、smart_ptr では勝手に管理されることに気づいたので
 *          全く意味が無いことに気付いた
 *
 * @author Takuya Shishido
 * @date 2009.11.25 11:13:07
 *
 * @version 0.01, Shishido Takuya, 2009.11.25 11:13:07
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/


#include <iostream>
#include <vector>


/**
 * @brief allocate データ保存クラス
 *          
 * @author  Takuya Shishido
 * @date    2009.11.25 11:14:30
 * @version 0.01, Shishido Takuya, 2009.11.25 11:14:30
 */
class Data
{
public:

	unsigned int line;
	const char* file;

	Data(unsigned int line_, const char* file_)
		: line(line_)
		, fine(file_)
	{ }
};
std::vector<Data> allocData;

/**
 * @brief 上記条件を満たすためのファンクタ
 *          
 * @author  Takuya Shishido
 * @date    2009.11.25 11:14:30
 * @version 0.01, Shishido Takuya, 2009.11.25 11:14:30
 */
class Deleter
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	Deleter();


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~Deleter();



	/**----------------------------------------------------
	 * @brief operator test
	 * @note    smart_ptr でも使えるように
	 *---------------------------------------------------*/
	void operator() (void* address, unsigned int line_, const char* file_) {
		Data
	}

private:


};    // class Deleter



int main()
{


	return 0;
}



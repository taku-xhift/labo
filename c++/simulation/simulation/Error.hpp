/**
 * @file
 * @brief 例外処理を管理するためのエラーモジュール
 *
 * @author Takuya Shishido
 * @date   2009.11.01 17:06:45
 *
 * @version 0.01, Shishido Takuya, 2009.11.01 17:06:45
 *      (c) 2009 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef ERROR_ERROR_HPP_INCLUDED
#define ERROR_ERROR_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------

namespace Error {

/**
 * @brief 指定されたオブジェクトが見つからなかった場合に使用
 * @author  Takuya Shishido
 * @date    2009.11.01 17:06:45
 * @version 0.01, Shishido Takuya, 2009.11.01 17:06:45
 */
class FindError
{
public:

	/**----------------------------------------------------
	 * @brief constructor
	 *---------------------------------------------------*/
	FindError() {}


	/**----------------------------------------------------
	 * @brief destructor
	 *---------------------------------------------------*/
	~FindError() {}

private:


};    // class FindError
}    // namespace Error

#endif


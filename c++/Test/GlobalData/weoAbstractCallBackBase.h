
#ifndef ABSTRACTCALLBACKBASE_HPP_INCLUDED
#define ABSTRACTCALLBACKBASE_HPP_INCLUDED

//-------------------------------------------------------------------
//  include
//-------------------------------------------------------------------



/****************************************************************
 * @brief コールバック処理のためのオブジェクト
 * @note    GlobalData に登録するためにはこれを継承するか、
 *              同等の関数を実装する必要がある
 * @tparam  取得したいデータの型
 ***************************************************************/
template<typename ValueType>
class AbstractCallBackBase
{
public:

	/****************************************************************
	 * @brief サーバからデータを受け取ったら呼び出されるコールバック
	 * @note    使う人は受け取ったデータに対する処理を記述する
	 * @param[in]   value   受け取ったデータ
	 ***************************************************************/
	virtual void callBackFunction(const ValueType& value) throw() = 0;

protected:

	/****************************************************************
	 * @brief destructor
	 * @note    非 virtual
	 ***************************************************************/
	~AbstractCallBackBase() throw() {}

};    // class AbstractCallBackBase




#endif


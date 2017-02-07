/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.04.04 15:08:30
 *
 * @version 0.01, Shishido Takuya, 2011.04.04 15:08:30
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#include "pm_mode.cnf"
#if (PM_MODE_ALLMENU_OFF != 1)

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include "weoGlobalData.h"
#include "weDebug.h"



#define PUSH_RELEASE(ptr, some)


GlobalData* GlobalData::this_ = NULL;
GlobalData::Mutex GlobalData::mutex_;


/********************************************************************
 * @brief str から trimmer を取り除く
 * @param[in, out]  str         取り除かれる文字列
 * @param[in]       trimmer     取り除く文字列
 *******************************************************************/
void strTrimming(std::string& str, const std::string& trimmer) throw() {
	std::string::size_type pos = 0;
	while(pos = str.find(trimmer, pos), pos != std::string::npos) {
		str.erase(pos, trimmer.length());
	}
}



/********************************************************************
 * @brief getInstance 可能かどうか
 * @retval      true    可能。
 * @retval      false   不可能。create がされていない
 *******************************************************************/
bool GlobalData::hasData() throw() { return (this_ != NULL); }


/********************************************************************
 * @brief オブジェクト取得
 * @note    const 参照の返却。
 *            データをセットしたい場合は素直に set を呼ぶこと
 * @return      クラスオブジェクト
 * @except      UnReadyLoadData     メモリが NULL だった
 *******************************************************************/
const GlobalData& GlobalData::getInstance() throw(pm_mode::task::UnReadyLoadData) {
	if (this_ == NULL) {
		throw pm_mode::task::UnReadyLoadData("Error in getting instance!!!");
	}
	return *this_;
}


/********************************************************************
 * @brief メモリ確保
 *******************************************************************/
void GlobalData::create() throw(pm_mode::task::MemoryAllocateException) {
	try {
		if (this_ == NULL) {
			UpLock uplock(mutex_);
			WriteLock writeLock(uplock);

			if (this_ == NULL) {
				this_ = NEW GlobalData();

				// 解放関数の登録
				PUSH_RELEASE(GlobalData::destroy, NULL);
			}
		}
	} catch (std::bad_alloc&) {
		throw pm_mode::task::MemoryAllocateException(ExceptionMessage("Memory allocation error!!!"));
	}
}


/********************************************************************
 * @brief メモリ解放
 *******************************************************************/
void GlobalData::destroy() throw() {
	SAFE_DELETE(this_);
}


/********************************************************************
 * @brief constructor
 *******************************************************************/
GlobalData::GlobalData() throw()
{
}


/********************************************************************
 * @brief destructor
 *******************************************************************/
GlobalData::~GlobalData() throw()
{
#if (!MASTER)
#endif // (!MASTER)
}


#endif    // #if (PM_MODE_ALLMENU_OFF != 1)

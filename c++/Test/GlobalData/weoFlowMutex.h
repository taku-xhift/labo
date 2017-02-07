/**
 * @file
 * @brief 
 *
 * @author Takuya Shishido
 * @date   2011.04.07 17:19:00
 *
 * @version 0.01, Shishido Takuya, 2011.04.07 17:19:00
 *      (c) 2011 Konami Digital Entertainment Co., Ltd. All Rights Reserved.
*/

#ifndef PM_MODE_MUTEX_HPP_INCLUDED
#define PM_MODE_MUTEX_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------
#include <windows.h>


namespace pm_mode {


/********************************************************************
 * @brief Mutex をロックするためのオブジェクト
 * @note    スコープに存在している間ロックさせる
 *******************************************************************/
template<typename Mutex>
class ScopedLocker {
public:

	/****************************************************************
	 * @brief constructor
	 * @note    mutex をロックする
	 * @param[in]   mutex   Mutex オブジェクト
	 ***************************************************************/
	ScopedLocker(const Mutex& mutex) throw()
		: mutex_(mutex)
	{
		this->mutex_.lock();
	}

	/****************************************************************
	 * @brief destructor
	 * @note    mutex をアンロックする
	 ***************************************************************/
	~ScopedLocker() throw() {
		this->mutex_.unlock();
	}


private:

	ScopedLocker& operator=(const ScopedLocker&);

	const Mutex& mutex_;    //!< もらったオブジェクトを保存しておく

};



/********************************************************************
 * @brief WindowsAPI(?) を使ってロックする
 * @note    何か使いやすい Mutex が手に入ればそっちを使ったらいい
 *******************************************************************/
class WindowsMutex {
public:

	WindowsMutex() throw() : mutex_(NULL) {
		this->mutex_ = CreateMutex(NULL,FALSE,NULL);	//ミューテックス生成
	}

	~WindowsMutex() throw() {
		CloseHandle(this->mutex_);
	}

	void lock() const throw() {
		WaitForSingleObject(this->mutex_, INFINITE);   // mutex 間は他のスレッドから変数を変更できない
	}

	void unlock() const throw() {
		ReleaseMutex(this->mutex_);
	}

	const HANDLE get() const throw() { return this->mutex_; }

private:

	volatile HANDLE mutex_;     //!< ハンドル。valatile は必要なのだろうか？
};

}    // namespace pm_mode


#endif


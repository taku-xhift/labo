
#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED


//---------------------------------------------------------
//  include
//---------------------------------------------------------
#include <string>
#include <map>
#include <ctime>
#include "NonCopyable.hpp"



//! \brief ���ԑ���N���X
//! \note   �I�u�W�F�N�g����������Ă���j�������܂ł̎��Ԃ𑪒�
//! \note   static �֐� �ƃ����o�֐����g��������悤�ɂ���
class Timer
	: private NonCopyable
{
public:

	typedef std::map<std::string, float> TimerList;     //!< �ʖ��ۑ�


	//! \brief constructor
	//! \param[in]  tag     ���肷�鎞�Ԃ̃^�O�B�ߋ��ɍ�������Ƃ��Ȃ��^�O�ł������B
	explicit Timer(const std::string& tag) throw()
		: tag_(tag)
	{
		this->start_ = std::clock();
	}


	//! \brief destructor
	//! \note   �j������鎞�ɑ���I�����A�ۑ�
	~Timer() {
		std::map<std::string, float>::iterator ite = timerList_.find(this->tag_);
		// tag �����݂��Ă��Ȃ���Ώ��������Ă���
		if (ite == timerList_.end()) {
			timerList_[this->tag_] = .0f;
		}
		timerList_[this->tag_] += static_cast<float>(std::clock() - this->start_)/CLOCKS_PER_SEC;
	}


	//! \brief �I�u�W�F�N�g����������Ă���̎��Ԏ擾
	float elapsed() const throw()           { return static_cast<float>(std::clock() - this->start_); }


	//! \brief �ߋ��ɑ��肵�����̂̍��v���擾����
	//! \param[in]  tag     ����ɗ��p�����^�O
	//! \except     UnFoundError    tag ��������Ȃ������ꍇ
	static float elapsed(const std::string& tag) throw(UnFoundError) {
		TimerList::iterator ite = timerList_.find(tag);
		if (ite != timerList_.end()) {
			return ite->second;
		} else {
			throw UnFoundError();
		}
	}


	//! \brief �I�u�W�F�N�g�̃^�C�}�[�����Z�b�g����
	void restart() throw() { this->start_ = std::clock(); }


	//! \brief �ߋ��ɑ��肵���^�C�}�[�����Z�b�g����
	//! \param[in]  tag     ���Z�b�g����^�O
	//! \except     UnFoundError    tag ��������Ȃ�����
	static void restart(std::string tag) throw(UnFoundError) {
		TimerList::iterator ite = timerList_.find(tag);
		if (ite != timerList_.end()) {
			ite->second = .0f;
		} else {
			throw UnFoundError();
		}
	}


private:

	std::clock_t    start_;         //!< �I�u�W�F�N�g���������ꂽ����
	std::string     tag_;           //!< ��������������^�O

	static TimerList timerList_;    //!< tag �ŊǗ����ꂽ���Ԃ̃��X�g�B
};

Timer::TimerList Timer::timerList_;



//-------------------------------------------------------------------------------------------------
//          �g�p��
//-------------------------------------------------------------------------------------------------
//
//
//#include <iostream>
//#include <vector>
//
//int main()
//{
//	std::vector<int> container;
//
//	{
//		Timer timer("insert");
//		for (int i = 0; i < 100000; ++i) {
//			container.push_back(i);
//		}
//	}
//	{
//		Timer timer("print");
//		for (std::vector<int>::iterator ite = container.begin(); ite != container.end(); ++ite) {
//			std::cout << *ite << "\n";
//		}
//		std::cout << std::endl;
//	}
//
//	std::cout << "insert = " << Timer::elapsed("insert") << std::endl;
//	std::cout << "print = " << Timer::elapsed("print") << std::endl;
//}
//
//-------------------------------------------------------------------------------------------------


#endif

// See http://www.boost.org/libs/any for Documentation.

#include <iostream>
#include <algorithm>
#include <limits>
#include <assert.h>


namespace pm {
namespace pc {
namespace Task {

class Any;


//! brief キャスト失敗を示すための例外クラス
class bad_any_cast;



//! brief 任意型データを保存するクラス
class Any
{
	static const unsigned int defaultID = UINT_MAX;//std::numeric_limits<unsigned int>::max();
public:

	//! \brief constructor
	Any() : content(NULL) {}

	//! \brief constructor
	//! \param[in]  value_  任意型のデータ
	template<typename ValueType>
	Any(const ValueType& value_)
		: content(new Holder<ValueType>(value_))
	{
	}

	//! \brief constructor
	//! \param[in]  value_  任意型のデータ
	Any(const Any& other_)
		: content(other_.content ? other_.content->clone() : NULL)
	{
	}

	//! \brief destructor
	~Any() {
		delete content;
	}

public:

	//! \brief もらった Any と自分のデータ入れ替え
	//! \param[in]  rhs_    入れ替え先
	Any& swap(Any& rhs_) {
		std::swap(this->content, rhs_.content);
		return *this;
	}

	//! \brief operator = (データ本体と = でつなぐ)
	//! \param[in]  rhs_    入れ替え先
	template<typename ValueType>
	Any& operator=(const ValueType& rhs_) {
		Any(rhs_).swap(*this);
		return *this;
	}

	//! \brief operator = (Any 型のデータとの =)
	//! \param[in]  rhs_    Any 型のデータ
	Any& operator=(Any rhs_) {
		rhs_.swap(*this);
		return *this;
	}

public:

	//! \brief データの有無のチェック
	//! \retval     true    有り
	//! \retval     false   無し
	bool empty() const { return !this->content; }

	//! \brief 持っているデータの typeID を返す
	//! \return     型毎にユニークな ID。なければ default の ID (Any 型内で定義)
	unsigned int dataTypeID() const             { return content ? content->dataTypeID() : defaultID; }

	//! \brief 内部にデータがセットされていない場合のデフォルトの ID を取得
	unsigned int defaultDataTypeID() const      { return Any::defaultID; }

	//! \breif cast して内部データを取得する(例外を使えない人はこれで)
	//! \return    キャスト済みのデータ。キャスト出来なければ NULL(安全ではない)
	template<typename ValueType>
	const ValueType& getAs() const throw(bad_any_cast) {
		if (this->content->dataTypeID() != ValueType::typeID) {
			assert(0);
			throw bad_any_cast();
		}
		return static_cast<Holder<ValueType>*>(this->content)->held;
	}

	//! \brief cast 済みのデータを取得する(渡したデータ型に自動で変換)
	//! \param[out] out_    データ出力先
	//! \retval     true    キャスト可能だった
	//! \retval     false   キャスト不可能だった
	template<typename ValueType>
	bool store(ValueType& out_) {
		if (this->content.dataTypeID() != ValueType::typeID) {
			return false;
		}
		out_ = static_cast<Holder<ValueType>*>(this->content)->held;
		return true;
	}


private:

	//! brief データホルダーのインターフェース型
	class PlaceHolder
	{
	public:

		//! \brief destructor
		virtual ~PlaceHolder() {}

		//! \brief 持っているデータの typeID を返す
		//! \return     型毎にユニークな ID。なければ default の ID (Any 型内で定義)
		virtual unsigned int dataTypeID() const = 0;

		//! \brief データのクローンを返す
		virtual PlaceHolder* clone() const = 0;
	};

	//! \brief データホルダーの実装
	template<typename ValueType>
	class Holder
		: public PlaceHolder
	{
	public:

		//! \brief copy constructor
		Holder(const ValueType& value_)
			: held(value_)
		{
		}

		//! \brief データの ID 取得
		//! \return     型 ID
		virtual unsigned int dataTypeID() const {
			return held.dataTypeID();
		}

		//! \brief データ本体のコピー
		//! \return     new した値
		virtual PlaceHolder* clone() const {
			return new Holder(held);
		}

	public:

		ValueType held;     //!< データ本体

	private:
		//! \brief operator = の禁止
		Holder& operator=(const Holder &);
	};

private:

	//! \brief cast 関数に対するデータの公開
	template<typename ValueType>
	friend ValueType* any_cast(Any*);

	PlaceHolder* content;   //!< 任意型を保存するためのデータホルダー
};

//! brief キャスト失敗を示すための例外クラス
class bad_any_cast : public std::bad_cast {
public:
	//! \brief 例外情報を取得する
	//! return 例外情報
	virtual const char* what() const throw() {
		return "boost::bad_any_cast: "
		       "failed conversion using boost::any_cast";
	}
};

//! \brief Any 型からキャストするためのメソッド。ポインタ・non-const 用。
//! \param[in]  operand_    取り出したい Any 型のオブジェクト
//! \return     変換済みデータ。失敗すれば NULL 型データ
template<typename ValueType>
ValueType* any_cast(Any* operand_) {
	return operand_ && (operand_->dataTypeID() == ValueType::typeID)
	        ? &static_cast<Any::Holder<ValueType>*>(operand_->content)->held : NULL;
}

//! \brief Any 型からキャストするためのメソッド。ポインタ・const 用。
//! \param[in]  operand_    取り出したい Any 型のオブジェクト
//! \return     変換済みデータ。失敗すれば NULL 型データ
template<typename ValueType>
inline const ValueType* any_cast(const Any* operand_) {
	return any_cast<ValueType>(const_cast<Any*>(operand_));
}

//! \brief Any 型からキャストするためのメソッド。リファレンス・non-const 用。
//! \param[in]  operand_    取り出したい Any 型のオブジェクト
//! \return     変換済みデータ。失敗すれば NULL 型データ
template<typename ValueType>
ValueType any_cast(Any& operand_) {
	ValueType* result = any_cast<ValueType>(&operand_);
	if(!result) {
		throw;
	}
	return *result;
}

//! \brief Any 型からキャストするためのメソッド。リファレンス・const 用。
//! \param[in]  operand_    取り出したい Any 型のオブジェクト
//! \return     変換済みデータ。失敗すれば NULL 型データ
template<typename ValueType>
inline ValueType any_cast(const Any& operand_) {
	typedef remove_reference<ValueType>::type nonref;
	return any_cast<const nonref &>(const_cast<Any&>(operand_));
}


}   // Task
}   // pc
}   // pm

class Sample {
public:

	static const unsigned int typeID = 0;       //!< 型ID

	//!< brief 型 ID を返す
	unsigned int dataTypeID() const { return Sample::typeID; }

	//! \brief constructor
	//! \param[in]  integer     データ
	Sample(int integer_ = std::numeric_limits<int>::max()) : integer(integer_) {}

	int integer;
};

int main()
{
	pm::pc::Task::Any any = Sample(34);

	std::cout << pm::pc::Task::any_cast<Sample>(any).integer << std::endl;
	std::cout << any.getAs<Sample>().integer << std::endl;
}



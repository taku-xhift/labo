
/*
  * 衝突を使ってのタグディスパッチの実験
*/

#include <iostream>
#include <string>


struct sphere_object { public: float sphereRange; };
struct squere_object {};


class Object
{
public:

	virtual std::string getType() const = 0;

private:

	std::string type;
};


class SphereObject : public Object, public sphere_object
{
public:
	typedef sphere_object objectType;

	float getRange() { this->sphereRange = 3.0f; return this->sphereRange; }
	std::string getType() const { return "Sphere"; }

};



class SquereObject : public Object
{
public:
	typedef squere_object objectType;

	std::string getType() const { return "Squere"; }
};


class Pentagon : public Object
{
public:

	std::string getType() const { return "Pentagon"; }
};





// 呼び出しの中身作成
template <class Type1, class Type2>
void _hitCheck(const Type1& object1, sphere_object, const Type2& object2, sphere_object)
{
	std::cout << "Sphere vs Sphere が理想" << std::endl;
	std::cout << object1.getType() << " vs " << object2.getType() << "\n" << std::endl;
}
template <class Type1, class Type2>
void _hitCheck(const Type1& object1, sphere_object, const Type2& object2, squere_object)
{
	std::cout << "Sphere vs Squere が理想" << std::endl;
	std::cout << object1.getType() << " vs " << object2.getType() << "\n" << std::endl;
}
template <class Type1, class Type2>
void _hitCheck(const Type1& object1, squere_object, const Type2& object2, sphere_object)
{
	std::cout << "Squere vs Sphere が理想" << std::endl;
	std::cout << object1.getType() << " vs " << object2.getType() << "\n" << std::endl;
}
template <class Type1, class Type2>
void _hitCheck(const Type1& object1, squere_object, const Type2& object2, squere_object)
{
	std::cout << "Squere vs Squere が理想" << std::endl;
	std::cout << object1.getType() << " vs " << object2.getType() << "\n" << std::endl;
}



template <class Type1, class Type2>
void hitCheck(const Type1& object1, const Type2& object2)
{
	_hitCheck(object1, typename Type1::objectType(), object2, typename Type2::objectType());
}



int main()
{
	SphereObject so1, so2;
	SquereObject sq1, sq2;
	//Pentagon pg;

	hitCheck(so1, so2);
	hitCheck(so1, sq1);
	hitCheck(sq1, so2);
	hitCheck(sq1, sq2);
	//hitCheck(sq1, pg);

	std::cout << so1.getRange() << std::endl;

	return 0;
}





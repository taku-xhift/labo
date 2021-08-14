
#include <iostream>
#include <fstream>
#include <string>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/xml_iarchive.hpp>

class Person {
public:
	int         age;
	std::string name;

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& archive, unsigned int version)
	{
		static_cast<void>(version); // No use
		archive & boost::serialization::make_nvp("Age", age);
		archive & boost::serialization::make_nvp("Name", name);
	}
};

int main()
{
	std::ifstream ifs("D:/PersonalTool/xyzzy/laboratory/c++/Boost/Serialize/person.xml");
	boost::archive::xml_iarchive iarchive(ifs);

	// XML�Ǎ�
	Person person;
	iarchive >> boost::serialization::make_nvp("Root", person);

	// �ǂݍ��񂾓��e��\��
	std::cout << person.age << "," << person.name << std::endl;
}

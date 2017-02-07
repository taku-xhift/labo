

#include <fstream>
#include <string>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/xml_oarchive.hpp>

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
    std::ofstream ofs("D:/PersonalTool/xyzzy/laboratory/c++/Boost/Serialize/person.xml");
    boost::archive::xml_oarchive oarchive(ofs);

    Person person;
    person.age  = 22;
    person.name = "Akira";

    // ÉNÉâÉXèÓïÒÇXMLèoóÕ
    oarchive << boost::serialization::make_nvp("Root", person);

    return 0;
}

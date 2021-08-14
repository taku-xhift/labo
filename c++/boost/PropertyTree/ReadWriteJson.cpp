
#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
using namespace std;

int main()
{
	// JSON�ǂݍ���
	boost::property_tree::ptree t;
	read_json("D:/PersonalTool/xyzzy/laboratory/c++/boost/PropertyTree/Example.json", t);

	// Image.Width ��\��
	cout << t.get<int>("Image.Width") << endl;

	// Image.Thumbnail.Url ��\��
	cout << t.get<string>("Image.Thumbnail.Url") << endl;

	// Image.IDs �m�[�h���擾
	boost::property_tree::ptree& id = t.get_child("Image.IDs");
	BOOST_FOREACH(const boost::property_tree::ptree::value_type& e,id) // �q�������Ԃɕ\��
		cout << e.second.data() << endl;

	// �ҏW
	t.put("Image.Width", 1200);
	t.put("Image.Height", 960);
	t.add("Memo", "Modified!!");

	// cout �֏o��
	cout << "--------" << endl;
	write_json(cout, t);
}


#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
using namespace std;

int main()
{
	// JSON読み込み
	boost::property_tree::ptree t;
	read_json("D:/PersonalTool/xyzzy/laboratory/c++/boost/PropertyTree/Example.json", t);

	// Image.Width を表示
	cout << t.get<int>("Image.Width") << endl;

	// Image.Thumbnail.Url を表示
	cout << t.get<string>("Image.Thumbnail.Url") << endl;

	// Image.IDs ノードを取得
	boost::property_tree::ptree& id = t.get_child("Image.IDs");
	BOOST_FOREACH(const boost::property_tree::ptree::value_type& e,id) // 子供を順番に表示
		cout << e.second.data() << endl;

	// 編集
	t.put("Image.Width", 1200);
	t.put("Image.Height", 960);
	t.add("Memo", "Modified!!");

	// cout へ出力
	cout << "--------" << endl;
	write_json(cout, t);
}

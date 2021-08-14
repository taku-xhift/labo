



#include <iostream>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>



class Test {
public:

	Test() throw()
		: integer_(40)
	{
		
	}

	void save(boost::property_tree::ptree& tree, std::string parentNode = "") const throw() {
		tree.put(parentNode + "Test.integer_", this->integer_);
	}
	void load(const boost::property_tree::ptree& tree, std::string parentNode = "") throw() {
		this->integer_ = tree.get<int>(parentNode + "Test.integer_");
	}

	int integer_;
};


class Composite {
public:

	Composite() throw() : integer_(2929) {
		this->testList_.resize(3);
	}


	void save(boost::property_tree::ptree& tree, std::string parentNode = "") const throw() {
		boost::property_tree::ptree subTree;
		BOOST_FOREACH(const Test& test, this->testList_) {
			boost::property_tree::ptree info;
			test.save(info, "");
			subTree.push_back(std::make_pair("", info));
		}
		tree.add_child("Composite.testList_", subTree);
		tree.put(parentNode + "Composite.integer_", this->integer_);
	}
	void load(const boost::property_tree::ptree& tree, std::string parentNode = "") throw() {
		this->integer_ = tree.get<int>(parentNode + "Composite.integer_");
		int count = 0;
		BOOST_FOREACH(const boost::property_tree::ptree::value_type& child, tree.get_child("Composite.testList_")) {
			const boost::property_tree::ptree& info = child.second;
			this->testList_.at(count).load(info);
			++count;
		}
	}

	std::vector<Test> testList_;
	int integer_;
};


int main() {
	Composite composite;
	//composite.test_.integer_ = 1000;
	composite.integer_ = 10;
	int count = 0;
	BOOST_FOREACH(Test& test, composite.testList_) {
		test.integer_ = count * 100;
		++count;
	}

	boost::property_tree::ptree tree;
	composite.save(tree);

	write_json("D:/PersonalTool/xyzzy/laboratory/c++/boost/PropertyTree/data_out.json", tree);

	Composite composite2;
	composite2.load(tree);

	std::cout << composite2.integer_ << std::endl;
	//std::cout << composite2.test_.integer_ << std::endl;
	BOOST_FOREACH(const Test& test, composite2.testList_) {
		std::cout << test.integer_ << std::endl;
	}
}


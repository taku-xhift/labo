


#include <iostream>
#include <fstream>
#include "PicoJson.hpp"

struct Thumbnail {
	std::string url_;
	int height_;
	int width_;
};

struct Image {
	int width_;
	int height_;
	Thumbnail thumbnail_;
	std::vector<int> IDs_;
};


int main() {
	using namespace picojson;

	std::string file;

	// 単なるファイルリード
	{
//		std::ifstream ifs;
//		ifs.open("example.json", std::ios::in);
//		std::string temp;
//		while (ifs.eof() == false) {
//			ifs >> temp;
//			file += temp;
//		}
//		ifs.close();
	}


	// Read
	{
		value v1;
		std::string error = parse(v1, std::ifstream("example.json", std::ios::in));
		//std::string error = parse(v1, file.begin(), file.end());

		object obj = v1.get<object>();
		for (object::const_iterator ite = obj.begin(); ite != obj.end(); ++ite) {
			std::cout << ite->first << " = " << ite->second.to_str() << std::endl;
			object obj2 = ite->second.get<object>();
			for (object::const_iterator ite2 = obj2.begin(); ite2 != obj2.end(); ++ite2) {
				if (ite2->second.is<array>()) {
					array obj3 = ite2->second.get<array>();
					std::cout << "\t" << ite2->first << " = " << ite2->second.to_str() << std::endl;
					for (array::const_iterator ite3 = obj3.begin(); ite3 != obj3.end(); ++ite3) {
						std::cout << "\t\t" << ite2->first << " = " << *ite3 << std::endl;
					}
				} else if (ite2->second.is<object>()) {
					object obj3 = ite2->second.get<object>();
					std::cout << "\t" << ite2->first << " = " << ite2->second.to_str() << std::endl;
					for (object::const_iterator ite3 = obj3.begin(); ite3 != obj3.end(); ++ite3) {
						std::cout << "\t\t" << ite3->first << " = " << ite3->second << std::endl;
					}
				} else {
					std::cout << "\t" << ite2->first << " = " << ite2->second.to_str() << std::endl;
				}
			}
		}
	}


	// Write
	{
		Thumbnail nail;
		nail.url_ = "http://google.com/";
		nail.height_ = 30;
		nail.width_ = 4000;

		Image image;
		image.width_ = 6;
		image.height_ = 50;
		image.thumbnail_ = nail;
		for (int i = 0; i < 10; ++i) {
			image.IDs_.push_back(i);
		}

		object imageO;
		object thumbO;
		value temp;
		thumbO.insert(std::make_pair<std::string, value>("width", temp.reset(nail.width_)));
		thumbO.insert(std::make_pair<std::string, value>("height", temp.reset(nail.height_)));
		thumbO.insert(std::make_pair<std::string, value>("url", temp.reset(nail.url_)));

		imageO.insert(std::make_pair<std::string, value>("width", temp.reset(image.width_)));
		imageO.insert(std::make_pair<std::string, value>("height", temp.reset(image.height_)));
		array IDs;
		for (std::vector<int>::const_iterator ite = image.IDs_.begin(); ite != image.IDs_.end(); ++ite) {
			IDs.push_back(temp.reset(*ite));
		}
		imageO.insert(std::make_pair<std::string, value>("IDs", temp.reset(IDs)));
		imageO.insert(std::make_pair<std::string, value>("Thumbnail", temp.reset(thumbO)));

		value v1(imageO);


		std::string serialize = v1.serialize();

		// ファイル出力
		{
			std::ofstream ofs("output.txt");
			ofs << serialize << std::endl;
			ofs.close();
		}
	}
}



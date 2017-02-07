

#include <iostream>

class to_be_deleted
{
public:
	~to_be_deleted() {
		std::cout << "ここで重要なコトをどうしても表示させたいのです。" << std::endl;
	}
};


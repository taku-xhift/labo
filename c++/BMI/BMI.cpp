

#include <iostream>
#include <string>


enum Result
{
	low = 0,
	normal,
	obese,
};


std::string Out(Result result)
{
	switch (result) {
		case low:
			return "Low!";
		case normal:
			return "Normal!";
		case obese:
			return "obese! Too Heavy!!!";
	}
}


double culcBMIIndex(double heightCM, double weightKG)
{
	return (weightKG * 10000)/(heightCM * heightCM);
}


Result culcBMI(double heightCM, double weightKG)
{
	double index = culcBMIIndex(heightCM, weightKG);
	
	if (index < 18.5) {
		return low;
	} else if (18.5 <= index || index < 25) {
		return normal;
	} else {
		return obese;
	}
}


double culcRolelIndex(double heightCM, double weightKG)
{
	double tryHeight = heightCM * heightCM * heightCM;
	return (weightKG / tryHeight) * 10000000;
}

Result culcRolel(double heightCM, double weightKG)
{
	double index = culcRolelIndex(heightCM, weightKG);

	if (index < 116) {
		return low;
	} else if (116 <= index || index < 144) {
		return normal;
	} else {
		return obese;
	}
}


int main()
{
	double height = 177.7;
	double weight = 75.0f;

	std::cout << "BMIIndex => " << culcBMIIndex(height, weight) << std::endl;
	std::cout << "BMI => " << Out(culcBMI(height, weight)) << std::endl;

	std::cout << "RolelIndex => " << culcRolelIndex(height, weight) << std::endl;
	std::cout << "Rolel => " << Out(culcRolel(height, weight)) << std::endl;	

	return 0;
}





#include <iostream>
#include <algorithm>
#include <functional>
#include <regex>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_io.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
//#include <boost/regex.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/detail/bind_functions.hpp>

#include <Personal/StreamObject.hpp>

#if defined (_DEBUG)
#pragma comment(lib, "libpngd.lib")
#pragma comment(lib, "zlibd.lib")
#else
#pragma comment(lib, "libpng.lib")
#pragma comment(lib, "zlib.lib")
#endif

using namespace std;
using namespace boost::gil;


// boost::gil �� pixel �\���̂����܂��g���Ȃ��c
class Color {
public:
	float red;
	float green;
	float blue;
	float alpha;
	std::string name;

	static const int colorBitMax = 0xff;

	Color(float red_ = .0f, float green_ = .0f, float blue_ = .0f, float alpha_ = .0f, std::string name_ = "")
		: red(red_/colorBitMax), green(green_), blue(blue_/colorBitMax), alpha(alpha_/colorBitMax), name(name_) {}

	bool operator==(const char* name_) {
		return this->name.compare(name_) == 0;
	}
};


namespace {
	Color brown = Color(115.0f, 12.0f, 33.0f, .0f, "brown");
	Color darkRed = Color(207.0f, .0f, 52.0f, .0f, "darkRed");
	Color red = Color(238.0f, 15.0f, 36.0f, .0f, "red");
	Color darkOrange = Color(255.0f, 76.0f, 1.0f, .0f, "darkOrange");
	Color orange = Color(248.0f, 76.0f, 1.0f, .0f, "orange");
	Color darkYellow = Color(245.0f, 207.0f, .0f, .0f, "darkYellow");
	Color yellow = Color(255.0f, 238.0f, 11.0f, .0f, "yellow");
	Color greenYellow = Color(230.0f, 255.0f, .0f, .0f, "greenYellow");
	Color yellowGreen = Color(189.0f, 248.0f, 104.0f, .0f, "yellowGreen");
	Color lightGreen = Color(.0f, 200.0f, 75.0f, .0f, "lightGreen");
	Color green = Color(60.0f, 172.0f, .0f, .0f, "green");
	Color darkGreen = Color(12.0f, 86.0f, 40.0f, .0f, "darkGreen");
	Color darkBlue = Color(38.0f, 46.0f, 128.0f, .0f, "darkBlue");
	Color blue = Color(12.0f, 60.0f, 170.0f, .0f, "blue");
	Color lightBlue = Color(.0f, 100.0f, 255.0f, .0f, "lightBlue");
	Color lightNavy = Color(50.0f, 100.0f, 186.0f, .0f, "lightNavy");
	Color navy = Color(.0f, 50.0f, 128.0f, .0f, "navy");
	Color turquoise = Color(.0f, 156.0f, 190.0f, .0f, "turquoise");
	Color lightSkyBlue = Color(156.0f, 224.0f, 255.0f, .0f, "lightSkyBlue");
	Color skyBlue = Color(52.0f, 180.0f, 248.0f, .0f, "skyBlue");
	Color steelBlue = Color(104.0f, 128.0f, 248.0f, .0f, "steelBlue");
	Color purple = Color(100.0f, 50.0f, 186.0f, .0f, "purple");
	Color darkMagenta = Color(130.0f, 24.0f, 136.0f, .0f, "darkMagenta");
	Color magenta = Color(230.0f, 50.0f, 148.0f, .0f, "magenta");
	Color pink = Color(252.0f, 174.0f, 188.0f, .0f, "pink");
	Color lightBrown = Color(128.0f, .0f, 2.0f, .0f, "lightBrown");
	Color cream = Color(245.0f, 245.0f, 220.0f, .0f, "cream");
	Color white = Color(255.0f, 255.0f, 255.0f, .0f, "white");
	Color gray = Color(192.0f, 192.0f, 192.0f, .0f, "gray");
	Color darkGray = Color(128.0f, 128.0f, 128.0f, .0f, "darkGray");
	Color lightBlack = Color(50.0f, 50.0f, 50.0f, .0f, "lightBlack");
	Color black = Color(.0f, .0f, .0f, .0f, "black");


	Color cl[] = {brown, darkRed, red, darkOrange, orange, darkYellow, yellow,      // 7
	    greenYellow, yellowGreen, lightGreen, green, darkGreen, darkBlue, blue,     // 14
	    lightBlue, lightNavy, navy, turquoise, lightSkyBlue, skyBlue, steelBlue,    // 21
	    purple, darkMagenta, magenta, pink, lightBrown, cream, white,               // 28
	    gray, darkGray, lightBlack, black};                                         // 32
	std::vector<Color> colorList(&cl[0], &cl[sizeof(cl)/sizeof(Color)]);
}

// �F�̔����o��
::boost::gil::rgba8_pixel_t g(::boost::gil::rgba8_pixel_t p) {
	return ::boost::gil::rgba8_pixel_t(p.at(::boost::mpl::int_<0>()), p.at(::boost::mpl::int_<1>()), p.at(::boost::mpl::int_<2>()), 0xff);
}

// color �̓��e�̏o��
class Output {
public:
	void operator()(rgba8_pixel_t pixel) {
		int red = pixel.at(::boost::mpl::int_<0>());
		int green = pixel.at(::boost::mpl::int_<1>());
		int blue = pixel.at(::boost::mpl::int_<2>());
		int alpha = pixel.at(::boost::mpl::int_<3>());
		if (alpha != 0) {
		so::out << "count = " << count << "\r\n";
		so::out  << "red = " << red << "\r\n";
		so::out  << "green = " << green << "\r\n";
		so::out  << "blue = " << blue << "\r\n";
		so::out  << "alpha = " << alpha << "\r\n";
		so::out << so::endl;
		}
		++count;
	}

	Output() : count(0) {}
	~Output() {}

private:
	int count;
};

// Pixel �ɑ΂��� for_each ��
template<typename View, typename Function>
Function forEachPixels(const View& src_, Function function_) {
	for (std::ptrdiff_t y = 0; y < src_.height(); ++y) {
		typename View::x_iterator srcIt=src_.row_begin(y);
		for (std::ptrdiff_t x = 0; x < src_.width(); ++x) {
			function_(srcIt[x]);
		}
	}
	return function_;
}

// �O���[�X�P�[����K�p����
class ComvertToColored// : public std::binary_function
{
public:
	typedef rgba8_pixel_t result_type;

	result_type operator()(const rgba8_pixel_t& grayScale_, const Color& color_) {
		float ratio = grayScale_.at(::boost::mpl::int_<3>())/0xff;
		return rgba8_pixel_t(grayScale_.at(::boost::mpl::int_<0>()) * color_.red, grayScale_.at(::boost::mpl::int_<1>()) * color_.green, grayScale_.at(::boost::mpl::int_<2>()) * color_.blue, grayScale_.at(::boost::mpl::int_<3>()));
	}
};

// ��������
class Combiner {
public:
	/**----------------------------------------------------
	 * @brief operator function call
	 *---------------------------------------------------*/
	::boost::gil::rgba8_pixel_t operator()(::boost::gil::rgba8_pixel_t lowPriority_, ::boost::gil::rgba8_pixel_t highPriority_) {
		auto alpha = highPriority_.at(::boost::mpl::int_<3>());
		if (alpha == 0) {
			return lowPriority_;
		} else {
			return highPriority_;
		}
	}
};

// �g�p�ł���F���ǂ������`�F�b�N
bool canUseColor(const char* color_) {
	return std::find_if(colorList.begin(), colorList.end(), ::boost::lambda::_1 == color_) != colorList.end();
}


// 1. �v���O������
// 2. base ��
// 3. �J���[�x�[�X�P
// 4. �J���[�P
// 5. �J���[�x�[�X�Q
// 6. �J���[�Q
// �̏��œ����Ă���
int main(int argc, char* argv[])
{
	if (argc != 0) {
		if (argc < 6) {
			so::out << "�����̐������Ȃ��ł��B\r\nbase���A�J���[�x�[�X�P�A�J���[�A�J���[�x�[�X�Q�A�J���[�̏��Ŏw�肵�Ă�������" << so::endl;
			assert(0);
		} else if (argc > 6) {
			so::out << "�����̐������Ȃ��ł��B\r\n�����������̂Ɋւ��Ă͖�������܂�" << so::endl;
			assert(0);
		}

		//::boost::regex pngExtension("(\.*.png)");
		//if (!(::boost::regex_match(argv[1], pngExtension))
		std::regex pngExtension("(\.*.png)");
		if (!(std::regex_match(argv[1], pngExtension))
			|| !(std::regex_match(argv[2], pngExtension))
			|| !(std::regex_match(argv[4], pngExtension)))
		{
			so::out << "�t�@�C���� png �ɂȂ��Ă��܂���" << so::endl;
			assert(0);
		}

		//if (!(canUseColor(argv[4]) && canUseColor(argv[6]))) {
		if (!(canUseColor(argv[3]) && canUseColor(argv[5]))) {
			so::out << "���̐F�͎w��ł��܂���" << so::endl;
			assert(0);
		}
	}

	// png�t�@�C���ǂݍ���
	::boost::gil::rgba8_image_t src1;
	::boost::gil::png_read_image("embTest_4040_base_r.png", src1);
	::boost::gil::rgba8_image_t src2;
	::boost::gil::png_read_image("embTest_4040_color1_r.png", src2);
	::boost::gil::rgba8_image_t src3;
	::boost::gil::png_read_image("embTest_4040_color2_r.png", src3);

	// ���F
	std::vector<Color>::iterator firstColor = std::find_if(colorList.begin(), colorList.end(), ::boost::lambda::_1 == argv[3]);
	std::vector<Color>::iterator secondColor = std::find_if(colorList.begin(), colorList.end(), ::boost::lambda::_1 == argv[5]);

	::boost::gil::rgba8_image_t coloredSrc2( 64, 64 );
	::boost::gil::transform_pixels(view(src2), view(coloredSrc2), boost::bind(ComvertToColored(), _1, *firstColor));
	::boost::gil::png_write_view("colored1.png", view(coloredSrc2));
	::boost::gil::rgba8_image_t coloredSrc3( 64, 64 );
	::boost::gil::transform_pixels(view(src3), view(coloredSrc3), boost::bind(ComvertToColored(), _1, *secondColor));
	::boost::gil::png_write_view("colored2.png", view(coloredSrc3));

	// ����
	::boost::gil::rgba8_image_t dst1( 64, 64 );
	::boost::gil::transform_pixels(view(src1), view(coloredSrc2), view(dst1), Combiner());
	::boost::gil::rgba8_image_t dst2( 64, 64 );
	::boost::gil::transform_pixels(view(dst1), view(coloredSrc3), view(dst2), Combiner());

	// �f�[�^�o��
	//forEachPixels(view(coloredSrc3), Output());

	// png�t�@�C����������
	::boost::gil::png_write_view("result.png", view(dst2));

	return 0;
}

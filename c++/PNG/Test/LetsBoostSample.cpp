#include <iostream>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_io.hpp>
using namespace std;
using namespace boost::gil;

#if defined (_DEBUG)
#pragma comment(lib, "libpngd.lib")
#pragma comment(lib, "zlibd.lib")
#else
#pragma comment(lib, "libpng.lib")
#pragma comment(lib, "zlib.lib")
#endif

// RGB の G 成分だけ残してみる
rgb8_pixel_t g(rgb8_pixel_t p)
{
	return rgb8_pixel_t( 0, at_c<1>(p), 0 );
}

int main()
{
	// pngファイル読み込み
	rgb8_image_t src;
	png_read_image("embTest_4040_base_r.png", src);

	// (100,100)-(300,300)を取り出して g で変換
	rgb8_image_t dst( 200, 200 );
	transform_pixels( subimage_view(view(src),100,100,200,200), view(dst), &g );

	// pngファイル書き込み
	png_write_view("result.png", view(dst) );
}

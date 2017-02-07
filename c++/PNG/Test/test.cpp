#include <utility>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_io.hpp>

int main() {
	//namespace gil = boost::gil;

	boost::gil::point2<ptrdiff_t> dim(400, 400);
	boost::gil::gray8_image_t img(dim);
	//boost::gil::any_image<boost::gil::gray8_image_t>::view_t view = boost::gil::view(img);
	auto view = boost::gil::view(img);
	//boost::gil::image<boost::gil::gray8_image_t> view = boost::gil::view(img);

	for (ptrdiff_t i = 0; i < dim.y; ++i) {
		for (ptrdiff_t j = 0; j < dim.x; ++j) {
			view(i, j) = 255 * (std::min(i, j) / static_cast<double>(dim.x));
		}
	}

	boost::gil::png_write_view("img.png", view);

    return 0;
}

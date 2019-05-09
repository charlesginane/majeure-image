#include <iostream>

#include "convert-img.hh"
#include "image.hh"
#include "image_io.hh"
#include "histogram.hh"


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "No image specified" << std::endl;
        std::cerr << "usage: ./tp1 <path_image>" << std::endl;
        return 2;
    }

    auto img = tifo::load_image(argv[1]);
    auto gray_img = convert_gray(img);
    auto histo = tifo::get_histo(&gray_img);

    tifo::save_image(*(tifo::convert_rgb(gray_img)), "sncf.TGA");


    auto equal_img = tifo::equal(gray_img, histo);

    tifo::save_image(equal_img, "sncf.TGA");


    /* int count = 0;
    int i = 0;
    for (auto num: histo.histogram) {
        std::cout << num << std::endl;
        count += num;
        ++i;
    }

    std::cerr << histo.histogram[0] << std::endl;*/

    auto histo_color = get_histo_color(img, false);

    for (auto num: histo_color.histogram) {
        std::cout << num << std::endl;
    }


    return 0;
}

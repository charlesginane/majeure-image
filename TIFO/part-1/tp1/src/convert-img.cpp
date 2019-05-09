#include "convert-img.hh"

namespace tifo {

    gray8_image convert_gray(rgb24_image* img) {
        auto gray_img = gray8_image(img->sx, img->sy);

        for (int i = 0; i < img->length / 3; i++)
        {
            gray_img.pixels[i] = (img->pixels[i * 3 + 2]+ img->pixels[i * 3 + 1] + img->pixels[i * 3]) / 3;
        }
        return gray_img;
    }

    rgb24_image* convert_rgb(gray8_image& img) {
        auto img_color = new rgb24_image(img.sx, img.sy);

        for (auto i = 0; i < img.sx * img.sy; i++) {
            img_color->pixels[i * 3] = img.pixels[i];
            img_color->pixels[i * 3 + 1] = img.pixels[i];
            img_color->pixels[i * 3 + 2] = img.pixels[i];
        }
        return img_color;
    }

    rgb24_image equal(gray8_image& img, histogram_1d hist) {
        auto gray_img = rgb24_image(img.sx, img.sy);

        /* Init of cumulated histogram */
        histogram_1d ch;
        for (auto i = 0; i < 256; ++i) {
            ch.histogram[i] = 0;
        }

        /* Fill cumulated histogram */
        auto nb_pix = 0;
        for (auto i = 0; i < 256; ++i) {
            nb_pix += hist.histogram[i];
            ch.histogram[i] = hist.histogram[i] + nb_pix;
        }

        /* Calculate new image */
        for (auto i = 0; i < img.length; i++)
        {
            float hist_sum = ((static_cast<float>(ch.histogram[img.pixels[i]])) / nb_pix);

            auto number = (255) * hist_sum;

            gray_img.pixels[i * 3 + 1] = number;
            gray_img.pixels[i * 3 + 2] = number;
            gray_img.pixels[i * 3] = number;
         }
         
         return gray_img;
    }
}

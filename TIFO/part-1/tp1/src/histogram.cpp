//************************************************
//*                                              *
//*   TP 1&2    (c) 2017 J. FABRIZIO             *
//*                                              *
//*                               LRDE EPITA     *
//*                                              *
//************************************************

#include <iostream>

#include "histogram.hh"

const float epsilon = 0.01f;

namespace tifo {

    /**
     ** This function init the histogram
     */
    histogram_1d init_histo(histogram_1d hist) {
        for (int i = 0; i < 256; ++i)
            hist.histogram[i] = 0;
        return hist;
    }

    /**
     ** Get histogram of a gray image
     */
    histogram_1d get_histo(const gray8_image* img) {
        /* Init */
        histogram_1d histo;
        for (auto i = 0; i < 256; ++i)
            histo.histogram[i] = 0;

        /* Fill */
        for (auto i = 0; i < img->sx * img->sy; ++i)
            histo.histogram[img->pixels[i]]++;

        return histo;
    }

    /**
     ** Get equal histogram
     */
    histogram_1d equal_histo(histogram_1d old_hist, int size, uint8_t* color) {
        /* Init of cumulated histogram */
        histogram_1d ch, hist;

        for (auto i = 0; i < 256; ++i) {
            ch.histogram[i] = 0;
            hist.histogram[i] = 0;
        }

        /* Fill cumulated histogram */
        auto nb_pix = 0;
        for (auto i = 0; i < 256; ++i) {
            nb_pix += old_hist.histogram[i];
            ch.histogram[i] = old_hist.histogram[i] + nb_pix;
        }

        /* Calculate new image */
        for (auto i = 0; i < size; i++)
        {
            float hist_sum = ((static_cast<float>(ch.histogram[color[i]])) / nb_pix);

            uint8_t number = (uint8_t)(255) * hist_sum;

            hist.histogram[number]++;
         }

         return hist;

    }


    /**
     ** Get color histogram in RGB
     */
    histogram_1d get_histo_color(const rgb24_image* img, bool hsv) {
        /* Decomposition of img */
        uint8_t* r = new uint8_t[img->length / 3];
        uint8_t* g = new uint8_t[img->length / 3];
        uint8_t* b = new uint8_t[img->length / 3];

        histogram_1d histo, red, green, blue;
        histogram_1d hh, hs, hv;

        histo = init_histo(histo);
        red = init_histo(red);
        green = init_histo(green);
        blue = init_histo(blue);
        hh = init_histo(hh);
        hs = init_histo(hs);
        hv = init_histo(hv);

        /* Init */
        for (auto i = 0; i < img->length / 3; ++i) {
            r[i] = 0;
            g[i] = 0;
            b[i] = 0;
        }

        for (auto i = 0; i < img->sx * img->sy ; ++i) {
            red.histogram[img->pixels[i * 3]]++;
            r[i] = img->pixels[i * 3];
            green.histogram[img->pixels[i * 3 + 1]]++;
            g[i] = img->pixels[i * 3 + 1];
            blue.histogram[img->pixels[i * 3 + 2]]++;
            b[i] = img->pixels[i * 3 + 2];
        }

        if (hsv) {
            float* h = new float[img->length / 3];
            float* s = new float[img->length / 3];
            float* v = new float[img->length / 3];


            for (auto i = 0; i < img->sx * img->sy; ++i) {
                auto hsv = convert_rgb_to_hsv(r[i], g[i], b[i]);
                h[i] = hsv.h;
                s[i] = hsv.s;
                v[i] = hsv.v;
            }
        }

        else {
            red = equal_histo(red, img->sx * img->sy / 3, r);
            green = equal_histo(green, img->sx * img->sy / 3, g);
            blue = equal_histo(blue, img->sx * img->sy / 3, b);
        }

        for (auto i = 0; i < 256; ++i) {
            histo.histogram[i] = red.histogram[i] + blue.histogram[i] + green.histogram[i];
        }

        delete(r);
        delete(g);
        delete(b);
        return histo;
    }

    /**
     ** Convert RGB to HSV
     */
    HSV convert_rgb_to_hsv(uint8_t red, uint8_t green, uint8_t blue) {
        HSV color;

        float r = red / 255;
        float g = green / 255;
        float b = blue / 255;

        float max = r;
        float min = r;

        if (g > max)
            max = g;
        else if (g < min)
            min = g;

        if (b > max)
            max = b;
        else if (b < min)
            min = b;

        if (fabs(max - min) < epsilon)
            color.h = 0;
        else if (fabs(max - r) < epsilon)
            color.h = 60 * ((g - b) / (max - min));
        else if (fabs(max - g) < epsilon)
            color.h = 60 * (2 + (b - r) / (max - min));
        else
            color.h = 60 * (4 + (r - g) / (max - min));

        color.s = 0;
        if (max != 0)
            color.s = (max - min) / max;

        color.v = max;

        return color;
    }

}

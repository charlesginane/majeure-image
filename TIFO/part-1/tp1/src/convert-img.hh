#ifndef CONVERT_IMG_HH
# define CONVERT_IMG_HH

# include "image.hh"
# include "histogram.hh"

# include <iostream>

namespace tifo {
    gray8_image convert_gray(rgb24_image* img);

    rgb24_image* convert_rgb(gray8_image& img);

    rgb24_image equal(gray8_image& img, histogram_1d hist);
}

#endif

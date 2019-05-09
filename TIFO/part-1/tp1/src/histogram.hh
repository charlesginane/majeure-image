//************************************************
//*                                              *
//*   TP 1&2    (c) 2017 J. FABRIZIO             *
//*                                              *
//*                               LRDE EPITA     *
//*                                              *
//************************************************

#ifndef HISTOGRAM_HH
#define	HISTOGRAM_HH

#include "image.hh"

#include <cmath>

namespace tifo {

  typedef struct { unsigned int histogram[IMAGE_NB_LEVELS]; } histogram_1d;

  typedef struct {
      float h;
      float s;
      float v;
  } HSV;



  histogram_1d get_histo(const gray8_image* img);

  histogram_1d equal_histo(histogram_1d old_hist, int size, uint8_t* color);

  histogram_1d get_histo_color(const rgb24_image* img, bool hsv);

  HSV convert_rgb_to_hsv(uint8_t red, uint8_t green, uint8_t blue);



}

#endif

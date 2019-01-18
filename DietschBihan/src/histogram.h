#ifndef HISTOGRAM_H__  
#define HISTOGRAM_H__

#include "image.h"

void createHistogramGrey(Image *image, int width, int height, char *imageName);
void createHistogramRGB(Image *image, int width, int height, char *imageName);

#endif
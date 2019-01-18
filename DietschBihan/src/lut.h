#ifndef LUT_H__
#define LUT_H__

#include "image.h"

typedef struct LUT{
	unsigned char lutR[256];
	unsigned char lutG[256];
	unsigned char lutB[256];
}LUT;

int initiateLUT(LUT *lut);
int lutToImage(Image *image, LUT *lut);
int addlumToLUT(LUT *lut, int percentage);
int dimlumToLUT(LUT *lut, int percentage);
int contrast(LUT *lut, int percentage, int add);
int sepia(Image *image);
int invert(LUT *lut);
int fullmirror(Image *image);
int blackWhite(Image *image);
int onlyred(Image *image, LUT *lut);
int redBlue(Image *image, LUT *lut);

int applyGradient(int *color1, int *color2, LUT *lut);
int bicolorFilter(Image *image, LUT *lut);
int shuffle(int *array, int number);

int vMirror(Image *image);

#endif
#ifndef LUT_H__
#define LUT_H__

#include "image.h"

typedef struct LUT{
	unsigned char lutR[256];
	unsigned char lutG[256];
	unsigned char lutB[256];
}LUT;

int initiateLUT(int pixelNumber, unsigned char *data, unsigned char *lut);
int lutToImage(int pixelNumber, unsigned char *lut, unsigned char *data);
int addlumToLUT(int nbPixels, unsigned char *lut, int percentage);
int contrast(int pixelNumber, unsigned char *lut, int percentage, int add);
int dimlumToLUT(int pixelNumber, unsigned char *lut, int percentage);
int dimContrast(int pixelNumber, unsigned char *lut, int percentage);
int sepia(int pixelNumber, unsigned char *lut, int param);
int mirror(int pixelNumber, unsigned char *lut);


int initiateLUT2(LUT *lut);
int lutToImage2(int pixelNumber, LUT *lut, unsigned char *data);
int addlumToLUT2(LUT *lut, int percentage);
int dimlumToLUT2(LUT *lut, int percentage);
int contrast2(LUT *lut, int percentage, int add);
int sepia2(Image *image);
int invert(LUT *lut);
int fullmirror2(Image *image);
int blackWhite(Image *image);
int onlyred(Image *image, LUT *lut);


#endif
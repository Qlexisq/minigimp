#ifndef LUT_H__
#define LUT_H__


int initiateLUT(int pixelNumber, unsigned char *data, unsigned char *lut);
int lutToImage(int pixelNumber, unsigned char *lut, unsigned char *data);
int addlumToLUT(int nbPixels, unsigned char *lut, int percentage);

#endif
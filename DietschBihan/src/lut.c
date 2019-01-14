#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lut.h"

//FOnction qui créé le LUT que l'on va utiliser 
int initiateLUT(int pixelNumber, unsigned char *data, unsigned char *lut){
	for(int i=0;i<pixelNumber*3;i++){
		lut[i] = data[i];
	}
	return 0;
}

int lutToImage(int pixelNumber, unsigned char *lut, unsigned char *data){
	for(int i=0;i<pixelNumber*3;i++){
		data[i] = lut[i];
	}
	return 0;
}

int addlumToLUT(int pixelNumber, unsigned char *lut, int percentage){
	for(int i=0;i<pixelNumber*3;i++){
		if(lut[i]+percentage*3 >= 255){
			lut[i] = 255;
		} else{
			lut[i] = lut[i]+percentage*3;
		}
	}
	return 0;
}
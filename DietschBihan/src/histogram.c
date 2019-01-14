#include <stdio.h>
#include <stdlib.h>
#include "histogram.h"
#include "image.h"
#define HISTOGRAM_SIZE 256

void createHistogramImage(int width, int height){
	Image imageHistogram;
	newImage(&imageHistogram, width, height);

	// création d'une image blanche
	for(int i=1;i<=(imageHistogram.width*imageHistogram.height)*3;i++){
		imageHistogram.data[i]=255;
	}
	
	saveImagePPM(&imageHistogram, "./images/histogram.ppm");

	freeImage(&imageHistogram);
}

void calculateHistogram(Image image){
	int histogram[HISTOGRAM_SIZE];

	//initialisation de l'histogramme à 0 pour toutes les cases
	for(int i=0;i<=255;i++){
		histogram[i]=0;
		printf("%d\n", histogram[i]);
	}

	//incrémentation de l'histogramme pour chaque valeur de nuance de gris
	for(int i=0;i<(image.width*image.height)*3;i=i+3){
		int greyValue=(image.data[i]+image.data[i+1]+image.data[i+2])/3;
		histogram[greyValue]++;
	}
}
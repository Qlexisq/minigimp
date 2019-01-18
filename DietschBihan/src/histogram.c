#include <stdio.h>
#include <stdlib.h>
#include "histogram.h"
#include "image.h"
#define HISTOGRAM_SIZE 256

void createHistogramGrey(Image image, int width, int height){
	int histogramGrey[HISTOGRAM_SIZE];
	int indexMaxHisto=0; // indice de la valeur maximale de l'histogramme

	// initialisation de l'histogramme à 0 pour toutes les cases
	for(int i=0;i<=255;i++){
		histogramGrey[i]=0;
	}

	// incrémentation de l'histogramme pour chaque valeur de nuance de gris
	for(int i=0;i<(image.width*image.height)*3;i=i+3){
		int greyValue=(image.data[i]+image.data[i+1]+image.data[i+2])/3;
		histogramGrey[greyValue] += 1;

		if(histogramGrey[greyValue]>histogramGrey[indexMaxHisto]){
			indexMaxHisto = greyValue; // mise à jour de l'indice de la valeur max
		}
	}
		printf("index max = %d\n", indexMaxHisto);

	// création de l'image de l'histogramme
	Image imageHistogram;
	float scalingCoefHeight = ((float)height)/histogramGrey[indexMaxHisto];  // mise à l'échelle en fonction de height
	float scalingCoefWidth = 255/((float)width-1);
	newImage(&imageHistogram, width, height);
	for(int x=0;x<width;x++){
		int xScale = x*scalingCoefWidth;
		for(int y=0;y<height;y++){
			if(height-y>=histogramGrey[xScale]*scalingCoefHeight){		
				imageHistogram.data[y*width*3+3*x]=0;
				imageHistogram.data[y*width*3+3*x+1]=0;
				imageHistogram.data[y*width*3+3*x+2]=0;
			}
			else{
				imageHistogram.data[y*width*3+3*x]=255;
				imageHistogram.data[y*width*3+3*x+1]=255;
				imageHistogram.data[y*width*3+3*x+2]=255;
			}
		}
	}
	
	saveImagePPM(&imageHistogram, "./images/histogram-grey.ppm");
	freeImage(&imageHistogram);
}

void createHistogramRGB(Image image, int width, int height){

	// création de tableaux de données d'histogramme pour les nuances de gris, de rouge, de vert et de bleu
	int histogramRed[HISTOGRAM_SIZE];
	int histogramGreen[HISTOGRAM_SIZE];
	int histogramBlue[HISTOGRAM_SIZE];

	// Valeur maximale de l'histogramme (nous sert à dimensionner la hauteur l'histogramme)
	int maxValue=0;

	// initialisation des données de chaque histogramme à 0
	for(int i=0;i<=255;i++){
		histogramRed[i]=0;
		histogramGreen[i]=0;
		histogramBlue[i]=0;
	}

	// incrémentation des données de chaque histogramme
	for(int i=0;i<(image.width*image.height)*3;i=i+3){
		int redValue=image.data[i];
		int greenValue=image.data[i+1];
		int blueValue=image.data[i+2];

		histogramRed[redValue] += 1;
		histogramGreen[greenValue] += 1;
		histogramBlue[blueValue] += 1;

		// mise à jour de l'indice de la valeur max
		// les conditions colorValue>5 et colorValue<250 permettent de supprimer le haut des éventuelss
		// grand pics proches de 0 et 255 et ainsi eviter que le reste de l'histogramme soit écrasé
		if(histogramRed[redValue]>maxValue && redValue>5 && redValue<250 ){
			maxValue = histogramRed[redValue]; 
		}
		if(histogramGreen[greenValue]>maxValue && greenValue>5 && greenValue<250 ){
			maxValue = histogramGreen[greenValue]; 
		}
		if(histogramBlue[blueValue]>maxValue && blueValue>5 && blueValue<250 ){
			maxValue = histogramBlue[blueValue]; 
		}
	}
		printf("index max = %d\n", maxValue);

	// création de l'image de l'histogramme
	Image imageHistogram;
	newImage(&imageHistogram, width, height);
	// mise à l'échelle en fonction de height et width choisies par l'utilisateur
	float scalingCoefHeight = ((float)height)/maxValue;
	float scalingCoefWidth = 255/((float)width-1);
	
	for(int x=0;x<width;x++){
		int xScale = x*scalingCoefWidth;
		for(int y=0;y<height;y++){
			// dessin des pixels de l'histogramme rouge
			if(height-y>=histogramRed[xScale]*scalingCoefHeight){		
				imageHistogram.data[y*width*3+3*x]=0;
			}
			else{
				imageHistogram.data[y*width*3+3*x]=255;
			}
			// dessin des pixels de l'histogramme vert
			if(height-y>=histogramGreen[xScale]*scalingCoefHeight){		
				imageHistogram.data[y*width*3+3*x+1]=0;
			}
			else{
				imageHistogram.data[y*width*3+3*x+1]=255;
			}
			// dessin des pixels de l'histogramme bleu
			if(height-y>=histogramBlue[xScale]*scalingCoefHeight){		
				imageHistogram.data[y*width*3+3*x+2]=0;
			}
			else{
				imageHistogram.data[y*width*3+3*x+2]=255;
			}
		}
	}

	saveImagePPM(&imageHistogram, "./images/histogram-rgb.ppm");
	freeImage(&imageHistogram);
}
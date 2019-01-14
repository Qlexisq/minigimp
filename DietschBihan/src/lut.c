#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lut.h"
#include <math.h>

//FOnction qui créé le LUT que l'on va utiliser 
int initiateLUT(int pixelNumber, unsigned char *data, unsigned char *lut){
	for(int i=0;i<pixelNumber*3;i++){
		lut[i] = data[i];
	}
	return 0;
}

//FOnction qui transmet les données du LUT dans data de l'image
int lutToImage(int pixelNumber, unsigned char *lut, unsigned char *data){
	for(int i=0;i<pixelNumber*3;i++){
		data[i] = lut[i];
	}
	return 0;
}

//Fonction pour ajouter de la luminosité
int addlumToLUT(int pixelNumber, unsigned char *lut, int percentage){
	for(int i=0;i<pixelNumber*3;i++){
			//si on passe au dessus de 255, on met à 255 pour éviter de revenir à 0
		if(lut[i]+percentage*3 >= 255){
			lut[i] = 255;
		} else{
			//percentage*3 = le pourcentage mais sur 255
			lut[i] = lut[i]+percentage*3;
		}
	}
	return 0;
}

//Fonction pour enlever de la luminosité
int dimlumToLUT(int pixelNumber, unsigned char *lut, int percentage){
	for(int i=0;i<pixelNumber*3;i++){
		//si on passe en dessous de 0 on met à 0 pour éviter de revenir à 255
		if(lut[i]-percentage*3 <= 0){
			lut[i] = 0;
		} else{
			//percentage*3 = le pourcentage mais sur 255
			lut[i] = lut[i]-percentage*3;
		}
	}
	return 0;
}

//FOnction pour ajouter du contraste
int addContrast(int pixelNumber, unsigned char *lut, int percentage){
	double x = (double)(259*(percentage+255))/(255*(259-percentage));
	int value = 0;
	for(int i=0;i<pixelNumber*3;i++){
		value = round(x*(lut[i]-128)+128);
		if(value >= 255){
			lut[i] = 255;
		} else if(value <= 0){
			lut[i] = 0;
		} else{
			lut[i] = value;
		}
	}
	return 0;
}
//Fonction pour enlever du contraste
int dimContrast(int pixelNumber, unsigned char *lut, int percentage){
	percentage = -1*percentage;
	double x = (double)(259*(percentage+255))/(255*(259-percentage));
	int value = 0;
	for(int i=0;i<pixelNumber*3;i++){
		value = round(x*(lut[i]-128)+128);
		if(value >= 255){
			lut[i] = 255;
		} else if(value <= 0){
			lut[i] = 0;
		} else{
			lut[i] = value;
		}
	}
	return 0;
}

/*
outputRed = (inputRed * .393) + (inputGreen *.769) + (inputBlue * .189)

outputGreen = (inputRed * .349) + (inputGreen *.686) + (inputBlue * .168)

outputBlue = (inputRed * .272) + (inputGreen *.534) + (inputBlue * .131)
*/

int sepia(int pixelNumber, unsigned char *lut, int param){
	double valueR=0, valueG=0, valueB=0;
	switch(param){
		case 1:;
			
			for(int i=0;i<pixelNumber*3;i++){
				//red
				if(i%3 == 0){

					valueR = lut[i]*0.393 + lut[i+1]*0.769 + lut[i+2]*0.189;
					valueG = lut[i]*0.349 + lut[i+1]*0.686 + lut[i+2]*0.168;
					valueB = lut[i]*0.272 + lut[i+1]*0.534 + lut[i+2]*0.131;

					lut[i] = (valueR>=255)? 255 : round(valueR);
					lut[i+1] = (valueG>=255)? 255 : round(valueG);
					lut[i+2] = (valueB>=255)? 255 : round(valueB);
				}  
			}
			break;
		case 2:;
			
			for(int i=0;i<pixelNumber*3;i++){
				//red
				if(i%3 == 0){

					valueR = lut[i+1]*0.393 + lut[i+2]*0.769 + lut[i]*0.189;
					valueG = lut[i+1]*0.349 + lut[i+2]*0.686 + lut[i]*0.168;
					valueB = lut[i+1]*0.272 + lut[i+2]*0.534 + lut[i]*0.131;

					lut[i] = (valueR>=255)? 255 : round(valueR);
					lut[i+1] = (valueG>=255)? 255 : round(valueG);
					lut[i+2] = (valueB>=255)? 255 : round(valueB);
				}  
			}
			break;
		//sepia wtf
		case 3:;
			for(int i=0;i<pixelNumber*3;i++){
				//red
				if(i%3 == 0){

					valueR = lut[i]*0.187 + lut[i+1]*0.532 + lut[i+2]*0.301;
					valueG = lut[i]*0.349 + lut[i+1]*0.686 + lut[i+2]*0.168;
					valueB = lut[i]*0.723 + lut[i+1]*0.123 + lut[i+2]*0.531;

					lut[i] = (valueR>=255)? 255 : round(valueR);
					lut[i+1] = (valueG>=255)? 255 : round(valueG);
					lut[i+2] = (valueB>=255)? 255 : round(valueB);
				}  
			}
			break;
	}
	
	return 0;
}

int mirror(int pixelNumber, unsigned char *lut){
	unsigned char *tempLUT = malloc(sizeof(unsigned char)*3*pixelNumber);
	for(int i=0;i<pixelNumber*3;i++){
		tempLUT[i] = lut[i];
	}
	for(int j=0;j<pixelNumber*3;j++){
		lut[j] = tempLUT[pixelNumber*3-j-1];
	}
	return 0;

}

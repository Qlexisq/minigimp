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
int contrast(int pixelNumber, unsigned char *lut, int percentage, int add){
	if(!add){
		percentage = -1*percentage;
	}
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
	int valueR=0,valueG=0,valueB=0;
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
	return 0;
}

int mirror(int pixelNumber, unsigned char *lut){
	unsigned char *tempLUT = malloc(sizeof(unsigned char)*3*pixelNumber);
	for(int i=0;i<pixelNumber*3;i++){
		tempLUT[i] = lut[i];
		//printf("%d - %d\n",tempLUT[i],lut[i]);

	}
	int compteur=0;
	int arraySize = pixelNumber*3-1;
	for(int j=0;j<pixelNumber*3;j++){
		switch (compteur){
			//red
			case 0:;
				lut[j] = tempLUT[arraySize-j-2];
				compteur++;
				break;
			//green
			case 1:;
				lut[j] = tempLUT[arraySize-j];
				compteur++;
				break;
			//blue
			case 2:;
				lut[j] = tempLUT[arraySize-j+2];
				compteur = 0;
				break;
		}
	}
	return 0;

}









//FOnction qui créé le LUT que l'on va utiliser 
int initiateLUT2(LUT *lut){
	for(int i=0;i<256;i++){
		lut->lutR[i]=i;
		lut->lutG[i]=i;
		lut->lutB[i]=i;
	}
	return 0;
}

//FOnction qui transmet les données du LUT dans data de l'image
int lutToImage2(int pixelNumber, LUT *lut, unsigned char *data){
	for(int i=0;i<pixelNumber*3;i+=3){
		data[i] = lut->lutR[data[i]];
		data[i+1] = lut->lutG[data[i+1]];
		data[i+2] = lut->lutB[data[i+2]];
	}
	return 0;
}

//Fonction pour ajouter de la luminosité
int addlumToLUT2(LUT *lut, int percentage){
	for(int i=0;i<256;i++){
		//condition ternaire pour éviter que la valeur ne soit supérieure à 255
		lut->lutR[i] = (lut->lutR[i]+percentage*3 >= 255) ? 255 : lut->lutR[i]+percentage*3;
		lut->lutG[i] = (lut->lutG[i]+percentage*3 >= 255) ? 255 : lut->lutG[i]+percentage*3;
		lut->lutB[i] = (lut->lutB[i]+percentage*3 >= 255) ? 255 : lut->lutB[i]+percentage*3;
	}
	return 0;
}

int dimlumToLUT2(LUT *lut, int percentage){
	for(int i=0;i<256;i++){
		//condition ternaire pour éviter que la valeur ne soit négative
		lut->lutR[i] = (lut->lutR[i]-percentage*3 <= 0) ? 0 : lut->lutR[i]-percentage*3;
		lut->lutG[i] = (lut->lutG[i]-percentage*3 <= 0) ? 0 : lut->lutG[i]-percentage*3;
		lut->lutB[i] = (lut->lutB[i]-percentage*3 <= 0) ? 0 : lut->lutB[i]-percentage*3;
	}
	return 0;
}

//FOnction pour ajouter du contraste
int contrast2(LUT *lut, int percentage, int add){
	//si on augmente ou diminue le contraste
	if(!add){
		percentage = -1*percentage;
	}
	//facteur de modification
	double x = (double)(259*(percentage+255))/(255*(259-percentage));
	int valueR = 0, valueB=0, valueG=0;
	for(int i=0;i<256;i++){
		//calcul de la nouvelle valeur
		valueR = round(x*(lut->lutR[i]-128)+128);
		valueG = round(x*(lut->lutG[i]-128)+128);
		valueB = round(x*(lut->lutB[i]-128)+128);

		/*condition ternaire dans condition ternaire pas très lisible pour avoir tout en une fonction
		* si la valeur est valide, on la garde, sinon on regarde si elle est supérieure à 255
		* si c'est le cas on lui affecte 255 et sinon on lui affecte 0 car ça ne peut pas être
		* autre chose
		*/
		lut->lutR[i] = (valueR >= 0 && valueR <= 255) ? valueR : (valueR > 255 ) ? 255 : 0;
		lut->lutG[i] = (valueG >= 0 && valueG <= 255) ? valueG : (valueG > 255 ) ? 255 : 0;
		lut->lutB[i] = (valueB >= 0 && valueB <= 255) ? valueB : (valueB > 255 ) ? 255 : 0;

	}
	return 0;
}

/*
outputRed = (inputRed * .393) + (inputGreen *.769) + (inputBlue * .189)

outputGreen = (inputRed * .349) + (inputGreen *.686) + (inputBlue * .168)

outputBlue = (inputRed * .272) + (inputGreen *.534) + (inputBlue * .131)
*/

/*Faire un LUT pour du sepia n'a pas de sens car on a besoin des valeurs RGB de chaque pixel, il faut donc modifier directement
* l'image pour faire un sepia correct
*
*/

int sepia2(Image *image){
	int pixelNumber = image->width*image->height;
	unsigned char *data = image->data;
	int valueR=0,valueG=0,valueB=0;
	for(int i=0;i<pixelNumber*3;i+=3){		
		valueR = data[i]*0.393 + data[i+1]*0.769 + data[i+2]*0.189;
		valueG = data[i]*0.349 + data[i+1]*0.686 + data[i+2]*0.168;
		valueB = data[i]*0.272 + data[i+1]*0.534 + data[i+2]*0.131;

		data[i] = (valueR>=255)? 255 : round(valueR);
		data[i+1] = (valueG>=255)? 255 : round(valueG);
		data[i+2] = (valueB>=255)? 255 : round(valueB);
		
	}
	return 0;
}

int invert(LUT *lut){
	for(int i=0;i<256;i++){
		lut->lutR[i] = 255-lut->lutR[i];
		lut->lutG[i] = 255-lut->lutG[i];
		lut->lutB[i] = 255-lut->lutB[i];
	}
	return 0;
}

int fullmirror2(Image *image){
	int pixelNumber = image->width*image->height;
	unsigned char *data = image->data;
	unsigned char *tempData = malloc(sizeof(unsigned char)*3*pixelNumber);
	for(int i=0;i<pixelNumber*3;i++){
		tempData[i] = data[i];
		//printf("%d - %d\n",tempLUT[i],lut[i]);

	}
	int index=0;
	int arraySize = pixelNumber*3-1;
	for(int j=0;j<pixelNumber*3;j++){
		switch (index){
			//red
			case 0:;
				data[j] = tempData[arraySize-j-2];
				index++;
				break;
			//green
			case 1:;
				data[j] = tempData[arraySize-j];
				index++;
				break;
			//blue
			case 2:;
				data[j] = tempData[arraySize-j+2];
				index = 0;
				break;
		}
	}
	return 0;

}

int blackWhite(Image *image){
	int pixelNumber = image->width*image->height;
	unsigned char *data = image->data;
	int avg = 0;
	for(int i=0;i<pixelNumber*3;i+=3){		
		avg = (int)(data[i] + data[i+1] + data[i+2])/3;
		data[i] = 
		data[i+1] = (avg>=255)? 255 : round(avg);
		data[i+2] = (avg>=255)? 255 : round(avg);
	}
	return 0;
}

int onlyred(Image *image, LUT *lut){
	int pixelNumber = image->width*image->height;
	unsigned char *data = image->data;
	int avg = 0;
	for(int i=0;i<pixelNumber*3;i+=3){		
		avg = (int)(data[i] + data[i+1] + data[i+2])/3;
		data[i] = lut->lutR[data[i]];
		data[i+1] = (avg>=255)? 255 : round(avg);
		data[i+2] = (avg>=255)? 255 : round(avg);
	}
	return 0;
}


int vMirror(int pixelNumber, unsigned char *data){

	unsigned char *tempData = malloc(sizeof(unsigned char)*3*pixelNumber);

	for(int i=0;i<pixelNumber*3;i++){
		tempData[i] = data[i];
		//printf("%d - %d\n",tempLUT[i],lut[i]);

	}
	int index=0;
	int arraySize = pixelNumber*3-1;
	for(int j=0;j<pixelNumber*3;j++){
		switch (index){
			//red
			case 0:;
				data[j] = tempData[arraySize-j-2];
				index++;
				break;
			//green
			case 1:;
				data[j] = tempData[arraySize-j];
				index++;
				break;
			//blue
			case 2:;
				data[j] = tempData[arraySize-j+2];
				index = 0;
				break;
		}
	}
	return 0;

}
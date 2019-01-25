//Ce fichier contient les fonctions que nous avions créées au début qui n'implémentaient pas correctement le principe du LUT

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




//fonction qui applique un dégradé entre 2 couleurs à l'image
int applyGradient(int *color1, int *color2, Image *image){
	/*besoin d'un lut temporaire qu'on applique directement à l'image dans cette fonction car le traitement 
	* à effectuer n'est pas le même que celui effectué par lutToImage2
	*/
	LUT tempLUT;
	initiateLUT2(&tempLUT);
	int pixelNumber = image->width*image->height;
	unsigned char *data = image->data;
	int avg = 0;
	//calcul de l'écart entre la couleur de départ et la couleur d'arrivée
	int redGap = abs(color2[0] - color1[0]);
	int greenGap = abs(color2[1] - color1[1]);
	int blueGap = abs(color2[2] - color1[2]);
	/*création de tableaux contenant un 1 à une position aléatoire qui servira d'indicateur pour 
	* savoir quand faire changer la couleur dans la boucle et la faire évoluer petit à petit 
	* vers la couleur de fin
	*/
	int redArray[256];
	int greenArray[256];
	int blueArray[256];
	shuffle(redArray, redGap);
	shuffle(greenArray, greenGap);
	shuffle(blueArray, blueGap);

	//on commence par initialiser les valeurs de newRedgreenblue à celles de la première couleur
	int newRed=color1[0]; int newGreen=color1[1]; int newBlue=color1[2];
	//boucle de remplissage du lut temporaire
	for(int i=0; i<256; i++){
		//si un 1 se trouve dans le tableau à l'indice i alors la composante R G ou B va changer sinon on garde l'ancienne valeur
		if(redArray[i] == 1){
			//test pour savoir si on doit augmenter ou baisser la valeur
			if(color2[0] - color1[0] > 0){
				newRed = newRed+1;
				tempLUT.lutR[i]= newRed;
			} else{
				newRed = newRed-1;
				tempLUT.lutR[i]=newRed;
			}	
		} else{
			tempLUT.lutR[i]=newRed;
		}
		if(greenArray[i] == 1){
			if(color2[1] - color1[1] > 0){
				newGreen = newGreen+1;
				tempLUT.lutG[i]=newGreen;
			} else{
				newGreen = newGreen-1;
				tempLUT.lutG[i]=newGreen;
			}
		} else{
			tempLUT.lutG[i]=newGreen;
		}
		if(blueArray[i] == 1){
			if(color2[2] - color1[2] > 0){
				newBlue = newBlue+1;
				tempLUT.lutB[i]=newBlue;
			} else{
				newBlue = newBlue-1;
				tempLUT.lutB[i]=newBlue;
			}
		} else{
			tempLUT.lutB[i]=newBlue;
		}
		printf("%d %d %d\n", newRed, newGreen, newBlue);
	}
	/* une fois le lut crée, on passe l'image en niveau de gris et en fonction de la valeur du pixel
	*  on attribue une couleur du dégradé qui se situe au même indice dans le lut temporaire
	*/
	for(int i=0; i<pixelNumber*3; i+=3){
		avg = (int)(data[i] + data[i+1] + data[i+2])/3;
		//DATA[i] = AVG ???? pour passer en noir et blanc
		data[i] = tempLUT.lutR[avg];
		data[i+1] = tempLUT.lutG[avg];
		data[i+2] = tempLUT.lutB[avg];
	}
	return 0;
}

int redBlue(Image *image, LUT *lut){
	//contrast2(lut, 20, 1);
	//lutToImage2(image, lut);
	int pixelNumber = image->width*image->height;
	unsigned char *data = image->data;
	int avg = 0;
	for(int i=0;i<pixelNumber*3;i+=3){		
		avg = (int)(data[i] + data[i+1] + data[i+2])/3;
		if(avg>128){
			data[i+1] = 0;
			data[i+2] = 0;
		} else{
			data[i] = 0;
			data[i+1] = 0;
		}
	}
	return 0;
}
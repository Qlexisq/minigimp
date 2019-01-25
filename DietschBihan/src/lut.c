#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lut.h"
#include <math.h>

//Fonction qui initialise le LUT global qu'on va utiliser
int initiateLUT(LUT *lut){
	for(int i=0;i<256;i++){
		lut->lutR[i]=i;
		lut->lutG[i]=i;
		lut->lutB[i]=i;
	}
	return 0;
}

//Fonction qui associe une nouvelle valeur à chaque composante de couleur de chaque pixel de l'image en fonction du LUT
int lutToImage(Image *image, LUT *lut){
	int pixelNumber = image->width*image->height;
	unsigned char *data = image->data;
	for(int i=0;i<pixelNumber*3;i+=3){
		data[i] = lut->lutR[data[i]];
		data[i+1] = lut->lutG[data[i+1]];
		data[i+2] = lut->lutB[data[i+2]];
	}
	return 0;
}


//Fonction pour modifier le LUT et rajouter percentage luminosité
int addlumToLUT(LUT *lut, int percentage){
	for(int i=0;i<256;i++){
		//condition ternaire pour éviter que la valeur ne soit supérieure à 255
		//percentage*3 = règle de 3 pour transformer le pourcent en valeur /255
		lut->lutR[i] = (lut->lutR[i]+percentage*3 >= 255) ? 255 : lut->lutR[i]+percentage*3;
		lut->lutG[i] = (lut->lutG[i]+percentage*3 >= 255) ? 255 : lut->lutG[i]+percentage*3;
		lut->lutB[i] = (lut->lutB[i]+percentage*3 >= 255) ? 255 : lut->lutB[i]+percentage*3;
	}
	return 0;
}

//Presque le même fonctionnement que la fonction plus haut
int dimlumToLUT(LUT *lut, int percentage){
	for(int i=0;i<256;i++){
		//condition ternaire pour éviter que la valeur ne soit négative
		lut->lutR[i] = (lut->lutR[i]-percentage*3 <= 0) ? 0 : lut->lutR[i]-percentage*3;
		lut->lutG[i] = (lut->lutG[i]-percentage*3 <= 0) ? 0 : lut->lutG[i]-percentage*3;
		lut->lutB[i] = (lut->lutB[i]-percentage*3 <= 0) ? 0 : lut->lutB[i]-percentage*3;
	}
	return 0;
}

//Fonction pour ajouter du contraste
int contrast(LUT *lut, int percentage, int add){
	//si on augmente ou diminue le contraste
	if(!add){
		percentage = -1*percentage;
	}
	//facteur de modification
	double x = (double)(259*(percentage+255))/(255*(259-percentage));
	int valueR = 0, valueB=0, valueG=0;
	for(int i=0;i<256;i++){
		//calcul de la nouvelle valeur de la couleur
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


//fonction qui inverse les couleurs (pas besoin d'explications)
int invert(LUT *lut){
	for(int i=0;i<256;i++){
		lut->lutR[i] = 255-lut->lutR[i];
		lut->lutG[i] = 255-lut->lutG[i];
		lut->lutB[i] = 255-lut->lutB[i];
	}
	return 0;
}
//fonction pour passer l'image en nuance de gris
int blackWhite(Image *image){
	int pixelNumber = image->width*image->height;
	unsigned char *data = image->data;
	//avg est la moyenne des trois composantes de couleur, ce qui déterminera l'intensité du pixel en niveau de gris
	int avg = 0;
	for(int i=0;i<pixelNumber*3;i+=3){		
		avg = (int)(data[i] + data[i+1] + data[i+2])/3;
		//affectation à chaque composante de couleur de l'intensité du pixel en niveau de gris
		data[i] = (avg>=255)? 255 : round(avg);
		data[i+1] = (avg>=255)? 255 : round(avg);
		data[i+2] = (avg>=255)? 255 : round(avg);
	}
	return 0;
}

int sepiaLUT(LUT *lut, Image *image){
	blackWhite(image);
	int valueR=0,valueG=0,valueB=0;
	//boucler sur la composante rouge de chaque pixel de l'image
	for(int i=0;i<256;i++){
		valueR = lut->lutR[i]*0.393 + lut->lutG[i]*0.769 + lut->lutB[i]*0.189; 
		valueG = lut->lutR[i]*0.349 + lut->lutG[i]*0.686 + lut->lutB[i]*0.168; 
		valueB = lut->lutR[i]*0.272 + lut->lutG[i]*0.534 + lut->lutB[i]*0.131; 
		lut->lutR[i] = (valueR>=255)? 255 : round(valueR);
		lut->lutG[i] = (valueG>=255)? 255 : round(valueG);
		lut->lutB[i] = (valueB>=255)? 255 : round(valueB);
	}
	return 0;
}

//Nuances de gris sauf pour le rouge
int redish(Image *image, LUT *lut, int param){
	int pixelNumber = image->width*image->height;
	unsigned char *data = image->data;
	int avg = 0;
	switch(param){
		case 0:
			for(int i=0;i<pixelNumber*3;i+=3){		
				avg = (int)(data[i] + data[i+1] + data[i+2])/3;
				data[i] = lut->lutR[data[i]];
				data[i+1] = (avg>=255)? 255 : round(avg);
				data[i+2] = (avg>=255)? 255 : round(avg);
			}
			break;
		case 1:
			for(int i=0;i<pixelNumber*3;i+=3){		
				avg = (int)(data[i] + data[i+1] + data[i+2])/3;
				data[i] = (avg>=255)? 255 : round(avg);
				data[i+1] = lut->lutG[data[i+1]];
				data[i+2] = (avg>=255)? 255 : round(avg);
			}
			break;
		case 2:
			for(int i=0;i<pixelNumber*3;i+=3){		
				avg = (int)(data[i] + data[i+1] + data[i+2])/3;
				data[i] = (avg>=255)? 255 : round(avg);
				data[i+1] = (avg>=255)? 255 : round(avg);
				data[i+2] = lut->lutB[data[i+2]];
			}
			break;
	}
	
	return 0;
}

/* Nuances de gris mais une couleur est boostée
* 0 = red
* 1 = green
* 2 = blue
*/
int enhanceColor(Image *image, LUT *lut, int param){
	blackWhite(image);
	switch(param){
		case 0:
			for(int i=0;i<256;i++){		
				lut->lutR[i]=255;
			}
			break;
		case 1:
			for(int i=0;i<256;i++){		
				lut->lutG[i]=255;
			}
			break;
		case 2:
			for(int i=0;i<256;i++){		
				lut->lutB[i]=255;
			}
			break;
	}
	return 0;
}


/* Fonction qui crée une image en dégradés d'une couleur simple
* 0 = red
* 1 = green
* 2 = blue
* 3 = yellow
* 4 = purple
* 5 = orange
* 6 = pink
*/
int onlyOneColorLUT(Image *image, LUT *lut, int param){
	blackWhite(image);
	switch(param){
		case 0:
			for(int i=0;i<256;i++){		
				lut->lutG[i]=0;
				lut->lutB[i]=0;
			}
			break;
		case 1:
			for(int i=0;i<256;i++){		
				lut->lutR[i]=0;
				lut->lutB[i]=0;
			}
			break;
		case 2:
			for(int i=0;i<256;i++){		
				lut->lutR[i]=0;
				lut->lutG[i]=0;
			}
			break;
		case 3:
			for(int i=0;i<256;i++){		
				lut->lutB[i]=0;
			}
			break;
		case 4:
			for(int i=0;i<256;i++){		
				lut->lutG[i]=0;
				lut->lutR[i]=lut->lutR[i]/2;
			}
			break;
		case 5:
			for(int i=0;i<256;i++){		
				lut->lutG[i]=lut->lutG[i]/2;
				lut->lutB[i]=0;
			}
			break;
		case 6:
			for(int i=0;i<256;i++){		
				lut->lutG[i]=0;
			}
			break;
		default:
			return 0;
	}
	return 0;
}
//Les couleurs sombres deviennent bleu et les claires rouge
int redBlue(Image *image, LUT *lut){
	//contrast2(lut, 20, 1);
	//passage en nuances de gris pour avoir l'intensité moyenne du pixel et en fonction de celle-ci mettre bleu ou rouge
	blackWhite(image);
	for(int i=0;i<256;i++){		
		if(i>127){
			lut->lutG[i]=0;
			lut->lutB[i]=0;
		} else{
			lut->lutR[i]=0;
			lut->lutG[i]=0;
		}
	}
	return 0;
}

//fonction honteusement copiée pour shuffle un array en c
int shuffle(int *array, int number) {    
	for(int i=0;i<256;i++){
		if(i<number){
			array[i] = 1;
		} else{
			array[i] = 0;
		}
	}
    size_t i;
    for (i = 256 - 1; i > 0; i--) {
        size_t j = (unsigned int) (drand48()*(i+1));
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
    return 0;
}


int bicolorFilter(Image *image, LUT *lut, int *color1, int *color2){
	//passage en nuances de gris pour que la transformation fonctionne lorsque l'association avec le LUT se fera
	blackWhite(image);
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
				lut->lutR[i]= newRed;
			} else{
				newRed = newRed-1;
				lut->lutR[i]=newRed;
			}	
		} else{
			lut->lutR[i]=newRed;
		}
		if(greenArray[i] == 1){
			if(color2[1] - color1[1] > 0){
				newGreen = newGreen+1;
				lut->lutG[i]=newGreen;
			} else{
				newGreen = newGreen-1;
				lut->lutG[i]=newGreen;
			}
		} else{
			lut->lutG[i]=newGreen;
		}
		if(blueArray[i] == 1){
			if(color2[2] - color1[2] > 0){
				newBlue = newBlue+1;
				lut->lutB[i]=newBlue;
			} else{
				newBlue = newBlue-1;
				lut->lutB[i]=newBlue;
			}
		} else{
			lut->lutB[i]=newBlue;
		}
	}
	return 0;
}

//fonction qui retourne complètement l'image, elle met le dernier pixel à la place du premier et ainsi de suite
int fullmirror(Image *image){
	int pixelNumber = image->width*image->height;
	unsigned char *data = image->data;
	//recopie de l'image temporaire
	unsigned char *tempData = malloc(sizeof(unsigned char)*3*pixelNumber);
	for(int i=0;i<pixelNumber*3;i++){
		tempData[i] = data[i];
	}
	int arraySize = pixelNumber*3-1;
	for(int j=0;j<pixelNumber*3;j+=3){
		data[j] = tempData[arraySize-j-2];
		data[j+1] = tempData[arraySize-j-1];
		data[j+2] = tempData[arraySize-j];
	}
	return 0;

}
//fonction pour faire une image mirroir
int vMirror(Image *image){
	int pixelNumber = image->width*image->height;
	unsigned char *data = image->data;
	//longueur d'une ligne de l'image dans le tableau data
	int effectiveWidth = image->width*3-1;
	//la valeur se situant au milieu pour savoir quand arrêter la recopie
	int middleValue = effectiveWidth/2;
	//valeur de fin de la ligne (égale à effective width au début pour la première ligne mais sera amené à changer)
	int endLine = effectiveWidth;
	//index pour parcourir le tableau dans l'autre sens en même temps que j
	int secondIndex = 0;
	//valeurs temporaires pour permettre l'échange 
	int tempValueR = 0, tempValueG =  0, tempValueB = 0;
	//on parcourt le tableau de 3 en 3 
	for(int j=0;j<pixelNumber*3;j+=3){
		//tant que j n'est pas le rouge du dernier pixel avant la valeur du milieu
		if(j<=middleValue-2){
			//on échange la valeur des composantes de couleurs des pixels symétriques par rapport au milieu
			//rouge
			tempValueR = data[j];
			data[j] = data[endLine-secondIndex-2];
			data[endLine-secondIndex-2] = tempValueR;
			//vert
			tempValueG = data[j+1];
			data[j+1] = data[endLine-secondIndex-1];
			data[endLine-secondIndex-1] = tempValueG;
			//bleu
			tempValueB = data[j+2];
			data[j+2] = data[endLine-secondIndex];
			data[endLine-secondIndex] = tempValueB;
			//on augmente de 3 aussi comme pour j
			secondIndex+=3;
		} else{
			//si j est le dernier pixel de la ligne, alors on passe à la ligne suivante et on change les valeurs
			if(j == endLine-2){
				middleValue = middleValue+effectiveWidth+1;
				secondIndex = 0;
				endLine = endLine+effectiveWidth+1;
			}
		}
	}

	return 0;
}

/* value est la force du flou
*  pour un flou de 1 on prend tous les pixels dans un rayon de 1 autour de celui en question
*  on fait la moyenne de toutes leurs composantes de couleurs séparemment 
*  on applique ces 3 valeurs moyennes à l'ensemble des pixels
*  besoin d'une copie de l'image pour pouvoir changer les valeurs et ne pas altérer le calcul du flou du pixel suivant ?
*  besoin d'une matrice de pixels pour pouvoir faire cela correctement
*
*/

/*int blur(Image *image, int value){
	//x;y => x+1;y  x-1;y  x;y+1  x;y-1  x+1;y+1 x-1
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"


int main(int argc, char **argv)
{
    //récupération nom image
    char *imageName = "";
    imageName = argv[1];
    // create an image
    Image image;

    // load a ppm file
    if(loadImagePPM(&image,imageName) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    int pixelNumber = image.width*image.height;
    unsigned char *lut = malloc(sizeof(unsigned char)*pixelNumber*3);
    initiateLUT(pixelNumber, image.data, lut);
    


    // modify the image (red pixel in the center)
    /*unsigned int pixel = (image.width*(image.height/2) + (image.width/2))*3;
    printf("%d\n",pixel);
    image.data[pixel + 0] = 255;
    image.data[pixel + 1] = 0;
    image.data[pixel + 2] = 0;*/
    
    for(int i=0;i<argc;i++){
        if(strcmp(argv[i],"-h") == 0 || strcmp(argv[i], "-histo") == 0){
            
        }
        if(strcmp(argv[i],"ADDLUM") == 0) addlumToLUT( pixelNumber, lut, atoi(argv[i+1]));//LANCER LA FCT ADDLUM AVEC LE PARAM i+1 
        if(strcmp(argv[i],"DIMLUM") == 0) printf("dimlum : %s",argv[i+1]);//LANCER LA FCT ADDLUM AVEC LE PARAM i+1 
        if(strcmp(argv[i],"ADDCON") == 0) printf("addcon : %s",argv[i+1]);//LANCER LA FCT ADDLUM AVEC LE PARAM i+1 
        if(strcmp(argv[i],"DIMCON") == 0) printf("dimcon : %s",argv[i+1]);//LANCER LA FCT ADDLUM AVEC LE PARAM i+1 
        if(strcmp(argv[i],"SEPIA") == 0) printf("sepia : %s",argv[i+1]);//LANCER LA FCT ADDLUM AVEC LE PARAM i+1 
    }
    lutToImage(pixelNumber, lut, image.data);
    //récupérer l'output name
    char *imageOutputName = "";
    imageOutputName = argv[argc-1];
    // save the image (if the directory "pics" already exists)
    saveImagePPM(&image, imageOutputName);

    // free the image memory
    freeImage(&image);

        
    
    return 0;
}
   


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

    /*********************** VERSION AVEC LUT SANS STRUCTURE OU LUT EST UNE COPIE DE L'IMAGE *************************/

    /*
    int pixelNumber = image.width*image.height;
    unsigned char *lut = malloc(sizeof(unsigned char)*pixelNumber*3);
    initiateLUT(pixelNumber, image.data, lut);
    
    
    for(int i=0;i<argc;i++){
        if(strcmp(argv[i],"-h") == 0 || strcmp(argv[i], "-histo") == 0){
            
        }
        if(strcmp(argv[i],"ADDLUM") == 0) addlumToLUT( pixelNumber, lut, atoi(argv[i+1]));
        if(strcmp(argv[i],"DIMLUM") == 0) dimlumToLUT( pixelNumber, lut, atoi(argv[i+1]));
        if(strcmp(argv[i],"ADDCON") == 0) contrast( pixelNumber, lut, atoi(argv[i+1]), 1);
        if(strcmp(argv[i],"DIMCON") == 0) contrast( pixelNumber, lut, atoi(argv[i+1]), 0);
        if(strcmp(argv[i],"SEPIA") == 0) sepia(pixelNumber, lut, atoi(argv[i+1]));
        if(strcmp(argv[i],"MIRROR") == 0) mirror(pixelNumber, lut);
    }
    lutToImage(pixelNumber, lut, image.data);
    */



    /**********************************************************************************************************************/

    /************************************ NOUVELLE VERSION ********************************************/


    //int pixelNumber = image.width*image.height;
    LUT lut;
    initiateLUT2(&lut);
    
    
    for(int i=0;i<argc;i++){
        if(strcmp(argv[i],"-h") == 0 || strcmp(argv[i], "-histo") == 0){
            //fonction histo
        }
        if(strcmp(argv[i],"ADDLUM") == 0) addlumToLUT2(&lut, atoi(argv[i+1]));
        if(strcmp(argv[i],"DIMLUM") == 0) dimlumToLUT2(&lut, atoi(argv[i+1]));
        if(strcmp(argv[i],"ADDCON") == 0) contrast2(&lut, atoi(argv[i+1]), 1);
        if(strcmp(argv[i],"DIMCON") == 0) contrast2(&lut, atoi(argv[i+1]), 0);
        if(strcmp(argv[i],"SEPIA") == 0) sepia2(&image);
        if(strcmp(argv[i],"INVERT") == 0) invert(&lut);
        if(strcmp(argv[i],"MIRROR") == 0) fullmirror2(&image);
        if(strcmp(argv[i],"BLACKWHITE") == 0) blackWhite(&image);
        if(strcmp(argv[i],"ONLYRED") == 0) onlyred(&image, &lut);
        if(strcmp(argv[i],"ONLYRED2") == 0) redBlue(&image, &lut);
        if(strcmp(argv[i],"BICOLOR") == 0) yellowPurple(&image, &lut);


    }
    lutToImage2(&image, &lut);


    /***************************************************************************************************/

    //récupérer l'output name
    char *imageOutputName = "";
    imageOutputName = argv[argc-1];
    // save the image (if the directory "pics" already exists)
    saveImagePPM(&image, imageOutputName);

    // free the image memory
    freeImage(&image);

        
    
    return 0;
}
   


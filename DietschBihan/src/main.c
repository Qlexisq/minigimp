#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"
#include "histogram.h"


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

    /**********************************************************************************************************************/

    /************************************ NOUVELLE VERSION ********************************************/


    LUT lut;
    initiateLUT(&lut);
    int histo=0;
    int histoWidth=0;
    int histoHeight=0;
    
    
    for(int i=0;i<argc;i++){
        if(strcmp(argv[i],"-h") == 0 || strcmp(argv[i], "-histo") == 0){
            histoWidth = atoi(argv[i+1]);
            histoHeight = atoi(argv[i+2]);
            createHistogramGrey(&image, histoWidth, histoHeight, imageName);
            createHistogramRGB(&image, histoWidth, histoHeight, imageName);
            histo = 1;

        }
        if(strcmp(argv[i],"ADDLUM") == 0) addlumToLUT(&lut, atoi(argv[i+1]));
        if(strcmp(argv[i],"DIMLUM") == 0) dimlumToLUT(&lut, atoi(argv[i+1]));
        if(strcmp(argv[i],"ADDCON") == 0) contrast(&lut, atoi(argv[i+1]), 1);
        if(strcmp(argv[i],"DIMCON") == 0) contrast(&lut, atoi(argv[i+1]), 0);
        if(strcmp(argv[i],"SEPIA") == 0) sepia(&image);
        if(strcmp(argv[i],"INVERT") == 0) invert(&lut);
        if(strcmp(argv[i],"MIRROR") == 0) fullmirror(&image);
        if(strcmp(argv[i],"VMIRROR") == 0) vMirror(&image);
        if(strcmp(argv[i],"BLACKWHITE") == 0) blackWhite(&image);
        if(strcmp(argv[i],"ONLYRED") == 0) onlyred(&image, &lut);
        if(strcmp(argv[i],"REDBLUE") == 0) redBlue(&image, &lut);
        if(strcmp(argv[i],"BICOLOR") == 0) bicolorFilter(&image, &lut);


    }
    lutToImage(&image, &lut);


    /***************************************************************************************************/

    //récupérer l'output name
    char *imageOutputName = "";
    imageOutputName = argv[argc-1];
    // save the image (if the directory "pics" already exists)
    saveImagePPM(&image, imageOutputName);
    if(histo){
        createHistogramGrey(&image, histoWidth, histoHeight, imageOutputName);
        createHistogramRGB(&image, histoWidth, histoHeight, imageOutputName);
    }

    // free the image memory
    freeImage(&image);

        
    
    return 0;
}
   


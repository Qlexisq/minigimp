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
        if(strcmp(argv[i],"SEPIA") == 0) sepiaLUT(&lut, &image);
        if(strcmp(argv[i],"INVERT") == 0) invert(&lut);
        if(strcmp(argv[i],"MIRROR") == 0) fullmirror(&image);
        if(strcmp(argv[i],"HMIRROR") == 0) {
            fullmirror(&image); 
            vMirror(&image);
        }
        if(strcmp(argv[i],"VMIRROR") == 0) vMirror(&image);
        if(strcmp(argv[i],"BW") == 0) blackWhite(&image);
        if(strcmp(argv[i],"REDISH") == 0) redish(&image, &lut,0);
        if(strcmp(argv[i],"GREENISH") == 0) redish(&image, &lut,1);
        if(strcmp(argv[i],"BLUEISH") == 0) redish(&image, &lut,2);
        if(strcmp(argv[i],"RED") == 0) onlyOneColorLUT(&image, &lut,0);
        if(strcmp(argv[i],"GREEN") == 0) onlyOneColorLUT(&image, &lut,1);
        if(strcmp(argv[i],"BLUE") == 0) onlyOneColorLUT(&image, &lut,2);
        if(strcmp(argv[i],"YELLOW") == 0) onlyOneColorLUT(&image, &lut,3);
        if(strcmp(argv[i],"PURPLE") == 0) onlyOneColorLUT(&image, &lut,4);
        if(strcmp(argv[i],"ORANGE") == 0) onlyOneColorLUT(&image, &lut,5);
        if(strcmp(argv[i],"PINK") == 0) onlyOneColorLUT(&image, &lut,6);
        if(strcmp(argv[i],"REDBLUE") == 0) redBlue(&image, &lut);
        if(strcmp(argv[i],"BICOLOR") == 0) {
            int color1[3] = {atoi(argv[i+1]), atoi(argv[i+2]), atoi(argv[i+3])};
            int color2[3] = {atoi(argv[i+5]), atoi(argv[i+6]), atoi(argv[i+7])};
            bicolorFilter(&image, &lut, color1, color2);
        }
        if(strcmp(argv[i],"MORERED") == 0) enhanceColor(&image, &lut,0);
        if(strcmp(argv[i],"MOREGREEN") == 0) enhanceColor(&image, &lut,1);
        if(strcmp(argv[i],"MOREBLUE") == 0) enhanceColor(&image, &lut,2);



    }
    lutToImage(&image, &lut);


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
   


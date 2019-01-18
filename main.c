#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	//Récupération adresse image rentrée en paramètre
	printf("%d\n\n",argc);
	char *image = "";
	image = argv[1];
	for(int i=0;i<argc;i++){
		if(strcmp(argv[i],"-h") == 0 || strcmp(argv[i], "-histo") == 0){
			//=============== FONCTION HISTO =================== //
			/*
			*
			*
			*
			*
			*/
		}
		if(strcmp(argv[i],"ADDLUM") == 0) printf("addlum : %s",argv[i+1]);//LANCER LA FCT ADDLUM AVEC LE PARAM i+1 
		if(strcmp(argv[i],"DIMLUM") == 0) printf("dimlum : %s",argv[i+1]);//LANCER LA FCT ADDLUM AVEC LE PARAM i+1 
		if(strcmp(argv[i],"ADDCON") == 0) printf("addcon : %s",argv[i+1]);//LANCER LA FCT ADDLUM AVEC LE PARAM i+1 
		if(strcmp(argv[i],"DIMCON") == 0) printf("dimcon : %s",argv[i+1]);//LANCER LA FCT ADDLUM AVEC LE PARAM i+1 
		if(strcmp(argv[i],"SEPIA") == 0) printf("sepia : %s",argv[i+1]);//LANCER LA FCT ADDLUM AVEC LE PARAM i+1 
		if(strcmp(argv[i],"-o") == 0){
			printf("Nom image : %s",argv[i+1]);
			//enregistrer le résultat sous le nom i+1
			
		}
	}

		
	
	return 0;
}
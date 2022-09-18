#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "abr.h"

int main(int argc, char **argv)
{

 	Lm_mot *lmot=lire_dico_Lmot("french_za");
 	Nd_mot *dico=Lm2abr(lmot);
 	if(!argv[1]||!argv[2]){
 		printf("Veuillez rentre un nombre de recherche et un mot en parametre\n");
 		return 0;
 	}
 	for(int i=0;i<atoi(argv[1]);i++){
 		Nd_mot *nd=(chercher_Nd_mot(dico,argv[2]));
 		if(nd){
 			printf("mot trouve\n");
 		}

 	}
 detruire_abr_mot(dico);
 
  return 0;
}

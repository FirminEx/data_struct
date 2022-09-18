#include <stdio.h>
#include <stdlib.h>
#include "arbre_lexicographique.h"


int main(int argc, char **argv)
{
  

	PNoeud racine=lire_dico("french_za");
	if(!argv[1]||!argv[2]){
 		printf("Veuillez rentre un nombre de recherche et un mot en parametre\n");
 		return 0;
 	}
 	for(int i=0;i<atoi(argv[1]);i++){
 		if(rechercher_mot(racine,argv[2]) ){
 		printf("mot trouve\n");
 		}
 	}
	detruire_dico(racine);
	
  return 0;
}

#include "arbre_lexicographique.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PNoeud creer_noeud(char lettre){
  PNoeud pn=(PNoeud)malloc(sizeof(Noeud));
  if (pn==NULL) {
    printf("Impossible d'allouer un noeud\n");
    return NULL;
  }
 
  pn->lettre=lettre;
  pn->fin_de_mot=non_fin;
  pn->frere_suivant=NULL;
  pn->fils=NULL;
  return pn;
}

void inserer_lettre(PNoeud *racine, PNoeud *n_lettre, char lettre) {
  PNoeud prec=NULL;
  PNoeud n=*racine;
  if (n==NULL) {
    *racine=creer_noeud(lettre);
    *n_lettre=*racine;
    return;
  }

  while(n!=NULL) {
    if (n->lettre == lettre) {
      *n_lettre=n;
      return;
    }
    if (n->lettre>lettre) {
      // on doit inserer avant n
      if (prec==NULL) {
        // insertion en tete
        prec=creer_noeud(lettre);
        prec->frere_suivant=n;
        *racine=prec;
        *n_lettre=*racine;
      }
      else {
        *n_lettre=creer_noeud(lettre);
        prec->frere_suivant=*n_lettre;
        (*n_lettre)->frere_suivant=n;
      }
      return;
    }
    prec=n;
    n = n->frere_suivant;
  }
  *n_lettre=creer_noeud(lettre);
  prec->frere_suivant=*n_lettre;
}

PNoeud ajouter_mot(PNoeud racine, char *mot) {
  PNoeud n=NULL;
  if (strlen(mot)==0) {
    return NULL;
  }
  inserer_lettre(&racine,&n,mot[0]);
  if (strlen(mot)==1) {
    n->fin_de_mot=fin;
  }
  else {
    n->fils=ajouter_mot(n->fils,mot+1);
  }
  return racine;
}

int taille(PNoeud racine) {
  if (racine==NULL) {
    return 0;
  }
  else {
    return 1+taille(racine->frere_suivant);
  }
}
void afficher_mots(PNoeud n, char mot_en_cours[], int index) {
  while(n){
  	if(n->frere_suivant){
  		afficher_mots(n->frere_suivant,mot_en_cours,index);
  	}
  	mot_en_cours[index]=n->lettre;
  	index++;
  	if(n->fin_de_mot==fin){
  		char *affichage=mot_en_cours;
  		affichage[index]='\0';
  		printf("%s\n",affichage);		
   	}
  	n=n->fils;
  }
}

void afficher_dico(PNoeud racine) {
	
	char *init=malloc(sizeof(char)*(LONGUEUR_MAX_MOT+1));
	afficher_mots(racine,init,0);
	free(init);
}

void detruire_dico(PNoeud dico) {
	if(!dico){return;}
	detruire_dico(dico->frere_suivant);
	detruire_dico(dico->fils);
	free(dico);
}

PNoeud chercher_lettre(PNoeud n, char lettre) {
  if (n==NULL) {
    return NULL;
  }
  if (n->lettre==lettre) {
    return n;
  }
  if (n->lettre>lettre) {
    return NULL;
  }
  return chercher_lettre(n->frere_suivant,lettre);
}

int rechercher_mot(PNoeud dico, char *mot) {
  PNoeud n=chercher_lettre(dico,mot[0]);
  if (n==NULL) {
    return 0;
  }
  if (strlen(mot)==1) {
    return n->fin_de_mot == fin;
  }
  return rechercher_mot(n->fils,mot+1);
}

PNoeud lire_dico(const char *nom_fichier) {
	char ligne[100];
	FILE *f=fopen(nom_fichier,"r");
	if (f==NULL){
	printf("Erreur lors de l'ouverture du fichier %s\n",nom_fichier);
		return NULL;
	}
	PNoeud retour=creer_noeud('.');
	
	
	while(fgets(ligne,100,f)){
		ligne[strlen(ligne)-1]='\0';
		ajouter_mot(retour,ligne);
	}
	fclose(f);
	
	return retour;

}

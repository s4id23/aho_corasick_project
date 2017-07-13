//Guettouche Islam
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../bibliotheque/matrice.h"

#define LENGTH_MOT 255
#define TAILLE_MAX 1000
#define TAILLE_MAX_TEXT 5000000


int main(int argc, char **argv){	
	
 if (argc != 3) {
		printf("Usage : %s wordsFile textFile\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	
	char **Liste_Mot = malloc(1000*sizeof(char*));
	char *Texte;
	char Mot[1000];
	int Nbr_Mot = 0;
	//on commence par ouvrir le fichier contenant la liste des mot a comparer
	FILE *F_liste_mot_a_comparer = fopen(argv[1], "r");
	if (F_liste_mot_a_comparer == NULL) {
		fprintf(stderr, "Error while opening %s", argv[1]);
	}

	char eof; 
	//cette boucle nous permet de récupérer chaque mot créer au paravent par genMot.c
	while((eof = fscanf(F_liste_mot_a_comparer, "%s", Mot)) != EOF)
	{
		Liste_Mot[Nbr_Mot] = malloc((strlen(Mot)+1)*sizeof(char));
		//on copy chaque mot dans Liste_Mot[Nbr_Mot] et on incrémente  wordNb
		strcpy(Liste_Mot[Nbr_Mot],Mot);
		Nbr_Mot++;
	}
	

	fclose(F_liste_mot_a_comparer);
	
	//on ouvre le fichier contenant le texte a comparer
	FILE *F_texte_comparer = fopen(argv[2], "r");

	if (F_texte_comparer == NULL) {
		fprintf(stderr, "Error while opening %s", argv[1]);
	}
	long tailleTexte = 0;
	//on place le curseur à la fin du fichier
	fseek(F_texte_comparer, 0, SEEK_END);
	//indique à quelle position vous êtes actuellement dans le fichier
	tailleTexte = ftell(F_texte_comparer);
	Texte = malloc((tailleTexte+1) * sizeof(char));
	//on place le curseur au début du fichier
	fseek(F_texte_comparer, 0, SEEK_SET);
	//on récupère le texte trouvant dans textFile
	fgets(Texte, tailleTexte, F_texte_comparer);	
	fclose(F_texte_comparer);

	//on lance la recherche a travers un arbre matrice
	clock_t tDeb,tFin;
	float temps_execution;
	tDeb=clock();
	ahoCorassickTrieMatrice(Liste_Mot, Nbr_Mot, Texte, strlen(Texte));
	tFin=clock();
	temps_execution =(float)(tFin-tDeb)/CLOCKS_PER_SEC;
	printf("Le temps d'exécution est: %f s\n",temps_execution);
	exit(EXIT_SUCCESS);
}

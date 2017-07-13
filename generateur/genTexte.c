//Guettouche Islam
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*Commence par récupérer La longueur du texte et La taille de l'alphabet après elle remplis la char alph[]  par une 
 série ordonnées de lettre A,B,C……. après on commence la création du texte a partir de alph[] et en choisissant aléatoirement 
 les lettre a laide dune fonction rand()*/
 
int main(int argc,char * argv[])
{
	FILE* F_Texte=NULL;
	int i,long_texte,j,taille_alphabet,G;
	char liste_de_lettre[255],A;
	    long_texte=atoi(argv[1]);	 
	    taille_alphabet=atoi(argv[2]);	

	    printf("La longueur du texte est : %d \n",  long_texte);
		printf("La taille de l'alphabet est: %d \n", taille_alphabet);
		F_Texte=fopen("Texte.txt","w+");

	// Pour que notre alphabet commence avec "A"
	j=65; 
	for(i=0;i<taille_alphabet;i++)
	{
		liste_de_lettre[i]=(char)(i+j);
	}

	for(i=0;i<long_texte;i++)
	{
		G=rand()%taille_alphabet;
		A=liste_de_lettre[G];
		printf("%c",A);
		fprintf(F_Texte, "%c" , A);

	}
       printf("\n");

	fclose(F_Texte);



return 0;
}

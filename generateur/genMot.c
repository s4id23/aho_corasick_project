//Guettouche Islam
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*Commence par récupérer Le nombre de mots, la longueur minimale des mots, la longueur maximale des mots,
 * La taille de l'alphabet après elle remplis la char liste_de_lettre[]  par une série ordonnées de lettre A,B,C……. après on commence 
la création des mots a partir de liste_de_lettre[] et en choisissant aléatoirement les lettre a laide dune fonction rand()*/
int main(int argc,char * argv[])
{
	FILE* F_Mot=NULL;
	int i,nbr_de_mots,j,long_min_mots,long_max_mots,taille_alphabet,G,k,N,temp;
	char liste_de_lettre[255],A;
		
		// nbr de mots
	    nbr_de_mots=atoi(argv[1]);
	    // la longueur minimale des mots  
	    long_min_mots=atoi(argv[2]);
	    // la longueur maximale des mots  
	    long_max_mots=atoi(argv[3]);  
	    // taille de l'alphabet.
        taille_alphabet=atoi(argv[4]);  
	    printf("Le nombre de mots est : %d \n",  nbr_de_mots);
		printf("la longueur minimale des mots est: %d \n", long_min_mots);
		printf("la longueur maximale des mots est: %d \n", long_max_mots);
		printf("La taille de l'alphabet est: %d \n", taille_alphabet);
		F_Mot=fopen("Mots.txt","w+");
		//Pour que notre alphabet commence avec "A"
		j=65; 
		for(temp=0;temp<taille_alphabet;temp++)
		{
			liste_de_lettre[temp]=(char)(temp+j);
			
		}

		for(i=0;i<nbr_de_mots;i++)
		{
			/*G nous permet de choisir un nbr aléatoire entre la longueur minimale et 
			maximale des mots qui vont être créer a l’intérieur de la boucle qui suit */
	    	G=rand()%(long_max_mots+1-long_min_mots) +long_min_mots;
	    	for(k=0;k<G;k++)
	    	{
            	N=rand()%taille_alphabet;
            	printf("%c",liste_de_lettre[N]);
            	A=liste_de_lettre[N];
            	fprintf(F_Mot, "%c" , A);

	    	}		 
	    	    printf("\n");
                fprintf(F_Mot, "\n");
		}
		 printf("\n");
		fclose(F_Mot);
		return 0;
}

//Guettouche Islam
#include <stdio.h>
#include <stdlib.h>
#include "../bibliotheque/matrice.h"

#define maxNoode 100000
#define LENGTH_MOT 255
#define TAILLE_MAX 1000
#define TAILLE_MAX_TEXT 5000000

void ahoCorassickTrieMatrice(char** mots, int nbrMots,unsigned char* text, int textLenght){
	ACMatrice acMatrice = preAhoCorassickTrieMatrice(mots, nbrMots);
	int target = 0, nbrOcc = 0, i;
	for( i = 0; i < textLenght; i++){
		while(acMatrice->trie->transition[target][(int)text[i]] == -1){
			target = acMatrice->suppleant[target];
		}
		target = acMatrice->trie->transition[target][(int) text[i]];
		nbrOcc += acMatrice->trie->finite[target];
	}
	printf("AC-MATRICE - Nombre d\'occurences : %d\n", nbrOcc);	
}

ACMatrice preAhoCorassickTrieMatrice(char** mots, int nbrMots){
	ACMatrice acMatrice = createACMatrice();
	int i;
	for(i = 0; i < nbrMots; i++){
		if(mots[i] == NULL){
			break;
		}
		else{
			insertInTrie(acMatrice->trie, mots[i]);
		}
	}
	
	for(i = 0; i < alphabet; i++){
		if(acMatrice->trie->transition[0][i] == -1){
			acMatrice->trie->transition[0][i] = 0;
		}
	}
	completer(acMatrice);
	
	return acMatrice;
}

void insertInTrie(Trie trie, unsigned char *w){
    int codeAscii =-1;
	int memo = 0;
	int j=0;
	int booleen=0;
	int fin=0;
	
	// traitement du premier mot donner
	if (trie->nextNode == 0) // premier ajout dans le trie
	{
		while (w[j] != '\0')
		{  
			codeAscii = w[j];
			trie->transition[trie->nextNode][codeAscii] = trie->nextNode+1;
			trie->nextNode++;
			j++;
		}	
		trie->finite[trie->nextNode] = 1;	
	} 
	else{	
		codeAscii = w[j];
		if (trie->transition[0][codeAscii] == -1) // ajout depuis la racine E
		{
			trie->transition[0][codeAscii] = trie->nextNode+1;
			trie->nextNode++;
			j++;
			while (w[j] != '\0')
			{                              
				codeAscii = w[j];
				trie->transition[trie->nextNode][codeAscii] = trie->nextNode+1;
				trie->nextNode++;
				j++;
			}
			trie->finite[trie->nextNode] = 1;
		}
		else // ajout depuis un noeud au milieu
		{	
			j=0;booleen = 0;				
			while (w[j] != '\0')
			{
				booleen = 0;
				while ((memo < trie->nextNode) && (booleen == 0))
				{	
					codeAscii = w[j];					
					if (trie->transition[memo][codeAscii] != -1) // existe un chemin
					{
						memo = trie->transition[memo][codeAscii]; // enregister le dernier noeud du chemin
						j++;// Avancer au prochaine caractere de 'w'
					}
					else if (trie->transition[memo][codeAscii] == -1)// fin du chemin existant
					{
						trie->transition[memo][codeAscii] = trie->nextNode+1;
						trie->nextNode++;
						j++;
						fin = 1;
						booleen=1;
					}
					
				}
				while (w[j] != '\0')
					{  
						codeAscii = w[j];
						trie->transition[trie->nextNode][codeAscii] = trie->nextNode+1;
						trie->nextNode++;
						j++;
					}
				trie->finite[trie->nextNode] = 1;
			}	
										
		}					
	}                         
}

Trie createTrie(int maxNode)
{   
	int i ,j;
	Trie t  = (Trie) malloc (sizeof(Trie));
	t->maxNode = maxNode;
	t->nextNode = 0;
	
    // allocation de la memoire pour la matrice de transition
    t->transition = (int**) malloc(maxNode * sizeof(int*));

    for (i = 0; i < maxNode; i++)
        t->transition[i] = (int*) malloc((alphabet) * sizeof(int));
        
    // allocation du tableau des etats
      
	t->finite = (int*) malloc(maxNode * sizeof(int));
      
	for (i=0;i<maxNode;i++)
	{
		for (j=0;j<alphabet;j++)  
		{
			t->transition[i][j] = -1;
		}  
	}
	  
	// initialisation du tabealu des fineaux
	for (i=0;i<maxNode;i++)
	{         
		t->finite[i] = 0;		
	}

    return t;	
}


	
void AffichageTrie(Trie trie)
{
	int i,j;

    for (i=0;i<trie->maxNode;i++)
    {	
		printf("\n%d : ",i);
		for (j=0;j<alphabet;j++)  
        {		
			if (trie->transition[i][j] != -1)
			{	
                printf("-------->[%c][%d]",(char)j,trie->transition[i][j]);
            }
              
        }  
    }
	printf("******************************************\n");
	for (i=0;i<trie->maxNode;i++)
    {	
		if(trie->finite[i] != 0)
			printf("[%d] = %c \n\n",i,trie->finite[i]);
    }
    
}
ACMatrice createACMatrice(){
	ACMatrice acMatrice = (ACMatrice) malloc (sizeof(ACMatrice));
	
	acMatrice->trie = createTrie(maxNoode);
	
	acMatrice->suppleant = (int*) malloc(maxNoode * sizeof(int));
	int i;
	for(i=0;i<maxNoode;i++){
		acMatrice->suppleant[i] = -1;
	}
	
	return acMatrice;
}



void completer(ACMatrice acMatrice){
	
	int i, suppleant; 
	int * l = acMatrice->trie->transition[0];
	for(i = 0; i < alphabet; i++){
		if(l[i] != 0){
			enfiler_matrice(l[i]);
			acMatrice->suppleant[l[i]] = 0;
		} 
	}
	
	while(!isEmpty_matrice()){
		int r = defiler_matrice();
		l = acMatrice->trie->transition[r];
		for(i = 0; i < alphabet; i++){
			if(l[i] != -1){
				enfiler_matrice(l[i]);
				suppleant = acMatrice->suppleant[r];
				while(acMatrice->trie->transition[suppleant][i] == -1){
					suppleant = acMatrice->suppleant[suppleant];
				}
				acMatrice->suppleant[l[i]] = acMatrice->trie->transition[suppleant][i];
				acMatrice->trie->finite[l[i]] += acMatrice->trie->finite[acMatrice->suppleant[l[i]]];
			}
		}
	}
}



void affichageSup(ACMatrice acMatrice){
    int i;
    for(i=0;i<maxNoode;i++){
		if(acMatrice->suppleant[i] != -1){
			printf("Sup[%d] = %d \n",i,acMatrice->suppleant[i]);
		}
    }
}

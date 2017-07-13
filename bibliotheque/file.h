//Guettouche Islam
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* structure pour implémenter une file */
struct _file{
	int element;
	struct _file *next;
};
typedef struct _file *File;

File firstFile; 

/* ajouter à la fin d'une file */
File enfiler(File file, int element);

/* supprimer le premier element de la file */
File defiler(File file);

/* retourne le prmemier element de la file*/
int premFile(File file);

/* afficher la file */
void AfficherFile(File file);

void enfiler_matrice(int target);

int defiler_matrice();

int isEmpty();

void afficherFile_matrice();

//Guettouche Islam
#include "../bibliotheque/file.h"

/* ajouter à la fin d'une file */

File enfiler(File file, int element){
	File temp = (File)malloc(sizeof(struct _file));
	temp->element = element;
    temp->next=NULL;

	File temp2 = file;
	// si la file est vide
	if(temp2 == NULL){
		return temp;
	}else{// si la file est non vide
		while(temp2->next != NULL)
			temp2 = temp2->next;
		
		temp2->next = temp;
		return file;
	}
}

/* supprimer le premier element de la file */
File defiler(File file){
	if(file != NULL){
		return file->next;
	}
	
	return NULL;
}

/* retourner le prmeier element de la file*/
int premFile(File file){
	if(file != NULL){
		int  element= file->element;
		return element;
	}
	
	
	return -1;
}

/* afficher la file */
void afficherFile(File file){
	printf("--%d", file->element);
	while(file->next != NULL){
		file = file->next;
		printf("--%d", file->element);
	}
	printf("\n");
}

#include <stdio.h>
#include <stdlib.h>
#include "../bibliotheque/file.h"

void initFile(){
	firstFile = NULL;
}

void enfiler_matrice(int element){
	
    File new = malloc(sizeof(File));
    
    if (new == NULL){
        exit(EXIT_FAILURE);
    }

    new->element = element;
    new->next = NULL;

    if (firstFile != NULL){
		File tmp = firstFile;
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = new;
    }
    else{
        firstFile = new;
    }
}


int defiler_matrice(){
    if (firstFile == NULL){
        exit(EXIT_FAILURE);
    }
	
	int element;
	
    if (firstFile != NULL){
        File tmp = firstFile;
        element = tmp->element;
        firstFile = tmp->next;
        free(tmp);
    }

    return element;
}

int isEmpty_matrice(){
	if(firstFile == NULL){
		return 1;
	}
	
	return 0;
}

void afficherFile_matrice()
{
    if (firstFile == NULL){
        exit(EXIT_FAILURE);
    }

    File tmp = firstFile;

    while (tmp != NULL){
        printf("%d ", tmp->element);
         tmp = tmp->next;
    }
}

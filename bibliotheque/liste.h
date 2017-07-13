//Guettouche Islam
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "file.h"

/* structure des transitions*/
struct _transitions{
	int debut;			/* etat de début de la transition */
	unsigned char lettre;	/* etiquette de la transition */
	int fin;			/* etat de fin de la transition*/
	struct _transitions *suivant;	/* transition suivante */
};
typedef struct _transitions *Transitions;

/* structure de la liste chainée */
struct _list{
	int targetNode;		/* cible de la transition*/
	unsigned char letter; 	/* etiquette de la transition  */
	struct _list *next;	/* maillon suivant */
};
typedef struct _list *List;

/* structure du trie */
struct _trie{
	int maxNode; 		/* Nombre maximal de noeuds du trie  */
	int nextNode; 		/* Indice du prochain noeud disponible */
	List *transition; 	/* liste d'adjacence */
	char *finite; 		/*  etats terminaux  */
	int * suppleance;	/* tableau de suppléances */
};

typedef struct _trie *Trie;

/* constructeur */
Trie createTrieList(int maxNode);


/* ajouter mot dans le trie */
void addInTrieList(Trie trie, char *w);

/* ajouter un caractère */
void addCaracter(int targetNode, unsigned char letter, int next, Trie trie); 

/* verifier l'existance d'un mot dans un trie */
int isInTrieList(Trie trie, char *w);

/* chercher caractère dans le trie */
int Chercher_Caracter(unsigned char c, int target, Trie trie);

/* afficehr le trie */
void printTrieList(Trie trie);


//la fonction qui existe dans le cours : ac.pdf , page 12
void completeTrieList(Trie trie);

//la fonction qui existe dans le cours : ac.pdf , page 10

Trie preAhoCorassickTrieList(char ** X, int k);

//la fonction qui existe dans le cours : ac.pdf , page 15

void ahoCorassickTrieList(char ** X, int k, char * y, int n);

/* inserer dans une transition */
Transitions insertIntoTransitions(int debut, unsigned char valeur, int fin, Transitions transitions);

/* retourne la liste des etats des transitions dans le trie */
Transitions transitionsList(Trie trie, int etat, Transitions transitions);


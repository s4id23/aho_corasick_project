//Guettouche Islam
#include "file.h"
#define alphabet 256

struct _trie {
int maxNode; /* Nombre maximal de noeuds du trie */
int nextNode; /* Indice du prochain noeud disponible */
int **transition; /* matrice de transition */
int *finite; /* etats terminaux */
};

typedef struct _trie *Trie;
Trie createTrie(int maxNode);
void insertInTrie(Trie trie, unsigned char *w);


struct _ACMatrice{
	Trie trie;
	int* suppleant;
};

typedef struct _ACMatrice* ACMatrice;

ACMatrice createACMatrice();

ACMatrice preAhoCorassickTrieMatrice(char** mots, int nbrMots);

void completer(ACMatrice acMatrice);

void affichageSup(ACMatrice acMatrice);

void ahoCorassickTrieMatrice(char** mots, int nbrMots,unsigned char* text, int textLenght);

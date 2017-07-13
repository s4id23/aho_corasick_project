//Guettouche Islam
#include "../bibliotheque/liste.h"
#define size_alphabet 256


//la fonction qui existe dans le cours : ac.pdf , page 15

void ahoCorassickTrieList(char ** Liste_Mot, int Nbr_Mot, char * Texte, int tailleTexte){
	
	/* temps en micro-secondes */
	clock_t initial_time, final_time; 
	/* temps en secondes */
	float cpu_time;	
	int occurence  = 0;
	//Recuperation du temps passe dans le programme.
	initial_time = clock();
	Trie TrieList = preAhoCorassickTrieList(Liste_Mot, Nbr_Mot);
	//printTrieList(TrieList);
	
	int j;
	int e = 0;
	for(j = 0; j < tailleTexte; j++){
		while(Chercher_Caracter(Texte[j], e, TrieList) == -1)
			e = TrieList->suppleance[e];
		
		e = Chercher_Caracter(Texte[j], e, TrieList);
		if(TrieList->finite[e] != 0){
			occurence += TrieList->finite[e];
		}
	}
	final_time = clock();
	cpu_time = (final_time - initial_time) * 1e-6;
	printf("AC-LISTE - Nombre d\'occurences : %d\n", occurence);
	printf("Le temps d'exécution est: %f s\n", cpu_time);
	
	
}

//la fonction qui existe dans le cours : ac.pdf , page 10

Trie preAhoCorassickTrieList(char ** Liste_Mot, int Nbr_Mot){
	int i;
	
	// somme de mots de X
	int maxNode = 0;
	for(i = 0; i < Nbr_Mot; i++)
		maxNode += strlen(Liste_Mot[i]);
	maxNode += 1;
	
	Trie TrieList = createTrieList(maxNode);
	
	// insertion des mots de X dans le trie
	for(i = 0; i < Nbr_Mot; i++)
		addInTrieList(TrieList, Liste_Mot[i]);
	
	for(i = 0; i < size_alphabet; i++){
		if(Chercher_Caracter(i , 0, TrieList) == -1)
			addCaracter(0, i, 0, TrieList);
	}
	
	completeTrieList(TrieList);
	return TrieList;
}


/* constructeur */
Trie createTrieList(int maxNode){
	Trie trie;
	trie = (Trie) malloc(sizeof(struct _trie));
	
	trie->maxNode = maxNode;
	trie->nextNode = 1;
	
	trie->finite = (char *) malloc(maxNode * sizeof(char));
	trie->transition = (List *) malloc(maxNode * sizeof(struct _list));
	trie->suppleance = (int*) malloc(maxNode * sizeof(int));
	
	int i;
	for(i = 0; i < maxNode; i++){
		trie->finite[i] = 0;
		trie->transition[i] = NULL;
		trie->suppleance[i] = 0;
	}

	return trie;
}

/* ajouter mot dans le trie */
void addInTrieList(Trie TrieList, char *Liste_Mot){
	//printf("\n++ Fonction addInTrieList : Mot à ajouter = %s\n", Liste_Mot); 
	
	int i = 0;
	int courant = 0;
	int taille_Mot = strlen(Liste_Mot);
	
	if(taille_Mot > 0){
		// si le caractère existe
		while((i < taille_Mot) && (TrieList->transition[courant] != NULL) && (Chercher_Caracter(Liste_Mot[i], courant, TrieList) != -1) ){
		//	printf("--> Ajout de la lettre qui  : %c, existe !\n", Liste_Mot[i]);
			courant = Chercher_Caracter(Liste_Mot[i], courant, TrieList);
			i++;
		}
		
		// creation d'un nouveau etat
		while(i < taille_Mot){
		//	printf("--> Ajout de la lettre : %c\n", Liste_Mot[i]);
			addCaracter(TrieList->nextNode, Liste_Mot[i], courant, TrieList);
			courant = TrieList->nextNode;
			TrieList->nextNode++;
			i++;
		}
		
		// ici c'est la fin du mot donc finite prend 1
		TrieList->finite[courant] = 1;
	}
}


/* chercher caractère dans le trie */
int Chercher_Caracter(unsigned char caracter, int target, Trie TrieList){
	List liste_chainee = (List) malloc(sizeof(struct _list));
	liste_chainee = TrieList->transition[target];
	
	/* si il n'y a pas de transitions */
	if(liste_chainee == NULL){
		return -1;
	}
	
	/* si la prmiere lettre == c */
	if(liste_chainee->letter == caracter){
		return liste_chainee->targetNode;
	}
	
	while(liste_chainee->next != NULL){
		liste_chainee = liste_chainee->next;
		if(liste_chainee->letter == caracter){
			return liste_chainee->targetNode;
		}
	}
	
	return -1;
}


/* ajouter caractère dans le trie */
void addCaracter(int targetNode, unsigned char letter, int next, Trie TrieList){
	List liste_chainee = (List) malloc(sizeof(struct _list));
	liste_chainee->targetNode = targetNode;
	liste_chainee->letter = letter;
	liste_chainee->next = TrieList->transition[next];
	TrieList->transition[next] = liste_chainee;
}


//la fonction qui existe dans le cours : ac.pdf , page 12

void completeTrieList(Trie TrieList){
	//on declare un fichier
	File file = NULL;
	//on declare une structure Transitions
	Transitions transitions = NULL;
	/* retourne la liste des etats des transitions dans le trie */
	transitions = transitionsList(TrieList, 0, transitions);
	int r, p, s;
	unsigned char a;
	
	while(transitions != NULL){
		r = transitions->debut;
		a = transitions->lettre;
		p = transitions->fin;
		transitions = transitions->suivant;
		file = enfiler(file, p);
	}
	
	while(file != NULL){
		r = premFile(file);
		file = defiler(file);
		transitions = NULL;
		transitions = transitionsList(TrieList, r, transitions);
		while(transitions != NULL){
			r = transitions->debut;
			a = transitions->lettre;
			p = transitions->fin;
			transitions = transitions->suivant;
			file = enfiler(file, p);
			s = TrieList->suppleance[r];
			while(Chercher_Caracter(a, s, TrieList) == -1)
				s = TrieList->suppleance[s];
			
			TrieList->suppleance[p] = Chercher_Caracter(a, s, TrieList);
			if(TrieList->finite[Chercher_Caracter(a, s, TrieList)]==1)
				TrieList->finite[p] = TrieList->finite[p]+1;
		}
		
	}
}



/* retourne la liste des etats des transitions dans le trie */
Transitions transitionsList(Trie TrieList, int etat, Transitions transitions){
	int i;
	for(i = 0; i < size_alphabet; i++){
		if(etat == 0 && Chercher_Caracter(i , etat, TrieList) != 0 && Chercher_Caracter(i , etat, TrieList) != -1){
			transitions = insertIntoTransitions(etat, i, Chercher_Caracter(i , etat, TrieList), transitions);
		}else{
			if(etat != 0 && Chercher_Caracter(i , etat, TrieList) != -1){
				transitions = insertIntoTransitions(etat, i, Chercher_Caracter(i , etat, TrieList), transitions);
			}
		}
		
	} 
	return transitions;
}



/* inserer dans la transition */
Transitions insertIntoTransitions(int debut, unsigned char valeur, int fin, Transitions transitions){
	Transitions temp = (Transitions) malloc(sizeof(struct _transitions));
	temp->debut = debut;
	temp->lettre = valeur;
	temp->fin = fin;
	temp->suivant = transitions;
	return temp;
}


/* afficher le trie*/
void printTrieList(Trie trie){
	// nombre de noeuds
	printf("Nombre de noeuds : %d\n", trie->maxNode);
	printf("Prochain noeud disponible : %d\n", trie->nextNode);
}



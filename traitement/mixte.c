//Guettouche Islam
#include "../bibliotheque/mixte.h"
#define size_alphabet 256

/*
la fonction qui existe dans le cours : ac.pdf , page 15*/
void ahoCorassickTrieMixte(char ** Liste_Mot, int Nbr_Mot, char * Texte, int tailleTexte){
	 /* temps en micro-secondes */
	clock_t initial_time, final_time;
	/* temps en secondes */
	float cpu_time;	
	int occurence  = 0;
	//Recuperation du temps passe dans le programme.
	initial_time = clock();
	
	Trie TrieMixte = preAhoCorassickTrieMixte(Liste_Mot, Nbr_Mot);
		
	int j;
	int e = 0;
	for(j = 0; j < tailleTexte; j++){
		while(Chercher_Caracter(Texte[j], e, TrieMixte) == -1)
			e = TrieMixte->suppleance[e];
		
		e = Chercher_Caracter(Texte[j], e, TrieMixte);
		//printf("resultat recherche %d\n",e);
			if(TrieMixte->finite[e] != 0){
			occurence += TrieMixte->finite[e];
		}
		
	}
	final_time = clock();
	cpu_time = (final_time - initial_time) * 1e-6;
	printf("AC-MIXTE - Nombre d\'occurences : %d\n", occurence);
	printf("Le temps d'exécution est: %f s\n", cpu_time);
	
	
}

/*
 la fonction qui existe dans le cours : ac.pdf , page 10 */
Trie preAhoCorassickTrieMixte(char ** Liste_Mot, int Nbr_Mot){
	int i;
	
	// somme des mots de X
	int maxNode = 0;
	for(i = 0; i < Nbr_Mot; i++)
		maxNode += strlen(Liste_Mot[i]);
	maxNode += 1;
	
	Trie TrieMixte = createTrieMixte(maxNode);
	
	// insertion des mots de x dans le trie
	for(i = 0; i < Nbr_Mot; i++){
		addInTrieMixte(TrieMixte, Liste_Mot[i]);
	}
	
	
	
	for(i = 0; i < size_alphabet; i++){
		if(Chercher_Caracter(i , 0, TrieMixte) == -1)
			addCaracter(0, i, 0, TrieMixte);
	}
	
	completeTrieMixte(TrieMixte);
	
	return TrieMixte;
}

/* constructeur */
//Cette fonction a pour but d’initialiser notre structure trie a partir 
//de nbr de lettre qu’on a envoyer
Trie createTrieMixte(int maxNode){
	Trie New_Trie;
	New_Trie = (Trie) malloc(sizeof(struct _trie));
	
	New_Trie->maxNode = maxNode;
	New_Trie->nextNode = 1;
	
	New_Trie->finite = (char *) malloc(maxNode * sizeof(char));
	New_Trie->transitionRoot = (int*) malloc(size_alphabet * sizeof(int));
	New_Trie->transitionOthers = (List *) malloc(maxNode * sizeof(struct _list));
	New_Trie->suppleance = (int*) malloc(maxNode * sizeof(int));
	
	int i;
	for(i = 0; i < maxNode; i++){
		New_Trie->suppleance[i] = 0;
		New_Trie->finite[i] = 0;
	}
	
	for(i = 0; i < maxNode - 1; i++){
		New_Trie->transitionOthers[i] = NULL;
	}
	
	for(i = 0; i < size_alphabet; i++){
		New_Trie->transitionRoot[i] = -1;
	}
	
	return New_Trie;
}

/* ajouter mot dans le trie */
void addInTrieMixte(Trie TrieMixte, char *Mot){
	int i,j,courant = 0;

	int Mot_size = strlen(Mot);
	
	// si le mot est non vide 
	if(Mot_size > 0){
		// creation  d'un nouveau etat
		if(TrieMixte->transitionRoot[Mot[0]] == -1){// si c’est la racine 
			// on récupere l’Indice du prochain noeud disponible
			TrieMixte->transitionRoot[Mot[0]] = TrieMixte->nextNode;
			courant = TrieMixte->nextNode;
			TrieMixte->nextNode++;
			
			// ajouter chaque caractère
			for(i = 1; i < Mot_size; i++){
				addCaracter(TrieMixte->nextNode, Mot[i], courant, TrieMixte);
				courant = TrieMixte->nextNode;
				// on incrémente l’Indice du prochain noeud disponible
				TrieMixte->nextNode++;
				
				// si c'est la fin du mot alors finite prend 1
				if(i == Mot_size - 1){
					TrieMixte->finite[courant] = 1;
				}
			}
		}else{
			courant = TrieMixte->transitionRoot[Mot[0]];
			// ajouter chaque caractère a notre structure du mixte
			for(i = 1; i < Mot_size; i++){
				if(TrieMixte->transitionOthers[courant - 1] != NULL 
				&& (Chercher_Caracter(Mot[i], courant, TrieMixte) != -1) ){
					courant = Chercher_Caracter(Mot[i], courant, TrieMixte);
				}else{
					// creation d'un nouveau etat
					for(j = i; j < Mot_size; j++){
						//  trie→nextNode :Indice du prochain noeud disponible+1
						//w[i]:un caractère de notre liste de mot
						// courant : Indice du prochain noeud disponible
						// trie:notre structure du mixte
						addCaracter(TrieMixte->nextNode, Mot[j], courant, TrieMixte);
						courant = TrieMixte->nextNode;
						TrieMixte->nextNode++;
						
						// si c'est la fin du mot alors finite prend 1 
						if(j == Mot_size - 1){
							TrieMixte->finite[courant] = 1;
						}
					}
					return;
				}
			}
			TrieMixte->finite[courant] = 1;
		}
	}
}

/* ajouter caractère */
void addCaracter(int targetNode, unsigned char letter, int next, Trie TrieMixte){
	// si c'est la racine
	if(next == 0){
		TrieMixte->transitionRoot[letter] = targetNode;
	}else{
		List liste_chainee = (List) malloc(sizeof(struct _list));
		liste_chainee->targetNode = targetNode;
		liste_chainee->letter = letter;
		liste_chainee->next = TrieMixte->transitionOthers[next - 1];
		TrieMixte->transitionOthers[next - 1] = liste_chainee;
	}
}

/* chercher caractère dans le trie */
int Chercher_Caracter(unsigned char caracter, int target, Trie TrieMixte){
	//on déclare une liste
	List liste_chainee = (List) malloc(sizeof(struct _list));
	//on lui affecte létat de transition
	liste_chainee = TrieMixte->transitionOthers[target - 1];
	
	//si le curseur courant == 0
	if(target == 0){
		return TrieMixte->transitionRoot[caracter];
	}
	
	/* si il n'y a pas de transition */
	if(liste_chainee == NULL){
		return -1;
	}
	
	/* si la première lettre == c */
	if(liste_chainee->letter == caracter){
		return liste_chainee->targetNode;
	}
	
	//boucle de recherche profonde
	while(liste_chainee->next != NULL){
		liste_chainee = liste_chainee->next;
		if(liste_chainee->letter == caracter){
			return liste_chainee->targetNode;
		}
	}
	
	return -1;
}

 
//la fonction qui existe dans le cours : ac.pdf , page 12

void completeTrieMixte(Trie TrieMixte){
	//on declare un fichier
	File file = NULL;
	//on declare une structure Transitions
	Transitions transitions = NULL;
	/* retourne la liste des etats des transitions dans le trie */
	transitions = transitionsMixte(TrieMixte, 0, transitions);
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
		transitions = transitionsMixte(TrieMixte, r, transitions);
		while(transitions != NULL){
			r = transitions->debut;
			a = transitions->lettre;
			p = transitions->fin;
			transitions = transitions->suivant;
			file = enfiler(file, p);
			s = TrieMixte->suppleance[r];
			while(Chercher_Caracter(a , s, TrieMixte) == -1){
				s = TrieMixte->suppleance[s];
			}
			
			TrieMixte->suppleance[p] = Chercher_Caracter(a , s, TrieMixte);
             if(TrieMixte->finite[Chercher_Caracter(a, s, TrieMixte)]==1)
				TrieMixte->finite[p] = TrieMixte->finite[p]+1;		
		}
	}
	
	
}

/* retourne la liste des etats des transitions dans le trie */
Transitions transitionsMixte(Trie TrieMixte, int etat, Transitions transitions){
	int i;
	for(i = 0; i < size_alphabet; i++){
		if(etat == 0 && TrieMixte->transitionRoot[i] != 0 && TrieMixte->transitionRoot[i] != -1){
			transitions = insertIntoTransitions(etat, i, TrieMixte->transitionRoot[i], transitions);
		}else{
			if(etat != 0 && Chercher_Caracter(i , etat, TrieMixte) != -1){
				transitions = insertIntoTransitions(etat, i, Chercher_Caracter(i , etat, TrieMixte), transitions);
			}
		}
		
	} 
	return transitions;
}


/* inserer dans une transition */
Transitions insertIntoTransitions(int debut, unsigned char valeur, int fin, Transitions transitions){
	Transitions temp = (Transitions) malloc(sizeof(struct _transitions));
	temp->debut = debut;
	temp->lettre = valeur;
	temp->fin = fin;
	temp->suivant = transitions;
	return temp;
}

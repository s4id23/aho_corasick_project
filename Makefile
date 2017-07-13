CC = gcc
all : executable/main_liste.c traitement/liste.c executable/main_matrice.c traitement/matrice.c executable/main_mixte.c traitement/mixte.c traitement/file.c traitement/file_matrice.c
	$(CC) -o document_teste/ac-liste executable/main_liste.c traitement/liste.c traitement/file.c -w
	$(CC) -o document_teste/ac-matrice executable/main_matrice.c traitement/matrice.c traitement/file.c traitement/file_matrice.c -w
	$(CC) -o document_teste/ac-mixte executable/main_mixte.c traitement/mixte.c traitement/file.c -w
	gcc generateur/genTexte.c -o document_teste/genere-texte
	gcc generateur/genMot.c -o document_teste/genere-mots

file.o : bibliotheque/file.h traitement/file.c
	$(CC) -c file.c

file_matrice.o : bibliotheque/file.h traitement/file_matrice.c
	$(CC) -c file_matrice.c

clean : 
		rm -rf *.o
		rm -rf *.gch

mrproper : clean
		rm -rf liste
		rm -rf matrice
		rm -rf mixte
		rm -rf file
		



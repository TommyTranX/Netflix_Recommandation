                                                                    //-----------------------PROJET C---------------------------//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"Question1.h"
#include"Question2.h"
#include"Question4.h"
#include"Question5.h"
#include"Question6.h"

  //MAIN

int main(int argc, char* argv[]){

	printf("\n\nBienvenue dans Dauphilme, le meilleur algorithme de suggestion de film sur le marche.\n\n");

  //INITIALISATION DES VARIABLES

	Cell** Movies = calloc(17771,sizeof(Cell)); //We add one because we didn't want to put a minus one everywhere
	if(Movies==NULL) return 1;
	Cell** Users = calloc(2649430,sizeof(Cell));
	if(Users==NULL) return 1;

  //OUVERTURES D(U)(ES) FICHIER(S)

	if(argc <= 1){
		printf("Vous avez lance l'application sans aucun fichier, reommencez le processus avec un (ou plusieurs) fichier(s).");
		return 1;
	}

  int i, nb_Cells = 0;
	FILE* file;
  for(i=1; i<argc ; i++){ //Begins at one because the first one is the instruction ./a.out
		printf("Chargement du fichier %s...\n\n", argv[i]);
    file = fopen(argv[i], "r"); //file is not in capital letters so there is no problem.
    if(file == NULL){
      printf("L'ouverture du fichier \"%s\" a echoue.", argv[i]);
      return 1;
    }

    nb_Cells = nb_Cells + Reading(file, Users, Movies);

    fclose(file);
  }

	printf("Fichiers ouverts avec succes.\n\n");

	//ZONE DE TESTS

printf("					<------- MENU ------->\n\n");
	printf("		1 : Recherche des voisins.\n\n");
	printf("		2 : Reco2.\n\n");
	printf("		3 : Reco3.\n\n");
	printf("		4 : Reco4.\n\n");
	printf("		5 : Creation d'une image PGM.\n\n");
	printf("		6 : Estimation de note.\n\n");
	printf("		7 : Test d'erreur.\n\n");
	printf("		8 : Quitter le menu.\n\n");
printf("					<-------------------->\n\n");
	printf(" 			   Faites votre choix : ");
	int choice;
	scanf("%d", &choice);
	while(choice<1 || choice>8){
		printf("\n\nVous devez choisir une option en ecrivant 1 pour Recherche des voisins par exemple : ");
		scanf("%d", &choice);
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

int id, nb_Neighbours, FocusedMovie, nb_movies;
float percent;
char* NameFile="";
if(choice==1){

	printf("Votre Id : ");
	scanf("%d", &id);
	printf("\n\nLe nombre de voisins : ");
	scanf("%d", &nb_Neighbours);

	List* Neighbours = ResearchNeighbours(Users, id , nb_Neighbours);
	if(Neighbours==NULL){
		printf("Cet utilisateur n'existe pas dans la base de donnee.\n");
		return 0;
	}
	Neig* n = Neighbours->begining;
	printf("Voisins :\n");
	while(n!=NULL){
		printf("L'utilisateur numero %d avec sim : %f.\n", n->use->idUser, n->sim);
		n = n->next;
	}

	FreeAllList(Neighbours);
}

else if(choice==2){

	printf("Votre Id : ");
	scanf("%d", &id);
	printf("\n\nLe nombre de voisins : ");
	scanf("%d", &nb_Neighbours);

	List* Neighbours = ResearchNeighbours(Users, id , nb_Neighbours);
	if(Neighbours==NULL){
		printf("Cet utilisateur n'existe pas dans la base de donnee.\n");
		return 0;
	}
	Neig* n = Neighbours->begining;
	printf("Voisins :\n");
	while(n!=NULL){
		printf("L'utilisateur numero %d avec sim : %f.\n", n->use->idUser, n->sim);
		n = n->next;
	}

	ListAdvice* Advices = SecondReco(Users, Movies, Neighbours, id);
	ListAdvice* la = Advices;
	printf("Films suggeres :\n");
	while(la!=NULL){
		printf("Le film numero %d avec note estimee : %f.\n", la->movie, la->estimation);
		la = la->NextA;
	}

	FreeAllList(Neighbours);
}

else if(choice==3){

	printf("Le fichier a remplir : ");
	scanf("%s", NameFile);

	FILE* f_input = fopen(NameFile, "r");
	FILE* f_out = fopen("f_out.txt", "w");
	ThirdReco(Users, f_input, f_out);
	fclose(f_input);
	fclose(f_out);

}

else if(choice==4){

	printf("Le nombre de films a noter : ");
	scanf("%d", &nb_movies);

	FILE* f = fopen("movie_titles.csv", "r");
	if(f==NULL){
		return 0;
	}
	FourthReco(f, Movies, Users, nb_movies);
	fclose(f);

}

else if(choice==5){
	printf("En cours de developpement.\n");
}

else if(choice==6){

	printf("Votre Id : ");
	scanf("%d", &id);
	printf("\n\nLe film dont vous voulez l'estimation : ");
	scanf("%d", &FocusedMovie);
	printf("\n\nLe nombre de voisins sur lesquels baser l'estimation : ");
	scanf("%d", &nb_Neighbours);

	List* Neighbours = ResearchNeighbours(Users, id , nb_Neighbours);
	if(Neighbours==NULL){
		printf("Cet utilisateur n'existe pas dans la base de donnee.\n");
		return 0;
	}
	printf("\n\nLa note estimee pour le film %d est de : %f", FocusedMovie, FirstReco(Neighbours, FocusedMovie));

	FreeAllList(Neighbours);
}

else if(choice==7){

	printf("%dQuel pourcentage (entre 0 et 1) a cacher : ", nb_Cells);
	scanf("%f", &percent);
	while(percent<=0 || percent>10){
		printf("\n\nQuel pourcentage (entre 0 et 1) a cacher : ");
		scanf("%f", &percent);
	}
	printf("\n\n Le nombre de voisins sur lesquels baser l'estimation : "); //Not too much
	scanf("%d", &nb_Neighbours);

	//This option is really slow.
	printf("L'erreur d'eleve a %f pourcents.\n\n", ErrorComputation(Users, floor((percent*nb_Cells)/100), nb_Neighbours));
}

else if(choice==8){
	printf("Vous nous quittez deja ?!\n\n");
}

  //LIBERATION DE LA MEMOIRE

  FreeAllTab(Movies, 17771);
  FreeAllTab(Users, 2649430);

	printf("\n\nMerci d'avoir choisi Dauphilme.\n");

	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include"Question1.h"
#include"Question2.h"
#include"Question4.h"
#include"Question5.h"

#define ADVICE_RANGE 10
#define NB_NEIG 10 //ThirdReco and FourthReco

ListAdvice* InitListAdvice(int m, double note){
  ListAdvice* l = malloc(sizeof(ListAdvice));
  if(l==NULL) return NULL;
  l->estimation = note;
  l->movie = m;
  l->NextA = NULL;
  return l;
}

  //SPECIFIC FUNCTIONS

int CountNotes(Cell* Movies[], int movie){
  int nb_notes = 0;
  Cell* p = Movies[movie];
  while(p!=NULL){
    nb_notes++;
    p = p->NextU;
  }

  return nb_notes;
}

void FourthReco(FILE* f, Cell* Movies[], Cell* Users[], int nb_movies){ //nb_movies is the limit of films the user notes
  int* FamousMovies = calloc(nb_movies+1, sizeof(int)); //coherance
  int* IdFamousMovies = calloc(nb_movies+1, sizeof(int));

  int min = CountNotes(Movies, 1);
  int id_min = 1;
  int j;
  for(j=1; j<=nb_movies ; j++){
    FamousMovies[j] = CountNotes(Movies, j);
    if(FamousMovies[j]<min){
      min = FamousMovies[j];
      id_min = j;
    }
    IdFamousMovies[j] = j;
  }

  for(int i=j; i<=17771 ; i++){
    int value = CountNotes(Movies, i);
    if(value > min){
      min = value;
      FamousMovies[id_min] = value;
      IdFamousMovies[id_min] = i;
      id_min = FindMin(FamousMovies, nb_movies);
    }
  }

  FillUser0(f, Users, Movies, FamousMovies, IdFamousMovies, nb_movies);

  List* NeighboursU = ResearchNeighbours(Users, 0, NB_NEIG); //A big number is no big deal because we do this only once
  if(NeighboursU==NULL){
    printf("Erreur interne.\n");
    return;
  }

  Neig* n = NeighboursU->begining;
	printf("Voisins :\n");
	while(n!=NULL){
		printf("L'utilisateur numero %d avec sim : %f.\n", n->use->idUser, n->sim);
		n = n->next;
	}

  ListAdvice* Advices = SecondReco(Users, Movies, NeighboursU, 0);
	ListAdvice* la = Advices; //Time to print
	printf("Films suggeres pour vous :\n");
	while(la!=NULL){
    char* word = GetNameMovie(f, la->movie);
		printf("Le film %s avec note estimee : %f.\n", word , la->estimation);
    free(word);
    free(la);
		la = la->NextA;
	}

  free(FamousMovies);
  free(IdFamousMovies);
  FreeAllList(NeighboursU);
}

void FillUser0(FILE* f, Cell* Users[], Cell* Movies[], int* FamousMovies, int* IdFamousMovies, int nb_movies){ //Because I take the identifier instead of the Cell directely
  int i;
  int value = 0;

  for(i=1; nb_movies>=i ; i++){
    char* word = GetNameMovie(f, IdFamousMovies[i]);
    printf("Donnez une note au film %s : ", word);
    scanf("%d", &value);
    while(value<1 || value>5){
      printf("La note doit se situer entre 1 et 5 : ");
      scanf("%d", &value);
    }
    free(word);

    Cell* new = InitCell(value, 0 , IdFamousMovies[i]);
    if(Users[0]==NULL){
      Users[0] = new;
    }
    else{
      new->NextM = Users[0];
      Users[0] = new;
    }

    //We need to insert in Movies because SecondReco takes Movies, not Users
    new->NextU = Movies[IdFamousMovies[i]]; //Movies[0] isn't null
    Movies[IdFamousMovies[i]] = new;

  }
}

void ThirdReco(Cell* Users[], FILE* f_input, FILE* f_out){
  int mov = 0, idUser = 0;
  int id = 0, nb_neighbours = NB_NEIG; //id is the identifier of the film we look for
  char* line = malloc(sizeof(char)*50);
  char* word = malloc(sizeof(char)*50);

  while(fgets(line, 50, f_input)!=NULL){

    mov = 0;

    int i = 0; //Get the identifier
    while(line[i]!='\n'){
      if(line[i]==':'){
        mov = 1;
				break;
      }
      else{
        word[i] = line[i];
      }
      i++;
    }
    word[i] = '\0';

  if(mov){
    id = atoi(word);
  }
  else{
    idUser = atoi(word);
  }

  fputs(word, f_out);

  if(!mov){
    List* L = ResearchNeighbours(Users, idUser, nb_neighbours);
    if(L==NULL){
      printf("Erreur interne.\n");
      return;
    }
    double rec = FirstReco(L, id);
    sprintf(word, "%f", rec); //Re-use of the word variable
    fputs(",", f_out);
    fputs(word, f_out);
  }
  else{
    fputs(":", f_out);
  }
  fputs("\n", f_out);

  }

  free(line);
  free(word);
}

ListAdvice* SecondReco(Cell* Users[], Cell* Movies[], List* NeighboursU, int u){
  int space = ADVICE_RANGE;
  ListAdvice* beg = NULL; //begining of the "list"

  int* NotesOfU = calloc(17771, sizeof(int)); //takes all the notes of U
  Cell* p = Users[u];
  while(p!=NULL){
    NotesOfU[p->idMovie] = p->note;
    p = p->NextM;
  }

  int i = 1;
  while(space && i<=17771){
    if(!NotesOfU[i]){
      double r = FirstReco(NeighboursU, i);
      ListAdvice* new = InitListAdvice(i, r);
      if(new==NULL) return NULL;
      new->NextA = beg;
      beg = new;
      space--;

      ListAdvice* previous = NULL;
      ListAdvice* l = beg; //That is to say new;
    	while(l->NextA!=NULL){
        if((l->NextA->estimation)<(new->estimation)){
          if(previous == NULL){
            beg = l->NextA;
            l->NextA = beg->NextA;
            beg->NextA = l;
            previous = beg;
          }
          else{
            previous->NextA = l->NextA;
            l->NextA = previous->NextA->NextA;
            previous->NextA->NextA = l;
            previous = previous->NextA;
          }
          continue;
        }
        break; //The list is organised now, we can leave the function
    	}
    }

    i++;
  }

  for(int j = i+1; j<=17771 ; j++){
    if(!NotesOfU[i]){
      double r = FirstReco(NeighboursU, j);
      if(r > (beg->estimation)){
        ListAdvice* new = InitListAdvice(j, r);
        if(new==NULL) return NULL;

        int inside = 0;
        ListAdvice* p = beg;
        while(inside==0 && p->NextA!=NULL){
          if(r < p->NextA->estimation){
            new->NextA = p->NextA;
            p->NextA = new;
            inside = 1;
          }
          p = p->NextA;
        }

        if(!inside){
          p->NextA = new;
        }

        free(beg); //We free the space pointed by beg, beg stays a viable variable
        beg = beg->NextA;
      }
    }
  }

  return beg;

}

double FirstReco(List* NeighboursU, int movie){ //We consider that u doesn't belong to the list, by the way, no need to have u in the arguments
  double SumWeight = 0; //"Somme pondérée"
  double SumSim = 0;

  Neig* p = NeighboursU->begining;
  while(p!=NULL){
    int Nn = NeighboursNote(p->use, movie);
    SumWeight = SumWeight + (p->sim)*Nn;
    if(Nn!=0){
      SumSim = SumSim + fabs(p->sim);
    }
    p = p->next;
  }

  if(SumSim==0){
    return 0;
  }

  return SumWeight/SumSim;
}

  //COMMON FUNCTIONS

int NeighboursNote(Cell* Neighbour, int movie){ //Returns 0 if the Neighbour hasn't noted the movie
  Cell* p = Neighbour;
  while(p!=NULL){
    if(p->idMovie == movie){
      return p->note;
    }
    p = p->NextM;
  }

  return 0;
}

double Positive(double f){
  if(f<0){
    f = (-1)*f;}
  return f;
}

int FindMin(int* tab, int length){ //tab contains only positive numbers
  int min = tab[1], id_min = 0;
  for(int i=1; i<=length ; i++){
    if(tab[i]<min){
        min = tab[i];
        id_min = i;
    }
  }

  return id_min;
}

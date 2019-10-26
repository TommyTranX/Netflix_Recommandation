
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"Question1.h"

Cell* InitCell(int n, int U, int M){
	Cell* m = malloc(sizeof(Cell));
	if(m==NULL){
		return NULL;
	}
	m->note = n;
	m->idMovie = M;
	m->idUser = U;
	m->NextU = NULL;
	m->NextM = NULL;
	return m;
}

//FREE FUNCTIONS

void FreeAllTab(Cell* tab[], int length){
  for(int i=0; length-i ; i++){ //Begins at 0 because we have to be careful and FourthReco Fills the User 0
    free(tab[i]);
  }
  free(tab);
}

//SPECIFIC FUNCTIONS

void FillTabs(Cell* Users[], Cell* Movies[], int note, int idUser, int idMovie){
  Cell* new = InitCell(note, idUser, idMovie);
  if(new == NULL) return;

  if(Users[idUser]!=NULL){
    new->NextM = Users[idUser];
    Users[idUser] = new;
  }
	else{Users[idUser] = new;}

  if(Movies[idMovie]!=NULL){
    new->NextU = Movies[idMovie];
    Movies[idMovie] = new;
	}
	else{Movies[idMovie] = new;}
}

int Reading(FILE* file, Cell* Users[], Cell* Movies[]){ //Do not forget to free line and word
  int mov = 0, note = 0, idUser = 0; //mov : 1 if we get a movie, 0 either
  int id = 0; //No need of static
	int nb_Cells = 0;
  char* line = malloc(sizeof(char)*50);
  char* word = malloc(sizeof(char)*50);

  while(fgets(line, 50, file)!=NULL){

		mov = 0;

    int i = 0; //Get the identifier
    int k = 0;
    while(line[i]!='\0'){
      if(line[i]==':'){
        mov = 1;
				break;
      }
      else if(line[i]==',')break;
      else{
        word[k] = line[i];
        k++;
      }
      i++;
    }
    word[k] = '\0'; //Is it necessary ?

	  if(mov){
	    id = atoi(word); //Do we need atol ?
		}
		else{
	    note = line[i+1] - '0'; //Translation char -> int with a digit
	    idUser = atoi(word);
	  }

	  if(!mov){
			nb_Cells++;
	    FillTabs(Users, Movies, note, idUser, id);
	  }

	}

	free(line);
  free(word);

  return nb_Cells;
}

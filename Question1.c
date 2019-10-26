#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
//#include"Question1.h"

/*Cell* InitCell(int n, int U, int M){
	Cell* m = malloc(sizeof(Cell));
	if(m==NULL){
		printf("Probleme d'initialisation.\n");
		return NULL;
	}
	m->note = n;
	m->idMovie = M;
	m->idUser = U;
	m->NextU = NULL;
	m->NextM = NULL;
	return m;
}

//FONCTIONS USUELLES

void FreeAllTab(Cell* tab[], int length){
  for(int i=0; length-i ; i++){
    free(tab[i]);
  }
  free(tab);
}

void InsertUser(Cell* begining, Cell* c){ //Insert the cell at its proper place
  if(c->idMovie <= 0 || c->idUser <= 0) return; //ADD an error message.
	Cell* previous = NULL;
	Cell* p = begining;
  while(p->NextM!=NULL){
    if((c->idMovie)<(p->idMovie)){
			c->NextM = previous->NextM;
			previous->NextM = c; //previous is no longer NULL because we have already tested this in FillTabs
			return;
    }
		previous = p;
    p = p->NextM;
  }
	if((c->idMovie)<(p->idMovie)){ //One last time
		c->NextM = previous->NextM;
		previous->NextM = c;
		return;
	}
	p->NextM = c;
}

void InsertMovie(Cell* begining, Cell* c){ //Insert the cell at its proper place
  if(c->idMovie <= 0 || c->idUser <= 0) return; //ADD an error message.
	Cell* previous = NULL;
	Cell* p = begining;
  while(p->NextU!=NULL){
    if((c->idUser)<(p->idUser)){
			c->NextU = previous->NextU;
			previous->NextU = c; //previous is no longer NULL because we have already tested this in FillTabs
			return;
    }
		previous = p;
    p = p->NextU;
  }
	if((c->idUser)<(p->idUser)){ //One last time
		c->NextU = previous->NextU;
		previous->NextU = c;
		return;
	}
	p->NextU = c;
}

//FONCTIONS SPECIFIQUES

void FillTabs(Cell* Users[], Cell* Movies[], int note, int idUser, int idMovie){
  Cell* p = InitCell(note, idUser, idMovie);
  if(p == NULL) return;

  if(Users[idUser]==NULL) {Users[idUser] = p;} //printf("1New noteur.\n");}
  else{
    if((Users[idUser]->idMovie)>(p->idMovie)){ //p becomes the begining Movie for User n°idUser
			//printf("2New noteur.\n");
			p->NextM = Users[idUser];
      Users[idUser] = p;
    }
    else{
			//printf("3New noteur.\n");
			InsertUser(Users[idUser], p);
		 }
  }

  if(Movies[idMovie]==NULL) {Movies[idMovie] = p;} //printf("1New film.\n");}
  else{
		if((Movies[idMovie]->idUser)>(p->idUser)){ //p becomes the begining User for Movie n°idMovie
			//printf("2New film.\n");
      p->NextU = Movies[idMovie];
      Movies[idMovie] = p;
    }
    else{
      InsertMovie(Movies[idMovie], p);
			//printf("3New film.\n");
		}
	}
}

int Reading(FILE* file, Cell* Users[], Cell* Movies[]){ //Do not forget to free line and word
  int mov = 0, note = 0, idUser = 0; //mov : 1 if we get a movie, 0 either
  int id = 0; //No need of static
  char* line = malloc(sizeof(char)*50);
  char* word = malloc(sizeof(char)*50);

  while(fgets(line, 50, file)!=NULL){
		//printf("Nous sommes la, ligne vaut : %s\n", line);
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
			//printf("On a le film numero : %d\n", id);
		}
		else{
	    note = line[i+1] - '0'; //Translation char -> int with a digit
	    idUser = atoi(word);
	  }

	  if(!mov){
			//printf("Nous avons l'utilisateur %d qui a note %d le film %d\n", idUser, note, id);
	    FillTabs(Users, Movies, note, idUser, id);
	  }

  //fgetc(file); //Because of the '\n'
	}

	free(line);
  free(word);

  return 1;
}
*/

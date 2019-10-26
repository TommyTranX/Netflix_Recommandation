#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include"Question1.h"
#include"Question2.h"

  //FREE FUNCTIONS

void FreeAllList(List* L){
  Neig* N = L->begining;
  for(int i=0; (L->length)-i ; i++){
    Neig* K = N;
    N = N->next;
    free(K);
  }
  free(L);
}

  //INITIALISATION FUNCTIONS

List* InitList(int l){
  List* L = malloc(l*sizeof(List));
  if(L==NULL) return NULL;
  L->length = 0;
  L->begining = NULL;
  return L;
}

Neig* InitNeig(Cell* m, double S){
  Neig* Li = malloc(sizeof(Neig));
  if(Li==NULL) return NULL;
  Li->use = m;
  Li->sim = S;
  Li->next = NULL;
  return Li;
}

  //SPECIFIC FUNCTIONS

List* ResearchNeighbours(Cell* Users[], int u, int k){ //Same aruments as the question
  if(Users[u]==NULL) return NULL;

  int SumU = 0;
  int* NotesOfU = calloc(17771, sizeof(int)); //takes all the notes of U
  Cell* p = Users[u];
  while(p!=NULL){
    NotesOfU[p->idMovie] = p->note;
    SumU = SumU + p->note;
    p = p->NextM;
  }

  List* N = InitList(k+1); //Initialisation of Neighbours, k+1 because we count u. u will be kicked afterwards
  if(N==NULL) return NULL;

  int j=1;
  while(Users[j]==NULL){ //Find the first non-NULL
    j++;
  }
  Neig* SimN = InitNeig(Users[j], BasicCosinus(Users, j, NotesOfU, SumU));
  if(SimN==NULL) return NULL;
  N->begining = SimN;
  N->length++;

  double sim = 0;
  for(int i = j+1; 2649430-i ; i++){
    if(Users[i]==NULL) continue;
    sim = BasicCosinus(Users, i, NotesOfU, SumU);
    InsertNeighbour(N, sim, Users[i], u, k+1);
  }

  free(NotesOfU);

  int old_length = N->length; //Let us kick U if it is in it (it is not a necessity)
  Neig* n = N->begining;
  while(n->next!=NULL){
    if(n->next->use->idUser==u){
      n->next = n->next->next; //Et le free ?
      N->length--;
      break; //To avoid the segmentation fault
    }
    n = n->next;
  }

  if(old_length==N->length){
    N->begining = N->begining->next; //if u is the first it works also
    N->length--;
  }


  return N;
} //Do not forget to free N after using it

void InsertNeighbour(List* N, double Sim, Cell* User, int u, int k){ //N is organised

  int space = (N->length==k) ? 1 : 0; //1 if there is no space
  if(Sim <= (N->begining->sim)){
    return;
  }
  else if(!space){
      Neig* m = InitNeig(User, Sim);
      if(m==NULL) return;
      m -> next = N->begining;
      N->begining = m;
      N->length++;

      Neig* previous = NULL;
      Neig* n = N->begining; //That is to say m;
    	while(n->next!=NULL){ //m has to be at its proper place
        if((n->next->sim)<(n->sim)){
          if(previous == NULL){
            N->begining = n->next;
            n->next = N->begining->next; //That is to say n->next->next
            N->begining->next = n;
            previous = N->begining;
          }
          else{
            previous->next = n->next;
            n->next = previous->next->next; //That is to say n6>next->next
            previous->next->next = n;
            previous = previous->next;
          }
          continue;
        }
        break;
    	}
    }

  int inside = 0;
  Neig* m = InitNeig(User, Sim);
  if(m==NULL) return;
  Neig* p = N->begining;
  while(p->next!=NULL){
    if((m->sim)<(p->next->sim)){
      m->next = p->next;
      p->next = m; //previous is != NULL
      inside = 1;
      break;
    }
    p = p->next;
  }

  if(!inside){ //One last time, if m is not already in the list
    p->next = m;
  }

  free(N->begining);
  N->begining = N->begining->next; //works

}

  //COMMON FUNCTIONS

double BasicCosinus(Cell* Users[], int X, int* NotesOfU, int SumU){ //With the minus 3

  double SumX = 0;
  double SumBoth = 0; //Because we don't want to have a "division entiere"

  Cell* User = Users[X];
  while(User!=NULL){
    SumX = SumX + User->note;
    if(NotesOfU[User->idMovie]){
        SumBoth = SumBoth + NotesOfU[User->idMovie];
    }
    User = User->NextM;
  }

  //Case deno == 0 not possible.
  return (SumBoth)/sqrt(SumU*SumX);

}

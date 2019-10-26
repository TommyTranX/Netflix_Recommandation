#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include"Question1.h"
#include"Question2.h"
#include"Question4.h"
#include"Question5.h"

double ErrorComputation(Cell* Users[], int length, int k){ //lenght is an integer portion of 17770

  Cell** HidenTab = malloc(length*sizeof(Cell));

  printf("On va en cacher %d.\n", length);

  for(int i = 0; i<=length ;i++){ //We only kick the Cell from Users, not Movies. Really quick.
    int j = rand()%17770 + 1; //Impossible to be 0.
    while(Users[j]==NULL){
      j = rand()%17770 + 1;
    }
    HidenTab[i] = Users[j]; //We take the begining instead of searching any Cell
    Users[j] = Users[j]->NextM;
  }

  printf("Cache reussi.\n");

  double error = 0;
  double estim;
  for(int i = 0 ; i<=length ; i++){
    List* L = ResearchNeighbours(Users, HidenTab[i]->idUser, k); //L is not NULL by definition.
    if(L==NULL) continue;
    printf("On a l'utilisateur %d sur le film %d\n", HidenTab[i]->idUser, HidenTab[i]->idMovie);
    estim = FirstReco(L, HidenTab[i]->idMovie);
    error = error + (HidenTab[i]->note - estim)*(HidenTab[i]->note - estim);
    FreeAllList(L);
  }

  for(int i = 0; i<=length ; i++){
    Users[HidenTab[i]->idUser] = HidenTab[i]; //HidenTab[i] is already linked to the begining
    //Therefore, even if Users[HidenTab[i]->idUser] is NULL (or not), both work
  }

  free(HidenTab); //Don't free the entire Tab !

  return sqrt(error/length);

}

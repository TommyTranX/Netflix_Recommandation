#ifndef QUESTION1_H
#define QUESTION1_H

//STRUCTURES ET METHODES

struct cell{
  struct cell* NextU; //Next user for the same movie
  struct cell* NextM; //Next user for the same user
  int note;
  int idUser;
  short idMovie; //We could have used a short
};
typedef struct cell Cell;

Cell* InitCell(int n, int U, int M);
void FreeAllTab(Cell* tab[], int length);
void InsertUser(Cell* begining, Cell* c);
void InsertMovie(Cell* begining, Cell* c);
void FillTabs(Cell* Users[], Cell* Movies[], int note, int idUser, int idMovie);
int Reading(FILE* file, Cell* Users[], Cell* Movies[]);

#endif

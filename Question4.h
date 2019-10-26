#ifndef QUESTION4_H
#define QUESTION4_H

typedef struct listAdvice{
  int movie;
  double estimation;
  struct listAdvice* NextA; //for next advice
}ListAdvice;

double FirstReco(List* NeighboursU, int movie);
ListAdvice* SecondReco(Cell* Users[], Cell* Movies[], List* NeighboursU, int u);
void ThirdReco(Cell* Users[], FILE* f_input, FILE* f_out);
void FourthReco(FILE* f, Cell* Movies[], Cell* Users[], int nb_movies);
ListAdvice* InitListAdvice(int m, double note);
int NeighboursNote(Cell* Neighbour, int movie);
void FillUser0(FILE* f, Cell* Users[], Cell* Movies[], int* FamousMovies, int* IdFamousMovies, int nb_movies);
double Positive(double f);
int CountNotes(Cell* Movies[], int movie);
int FindMin(int* tab, int length);

#endif

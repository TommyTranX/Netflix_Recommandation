#ifndef QUESTION2_H
#define QUESTION2_H

struct neighbour{ //We chose not to include the id of the user we look for within the structur
  Cell* use;
  double sim;
  struct neighbour* next;
};
typedef struct neighbour Neig;

struct list{ //Too specific
  Neig* begining;
  int length;
};
typedef struct list List;

void FreeAllList(List* L);
List* InitList(int l);
Neig* InitNeig(Cell* m, double S);
List* ResearchNeighbours(Cell* Users[], int u, int k);
void InsertNeighbour(List* N, double Sim, Cell* User, int u, int k);
double BasicCosinus(Cell* Users[], int X, int* NotesOfU, int SumU);

#endif

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"Question1.h"
#include"Question2.h"
#include"Question4.h"

char* GetNameMovie(FILE* f, int movie){

  int comas = 0, id = 0;
  char* line = malloc(sizeof(char)*200);
  char* word = malloc(sizeof(char)*200);
  char* number = malloc(sizeof(char)*50);

  while(fgets(line, 200, f)!=NULL){

    comas = 0; //!!!!!

    int i = 0; //Get the identifier
    while(comas==0 && line[i]!='\n'){
      if(line[i]==','){
        comas++;
      }
      else{
        number[i] = line[i];
        i++;
      }
    }
    number[i]='\0';

    id = atoi(number);

    if(id != movie){
      continue;
    }

    i++; //Skip the coma
    while(comas==1){
      if(line[i]==','){
        comas++;
      }
      i++;
    }

    int j = 0;
    while(line[i]!='\n'){
      word[j] = line[i];
      i++;
      j++;
    }
    word[j] = '\0';

  free(line);
  //free(word) is Impossible here because we return word
  free(number);

  rewind(f);

  //printf("** %s **\n", word);
  return word;
  }

  rewind(f);

  return NULL;
}

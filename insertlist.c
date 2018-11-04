#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/** Type definition for a tuple */
typedef struct tuple {
int32_t key;
int32_t payload;
}tuple;
/**
 * Type definition for a relation.
 * It consists of an array of tuples and a size of the relation.
 */
typedef struct relation {
  tuple  *tuples;
  uint32_t num_tuples;
}relation;

#define size 1024*1024/64

typedef struct result {
  int buffer[size][2];
  struct result* next;
  int c;
}result;

result* listAppend(result* ptr)
{
  result* newNode;
  newNode = (result*)malloc(sizeof(result));
  newNode->next = NULL;

  while(ptr->next!=NULL)
  {
    ptr = ptr->next;
  }

  ptr->next = newNode;

  return ptr->next;
}

result* createResult()
{
  result* rhj;
  rhj = (result*)malloc(sizeof(result));
  return rhj;
}

void insertResults(int Rid, int Sid, result* rhj)
{
  result* current = rhj;

  while(current->next != NULL){
    current = current->next;
  }

  if(current->c<size)
  {
    current->buffer[current->c][0] = Rid;
    current->buffer[current->c][1] = Sid;
    current->c++;
  }
  else
  {
    current = listAppend(current);
    current->c=0;
    insertResults(Rid, Sid, current);
  }
  return;
}

void printResults(result* rhj)
{
  while(rhj->next != NULL)
  {
    for(int i=0; i<size; i++)
    {
      printf("|%d  |  %d|\n", rhj->buffer[i][0], rhj->buffer[i][1]);
    }
    rhj = rhj->next;
  }
}

/** Radix Hash Join**/
result* RadixHashJoin(relation *relR, relation *relS);

int main(void){
  result* rhj;
  rhj = createResult();
  for(int i=0; i<size*2; i++){
    insertResults(1, 2, rhj);
  }
  printResults(rhj);
}

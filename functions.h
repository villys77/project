//
// Created by villys on 5/11/2018.
//

#ifndef PROJECT_FUNCTIONS_H
#define PROJECT_FUNCTIONS_H

#include "structs.h"
extern int num_of_matches;


result* listAppend(result*);
result* createResult();
void insertResults(int, int , result*);
void printResults(result*,int );
void free_list(result*);
int Number_used_for_hashing(int);
int H2 (int);
result * radish_hash_join(relation,int,relation,int);
uint64_t *loadRelation(char*);
int max_value(tuple *, int);
int min_value(tuple *, int);
endiamesiDomh* createEndiamesiDomh(int , int*);
int ReltionInMid(endiamesiDomh*, int, int);
relation* newRelation(endiamesiDomh*, int, int, relation*);
void FilterUpdate(endiamesiDomh*, int, int, result*, int, int*);
void queries_analysis(char*,struct data *);


#endif //PROJECT_FUNCTIONS_H

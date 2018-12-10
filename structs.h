//
// Created by villys on 5/11/2018.
//

#ifndef PROJECT_STRUCTS_H
#define PROJECT_STRUCTS_H

#include <stdint.h>
#define size 1024*1024/64

typedef struct tuple
{
    int32_t key;
    int32_t payload;
    int check;
}tuple;


typedef struct hist
{
    unsigned binary;
    unsigned count;
}hist;

typedef struct relation
{
    struct tuple *tuples;
    uint32_t num_tuples;
}relation;

typedef struct result
{
    int buffer[size][2];
    struct result* next;
    int c;

}result;

typedef struct data
{
    int num_tuples;
    int num_columns;
    int ** array;
    struct relation * relations ;
    int * min;
    int * max;
}data;


struct preds{
    int relation1; // h prwth sxesh
    int colum1; // h kolona apo thn prwth sxesh
    int relation2; // h deyterh sxesh
    int colum2; // h kolona apo thn deuterh sxesh
    int num;
    char op; //einai h praksi ('<','>','=')
};


#endif //PROJECT_STRUCTS_H

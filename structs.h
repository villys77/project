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

typedef struct relation {
    struct tuple *tuples;
    int num_tuples;
}relation;

typedef struct result {
    int buffer[size][2];
    struct result* next;
    int c;
}result;

#endif //PROJECT_STRUCTS_H

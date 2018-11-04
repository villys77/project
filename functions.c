//
// Created by villys on 5/11/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"

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

int Number_used_for_hashing(int num)
{
    int flag , i , j;

    for( i = num+1; i; i++)
    {

        flag=0;

        for(j = 2; j < i; ++j)
        {
            if(i % j == 0)
            {
                flag=1;
                break;
            }
        }

        if(flag == 0)
        {
            printf("next prime is:%d",i);
            return  i;
        }
    }
}

void H2 ( struct relation *table_index , int * bucket , int * chain, int M )
{
    int i , k ;
    for (i = 0; i <table_index->num_tuples; i++)
    {
        k = (table_index->tuples[i].payload % M);
        if (bucket[k] == -1)
        {
            bucket[k] = table_index->tuples[i].key;
            chain[table_index->tuples[i].key] = 0;
            //printf("grafw to %d sto %d me payload %d \n \n " , PinakasR[i].key, k, PinakasR[i].payload);
        }
        else
        {
            chain[table_index->tuples[i].key] = bucket[k];
            bucket[k] = table_index->tuples[i].payload;
            // printf("grafw sto %d \n",PinakasR[i].key);
            // printf ( " eixa to %d kai twra exw to %d \n" , chainR[PinakasR[i].key] ,BucketR[k]);
            //printf( " me payloads ta %d \n" , PinakasR[PinakasR[i].key].payload);
        }
    }
}


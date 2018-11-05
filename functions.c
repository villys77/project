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

void printResults(result* rhj,int num_of_matches)
{
    while(rhj!= NULL)
    {
        for(int i=0; i<size; i++)
        {
            if(i==num_of_matches)
            {
                return;
            }
            printf("|%d  |  %d|\n", rhj->buffer[i][0], rhj->buffer[i][1]);
        }
        num_of_matches-=size;
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
            return  i;
        }
    }
}

//Hashing method
int  H2 (int a)
{
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}



//
// Created by villys on 5/11/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "structs.h"
#include "functions.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define n 12

int num_of_matches;
int num_of_matches1;

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
    rhj = malloc(sizeof(result));
    rhj->next=NULL;
    rhj->c=0;
    return rhj;
}

void insertResults(int Rid, int Sid, result* rhj)
{
    result* current = rhj;

    while(current->next != NULL)
    {
        current = current->next;
    }

    if(current->c<size)
    {
        current->buffer[current->c][0] = Rid+1;
        current->buffer[current->c][1] = Sid+1;
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
    int i=0;
    while(rhj!= NULL)
    {
        for(i=0; i<size; i++)
        {
            if(i==num_of_matches)
            {
                return;
            }
            printf("|%d  |  %d|\n", rhj->buffer[i][0], rhj->buffer[i][1]);
        }
        if(num_of_matches>=size)
        {

            num_of_matches-=size;
        }
        rhj = rhj->next;

    }
}
////////////////////////////////////
result1* listAppend1(result1* ptr)
{
    result1* newNode;
    newNode = (result1*)malloc(sizeof(result1));
    newNode->next = NULL;

    while(ptr->next!=NULL)
    {
        ptr = ptr->next;
    }

    ptr->next = newNode;

    return ptr->next;
}

result1* createResult1()
{
    result1* list;
    list = malloc(sizeof(result1));
    list->next=NULL;
    list->c=0;
    return list;
}

void insertResults1(int Rid,result1* list)
{
    result1* current = list;

    while(current->next != NULL)
    {
        current = current->next;
    }

    if(current->c<size)
    {
        current->buffer[current->c]= Rid;
        //current->buffer[current->c][1] = Sid+1;
        current->c++;
    }
    else
    {
        current = listAppend1(current);
        current->c=0;
        insertResults1(Rid,current);
    }
    return;
}
void printResults1(result1* list,int num_of_matches1)
{
    int i=0;
    while(list!= NULL)
    {
        for(i=0; i<size; i++)
        {
            if(i==num_of_matches1)
            {
                return;
            }
            printf("%d\n", list->buffer[i]);
        }
        if(num_of_matches1>=size)
        {

            num_of_matches1-=size;
        }
        list = list->next;

    }
}

result1 * Equalizer(relation array,int b_size,int given_num,int given_mode)
{
    result1 * list=createResult1();
    //pairnw ena array kai prepei na to diatreksw olo wste na brw tis times pou einai megaluteres 'h mikroteres 'h ises apo kapoion ari8mo
    //orizw mode1 gia to = , mode 2 gia to > kai mode 3 gia to <
    num_of_matches1=0;
    int i;
    if(given_mode == 1)
    {
        for(i = 0 ; i < b_size; i++)
        {
            if(array.tuples[i].payload == given_num)
            {
                num_of_matches1++;
                insertResults1(array.tuples[i].key,list);
            }
        }
    }
    if(given_mode == 2)
    {
        for(i=0; i< b_size; i++)
        {
            if(array.tuples[i].payload > given_num)
            {
                num_of_matches1++;
                insertResults1(array.tuples[i].key,list);
            }
        }
    }
    if ( given_mode ==3)
    {
        for(i =0; i< b_size; i++)
        {
            if(array.tuples[i].payload < given_num)
            {
                num_of_matches1++;
                insertResults1(array.tuples[i].key,list);
            }
        }
    }
    return list;
    //printResults(list,num_of_matches);
}

void free_list1(result1 *list)
{
    result1 * current_node=list;

    while(current_node)
    {
        result1 * temp_next = current_node;
        current_node = current_node->next;
        free(temp_next);
    }

}

////////////////////////////////////
void free_list(result *rhj)
{
    result * current_node=rhj;

    while(current_node)
    {
        result * temp_next = current_node;
        current_node = current_node->next;
        free(temp_next);
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

int * select_pred(int total_preds , struct preds *my_preds)
{
    int* prio_array = malloc(total_preds*(sizeof(int)));
    int i,j,prio=0;
    int here = 0;
    for(i =0; i<total_preds; i++)
    {
        prio_array[i] = -1;
    }

    for(i =0; i<total_preds; i++)
    {
        if(my_preds[i].num != -1)
        {
            for(j=0; j<total_preds; j++)
            {
                if(i != j)
                {
                    //edw tsekarw an exw kapoia sugkrisi me ari9mo kai tsekarw an h sxesh epenalambanetai ths dinw proteraiothta
                    if(my_preds[i].relation1 == my_preds[j].relation1 || my_preds[i].relation1 == my_preds[j].relation2
                       || my_preds[i].relation2 == my_preds[j].relation1 || my_preds[i].relation2 == my_preds[j].relation2)
                    {
                        if(my_preds[i].prio == -1)
                        {
                            my_preds[i].prio = prio;
                            prio ++;
                            my_preds[j].prio = prio;
                            prio++;
                            continue;
                        }
                    }
                }
            }
        }
    }

    if(prio == 0)//den exw oute mia praksi tupou >,< ,=
    {
        for(i =0; i< total_preds; i++)
        {
            for(j=0; j<total_preds; j++)
            {
                if(i != j)
                {
                    //edw tsekarw an exw kapoia sugkrisi me ari9mo kai tsekarw an h sxesh epenalambanetai ths dinw proteraiothta
                    if(my_preds[i].relation1 == my_preds[j].relation1 || my_preds[i].relation1 == my_preds[j].relation2
                       || my_preds[i].relation2 == my_preds[j].relation1 || my_preds[i].relation2 == my_preds[j].relation2)
                    {
                        if(my_preds[i].prio == -1)
                        {
                            my_preds[i].prio=prio;
                            prio ++;
                            my_preds[j].prio=prio;
                            prio++;
                            continue;
                        }
                    }
                    else
                    {
                        if(my_preds[i].prio == -1)
                        {
                            my_preds[i].prio =prio;
                            prio++;
                            continue;
                        }
                    }
                }

            }
        }
    }
    for(i =0; i< total_preds; i++)
    {
        if(my_preds[i].prio == -1)
        {
            my_preds[i].prio = prio;
            prio++;
        }
    }
    for(i = 0; i< total_preds; i++)
    {
        for(j=0; j<total_preds; j++)
        {
            if(my_preds[j].prio == i)
            {
                prio_array[i]= j;
            }
        }
    }
    return prio_array;
}

result * radix_hash_join(relation array_R,int R_size,relation array_S,int S_size)
{
    int i=0,j=0;

    num_of_matches=0;
    result *rhj=createResult();///dhmiourgia listas pou 8a xrhsimopoihsw argotera sto teleutaio stadio gia na krataw ta apotelesmata moy

    int power = pow(2, n); /// 2^n (megethos pinakwn psum kai hist)
    int mask = power - 1; //// maska gia &

    //////////////////////////////////////////////////
    /////////FIRST HASHING



    ///////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////
    ////////HIST
    hist Hist_array_R[power];

    for (i = 0; i < power; i++)
    {
        Hist_array_R[i].binary = i;
        Hist_array_R[i].count = 0;
    }

    for (i = 0; i < R_size; i++)
    {
        for (j = 0; j < power; j++)
        {
            if ((array_R.tuples[i].payload & mask) == Hist_array_R[j].binary)
            {
                Hist_array_R[j].count++;
                break;
            }
        }
    }


    ///////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////
    //////////////PSUM
    hist Psum_R[power];
    for (i = 0; i < power; i++)
    {

        Psum_R[i].binary = i;
        if (i == 0)
        {
            Psum_R[i].count = 0;
        }
        else
        {
            Psum_R[i].count = Psum_R[i - 1].count + Hist_array_R[i - 1].count;
        }
    }

    //////////////////////////////////////////////////////////////////



    relation final_array_R;
    final_array_R.tuples= malloc(sizeof(struct tuple)*R_size);
    for(i=0; i<R_size; i++)
    {
        final_array_R.tuples[i].key=0;
        final_array_R.tuples[i].payload=0;
        final_array_R.tuples[i].check=0;
    }

    int where_R = 0;
    while (where_R < power)
    {
        if (where_R == power - 1) ///////pepiptwsh pou eimaste sthn teleytaia epanalh4h
        {
            for (i = Psum_R[where_R].count; i < R_size; i++)
            {
                for (j = 0; j < R_size; j++)
                {
                    if ((array_R.tuples[j].payload & mask) == where_R && (array_R.tuples[j].check == 0))
                    {
                        final_array_R.tuples[i].key = array_R.tuples[j].key;
                        final_array_R.tuples[i].payload = array_R.tuples[j].payload;
                        array_R.tuples[j].check = 1;
                        break;
                    }
                }
            }
            break;
        }
        else ///opoiadhpote endiamesh periptwsh
        {

            for (i = Psum_R[where_R].count; i < Psum_R[where_R + 1].count; i++)
            {
                for (j = 0; j < R_size; j++)
                {
                    if ((array_R.tuples[j].payload & mask) == where_R && (array_R.tuples[j].check == 0))
                    {
                        final_array_R.tuples[i].key = array_R.tuples[j].key;
                        final_array_R.tuples[i].payload = array_R.tuples[j].payload;
                        array_R.tuples[j].check = 1;
                        break;
                    }
                }
            }
        }

        where_R++;
    }


/////MEXRI EDW GIA TO R
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







    ////////////////////////////////////////////////////////
    ////////HIST
    hist Hist_array_S[power];

    for (i = 0; i < power; i++)
    {
        Hist_array_S[i].binary = i;
        Hist_array_S[i].count = 0;
    }

    for (i = 0; i <S_size; i++)
    {
        for (j = 0; j < power; j++)
        {
            if ((array_S.tuples[i].payload & mask) == Hist_array_S[j].binary)
            {
                Hist_array_S[j].count++;
                break;
            }
        }
    }


    /////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////
    //////////////PSUM
    hist Psum_S[power];
    for (i = 0; i < power; i++)
    {

        Psum_S[i].binary = i;
        if (i == 0)
        {
            Psum_S[i].count = 0;
        }
        else
        {
            Psum_S[i].count = Psum_S[i - 1].count + Hist_array_S[i - 1].count;
        }
    }
    //////////////////////////////////////////////////////////////////



    relation final_array_S;
    final_array_S.tuples= malloc(sizeof(struct tuple)*S_size);
    for(i=0; i<S_size; i++)
    {
        final_array_S.tuples[i].key=0;
        final_array_S.tuples[i].payload=0;
        final_array_S.tuples[i].check=0;
    }
    int where_S = 0;
    while (where_S <= power)
    {
        if (where_S == power - 1) ///////pepiptwsh pou eimaste sthn teleytaia epanalh4h
        {
            for (i = Psum_S[where_S].count; i < S_size; i++)
            {
                for (j = 0; j < S_size; j++)
                {
                    if ((array_S.tuples[j].payload & mask) == where_S && (array_S.tuples[j].check == 0))
                    {
                        final_array_S.tuples[i].key = array_S.tuples[j].key;
                        final_array_S.tuples[i].payload = array_S.tuples[j].payload;
                        array_S.tuples[j].check = 1;
                        break;
                    }
                }
            }
            break;
        }
        else ///opoiadhpote endiamesh periptwsh
        {

            for (i = Psum_S[where_S].count; i < Psum_S[where_S + 1].count; i++)
            {
                for (j = 0; j < S_size; j++)
                {
                    if ((array_S.tuples[j].payload & mask) == where_S && (array_S.tuples[j].check == 0))
                    {
                        final_array_S.tuples[i].key = array_S.tuples[j].key;
                        final_array_S.tuples[i].payload = array_S.tuples[j].payload;
                        array_S.tuples[j].check = 1;
                        break;
                    }
                }
            }
        }

        where_S++;
    }


////////MEXRI EDW S
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
    //////////exoune dhmiourghyhei oi pinakes R' kai S' ws final_array_R kai final_array_S
    ////////// kai apo dw kai katw ftiaxnoyme ta eurethria typou hash(bucket-chain)
    int next_prime;
    struct relation* table_index; // to table pou tha exei to hash table
    struct relation* table;
    int smaller_hist, bigger_hist;
    int size_of_table_to_hash;
    int size_of_other_table;
    int startSmaller , startBigger; // to shmeio apo to opoio tha ksekinhsw na koitaw to kathe ena bucket
    int *chain=NULL,  *bucket=NULL;
    int tuple_numR =0 , tuple_numS = 0;
    int flag;
    int hash_key;



    table_index = malloc(sizeof(struct relation));
    table_index->tuples=NULL;
    table_index->num_tuples=0;
    table = malloc(sizeof(struct relation));
    table->tuples=NULL;
    table->num_tuples=0;


    for ( i = 0; i<power; i++)
    {
        tuple_numR += Hist_array_R[i].count;
        tuple_numS += Hist_array_S[i].count;
    }

    for ( i = 0; i<power; i++)
    {

        if (Hist_array_R[i].count == 0 || Hist_array_S[i].count == 0)
        {
            continue;
        }
        if (Hist_array_R[i].count < Hist_array_S[i].count)
        {
            flag =0;
            table_index->tuples = malloc(tuple_numR *sizeof(tuple));
            table->tuples = malloc(tuple_numS * sizeof(tuple));

            int count;
            for (count = 0; count < tuple_numR; count++)
            {
                table_index->tuples[count].key = final_array_R.tuples[count].key;
                table_index->tuples[count].payload = final_array_R.tuples[count].payload;
            }
            for (count = 0; count < tuple_numS; count++)
            {
                table->tuples[count].key = final_array_S.tuples[count].key;
                table->tuples[count].payload = final_array_S.tuples[count].payload;
            }
            startSmaller = Psum_R[i].count;
            startBigger = Psum_S[i].count;

            size_of_table_to_hash = Hist_array_R[i].count;
            size_of_other_table = Hist_array_S[i].count;


        }
        else
        {
            flag = 1;
            int count;

            table_index->tuples = malloc(tuple_numS * sizeof(tuple));
            table->tuples = malloc(tuple_numR * sizeof(tuple));

            for (count = 0; count < tuple_numS; count++)
            {
                table_index->tuples[count].key = final_array_S.tuples[count].key;
                table_index->tuples[count].payload = final_array_S.tuples[count].payload;
            }
            for (count = 0; count < tuple_numR; count++)
            {
                table->tuples[count].key = final_array_R.tuples[count].key;
                table->tuples[count].payload = final_array_R.tuples[count].payload;
            }
            startSmaller = Psum_S[i].count;
            startBigger = Psum_R[i].count;

            size_of_table_to_hash = Hist_array_S[i].count;
            size_of_other_table = Hist_array_R[i].count;
        }

        next_prime = Number_used_for_hashing(size_of_table_to_hash);
        chain = malloc((size_of_table_to_hash)*sizeof(int));
        int count = 0;
        for (count = 0; count < size_of_table_to_hash; count++)
        {
            chain[count] = -1;
        }
        table_index->num_tuples = (uint32_t )size_of_table_to_hash;
        table->num_tuples = (u_int32_t )size_of_other_table;


        bucket = malloc(next_prime* sizeof(int));
        for(count = 0 ; count<next_prime; count ++)
        {
            bucket[count] = -1;
        }
        int counter=0,k=0,temp1=0,temp2=0;
        for (counter = 0; counter <size_of_table_to_hash; counter++)
        {
            k = H2(table_index->tuples[startSmaller + counter].payload) % next_prime;
            temp1 = bucket[k];
            temp2 =counter;
            bucket[k] = temp2;
            if(temp1 != -1)
            {
                chain[temp2] =temp1;
            }
        }



        int check_id,check1,check2,key1,key2;
        for( j = 0 ; j < size_of_other_table; j++)
        {
            hash_key = H2(table->tuples[startBigger + j].payload) % next_prime;
            check_id = bucket[hash_key];
            while (check_id != -1)
            {
                check1 = table_index->tuples[startSmaller + check_id].payload;
                check2 = table->tuples[startBigger + j].payload;
                // printf("check 1 = %d kai check2 = %d\n", check1, check2);
                if (check1 == check2)
                {
                    num_of_matches++;
                    key1 = table_index->tuples[startSmaller + check_id].key;
                    key2 = table->tuples[startBigger + j].key;
                    if (flag == 0)
                    {
                        insertResults(key1,key2,rhj);
                    }
                    else
                    {
                        insertResults(key2,key1,rhj);
                    }
                }
                check_id = chain[check_id];
            }

        }
        if(bucket)
        {
            free(bucket);
        }
        if(chain)
        {
            free(chain);
        }
        if(table->tuples)
        {
            free(table->tuples);
        }

        if(table_index->tuples)
        {
            free(table_index->tuples);
        }


    }
    free(final_array_R.tuples);
    free(final_array_S.tuples);
    free(table);
    free(table_index);

    return rhj;
}
uint64_t * loadRelation(char* fileName)
{
    int fp = open(fileName, O_RDONLY);

    if (fp == -1)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    struct stat sb;

    if (fstat(fp,&sb)==-1)
    {
        perror("stat\n");
        exit(EXIT_FAILURE);
    }

    size_t length = sb.st_size;

    uint64_t* ptr = mmap(NULL, length ,PROT_READ, MAP_PRIVATE, fp, 0);

    if (ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    close(fp);
    return ptr;


}

int min_value(tuple *array, int numrows)
{
    int c;
    int min = array[0].payload;

    for (c = 1; c < numrows; c++)
    {
        if (array[c].payload < min)
        {
            min = array[c].payload;
            int location = array[c].key;
        }
    }
    return min;
}

int max_value(tuple *array, int numrows)
{
    int max = array[0].payload;

    int c;
    for (c = 1; c < numrows; c++)
    {
        if (array[c].payload > max)
        {
            max = (int)array[c].payload;
            int location = array[c].key;
        }
    }
    return max;
}

endiamesiDomh* createEndiamesiDomh(int numRel, int* rel)
{
    int i;

    endiamesiDomh* mid = malloc(sizeof(endiamesiDomh));
    mid->relResults = malloc(numRel*sizeof(int));  //pinakas me to se poia relations exw vrei matches
    mid->resArray = (int**)malloc(numRel*sizeof(int*));  //pinakas me ta ids twn rels kai ta apotelesmata tous

    for(i=0; i<numRel; i++)
    {
        mid->relResults[i] = -1; //arxikopoiw me -1 ton pinaka me ta relations pou exoun apotelesmata
        mid->resArray[i] = malloc(sizeof(int));
        mid->resArray[i][0] = rel[i];
    }

    return mid;
}

int ReltionInMid(endiamesiDomh* mid, int rel_to_check, int numRel)
{
    int i;
    for(i=0; i<numRel; i++)
    {
        if(mid->resArray[i][0]==rel_to_check && mid->relResults[i]!=-1)
        {
            return 1;
        }
    }
    return 0;
}

relation* newRelation(endiamesiDomh* mid, int numRel, int rel_id, relation* rel)
{
    int i, j;

    relation* newRel = malloc(sizeof(relation));

    for(i=0; i<numRel; i++)
    {
        if(mid->resArray[i][0]==rel_id)
        {
            newRel->num_tuples = mid->relResults[i]; //num_tuples = o arithmos twn apotelesmatwn tou relation sthn endiamesh domh
            //dasmeuw mnhmh
            newRel->tuples = malloc(mid->relResults[i]*sizeof(tuple));
            //pernaw ta rowIds kai ta values sto neo relation
            for(j=1; i<newRel->num_tuples; i++)
            {
                newRel->tuples[i].key = mid->resArray[i][j];//vazw sto key to rowId apo thn andiamesh
                newRel->tuples[i].payload = rel->tuples[mid->resArray[i][j]].payload; //sto value vazw auto pou antistoixei
            }
            break;
        }
    }
    return newRel;
}


endiamesiDomh *FilterUpdate(endiamesiDomh *mid, int numRel, int rel_id, result1 *apotelesmata, int numOfResults, int *rel)
{
    int i, j;
    for (i = 0; i < numRel; i++) {
        if (mid->resArray[i][0] == rel_id) {
            //an den exw prohgoumena apotelesmata
            if (mid->relResults[i] == -1) {
                mid->relResults[i] = numOfResults; //enmerwnw posa apotelesmata exei to relation me rel_id
                //pernaw ta stoixeia 1-1 ston resArray[i][numofresults]

                //desmeuw mnimi thn prwth thesh thn exw hdh desmeusei kai krataei to rel_id)
                mid->resArray[i] = realloc(mid->resArray[i], (numOfResults) * sizeof(int));
                result1 *tmp = apotelesmata;
                while (tmp != NULL) {
                    int c = 1;
                    for (j = 0; j < size; j++) {
                        mid->resArray[i][c] = tmp->buffer[j];
                        c++;
                    }
                    tmp = tmp->next;
                }
                return mid;
            } else {
                //alliws ftiaxnw nea endiamesi
                endiamesiDomh *new_mid;
                new_mid = createEndiamesiDomh(numRel, rel);//arxikopoiw to new endiamesiDomh
                //gia kathe relation
                for (i = 0; i < numRel; i++) {
                    if (new_mid->relResults[i] == -1 && mid->relResults[i] != -1)//an exei prohgoumena apotelesmata
                    {
                        //desmeuw mnhmh gia to new_mid
                        new_mid->resArray[i] = realloc(new_mid->resArray[i], numOfResults * sizeof(int));
                        result1 *tmp = apotelesmata;
                        while (tmp != NULL) {
                            int c = 1;
                            for (j = 0; j < size; j++) {
                                //to stoixeio pou pernaw vrisketai sth thesh ths timhs pou mas dinei o buffer stin prohgoumeni ediamesh
                                new_mid->resArray[i][c] = mid->resArray[i][tmp->buffer[j]];
                                c++;
                            }
                            tmp = tmp->next;
                        }
                        new_mid->relResults[i] = numOfResults;
                    }
                }
                return new_mid;
            }
        }
    }
}


void queries_analysis(char * FileToOpen,struct  data * my_data)
{

    FILE *file;
    if((file = fopen(FileToOpen, "r")) == NULL)
    {

        fprintf(stderr,"Error Opening file\n");
        exit(0);
    }
    //int num_of_matches1 =0;
    char ch;
    size_t len = 0;
    ssize_t flag;
    char* line = NULL;
    int i,j;
    int space_num = 0;
    int relations_to_check;
    int total_ques;
    int plus_num =0;
    char* temp_str = NULL;
    while(flag = getline(&line , &len ,file ) != -1 )
    {

        char* token;
        char **tokens;
        // edw tsekarw an h grammh mou exei megethos megalutero apo ena
        if(strlen(line) < 3) continue;
        tokens = malloc(3*sizeof(char*));
        token = strtok(line,"|");
        tokens[0] = malloc(strlen(token)*sizeof(char)+1);
        bzero(tokens[0],strlen(token)+1);
        strcpy(tokens[0],token);

        token = strtok(NULL,"|");
        tokens[1] = malloc(strlen(token)*sizeof(char)+1);
        bzero(tokens[1],strlen(token)+1);
        strcpy(tokens[1],token);

        token = strtok(NULL,"\n");
        tokens[2] = malloc ( strlen(token)*sizeof(char)+1);
        bzero(tokens[2],strlen(token)+1);
        strcpy(tokens[2],token);

       ///debugging printf("%s|%s|%s\n",tokens[0],tokens[1],tokens[2]);

        //prepei na brw posa relation prepei na xrhsimopoihsw.
        for(i=0; i<strlen(tokens[0]); i++)
        {
            //metraw ta kena pou exw wste na brw kai to poses sxeseis exw
            if(line[i] ==' ')
            {
                space_num ++;
            }
        }
        relations_to_check = space_num + 1; // ta sunolika relation pou exoume na koitaksoume


        char * re=NULL;
        char * sxeseis=strdup(tokens[0]);
        data * mapping=malloc(sizeof(data)*relations_to_check);
        char * temp=strtok_r(sxeseis," ",&re);
        int id=atoi(temp);
        int* rel = malloc(relations_to_check*sizeof(int));
        rel[0]=id;
        mapping[0]=my_data[id];
        for(i=1; i<relations_to_check; i++)
        {

            char * temp=strtok_r(re," ",&re);
            int id=atoi(temp);
            rel[i]=id;
            mapping[i]=my_data[id];

        }
        free(sxeseis);
        //edw prepei na ftiaksoume enan pinaka me deiktes stous arxikous pinakes pou exoume wste na deixnoun oi relations_to_check
        //deiktes sta colls pou prepei

        //blepw posa queries exw.

        endiamesiDomh * end_domh=createEndiamesiDomh(relations_to_check,rel);

        for(i=0; i<strlen(tokens[1]); i++)
        {
            if(line[i+strlen(tokens[0])] =='&')
            {
                plus_num ++;
            }
        }
        total_ques = plus_num + 1;

       ///debugging printf("Exw sunolika %d sxeseis kai %d queries\n\n",relations_to_check,total_ques);
        //edw prepei na dhmiourghsw enan pinaka total_ques megethous opou tha balw mesa ena ena ta erwthmata pou mou zhtaei
        struct preds *predicates = malloc(total_ques*sizeof(struct preds));

        char* temp_str = malloc(strlen(tokens[1])*(sizeof(char))+1);
        bzero(temp_str ,strlen(tokens[1])+1);
        strcpy(temp_str,tokens[1]);
        int counter=0,erwthmata=0;

        int flag = 0;
        int flag1 =0;
        char *rest = NULL;
        token = strtok_r(tokens[1],"&",&rest);

        for(j=0; j<strlen(temp_str); j++)
        {
            //arxika tha brw thn praksi sugkrisis pou prokeitai na kanw.
            if(temp_str[j] == '<' || temp_str[j] == '>' || temp_str[j]== '=')
            {
                predicates[counter].op = temp_str[j];
                ///debugging printf("%c\n",predicates[counter].op);
                counter ++;
                erwthmata ++;
            }
        }
        //Init values to -1
        for(i =0; i<total_ques; i++)
        {
            predicates[i].relation1 =-1;
            predicates[i].relation2 =-1;
            predicates[i].num =-1;
            predicates[i].colum1=-1;
            predicates[i].colum2=-1;
            predicates[i].prio = -1;
        }
        /////////////////////////
        counter =0;
        while (erwthmata > 0)
        {
            for(i =0; i<strlen(token); i++)
            {
                if(token[i] == '=' || token[i] == '>' || token[i] =='<')
                {
                    flag = 1;
                }
                if(token[i] == '.' && predicates[counter].op == '=' && flag==0)
                {
                    token = strtok(token,".");
                    predicates[counter].relation1 = atoi(token);
                    token=strtok(NULL,"=");
                    predicates[counter].colum1 = atoi(token);

                   ///debugging printf("%d.%d %c ",predicates[counter].relation1,predicates[counter].colum1,predicates[counter].op);

                    token = strtok(NULL , "&");

                    for(j =0; j<strlen(token); j++)
                    {
                        if(token[j] == '.')
                        {
                            token = strtok(token,".");
                            predicates[counter].relation2 = atoi(token);
                            token= strtok(NULL,"&");
                            predicates[counter].colum2 = atoi(token);

                            ///debugging printf("%d.%d \n",predicates[counter].relation2,predicates[counter].colum2);
                            flag1 = 1;
                        }
                    }

                    if(flag1 == 0)
                    {
                        predicates[counter].num = atoi(token);
                       ///debugging printf("%d\n",predicates[counter].num);
                    }
                    counter ++;
                }
                else if(token[i] == '.' && (predicates[counter].op == '>' || predicates[counter].op == '<') && flag == 0)
                {
                    token = strtok(token,".");
                    predicates[counter].relation1 = atoi(token);
                    if(predicates[counter].op == '>')
                    {
                        token = strtok(NULL,">");
                    }
                    else if(predicates[counter].op == '<')
                    {
                        token = strtok(NULL,"<");
                    }
                    predicates[counter].colum1 = atoi(token);

                 ///debugging   printf("%d.%d %c " ,predicates[counter].relation1 , predicates[counter].colum1, predicates[counter].op );
                    token = strtok(NULL,"&");
                    predicates[counter].num = atoi(token);
                   ///debugging printf("%d\n", predicates[counter].num);
                    counter ++;
                }
                if(flag == 1)
                {
                    if(predicates[counter].op == '=')
                    {
                        token = strtok(token,"=");
                        predicates[counter].num = atoi(token);
                        token = strtok(NULL,".");
                        predicates[counter].relation1  = atoi(token);
                        token = strtok(NULL,"&");
                        predicates[counter].colum1 = atoi(token);
                       ///debugging printf("%d %c %d.%d\n" , predicates[counter].num , predicates[counter].op, predicates[counter].relation1,predicates[counter].colum1);
                        counter ++;
                        flag = 0;
                    }
                    else if(predicates[counter].op == '>')
                    {
                        token = strtok(token,"<");
                        predicates[counter].num = atoi(token);
                        token = strtok(NULL,".");
                        predicates[counter].relation1  = atoi(token);
                        token = strtok(NULL,"&");
                        predicates[counter].colum1 = atoi(token);
                        ///debugging printf("%d %c %d.%d\n" , predicates[counter].num , predicates[counter].op, predicates[counter].relation1,predicates[counter].colum1);
                        counter ++;
                        flag = 0;
                    }
                    else if(predicates[counter].op == '<')
                    {
                        token = strtok(token,"<");
                        predicates[counter].num = atoi(token);
                        token = strtok(NULL,".");
                        predicates[counter].relation1  = atoi(token);
                        token = strtok(NULL,"&");
                        predicates[counter].colum1 = atoi(token);
                        ///debugging printf("%d %c %d.%d\n" , predicates[counter].num , predicates[counter].op, predicates[counter].relation1,predicates[counter].colum1);
                        counter ++;
                        flag = 0;
                    }

                }
            }
            if(erwthmata != 1)
            {
                token = strtok_r(rest ,"&",&rest);
            }
            erwthmata --;
            flag1 = 0;
        }
        int *prio;
        prio  = select_pred(total_ques,predicates);
        for(j= 0; j< total_ques; j++)
        {
            if(predicates[prio[j]].num == -1)//exw join.
            {
                relation relation1,relation2;
                relation1.num_tuples=mapping[predicates[prio[j]].relation1].num_tuples;
                relation2.num_tuples=mapping[predicates[prio[j]].relation2].num_tuples;
               ///debugging printf("num1 %d num2 %d\n",relation1.num_tuples,relation2.num_tuples);
                relation1.tuples=malloc(sizeof(tuple)*relation1.num_tuples);
                relation2.tuples=malloc(sizeof(tuple)*relation2.num_tuples);
                for(i=0; i<relation1.num_tuples; i++)
                {
                    relation1.tuples[i].check=0;
                }
                for(i=0; i<relation2.num_tuples; i++)
                {
                    relation2.tuples[i].check=0;
                }

                for(i=0; i<relation1.num_tuples; i++)
                {
                    relation1.tuples[i].key=mapping[predicates[prio[j]].relation1].relations[predicates[prio[j]].colum1].tuples[i].key;
                    relation1.tuples[i].payload=mapping[predicates[prio[j]].relation1].relations[predicates[prio[j]].colum1].tuples[i].payload;

                }
                for(i=0; i<relation2.num_tuples; i++)
                {
                    relation2.tuples[i].key=mapping[predicates[prio[j]].relation2].relations[predicates[prio[j]].colum2].tuples[i].key;
                    relation2.tuples[i].payload=mapping[predicates[prio[j]].relation2].relations[predicates[prio[j]].colum2].tuples[i].payload;

                }

                result * rhj=radix_hash_join(relation1,relation1.num_tuples,relation2,relation2.num_tuples);
               // printResults(rhj,num_of_matches);
                free(relation1.tuples);
                free(relation2.tuples);
                free_list(rhj);


            }
            else // exw sugkrish me enan ari8mo
            {
                int exists=0;

                relation relation1;
                relation1.num_tuples = mapping[predicates[prio[j]].relation1].num_tuples;
                relation1.tuples = malloc(sizeof(tuple)*relation1.num_tuples);

                for(i=0; i<relation1.num_tuples; i++)
                {
                    relation1.tuples[i].check =0;
                }
                for(i =0; i<relation1.num_tuples; i++)
                {
                    relation1.tuples[i].key=mapping[predicates[prio[j]].relation1].relations[predicates[prio[j]].colum1].tuples[i].key;
                    relation1.tuples[i].payload=mapping[predicates[prio[j]].relation1].relations[predicates[prio[j]].colum1].tuples[i].payload;
                }

                //exists=ReltionInMid(end_domh,relations_to_check,predicates[prio[j]].relation1);

                 //if exists endiamesh domh klp ...

                if(predicates[prio[j]].op == '<')
                {
                    result1 * list = Equalizer(relation1,relation1.num_tuples,predicates[prio[j]].num,3);
//                    printResults1(list,num_of_matches1);
                    free_list1(list);
                }
                else if(predicates[prio[j]].op == '=')
                {
                    result1 * list = Equalizer(relation1,relation1.num_tuples,predicates[prio[j]].num,1);
//                        printResults1(list,num_of_matches1);
                    free_list1(list);
                }
                else if( predicates[prio[j]].op == '>')
                {
                    result1 * list = Equalizer(relation1,relation1.num_tuples,predicates[prio[j]].num,2);
//                      printResults1(list,num_of_matches1);
                    free_list1(list);
                }
                free(relation1.tuples);





            }
        }

        space_num = 0;
        plus_num =0;
        free(temp_str);
        for(i=0; i<3; i++)
        {
            free(tokens[i]);
        }
        free(tokens);
        free(predicates);
        free(mapping);
        free(prio);
        free(rel);
        //free(end_domh);

    }
    free(line);
    fclose(file);

}
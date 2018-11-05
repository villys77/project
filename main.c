#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "functions.h"

#define n 12


int main(int argc,char **argv)
{
    time_t t;
    srand((unsigned) time(&t));

    result *rhj=createResult();///dhmiourgia listas pou 8a xrhsimopoihsw argotera sto teleutaio stadio gia na krataw ta apotelesmata moy

    int power = pow(2, n); /// 2^n (megethos pinakwn psum kai hist)
    int mask = power - 1; //// maska gia &

    //////////////////////////////////////////////////
    /////////FIRST HASHING
    tuple *array_R = malloc(sizeof(struct tuple) * 100);
    for (int i = 0; i < 100; i++)
    {
        array_R[i].check = 0;
        array_R[i].key = i;
        array_R[i].payload = 1;
    }

    /*
     * prints gia debugging
     *
    printf("\nARRAY R\n");
    for (int i = 0; i < 10; i++)
    {
        printf("id %d:\t%d\n", array_R[i].key, array_R[i].payload);
    }
    */
    ///////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////
    ////////HIST
    hist *Hist_array_R = malloc(sizeof(hist) * power);

    for (int i = 0; i < power; i++)
    {
        Hist_array_R[i].binary = i;
        Hist_array_R[i].count = 0;
    }

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < power; j++)
        {
            if ((array_R[i].payload & mask) == Hist_array_R[j].binary)
            {
                Hist_array_R[j].count++;
                break;
            }
        }
    }

    /*
     * prints gia debugging
     *
    printf("\nHIST R\n");
    for (int i = 0; i < power; i++)
    {
        printf("id %d: \t %d\n", Hist_array_R[i].binary, Hist_array_R[i].count);
    }

     */
    ///////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////
    //////////////PSUM
    hist *Psum_R = malloc(sizeof(hist) * power);
    for (int i = 0; i < power; i++)
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
    /*
     *prints gia debugging
    printf("\nPSUM R\n");
    for (int i = 0; i < power; i++)
    {
        printf("id %d: \t %d\n", Psum_R[i].binary, Psum_R[i].count);

    }
     */
    //////////////////////////////////////////////////////////////////



    tuple *final_array_R = malloc(sizeof(struct tuple) * 100);
    int where_R = 0;
    while (where_R < power)
    {
        if (where_R == power - 1) ///////pepiptwsh pou eimaste sthn teleytaia epanalh4h
        {
            for (int i = Psum_R[where_R].count; i < 10; i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    if ((array_R[j].payload & mask) == where_R && (array_R[j].check == 0))
                    {
                        final_array_R[i].key = array_R[j].key;
                        final_array_R[i].payload = array_R[j].payload;
                        array_R[j].check = 1;
                        break;
                    }
                }
            }
            break;
        }
        else ///opoiadhpote endiamesh periptwsh
        {

            for (int i = Psum_R[where_R].count; i < Psum_R[where_R + 1].count; i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    if ((array_R[j].payload & mask) == where_R && (array_R[j].check == 0))
                    {
                        final_array_R[i].key = array_R[j].key;
                        final_array_R[i].payload = array_R[j].payload;
                        array_R[j].check = 1;
                        break;
                    }
                }
            }
        }

        where_R++;
    }


  //  /*
    // *      *prints gia debugging
     //*
    printf("\nFINAL R\n");
    for (int i = 0; i < 10; i++)
    {
        printf("id %d:\t%d\n", final_array_R[i].key, final_array_R[i].payload);

    }
     //*/

/////MEXRI EDW GIA TO R
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    tuple *array_S = malloc(sizeof(struct tuple) * 100);
    for (int i = 0; i < 100; i++)
    {
        array_S[i].check = 0;
        array_S[i].key = i ;
        array_S[i].payload = rand()%40;
    }


    /*
     *prints gia debugging
     *
    printf("\nARRAY S\n");
    for (int i = 0; i < 10; i++)
    {
        printf("id %d:\t%d\n", array_S[i].key, array_S[i].payload);
    }

    ///////////////////////////////////////////////////////
    */

    ////////////////////////////////////////////////////////
    ////////HIST
    hist *Hist_array_S = malloc(sizeof(hist) * power);

    for (int i = 0; i < power; i++)
    {
        Hist_array_S[i].binary = i;
        Hist_array_S[i].count = 0;
    }

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < power; j++)
        {
            if ((array_S[i].payload & mask) == Hist_array_S[j].binary)
            {
                Hist_array_S[j].count++;
                break;
            }
        }
    }

    /*
     * prints gia debugging
     *
    printf("\nHIST S\n");
    for (int i = 0; i < power; i++)
    {
        printf("id %d: \t %d\n", Hist_array_S[i].binary, Hist_array_S[i].count);
    }
     */
    /////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////
    //////////////PSUM
    hist *Psum_S = malloc(sizeof(hist) * power);
    for (int i = 0; i < power; i++)
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
    /*
     * prints gia debugging
     *
    printf("\nPSUM S\n");
    for (int i = 0; i < power; i++)
     {
        printf("id %d: \t %d\n", Psum_S[i].binary, Psum_S[i].count);

    }
     */
    //////////////////////////////////////////////////////////////////



    tuple *final_array_S = malloc(sizeof(struct tuple) * 100);
    int where_S = 0;
    while (where_S <= power)
    {
        if (where_S == power - 1) ///////pepiptwsh pou eimaste sthn teleytaia epanalh4h
        {
            for (int i = Psum_S[where_S].count; i < 100; i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    if ((array_S[j].payload & mask) == where_S && (array_S[j].check == 0))
                    {
                        final_array_S[i].key = array_S[j].key;
                        final_array_S[i].payload = array_S[j].payload;
                        array_S[j].check = 1;
                        break;
                    }
                }
            }
            break;
        }
        else ///opoiadhpote endiamesh periptwsh
        {

            for (int i = Psum_S[where_S].count; i < Psum_S[where_S + 1].count; i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    if ((array_S[j].payload & mask) == where_S && (array_S[j].check == 0))
                    {
                        final_array_S[i].key = array_S[j].key;
                        final_array_S[i].payload = array_S[j].payload;
                        array_S[j].check = 1;
                        break;
                    }
                }
            }
        }

        where_S++;
    }


    ///*
     //* prints gia debbugging
    printf("\nFINAL S\n");
    for (int i = 0; i < 100; i++)
    {
        printf("id %d:\t%d\n", final_array_S[i].key, final_array_S[i].payload);

    }
       //*/


////////MEXRI EDW R
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
    //////////exoune dhmiourghyhei oi pinakes R' kai S' ws final_array_R kai final_array_S
    ////////// kai apo dw kai katw ftiaxnoyme ta eurethria typou hash(bucket-chain)
    int i,j,num_of_matces=0;
    int all_buckets = pow(2, n);
    int next_prime;
    struct relation *table_index; // to table pou tha exei to hash table
    struct relation *table;
    int smaller_hist, bigger_hist;
    int size_of_table_to_hash;
    int size_of_other_table;
    int startSmaller, startBigger; // to shmeio apo to opoio tha ksekinhsw na koitaw to kathe ena bucket
    int *chain, *bucket;
    int tuple_numR = 0, tuple_numS = 0;
    int flag;
    int hash_key;


    table_index = malloc(sizeof(struct relation));
    table = malloc(sizeof(struct relation));


    for (i = 0; i < all_buckets; i++)
    {
        tuple_numR += Hist_array_R[i].count;
        tuple_numS += Hist_array_S[i].count;
    }

    for (i = 0; i < all_buckets; i++)
    {

        if (Hist_array_R[i].count == 0 || Hist_array_S[i].count == 0)
        {
            continue;
        }
        if (Hist_array_R[i].count < Hist_array_S[i].count)
        {
            flag = 0;
            table_index->tuples = malloc(tuple_numR *sizeof(tuple));
            table->tuples = malloc(tuple_numS *sizeof(tuple));

            int count;
            for (count = 0; count < tuple_numR; count++)
            {
                table_index->tuples[count].key = final_array_R[count].key;
                table_index->tuples[count].payload = final_array_R[count].payload;
            }
            for (count = 0; count < tuple_numS; count++)
            {
                table->tuples[count].key = final_array_S[count].key;
                table->tuples[count].payload = final_array_S[count].payload;
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
                table_index->tuples[count].key = final_array_S[count].key;
                table_index->tuples[count].payload = final_array_S[count].payload;
            }
            for (count = 0; count < tuple_numR; count++)
            {
                table->tuples[count].key = final_array_R[count].key;
                table->tuples[count].payload = final_array_R[count].payload;
            }
            startSmaller = Psum_S[i].count;
            startBigger = Psum_R[i].count;

            size_of_table_to_hash = Hist_array_S[i].count;
            size_of_other_table = Hist_array_R[i].count;
        }

        next_prime = Number_used_for_hashing(size_of_table_to_hash);
        chain = malloc((size_of_table_to_hash + 1) * sizeof(int));
        int count = 0;
        for (count = 0; count < size_of_table_to_hash + 1; count++)
        {
            chain[count] = -1;
        }
        table_index->num_tuples = size_of_table_to_hash;
        table->num_tuples = size_of_other_table;


        bucket = malloc(next_prime * sizeof(int));
        for (count = 0; count < next_prime; count++)
        {
            bucket[count] = -1;
        }
        int counter, k, temp1, temp2;
        for (counter = 0; counter < table_index->num_tuples; counter++)
        {
            k = H2(table_index->tuples[startSmaller + counter].payload) % next_prime;
            temp1 = bucket[k];
            temp2 = table_index->tuples[startSmaller + counter].key;
            bucket[k] = temp2;
            if (temp1 != -1)
            {
                chain[temp2] = temp1;
            }
        }

        int check_id, check1, check2, key1, key2;
        for (j = 0; j < size_of_other_table; j++)
        {
            hash_key = H2(table->tuples[startBigger + j].payload) % next_prime;
            check_id = bucket[hash_key];
            while (check_id != -1)
            {
                if (flag == 0)
                {
                    check1 = array_R[check_id].payload;
                }
                else
                {
                    check1 = array_S[check_id].payload;
                }
                check2 = table->tuples[startBigger + j].payload;
                if (check1 == check2)
                {
                    num_of_matces++;
                    if (flag == 0)
                    {
                        key1 = array_R[check_id].key;
                    }
                    else
                    {
                        key1 = array_S[check_id].key;
                    }
                    key2 = table->tuples[startBigger + j].key;
                    if(flag==0)
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
    }
    printResults(rhj,num_of_matces);
    printf("Matches are : %d\n",num_of_matces);
}

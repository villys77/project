#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "functions.h"

#define n 2


int main(int argc,char **argv)
    {
        time_t t;
        srand((unsigned) time(&t));

        int power=pow(2,n);
        int mask=power-1;

        //////////////////////////////////////////////////
        /////////FIRST HASHING
        tuple *array_R=malloc(sizeof(struct tuple)*10);
        for(int i=0; i<10; i++)
        {
            array_R[i].check=0;
            array_R[i].key=i+1;
            array_R[i].payload=rand()%10;
        }

        printf("\nARRAY R\n");
        for(int i=0; i<10; i++)
        {
            printf("id %d:\t%d\n",array_R[i].key,array_R[i].payload);
        }

        ///////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////
        ////////HIST
        hist * Hist_array_R=malloc(sizeof(hist)* pow(2,n));

        for(int i=0; i<power; i++)
        {
            Hist_array_R[i].binary=i;
            Hist_array_R[i].count=0;
        }

        for(int i=0; i<10; i++)
        {
            for(int j=0; j<power; j++)
            {
                if( (array_R[i].payload & mask)==Hist_array_R[j].binary)
                {
                    Hist_array_R[j].count++;
                    break;
                }
            }
        }
        printf("\nHIST R\n");
        for(int i=0; i < power; i++)
        {
            printf("id %d: \t %d\n",Hist_array_R[i].binary,Hist_array_R[i].count);
        }

        ///////////////////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////////////
        //////////////PSUM
        hist * Psum_R=malloc(sizeof(hist)*(power));
        for(int i=0; i<power; i++)
        {

            Psum_R[i].binary=i;
            if(i==0)
            {
                Psum_R[i].count = 0;
            }
            else
            {
                Psum_R[i].count = Psum_R[i-1].count + Hist_array_R[i-1].count;
            }
        }
        printf("\nPSUM R\n");
        for (int i = 0; i <power ; i++)
        {
            printf("id %d: \t %d\n",Psum_R[i].binary,Psum_R[i].count);

        }
        //////////////////////////////////////////////////////////////////



        tuple *final_array_R=malloc(sizeof(struct tuple)*10);
        int where_R=0;
        while(where_R < power)
        {
            if(where_R==power-1) ///////pepiptwsh pou eimaste sthn teleytaia epanalh4h
            {
                for(int i=Psum_R[where_R].count; i<10; i++)
                {
                    for(int j=0; j<10; j++)
                    {
                        if( (array_R[j].payload & mask)==where_R && (array_R[j].check==0))
                        {
                            final_array_R[i].key=array_R[j].key;
                            final_array_R[i].payload=array_R[j].payload;
                            array_R[j].check=1;
                            break;
                        }
                    }
                }
                break;
            }
            else ///opoiadhpote endiamesh periptwsh
            {

                for(int i=Psum_R[where_R].count; i<Psum_R[where_R+1].count; i++)
                {
                    for(int j=0; j<10; j++)
                    {
                        if( (array_R[j].payload & mask)==where_R && (array_R[j].check==0))
                        {
                            final_array_R[i].key=array_R[j].key;
                            final_array_R[i].payload=array_R[j].payload;
                            array_R[j].check=1;
                            break;
                        }
                    }
                }
            }

            where_R++;
        }


        printf("\nFINAL R\n");
        for(int i=0; i<10; i++)
        {
            printf("id %d:\t%d\n",final_array_R[i].key,final_array_R[i].payload);

        }

/////MEXRI EDW GIA TO R
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        tuple *array_S=malloc(sizeof(struct tuple)*10);
        for(int i=0; i<10; i++)
        {
            array_S[i].check=0;
            array_S[i].key=i+1;
            array_S[i].payload=rand()%10;
        }

        printf("\nARRAY S\n");
        for(int i=0; i<10; i++)
        {
            printf("id %d:\t%d\n",array_S[i].key,array_S[i].payload);
        }

        ///////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////
        ////////HIST
        hist * Hist_array_S=malloc(sizeof(hist)* pow(2,n));

        for(int i=0; i<power; i++)
        {
            Hist_array_S[i].binary=i;
            Hist_array_S[i].count=0;
        }

        for(int i=0; i<10; i++)
        {
            for(int j=0; j<power; j++)
            {
                if( (array_S[i].payload & mask)==Hist_array_S[j].binary)
                {
                    Hist_array_S[j].count++;
                    break;
                }
            }
        }
        printf("\nHIST S\n");
        for(int i=0; i < power; i++)
        {
            printf("id %d: \t %d\n",Hist_array_S[i].binary,Hist_array_S[i].count);
        }
    /////////////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////////////
        //////////////PSUM
        hist * Psum_S=malloc(sizeof(hist)*(power));
        for(int i=0; i<power; i++)
        {

            Psum_S[i].binary=i;
            if(i==0)
            {
                Psum_S[i].count = 0;
            }
            else
            {
                Psum_S[i].count = Psum_S[i-1].count + Hist_array_S[i-1].count;
            }
        }
        printf("\nPSUM S\n");
        for (int i = 0; i <power ; i++)
        {
            printf("id %d: \t %d\n",Psum_S[i].binary,Psum_S[i].count);

        }
        //////////////////////////////////////////////////////////////////



        tuple *final_array_S=malloc(sizeof(struct tuple)*10);
        int where_S=0;
        while(where_S <= power)
        {
            if(where_S==power-1) ///////pepiptwsh pou eimaste sthn teleytaia epanalh4h
            {
                for(int i=Psum_S[where_S].count; i<10; i++)
                {
                    for(int j=0; j<10; j++)
                    {
                        if( (array_S[j].payload & mask)==where_S && (array_S[j].check==0))
                        {
                            final_array_S[i].key=array_S[j].key;
                            final_array_S[i].payload=array_S[j].payload;
                            array_S[j].check=1;
                            break;
                        }
                    }
                }
                break;
            }
            else ///opoiadhpote endiamesh periptwsh
            {

                for(int i=Psum_S[where_S].count; i<Psum_S[where_S+1].count; i++)
                {
                    for(int j=0; j<10; j++)
                    {
                        if( (array_S[j].payload & mask)==where_S && (array_S[j].check==0))
                        {
                            final_array_S[i].key=array_S[j].key;
                            final_array_S[i].payload=array_S[j].payload;
                            array_S[j].check=1;
                            break;
                        }
                    }
                }
            }

            where_S++;
        }


        printf("\nFINAL S\n");
        for(int i=0; i<10; i++)
        {
            printf("id %d:\t%d\n",final_array_S[i].key,final_array_S[i].payload);

        }



////////MEXRI EDW R
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

    //////////exoune dhmiourghyhei oi pinakes R' kai S' ws final_array_R kai final_array_S
    ////////// kai apo dw kai katw ftiaxnoyme ta eurethria typou hash(bucket-chain)

    int all_buckets = pow(2,n);
    int next_prime;
    struct relation* table_index; // to table pou tha exei to hash table
    struct relation* table;
    int smaller_hist, bigger_hist;
    int size_of_table_to_hash;
    int size_of_other_table;
    int startSmaller , startBigger; // to shmeio apo to opoio tha ksekinhsw na koitaw to kathe ena bucket
    int *chain ,  *bucket;


    int i, hash_key ,j  ;



    table_index = malloc(sizeof(struct relation));
    table = malloc(sizeof(struct relation));

    for ( i = 0; i<all_buckets; i++)
    {

        if(Hist_array_R[i].count == 0 || Hist_array_S[i].count == 0)
        {
            continue;
        }
        if( Hist_array_R[i].count < Hist_array_S[i].count)
        {
            smaller_hist = Hist_array_R[i].count;
            bigger_hist = Hist_array_S[i].count;
            startSmaller = Psum_R[i].count;
            startBigger = Psum_S[i].count;

            table_index->tuples = malloc(smaller_hist *sizeof(tuple));
            table ->tuples = malloc ( bigger_hist *sizeof(tuple));

            table_index->num_tuples =smaller_hist ;
            table->num_tuples = bigger_hist;
            int count;

            for (count = 0; count < smaller_hist; count++)
            {
                table_index->tuples[count].key = final_array_R[startSmaller+count].key;
                table_index->tuples[count].payload = final_array_R[startBigger+count].payload;
            }
            for(count = 0 ; count < bigger_hist; count++)
            {
                table->tuples[count].key = final_array_S[startBigger+count].key;
                table->tuples[count].payload = final_array_S[startBigger+count].payload;
            }
        }
        else
        {
            smaller_hist = Hist_array_S[i].count;
            bigger_hist = Hist_array_R[i].count;

            startBigger = Psum_R[i].count;
            startSmaller = Psum_S[i].count;


            table_index->tuples= malloc(smaller_hist *sizeof(struct tuple));
            table ->tuples = malloc(bigger_hist *sizeof(struct tuple));

            table_index->num_tuples = smaller_hist;
            table->num_tuples = bigger_hist;

            int count;

            for (count = 0; count < smaller_hist; count++)
            {
                table_index->tuples[count].key = final_array_S[startSmaller+count].key;
                table_index->tuples[count].payload = final_array_S[startSmaller+count].payload;
            }
            printf("table index  : \n" );
            for(count =0; count < smaller_hist; count++)
            {
                printf("%d\n",table_index->tuples[count].payload);
            }

            for(count = 0 ; count < bigger_hist; count++)
            {
                table->tuples[count].key = final_array_R[startBigger+count].key;
                table->tuples[count].payload = final_array_R[startBigger+count].payload;
            }

            printf("\n table : \n");
            for(count =0; count < bigger_hist; count++)
            {
                printf("%d\n",table->tuples[count].payload);
            }

        }

        size_of_table_to_hash = Number_used_for_hashing(smaller_hist);

        chain = (int *)malloc((smaller_hist + 1) *sizeof(int));
        bucket = (int *)malloc ( size_of_table_to_hash *sizeof(int));

        //arxikopoihsh twn pinakwn bucket kai chain
        int count;
        for(count = 0; count<size_of_table_to_hash; count++)
        {
            bucket[i] = -1;
        }
        for(count = 0; count<smaller_hist + 1 ; count++)
        {
            chain[count] = -1;
        }

        //hasharw ola ta stoixeia tou pinaka pou tha parw gia na kanw to eurethrio

        H2(table_index , bucket , chain , size_of_table_to_hash);

        //twra exw ton pinaka twn bucket kai tou chain kai prepei na kanw tous elegxous
        int check_id , x ,y , key1 , key2;

        for ( j = 0; j<bigger_hist; j++)
        {
            hash_key = (table->tuples[j].payload % size_of_table_to_hash);

            check_id = bucket[hash_key] +1 ;

            y = table->tuples[j].payload;
            while(check_id!= -1 )
            {
                x = table_index->tuples[check_id].payload;
                if(x == y)
                {
                    key1 = table_index->tuples[check_id].key;
                    key2 = table->tuples[j].key;
                    printf ("edw ektupwnw giati %d = %d \n" , x,y);
                    printf("me id ");
                    printf( " %d --- %d \n", key1,key2);
                }
                else
                {
                    printf("Edw den ektupwnw giati x = %d kai y = %d \n \n ", x, y);
                }

                check_id = chain[check_id + 1];
            }

        }
    }
   /* table_index = malloc(sizeof(struct relation));
    table = malloc(sizeof(struct relation));

    for ( j = 0 ; j < all_buckets; j++)
    {
        printf( " ---------%d \n " , j);
        if(Hist_array_R[j].count == 0 || Hist_array_S[j].count == 0 )
        {
            continue;
        }
        if( Hist_array_R[j].count < Hist_array_S[j].count )
        {
                size_of_table_to_hash = Hist_array_R[j].count ;
                size_of_other_table = Hist_array_S[j].count;

                printf (" to megethos tou R %d kai tou S %d \n", size_of_table_to_hash, size_of_other_table);

                table_index->tuples = malloc(size_of_table_to_hash* sizeof(struct tuple));
                table->tuples = malloc(size_of_other_table* sizeof(struct tuple));

                table_index->num_tuples = size_of_table_to_hash;
                table ->num_tuples = size_of_other_table;
            //edw prepei na mpei kai elegxow me to psum , gia na kserw apo pou tha ksekinhsw na tsekarw sto bucket.
                    startR = Psum_R[j].count;
                    startS = Psum_S[j].count;

                    printf(" exw sR kai sS %d %d  \n " , startR , startS);

                    for(i =0 ; i < size_of_table_to_hash ; i ++)
                    {
                        table_index->tuples[i].key = final_array_R[startR+i].key;
                        table_index->tuples[i].payload = final_array_R[startR+i].payload;

                    }
                    for(i = 0 ; i < size_of_other_table; i++)
                    {
                        table->tuples[i].key = final_array_S[startS+i].key;
                        table->tuples[i].payload = final_array_S[startS+i].payload;
                    }
        }
        else
        {
            size_of_table_to_hash = Hist_array_S[j].count;
            size_of_other_table = Hist_array_R[j].count;

            printf (" to megethos tou S %d kai tou R %d \n", size_of_table_to_hash, size_of_other_table);


            table_index->tuples = malloc(size_of_table_to_hash*sizeof(struct tuple));
            table->tuples = malloc(size_of_other_table*sizeof(struct tuple));

            table_index->num_tuples = size_of_table_to_hash;
            table ->num_tuples = size_of_other_table;

            //to idio me to apo panw
                    startS = Psum_S[j].count;
                    startR = Psum_R[j].count;

            printf(" exw sR kai sS %d %d  \n " , startR , startS);

            for(i =0 ; i < size_of_table_to_hash ; i ++)
            {
                table_index->tuples[i].key = final_array_S[startS+i].key;
                table_index->tuples[i].payload = final_array_S[startS+i].payload;

            }
            for(i = 0 ; i < size_of_other_table; i++)
            {
                table->tuples[i].key = final_array_R[startR+i].key;
                table->tuples[i].payload = final_array_R[startR+i].payload;
            }

        }

        table_index->num_tuples = size_of_table_to_hash;
        table->num_tuples = size_of_other_table;

        hash_key = Number_used_for_hashing(size_of_table_to_hash);
        bucket = malloc(sizeof (int) * hash_key);
        chain = malloc(size_of_table_to_hash * sizeof(int));

        for( i = 0; i < size_of_table_to_hash; i++)
        {
            chain[i] = -1;
        }

        for( i = 0; i < hash_key; i++)
        {
            bucket[i] = -1;
        }

        H2(table_index , chain , bucket , hash_key);

        for(i = 0 ; i < size_of_table_to_hash ; i++)
        {
            printf(" %d \n " , chain[i]);
        }

        int k;
        int check_id;
        int x,y;
        int to_insert_key1 , to_insert_key2;
        for(i = 0 ; i < size_of_other_table; i++)
        {
            k = (table->tuples[startS+i].payload % hash_key);
            check_id = bucket[k];
            x = table_index->tuples[i].payload;

            while(check_id != 0)
            {
                y = table->tuples[startS+i].payload;

                if( x == y )
                {
                    to_insert_key1 = table_index->tuples[i].key;
                    to_insert_key2 = table->tuples[startS+i].key;
                    //kaleitai h sunarthsh me tis listes
                            printf(" \n to x %d , to y %d \n" ,x,y );
                            printf(" \n %d -> %d \n" , to_insert_key1, to_insert_key2);
                }
                check_id = chain[check_id];
            }
        }
    }*/



}


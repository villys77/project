#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
<<<<<<< HEAD
#include "structs.h"
#include "functions.h"

#define n 2

=======

#define n 2

    typedef struct tuple
    {
        unsigned key;
        unsigned payload;
        int check;
    }tuple;

    typedef struct hist
    {
        unsigned binary;
        unsigned count;
    }hist;




struct relation {
    struct tuple *tuples;
    int num_tuples;
};


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

>>>>>>> 24e7f90448cdcf58dc507ea71818bf1e9c6dfbb1

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
            array_R[i].key=i;
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
<<<<<<< HEAD

/////MEXRI EDW GIA TO R
=======
        /////MEXRI EDW GIA TO R
>>>>>>> 24e7f90448cdcf58dc507ea71818bf1e9c6dfbb1
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        tuple *array_S=malloc(sizeof(struct tuple)*10);
        for(int i=0; i<10; i++)
        {
            array_S[i].check=0;
            array_S[i].key=i;
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
<<<<<<< HEAD
            if(where_S==power-1) ///////pepiptwsh pou eimaste sthn teleytaia epanalh4h
=======
            if(where_S==power-1) ///////pepiptwsh pou eimaste sthn teleytaia epanalh4h me plhres PSUM
>>>>>>> 24e7f90448cdcf58dc507ea71818bf1e9c6dfbb1
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


<<<<<<< HEAD

////////MEXRI EDW R
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

    //////////exoune dhmiourghyhei oi pinakes R' kai S' ws final_array_R kai final_array_S
    ////////// kai apo dw kai katw ftiaxnoyme ta eurethria typou hash(bucket-chain)
=======
    /////apo toon basilh erxontai ayta
    /////////////////////////////////////
>>>>>>> 24e7f90448cdcf58dc507ea71818bf1e9c6dfbb1

    int all_buckets = pow(2,n);
    int next_prime;
    struct relation * table_index; // to table pou tha exei to hash table
    struct relation * table;
    int size_of_table_to_hash;
    int size_of_other_table;
    int startR , startS; // to shmeio apo to opoio tha ksekinhsw na koitaw to kathe ena bucket
    int * chain ,  * bucket;

    int i, hash_key ;
    table_index = malloc(sizeof(struct relation));
    table = malloc(sizeof(struct relation));

    for ( i = 0 ; i < all_buckets; i++)
    {
        if(Hist_array_R[i].count == 0 || Hist_array_S[i].count == 0 )
        {
            continue;
        }
        if( Hist_array_R[i].count < Hist_array_S[i].count )
        {
                size_of_table_to_hash = Hist_array_R[i].count ;
                size_of_other_table = Hist_array_S[i].count;
                table_index[i].tuples = malloc(size_of_table_to_hash* sizeof(struct tuple));
                table[i].tuples = malloc(size_of_other_table* sizeof(struct tuple));

            //edw prepei na mpei kai elegxow me to psum , gia na kserw apo pou tha ksekinhsw na tsekarw sto bucket.
                    startR = Psum_R[i].count;
                    startS = Psum_S[i].count;
                    for(i =0 ; i < size_of_table_to_hash ; i ++)
                    {
                        table_index->tuples[i].key = final_array_R[i].key;
                        table_index->tuples[i].payload = final_array_R[i].payload;

                    }
                    for(i = 0 ; i < size_of_other_table; i++)
                    {
                        table->tuples[i].key = final_array_S[i].key;
                        table->tuples[i].payload = final_array_S[i].payload;
                    }
        }
        else
        {
            size_of_table_to_hash = Hist_array_S[i].count;
            size_of_other_table = Hist_array_R[i].count;
            table_index[i].tuples = malloc(size_of_table_to_hash* sizeof(struct tuple));
            table[i].tuples = malloc(size_of_other_table* sizeof(struct tuple));
            //to idio me to apo panw
                    startS = Psum_S[i].count;
                    startR = Psum_R[i].count;
            for(i =0 ; i < size_of_table_to_hash ; i ++)
            {
                table_index->tuples[i].key = final_array_S[i].key;
                table_index->tuples[i].payload = final_array_S[i].payload;

            }
            for(i = 0 ; i < size_of_other_table; i++)
            {
                table->tuples[i].key = final_array_R[i].key;
                table->tuples[i].payload = final_array_R[i].payload;
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

        int k;
        int check_id;
        int x,y;
        int to_insert_key1 , to_insert_key2;
        for(i = 0 ; i < size_of_other_table; i++)
        {
            k = (table->tuples[i].payload % hash_key);
            check_id = bucket[k];

            while(check_id != -1)
            {
                x = array_R[check_id].payload;
                y = table->tuples[startS + i].payload;

                if( x == y )
                {
                    to_insert_key1 = table_index->tuples[startR + check_id].key;
                    to_insert_key2 = table->tuples[startS + check_id].key;
                    //kaleitai h sunarthsh me tis listes
                            printf(" \n to x %d , to y %d \n" ,x,y );
                            printf(" \n %d -> %d \n" , to_insert_key1, to_insert_key2);
                }

                check_id = chain[check_id];
            }
        }



    }



}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

    typedef struct tuple
    {
        unsigned key;
        unsigned payload;
    }tuple;

    typedef struct hist
    {
        unsigned binary;
        unsigned count;
    }hist;


    int main(int argc,char **argv)
    {
        int n=2; ////2^n
        time_t t;
        srand((unsigned) time(&t));


        tuple *array=malloc(sizeof(struct tuple)*10);
        for(int i=0; i<10; i++)
        {
            array[i].key=i+1;
            array[i].payload=rand()%10;
        }

        for(int i=0; i<10; i++)
        {
            printf("id %d:\t%d\n",array[i].key,array[i].payload);
        }


        hist * hist_array=malloc(sizeof(hist)* pow(2,n));

        for(int i=0; i<pow(2,n); i++)
        {
            hist_array[i].binary=i;
            hist_array[i].count=0;
        }


        for(int i=0; i<10; i++)
        {
            for(int j=0; j<pow(2,n); j++)
            {
                //printf("%d  kai %d \n",array[i].payload & 0x2,hist_array[j].binary);
                if( (array[i].payload & 0x3)==hist_array[j].binary)
                {
                    //  printf("mphka\n");
                    hist_array[j].count++;
                }
            }
        }

        for(int i=0; i < pow(2,n); i++)
        {
            //printf("id %d: \t %d\n",hist_array[i].binary,hist_array[i].count);
        }


        hist * psum=malloc(sizeof(hist)*pow(2,n));
        psum[0].binary=0;
        psum[0].count=0;
        for(int i=1; i<pow(2,n); i++)
        {
            psum[i].binary=i;
            int k=i-1;
            psum[i].count=psum[k].count+hist_array[k].count;
        }

        for (int i = 0; i <pow(2,n) ; i++)
        {
            printf("id %d: \t %d\n",psum[i].binary,psum[i].count);

        }

        tuple *final_array=malloc(sizeof(struct tuple)*10);

        int where=0;
        while(where <= pow(2,n))
        {

            for(int i=psum[where].count; i<psum[where+1].count; i++)
            {
                for(int j=0; j<10; j++)
                {
                    if( (array[j].payload & 0x3)==where)
                    {
                        final_array[i].payload=array[j].payload;
                        final_array[i].key=array[j].key;
                        array[j].key=-1;
                        array[j].payload=-1;
                        break;
                    }
                }
            }
            where++;
        }
        for(int i=0; i<10; i++)
        {
            printf("id %d:\t%d\n",final_array[i].key,final_array[i].payload);

        }
    }


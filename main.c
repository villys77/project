#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/mman.h>
#include "structs.h"
#include "functions.h"


int main(int argc,char **argv)
{
    int i=0,j=0,z=0;
    FILE *file;
    file = fopen(argv[1], "r"); ////read file
    if (file == NULL)
    {
        printf("Error");
    }


    char *line = NULL;
    size_t len = 0;
    ssize_t my_read;

    int size_of_file = 0;
    while (!feof(file))
    {
        if ((my_read = getline(&line, &len, file)) != -1)
        {
            size_of_file++; //// count lines of doc
        }
    }

    data * my_data=malloc(sizeof(data)*size_of_file);

    rewind(file);

    while (!feof(file))
    {
        if ((my_read = getline(&line, &len, file)) != -1)
        {

            line[strcspn(line, "\n")] = 0;
            uint64_t * ptr=loadRelation(line);

            my_data[i].num_tuples=(int)ptr[0];
            my_data[i].num_columns=(int)ptr[1];
            my_data[i].array=malloc(sizeof(int*)*my_data[i].num_columns);
            my_data[i].array[0]=(int*)ptr;
            my_data[i].array[0]+=4;


            for( j=1; j<my_data[i].num_columns; j++)
            {
                my_data[i].array[j]=my_data[i].array[0] + ((my_data[i].num_tuples*2)*j);
            }

            i++;
        }
    }
/*
    for(int i=0; i<size_of_file; i++)
    {
        for(int j=0; j<my_data[i].num_columns; j++)
        {
            printf("%d ",*(my_data[i].array[j]));

        }
        printf("\n");
    }
*/

    int where=0;
    for(i=0; i<size_of_file; i++)
    {
        where=0;
        my_data[i].relations=malloc(sizeof(struct relation)*my_data[i].num_columns);
        for(j=0; j<my_data[i].num_columns; j++)
        {
            my_data[i].relations[j].tuples = malloc(sizeof(struct tuple)*my_data[i].num_tuples);

        }

        for( j=0; j<my_data[i].num_columns; j++)
        {
            where=0;

            for( z=0; z<my_data[i].num_tuples; z++)
            {

                my_data[i].relations[j].tuples[z].key=z;
                int *num=my_data[i].array[j];
                num+=where;
                my_data[i].relations[j].tuples[z].payload=*num;
                my_data[i].relations[j].tuples[z].check=0;
                where+=2;

            }
        }

    }

    /*
    for(int i=0; i<size_of_file; i++)
    {
        for(int j=0; j< my_data[i].num_columns; j++)
        {
            for(int z=0; z<my_data[i].num_tuples; z++)
            {

                printf("%d %d\n",my_data[i].relations[j].tuples[z].key,my_data[i].relations[j].tuples[z].payload);
            }
        }
    }
    */
    queries_analysis(argv[2],my_data);


    for(i=0; i<size_of_file; i++)
    {
        for( j=0; j< my_data[i].num_columns; j++)
        {
            free(my_data[i].relations[j].tuples);
        }
    }
    for(i=0; i<size_of_file; i++)
    {
        free(my_data[i].array);
        free(my_data[i].relations);
    }

    free(my_data);
    free(line);
    fclose(file);
}

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
//pameeeeeeeeee
#define n 12



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

    while(current->next != NULL){
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
        current->c=1;
        insertResults(Rid, Sid, current);
    }
    return;
}

void printResults(result* rhj,int num_of_matches)
{
    int i;
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

result * radish_hash_join(relation array_R,int R_size,relation array_S,int S_size)
{
    num_of_matches = 0;
    result *rhj=createResult();///dhmiourgia listas pou 8a xrhsimopoihsw argotera sto teleutaio stadio gia na krataw ta apotelesmata moy

    int power = pow(2, n); /// 2^n (megethos pinakwn psum kai hist)
    int mask = power - 1; //// maska gia &
    int i,j;
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
   // int i=0,j=0;
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
        int counter,k,temp1,temp2;
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
    /*
     *
     * for debugging

    int numrows = ptr[0];
    int numcol = ptr[1];

    for (int i = 2; i < numrows+2; i++)
    {
        for(int j = 0; j < numcol; j++)
        {
            printf("%d | ", (int)ptr[j*numrows+i]);
        }
        printf("\n");
    }

    printf("num rows = %d\n", (int)ptr[0]);
    printf("num columns = %d\n", (int)ptr[1]);

 */

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
    int c;
    int max = array[0].payload;


    for (c = 1; c < numrows; c++)
    {
        if (array[c].payload > max)
        {
            printf("mphkaaaa]\n\n");
            max = (int)array[c].payload;
            int location = array[c].key;
        }
    }
    return max;
}
void queries_analysis(char * FileToOpen,struct  data * my_data)
{

    FILE *file;
    if((file = fopen(FileToOpen, "r")) == NULL)
    {

        fprintf(stderr,"Error Opening file\n");
        exit(0);
    }

    char ch;
    size_t len = 0;
    ssize_t check;
    char* line = NULL;
    int i,j;
    int space_num = 0;
    int relations_to_check;
    int total_ques;
    int plus_num =0;
    char* temp_str = NULL;
    while(check = getline(&line , &len ,file ) != -1 )
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

        printf("%s|%s|%s\n",tokens[0],tokens[1],tokens[2]);

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
        //printf("%s\n",re);
        //printf("%d\n",id);
        mapping[0]=my_data[id];
        for(i=1; i<relations_to_check; i++)
        {

                char * temp=strtok_r(re," ",&re);
                //printf("%s\n",re);
                int id=atoi(temp);
                //printf("%d\n",id);
                mapping[i]=my_data[id];

        }
        free(sxeseis);
        //edw prepei na ftiaksoume enan pinaka me deiktes stous arxikous pinakes pou exoume wste na deixnoun oi relations_to_check
        //deiktes sta colls pou prepei

        //blepw posa queries exw.
        for(i=0; i<strlen(tokens[1]); i++)
        {
            if(line[i+strlen(tokens[0])] =='&')
            {
                plus_num ++;
            }
        }
        total_ques = plus_num + 1;

        printf("Exw sunolika %d sxeseis kai %d queries\n\n",relations_to_check,total_ques);
        //edw prepei na dhmiourghsw enan pinaka total_ques megethous opou tha balw mesa ena ena ta erwthmata pou mou zhtaei
        struct preds *predicates = malloc(total_ques*sizeof(struct preds));

        char* temp_str = malloc(strlen(tokens[1])*(sizeof(char)));
        bzero(temp_str ,strlen(tokens[1]));
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
                // printf("%c\n",predicates[counter].op);
                counter ++;
                erwthmata ++;
            }
        }
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

                    printf("%d.%d %c ",predicates[counter].relation1,predicates[counter].colum1,predicates[counter].op);

                    token = strtok(NULL , "&");

                    for(j =0; j<strlen(token); j++)
                    {
                        if(token[j] == '.')
                        {
                            token = strtok(token,".");
                            predicates[counter].relation2 = atoi(token);
                            token= strtok(NULL,"&");
                            predicates[counter].colum2 = atoi(token);

                            printf("%d.%d \n",predicates[counter].relation2,predicates[counter].colum2);
                            flag1 = 1;
                        }
                    }
                    if(flag1==1)
                    {
                        //printf("%d\n",mapping[ predicates[counter].relation1].num_tuples);
                        //printf("%d\n",mapping[ predicates[counter].relation2].num_tuples);

                        /*result * rjh=radish_hash_join(mapping[ predicates[counter].relation1].relations[predicates[counter].colum1],
                                                      mapping[ predicates[counter].relation1].num_tuples,
                                                      mapping[ predicates[counter].relation2].relations[predicates[counter].colum2],
                                                      mapping[predicates[counter].relation2].num_tuples);
                        printResults(rjh,num_of_matches);
                        free_list(rjh);*/
                    }


                    if(flag1 == 0)
                    {
                        predicates[counter].num = atoi(token);
                        printf("%d\n",predicates[counter].num);
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

                    printf("%d.%d %c " ,predicates[counter].relation1 , predicates[counter].colum1, predicates[counter].op );
                    token = strtok(NULL,"&");
                    predicates[counter].num = atoi(token);
                    printf("%d\n", predicates[counter].num);
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
                        printf("%d %c %d.%d\n" , predicates[counter].num , predicates[counter].op, predicates[counter].relation1,predicates[counter].colum1);
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
                        printf("%d %c %d.%d\n" , predicates[counter].num , predicates[counter].op, predicates[counter].relation1,predicates[counter].colum1);
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
                        printf("%d %c %d.%d\n" , predicates[counter].num , predicates[counter].op, predicates[counter].relation1,predicates[counter].colum1);
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
        printf("\n");
        space_num = 0;
        plus_num =0;
    }
}


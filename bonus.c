#include "gamelib.h"
#include<ctype.h>

#define NRMAX 100
#define PAS 2

int main()
{
    FILE *in=fopen("input","rt");
    FILE *out=fopen("output","wt");
    if( in == NULL || out == NULL)
    {
        printf("\n fisierul nu poate fi sdeschis");
        exit(1);
    }

    int nr_gen, i=0, j;
    char *linie = NULL;
    const char *p = NULL; // a pointer to use for strtok
    Stack *top = NULL;
    Node *head = NULL;
    int N = 0, M = 0;
    char *buffer=(char*)malloc(NRMAX*NRMAX*sizeof(char));
    if( buffer == NULL )
    {
        printf("\n alocare esuata");
        exit(1);
    }
    
    //reading stack's data
    while( fscanf(in,"%d",&nr_gen)== 1 ) // every row starts with nr_gen
    {
        i=0;
        fgetc(in);
        int *vector=(int*)malloc( NRMAX * sizeof(int) ); 
        printf("nr_gen = %d",nr_gen);
        linie=(char*)malloc( NRMAX * sizeof(char) );
        if(vector == NULL ||  linie == NULL)
        {
            printf("\n alocare esuata");
            exit(1);
        }
        fgets(linie,NRMAX,in); // fgets reads everything till the end of the row 
        p=strtok(linie," "); 
        // creating an array with all the coords per nr_gen
        while(p)
        {
            vector[i]=atoi(p); 
            i++;
            p=strtok(NULL," ");
        }

        //creating the list
        int NUMBERSPERLINE = i; 
        if( NUMBERSPERLINE % 2 == 1 )
        {
            printf("\n eroare NUMBERSPERLINE");
        }
        for( i = 0; i < NUMBERSPERLINE; i++ )
        {
            printf(" %d",vector[i]);
        }
        for( i = 0; i < NUMBERSPERLINE; i=i+PAS) // NUMBERSPERLINE is an even nr
        {
            insertNewNode(&head,vector[i],vector[i+1]); 
        }
        push(&top,head,nr_gen); 
       // printStackInstant(top); // debugging tool
        printStack(top); // debugging tool 
        head = NULL;
        free(vector);
        free(linie);
        printf("\n");
        linie=NULL; 
        vector=NULL;
    }
    fscanf(in,"\n");
    printStack(top); //double check
    linie=(char*)malloc(NRMAX*sizeof(char));
    if( linie == NULL )
    {
        printf("\n alocare esuata");
        exit(1);
    }
    //reading the array of N x M dimension
    while( fgets(linie,NRMAX,in) )
    {
        M=strlen(linie)-1; // 1 because of "\n"
        for (i = 0; i < M; i++) {
            *(buffer + N * M + i) = linie[i];
        }
        N++;
    }
    //creating the array
    char *matrice=(char*)malloc(N * M * sizeof(char)); 
    if( matrice == NULL )
    {
        printf("\n alocare esuata");
        exit(1);
    }
    printf("\n N=%d M=%d \n",N,M); 
    for(i = 0; i < N; i++ )
    {
        for( j = 0; j < M; j++ )
        {
            *(matrice + i * M + j) = *(buffer + i * M + j);
            printf("%c", *(matrice + i * M + j));
        }
        printf("\n");
    }
    free(buffer);
    buffer=NULL;
    free(linie);
    linie=NULL;
    while( top != NULL )
    {
        printf("\n Generatia %d",top->nr_gen);
        Node *temp=top->headList;
        while( temp != NULL)
        {
            int n,m; 
            n=temp->l;
            m=temp->c;  
            if (n >= 0 && n < N && m >= 0 && m < M)
            {
                printf("Modific matrice[%d][%d] din %c in ", n, m, *(matrice + M * n + m));
                if (*(matrice + M * n + m) == VIE)
                    *(matrice + M * n + m) = MOARTA;
                else
                    *(matrice + M * n + m) = VIE;
                printf("%c\n", *(matrice + M * n + m));
            }
            else
            {
                printf("Coordonate invalide: n=%d, m=%d\n", n, m);
            }
            temp=temp->urm;
        }  
    pop(&top);  
    }

    printf("\n N=%d M=%d \n",N,M);
    //writing in output file
    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < M; j++)
        {
            fprintf(out,"%c", *(matrice + i * M + j));
        }
    fprintf(out,"\n");
    }
    
    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < M; j++)
        {
            printf("%c", *(matrice + i * M + j));
        }
    printf("\n");
    }
    
    deleteStack(&top);
    free(matrice);
    matrice=NULL;
    fclose(in);
    fclose(out);
    return 0;
    }
    
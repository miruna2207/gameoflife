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
    const char *p = NULL;
    Stack *top = NULL;
    Node *head = NULL;
    int N = 0, M = 0;
    char *buffer=(char*)malloc(NRMAX*NRMAX*sizeof(char));
    if( buffer == NULL )
    {
        printf("\n alocare esuata");
        exit(1);
    }
    
    //citirea stivei
    while( fscanf(in,"%d",&nr_gen)== 1 ) // fiecare rand incepe cu nr_gen
    {
        i=0;
        fgetc(in);
        int *vector=(int*)malloc( NRMAX * sizeof(int) ); // vectorul va contine lista de coordonate de pe fiecare rand
        printf("nr_gen = %d",nr_gen);
        linie=(char*)malloc( NRMAX * sizeof(char) );
        if(vector == NULL ||  linie == NULL)
        {
            printf("\n alocare esuata");
            exit(1);
        }
        fgets(linie,NRMAX,in); // fgets citeste pana la \n
        p=strtok(linie," "); // strtok sa mi separe caracterele cautate(cifrele) de space
        while(p)
        {
            vector[i]=atoi(p); // atoi pentru a transforma din char in int
            i++;
            p=strtok(NULL," ");
        }

        //din vectorul construit formez lista
        int NUMBERSPERLINE = i; 
        if( NUMBERSPERLINE % 2 == 1 )
        {
            printf("\n eroare NUMBERSPERLINE");
        }
        for( i = 0; i < NUMBERSPERLINE; i++ )
        {
            printf(" %d",vector[i]);
        }
        for( i = 0; i < NUMBERSPERLINE; i=i+PAS) // NUMBERSPERLINE e nr par fiind format din perechi de coord
        {
            insertNewNode(&head,vector[i],vector[i+1]); // construim mai intai lista
        }
        push(&top,head,nr_gen); // in push voi crea o copie a lui head pt a evita erorile
        printStackInstant(top); // sa vad stiva ca in input
        printStack(top); // s o vad in forma ei din cod
        deleteList(&head);
        head=NULL; // necesar
        free(vector);
        free(linie);
        printf("\n");
        linie=NULL; // necesar
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
    //citire matrice finala
    while( fgets(linie,NRMAX,in) )
    {
        M=strlen(linie)-1; // 1 pentru endline
        for (i = 0; i < M; i++) {
            *(buffer + N * M + i) = linie[i];
        }
        N++;
    }
    char *matrice=(char*)malloc(N * M * sizeof(char)); // vr sa inlocuiesc buffer si sa exact atata memorie cat imi trebuie
    if( matrice == NULL )
    {
        printf("\n alocare esuata");
        exit(1);
    }
    printf("\n N=%d M=%d \n",N,M); // nu puteam afla N si M daca nu cream o matrice supradimensionata
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
    /*
    for( i = 0; i < N; i++ )
    {
        for( j = 0; j < M; j++ )
        {
            printf("\n v[%d][%d]=%c",i,j,*(buffer+M*i+j));
        }
    }
    */
    while(top != NULL)
    {
        printf("\n Generatia %d",top->nr_gen);
        Node *temp=top->headList;
        while( temp )
        {
            int n,m; // coordonatele punctelor
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
    //scriu matricea in output,stiu ca am un write_in_file_matrice, dar imi pune un \n in plus, care e bun pt outputul de la task1
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
    
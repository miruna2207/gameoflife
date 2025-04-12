#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "gamelib.h"

void next_matrice(FILE *text1,char *matrice,int N,int M)
{
	int i,j;
	char *copy=NULL;
	copy=(char*)malloc(N*M*sizeof(char));
	if(copy==NULL)
	{
		printf("\n Alocare dinamica esuata");
		exit(1);
	}
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			*(copy+i*M+j)=*(matrice+i*M+j);
		}
	}
	int vecini;
	for(i=0;i<N;i++)
	{   
		for(j=0;j<M;j++)
		{   
			vecini=calculare_vecini(copy,N,M,i,j);
			if(*(copy+i*M+j)==VIE)
			{ 
				if(vecini<2)
					*(matrice+i*M+j)=MOARTA;
				if(vecini==2 || vecini==3)
					*(matrice+i*M+j)=VIE;
				if(vecini>3)
					*(matrice+i*M+j)=MOARTA;
			}     
			if(*(copy+i*M+j)==MOARTA)
				{
				if(vecini==3)
					*(matrice+i*M+j)=VIE;
				else
					*(matrice+i*M+j)=MOARTA;
				}
		}
	}
	write_in_file_matrice(text1,matrice,N,M);
	free(copy);
};

void main(int argc, const char* argv[])
{
    for( int i = 0; i < argc; i++)
    {
        printf("argv[%d]= %s \n",i,argv[i]);
    }
	FILE *text=fopen(argv[1],"rt");
	FILE *text1=fopen(argv[2],"w+t");
	int task,i,j,N,M,nr_gen;
	char *matrice=NULL;
	if(text==NULL || text1==NULL)
	{
		printf("\n Fisierul nu poate fi deschis");
		exit(1);
	}
	fscanf(text,"%d",&task);
	fscanf(text, "\n");
	printf("\n task=%d",task);
	fscanf(text,"%d %d",&N,&M);
	fscanf(text, "\n");
	printf("\n N=%d M=%d",N,M);
	matrice=(char*)malloc(N*M*sizeof(char));
	if(matrice==NULL)
	{
		printf("\n Alocare dinamica esuata");
		exit(1);
	}
	fscanf(text,"%d",&nr_gen);
	printf("\n nr_gen=%d\n",nr_gen);
	fscanf(text, "\n");
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			fscanf(text,"%c",(matrice+i*M+j));
		}
		fscanf(text, "\n");
	}
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			printf("%c",*(matrice+i*M+j));
		}
		printf("\n");
	}
	switch(task)
	{
		case 1:
		{
		write_in_file_matrice(text1,matrice,N,M);
		for(i=0;i<nr_gen;i++)
		{
		next_matrice(text1,matrice,N,M);  
		}
		break;
		}
		case 2:
		{
			Stack *top=NULL;
			top=(Stack*)malloc(sizeof(Stack));
  			Node *head_gen=NULL;
   			if( top == NULL)
			{
			printf("\n alocare esuata");
			exit(1);
			}
			top->nr_gen=0;
			top->headList =NULL;
			top->next=NULL;

			for( i = 0; i < nr_gen; i++ )
			{
				writeChanges(&head_gen,matrice,N,M);
				printList(head_gen);
				push(&top,head_gen,i+1);
                fprintStack(top,text1);
                printStackInstant(top);
				deleteList(&head_gen);
			}
			deleteStack(&top);
			break;

		}
		default:
		{
			printf("\n taskul nu e bun");
		}
	}
	free(matrice);
	fclose(text);
	fclose(text1);
}


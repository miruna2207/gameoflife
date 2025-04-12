#include "gamelib.h"

int calculare_vecini(char *matrice,int N,int M,int i,int j)
{
    int vecini=0;
    if(i-1>=0)
    {
        if(*(matrice+(i-1)*M+j)==VIE)
            vecini++;
    }
    if(i+1<N)
    {
        if(*(matrice+(i+1)*M+j)==VIE)
            vecini++;
    }
    if(j-1>=0)
    {
        if(*(matrice+i*M+j-1)==VIE)
            vecini++;
    }
    if(j+1<M)
    {
        if(*(matrice+i*M+j+1)==VIE)
            vecini++;
    }
    if(i-1>=0 && j-1>=0)
    {
        if(*(matrice+(i-1)*M+j-1)==VIE)
            vecini++;
    }
    if(i+1<N && j+1<M)
    {
        if(*(matrice+(i+1)*M+j+1)==VIE)
            vecini++;
    }
    if(i-1>=0 && j+1<M)
    {
        if(*(matrice+(i-1)*M+j+1)==VIE)
            vecini++;
    }
    if(i+1<N && j-1>=0)
    {
        if(*(matrice+(i+1)*M+j-1)==VIE)
            vecini++;
    }
    return vecini;
};

void write_in_file_matrice(FILE *text1,char *matrice,int N,int M)
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            fprintf(text1,"%c",*(matrice+i*M+j));
        }
        fprintf(text1,"\n");
    }
    fprintf(text1,"\n");
};

void insertNewNode(Node **head,int i, int j)
{
    Node *newNode=(Node*)malloc(sizeof(Node));
    if( newNode == NULL)
    {
        printf("\n alocare esuata");
        exit(1);
    }
    newNode->l=i;
    newNode->c=j;
    newNode->urm=NULL;
    if( *head == NULL)
    {
        *head=newNode;
    }
    else
    {
        Node *temp=*head;
        while(temp->urm != NULL)
        {
            temp=temp->urm;
        }
        temp->urm=newNode;
    }
};

void deleteList(Node **head)
{
    if( *head == NULL ) 
        return ;
    while( *head != NULL)
    {
        Node *temp=NULL;
        temp = *head;
        *head = (*head)->urm;
        free(temp);
        temp = NULL;
    }
};

void printList(Node *head)
{
    Node *temp=head;
    while(temp)
    {
        printf("(%d,%d) ",temp->l,temp->c);
        temp=temp->urm;
    }
    printf("\n");
};


void push(Stack **top,Node *head,int k)
{
    Stack *newNode=(Stack*)malloc(sizeof(Stack));
    if ( newNode == NULL)
    {
        printf("\n alocare esuata");
        exit(1);
    }
    newNode->nr_gen=k;
    newNode->headList=head;
    newNode->next=NULL;
    if( *top == NULL)
    {
        newNode->next=NULL;
    }
    else
    {
        newNode->next=*top;
    }
    *top=newNode;
};

void printStackInstant(Stack *top)
{
        printf("Generatia %d\n",top->nr_gen);
        printf("Lista: ");
        printList(top->headList);
        printf("\n");
};


void fprintStack(Stack *top,FILE *text1)
{
        Node *temp=top->headList;
        fprintf(text1,"%d",top->nr_gen);
        while(temp)
        {
            fprintf(text1," %d %d",temp->l,temp->c);
            temp=temp->urm;
        }
        fprintf(text1,"\n");
};

void deleteStack(Stack **top)
{
    if (*top == NULL) return;
    Stack *temp=NULL;
    while(*top)
    {
        temp=*top;
        *top=(*top)->next;
        free(temp);
    }
};

void writeChanges(Node **head_gen, char *matrice, int N, int M)
{
    int i, j;
    char *copy =NULL;
    copy=(char*)malloc(N*M*sizeof(char));
    if (copy == NULL)
    {
        printf("\n Alocare dinamica esuata");
        exit(1);
    }
    for (i=0;i<N;i++)
    {
        for (j=0;j<M;j++)
        {
            *(copy+i*M+j) =*(matrice+i*M+j);
        }
    }

    int vecini;
    for (i=0;i<N;i++)
    {
        for (j=0;j<M;j++)
        {
            vecini=calculare_vecini(copy,N,M,i,j);
            if (*(copy+i*M+j) == VIE)
            {
                if (vecini < 2 || vecini > 3)
                {
                    *(matrice+i*M+j) = MOARTA;
                    insertNewNode(head_gen,i,j); 
                }
            }
            else if (*(copy+i*M +j) == MOARTA)
            {
                if (vecini == 3)
                {
                    *(matrice + i * M + j) = VIE;
                    insertNewNode(head_gen,i,j); 
                }
            }
        }
    }
    free(copy);
    copy=NULL;
};
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define VIE 'X'
#define MOARTA '+'

struct info{
    int l,c;
    struct info *urm;
};

typedef struct info Node;

struct stiva{
    int nr_gen;
    Node *headList;
    struct stiva *next;
};

typedef struct stiva Stack;

int calculare_vecini(char *matrice,int N,int M,int i,int j);

void write_in_file_matrice(FILE *text1,char *matrice,int N,int M);

void insertNewNode(Node **head,int i, int j);

void deleteList(Node **head);

void printList(Node *head);

void push(Stack **top,Node *head,int k);

void printStackInstant(Stack *top);

void fprintStack(Stack *top,FILE *text1);

void deleteStack(Stack **top);

void writeChanges(Node **head_gen,char *matrice,int N,int M);


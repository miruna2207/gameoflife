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

struct copac{
    Node *head;
    struct copac *left,*right;
};
typedef struct copac TreeNode;


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

char* RuleB(Node **head,char *matrice,int N,int M);

void parcurgereCopac(TreeNode* root);

void Matrix(char* matrice,int N,int M);

char* applyChanges(Node *head,char* matrice,int N,int M);

void right(TreeNode **root,char* matrice,int N,int M);

void left(TreeNode** root,char* matrice,int N,int M);

void parcurgere(TreeNode *root,const char* matrice,int N,int M,int lvl,int max);

void listingTreeM(TreeNode* root, char* matrice, int N, int M,FILE* text1, int lvl);

void deleteTree(TreeNode** root);

void next_matrice(FILE *text1,char *matrice,int N,int M);
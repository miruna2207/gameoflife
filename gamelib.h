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

typedef struct Ngraph{
    int l,c;
}Nodegraph;

typedef struct graphs{
    Nodegraph *v;
    int V; //nr of nodes
    int conex; //0 or 1
}graph;

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

void deleteGraph(graph** g);

void deleteTree(TreeNode** root);

void next_matrice(FILE *text1,char *matrice,int N,int M);

void pop(Stack **top);

void printStack(Stack *top);

graph* creategraph(char* m,int N,int M);

int isconnected(Nodegraph a,Nodegraph b);

int**  adjency_matrix(graph *g);

void DFS_scan(int**m,int V,int visited[],int i);

int DFS(int**m,int V,int* comp);

int is_best(int path[], int bestpath[], int n, graph* g);

void dfsPath(int** m, int V, int node, int* visited, int* path, int n, int* bestn, int* bestpath,graph* g);

void getLongestPath(int** m, int V, graph* g,int comp_conexe,int* comp);

int* copyINTarray(int* copy,int* original,int V);

#include "gamelib.h"

void next_matrice(FILE *text1,char *matrice,int N,int M)
{
	int i,j;
	char *copy = NULL;
	copy = (char*)malloc(N*M*sizeof(char));
	if( copy == NULL )
	{
		printf("\n Alocare dinamica esuata");
		exit(1);
	}
	for( i=0; i < N; i++ )
	{
		for( j = 0; j < M; j++ )
		{
			*(copy+i*M+j)=*(matrice+i*M+j); // strcpy is sometimes unstable
		}
	}
	int vecini;
	for( i = 0; i < N; i++ )
	{   
		for( j = 0; j < M; j++ )
		{   
			vecini = calculare_vecini(copy,N,M,i,j); // calculating for copy to avoid data inconsistency
			if(*(copy+i*M+j) == VIE)
			{ 
				if( vecini < 2 || vecini > 3)
					*(matrice + i * M + j) = MOARTA;
			}     
			if(*(copy+i*M+j) == MOARTA && vecini == 3)
				*(matrice+i*M+j) = VIE;
				
		}
	}
	write_in_file_matrice(text1,matrice,N,M);
	free(copy);
};

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
        *head = newNode;
    }
    else
    {
        Node *temp = *head;
        while(temp->urm != NULL)
        {
            temp = temp->urm;
        }
        temp->urm = newNode;
    }
};

void deleteList(Node **head)
{
    if( *head == NULL ) 
        return ;
    while( *head != NULL)
    {
       Node *temp = *head;
       *head = (*head)->urm;
        free(temp);
        temp = NULL;
    }
    *head = NULL;
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

void pop(Stack **top)
{
    if( *top == NULL )
        return;
    Stack *temp;
    temp = *top;
    *top = (*top)->next;
    deleteList(&(temp->headList));
    free(temp);
    temp = NULL;
}


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
    if( *top == NULL)
    {
        newNode->next=NULL;
    }
    else
    {
        newNode->next=*top;
    }
    *top = newNode;
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

void deleteStack(Stack** top) {
    while ((*top) != NULL) {  
        Stack *temp = *top;
        *top = (*top)->next;
        deleteList(&(temp->headList));
        free(temp);
        temp = NULL;
    }
}

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

void Matrix(char* matrice,int N,int M)
{
    int i,j;
    for( i = 0; i < N; i++ )
    {
        for( j = 0; j < M; j++ )
        {
            printf("%c ",*( matrice + i*M +j));
        }
        printf("\n");
    }
    printf("\n");
};

char* applyChanges(Node *head,char* matrice,int N,int M)
{
        while( head != NULL )
        {
            int n,m; // cells' coords
            n=head->l;
            m=head->c;  
            if (n >= 0 && n < N && m >= 0 && m < M)
            {
                    printf("\n da");
                   // printf("Modific matrice[%d][%d] din %c in ", n, m, *(matrice + M * n + m));
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
            head=head->urm;
        }
        return matrice;
};


void left(TreeNode** root,char* matrice,int N,int M)
{
	if( *root == NULL)
	{
		*root=(TreeNode*)malloc( sizeof(TreeNode) );
		if( *root == NULL )
		{
			printf("\n alocare esuata");
			exit(1);
		}
		(*root)->head = NULL;
		(*root)->left = (*root)->right = NULL;
	}
	RuleB(&((*root)->head),matrice,N,M);
}

void right(TreeNode **root,char* matrice,int N,int M)
{
	if( *root == NULL)
	{
		*root=(TreeNode*)malloc( sizeof(TreeNode));
		if( *root == NULL )
		{
			printf("\n alocare esuata");
			exit(1);
		}
		(*root)->head=NULL;
		(*root)->left = (*root)->right = NULL;
	}
	writeChanges(&( (*root)->head ),matrice,N,M);
}

void parcurgere(TreeNode *root,const char* matrice,int N,int M,int lvl,int max)
{
	if(root == NULL)
		return;
	if(lvl >= max)
		return;

	char* mat_st=(char*)malloc(N*M*sizeof(char)); // two matrix to avoid data race
	if(mat_st == NULL)
	{
		printf("\n alocare esuata");
		exit(1);
	}
	strcpy(mat_st,matrice);
	left( &(root->left),mat_st,N,M);
	parcurgere( (root->left),mat_st,N,M,lvl+1,max);
	free(mat_st);

	char* mat_dr=(char*)malloc( N*M* sizeof(char));
	if(mat_dr == NULL)
	{
		printf("\n alocare esuata");
		exit(1);
	}
	strcpy(mat_dr,matrice);
	right(&(root->right),mat_dr,N,M);
	parcurgere( (root->right),mat_dr,N,M,lvl+1,max);
	free(mat_dr);

};

void listingTreeM(TreeNode* root, char* matrice, int N, int M,FILE* text1, int lvl)
{
    if (!root)
        return;

	if( lvl != 0) // avoiding root because otherwise all the cells are DEAD
    	applyChanges(root->head, matrice, N, M); 
	write_in_file_matrice(text1,matrice,N,M);

    // the matrix for left side
    char* mat_st = (char*)malloc(N * M * sizeof(char));
    if (mat_st == NULL)
    {
        printf("\n Alocare dinamica esuata pentru mat_st");
        exit(1);
    }
    strcpy(mat_st, matrice);
    listingTreeM(root->left, mat_st, N, M,text1, lvl + 1);
    free(mat_st);

    // matrix for right side
    char* mat_dr = (char*)malloc(N * M * sizeof(char));
    if (mat_dr == NULL)
    {
        printf("\n Alocare dinamica esuata pentru mat_dr");
        exit(1);
    }
    strcpy(mat_dr, matrice);
    listingTreeM(root->right, mat_dr, N, M,text1, lvl + 1);
    free(mat_dr);
}

void deleteTree(TreeNode **root)
{
    if( *root == NULL )
        return ;
    deleteTree(&(*root)->left);
    deleteTree(&(*root)->right);
    deleteList(&(*root)->head);
    free(*root);
    *root = NULL;
}

void parcurgereCopac(TreeNode* root)
{
    //debbuging tool
    if( root == NULL )
        return;
    printList(root->head);
    parcurgereCopac(root->left);
    parcurgereCopac(root->right);
}

char* RuleB(Node **head,char *matrice,int N,int M)
{
    printf("\n inceput ruleB");
    Matrix(matrice,N,M);
    int i, j;
    char* copy=(char*)malloc( N*M*sizeof(char));
    for ( i = 0; i < N; i++)
    {
        for ( j = 0 ; j < M ; j++)
        {
            *(copy+i*M+j) =*(matrice+i*M+j);
        }
    }
    int vecini;
    for ( i = 0; i < N; i++ ) 
    {
        for ( j = 0 ; j < M ; j++)
        {
            vecini=calculare_vecini(copy,N,M,i,j);
            if (*(copy+i*M+j) == MOARTA && vecini == 2)
            {
                *(matrice + i * M + j) = VIE;
                printf("\n modific celula %d %d in Moarta",i,j);
                insertNewNode(head,i,j); 
            }
            }
        }
    
    printf("\n iesire ruleB");
    Matrix(matrice,N,M);
    free(copy);
    return matrice;
};  

void printStack(Stack *top)
{
        Node *temp=top->headList;
        printf("\n nr_gen=%d",top->nr_gen);
        while(temp)
        {
            printf(" ( %d,%d)",temp->l,temp->c);
            temp=temp->urm;
        }
};

graph* creategraph(char* m,int N,int M)
{   
    graph *g=(graph*)malloc( sizeof(graph));
    if( g == NULL)
    {
        printf("\n alocare esuata");
        exit(1);
    }
    g->v=(Nodegraph*)malloc(N*M*sizeof(Nodegraph));
    if( g->v == NULL ){
        printf("\n alocare esuata");
        exit(1);
    } 
    int index=0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++ )
        {
            if( m[ i * M + j ] == VIE)
            {
                g->v[index].l = i;  
                g->v[index].c = j;
                index++;
                g->V=index;
            }
        }
    }
    return g;
    
}

int isconnected(Nodegraph a,Nodegraph b)
{
    if( ((a.l-b.l) <= 1) && ((a.l-b.l) >= -1) && ((a.c-b.c) <= 1) && ((a.c-b.c) >= -1))
        return 1;
    else 
        return 0;
}

int**  adjency_matrix(graph *g)
{  
    int val;
    int i,j;
    int V=g->V;
    int** m=(int**)malloc( V * sizeof(int*));
    if( m == NULL ){
        printf("\n alocare esuata");
        exit(1);
    }
    for( i = 0; i < V; i++)
    {
        m[i]=(int*)malloc( V * sizeof(int));
        if( m[i] == NULL)
        {
            printf("\n alocare esuata");
            exit(1);
        }
    }
    for( i = 0; i < V; i++)
    {     
        for( j = 0; j < i; j++ )
        {
           val=isconnected(g->v[i],g->v[j]);
           m[i][j] = m[j][i] = val;
        }
    }
    return m;
}

void DFS_scan(int**m,int V,int visited[],int i)
{
    int j;
    visited[i] = 1;
    for( j = 0; j < V; j++)
    {
        if( m[i][j] == 1 && visited[j] == 0)
            DFS_scan(m,V,visited,j);
    }
    
}

int DFS(int**m,int V,int* comp)
{
    int i, *comp_conexe,visited[V];
    *comp_conexe = 0;
    for( i = 0; i < V; i++)
        visited[i] = 0;
    for( i = 0; i < V; i++)
    {
        if(visited[i] == 0){ // the nodes are in increasing order
            DFS_scan(m,V,visited,i);
            comp[*comp_conexe] = i;
            printf("\n hey,comp_conexe =%d",*comp_conexe);
            (*comp_conexe)++;
        }
    }
    printf("final =%d\n",*comp_conexe);
    return *comp_conexe;
}


int is_best(int path[], int bestpath[], int n, graph* g) {
    for (int i = 0; i < n; i++) {
        if (g->v[path[i]].l < g->v[bestpath[i]].l)
            return 1;
        if (g->v[path[i]].l > g->v[bestpath[i]].l) 
            return 0;
        if (g->v[path[i]].c <g->v[bestpath[i]].c) 
            return 1;
        if (g->v[path[i]].c >g->v[bestpath[i]].c) 
        return 0;
    }
    return 0;
}


void dfsPath(int** m, int V, int node, int* visited, int* path, int n, //basicly the dfs_scan code 
             int* bestn, int* bestpath,graph* g)                        // but saving the path and backtracking
{                                                                                   
    visited[node] = 1;
    path[n] = node;
    n++;
    if ( n > *bestn || ( n == *bestn && (is_best(path, bestpath, n, g) == 0))) 
    {
        *bestn = n;
        bestpath = copyINTarray(bestpath,path,V);
    }

    for (int i = 0; i < V; i++) {
        if (m[node][i] == 1 && visited[i] == 0) {
            dfsPath(m, V, i, visited, path, n, bestn, bestpath, g);
        }
    }

    visited[node] = 0; //backtrack 
    
}


void getLongestPath(int** m, int V, graph* g,int comp_conexe,int* comp) {
    int* visited=(int*)malloc( V * sizeof(int) );
    if( visited == NULL ){
        printf("\n alocare esuata");
        exit(1);
    }
    for(int i =  0; i < V; i++) 
        visited[i]=0;
    int* path = (int*)malloc( (V+1) *sizeof(int));
    int* bestpath= (int*)malloc( (V+1) *sizeof(int));
    if( path == NULL || bestpath == NULL){
        printf("\n alocare esuata");
        exit(1);
    }
    int bestn = -1;

    for (int start = 0; start < comp_conexe; start++) {
        dfsPath(m, V, comp[start], visited, path, 0, &bestn, bestpath, g);
    }

    if (bestn < V && g->conex == 1 ) {
        printf("-1\n");
        return;
    }

    printf("%d\n", bestn);
    for (int i = 0; i < bestn; i++) {
        printf("(%d,%d) ", g->v[bestpath[i]].l, g->v[bestpath[i]].c);
        
    }
    printf("\n");
}

int* copyINTarray(int* copy,int* original,int V){
    for(int i = 0; i < V; i++)
        {
            copy[i]=original[i];
        }
    return copy;
    
}

void deleteGraph(graph** g)
{
    free((*g)->v);
    (*g)->v = NULL;
    free(*g);
    *g = NULL;
};
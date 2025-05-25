#include "gamelib.h"
#include "graph.h"

/*
void push2(NodeM** top,TreeNode* root,int reverse){
    NodeM* new=(NodeM*)malloc( sizeof(NodeM) );
    if( new == NULL){
        printf("\n alocare esuata");
        exit(1);
    }
    new->root = root;
    new->reverse = reverse;
    new->next = *top;
    *top = new;
}

TreeNode* pop2(NodeM** top){

    if( *top == NULL)
        return NULL;

    NodeM* temp = *top;
    *top = (*top)->next;
    TreeNode* result=temp->root;
    free(temp);
    temp = NULL;
    return result;
}

int isEmpty(const NodeM* top){
    if( top == NULL)
        return 1;
    else
        return 0;
}

void Matrix_Graph_iterative(TreeNode* root,char* matrice_initiala,int N,int M,FILE* output,int lvl){

    if( root == NULL)
        return;

    NodeM* top = NULL;
    push2(&top,root,0);
    while( !isEmpty(top) )
    {
        TreeNode *current = pop2(&top);
        
        int reverse = 0;
        if( top != NULL)
            reverse = top->reverse;
        
        if( reverse == 0) {
            if( lvl!= 0)
                applyChanges(current->head,matrice_initiala,N,M);
            graph* g = creategraph(matrice_initiala,N,M);
            int** adj =adjency_matrix(g);
            int V = g->V;
            int* comp = (int*)calloc(V,sizeof(int));
            if( comp == NULL){
                printf("alocare esuata\n");
                exit(1);
            }
            int comp_conexe = DFS(adj,V,comp);
            graf_grade(g,adj);
            getLongestPath(adj,V,g,comp_conexe,comp,output,N,M);

            free(comp);
            comp = NULL;
            for(int i = 0; i < V; i++){
                free(adj[i]);
                adj[i] = NULL;
            }
            free(adj);
            adj = NULL;
            deleteGraph(&g);

            push2(&top,current,1);
             if( current->left != NULL && current->right != NULL)
            {
                push2(&top,current->right,0);
                push2(&top,current->left,0);
                
            }    
            lvl++;

        }
        else{
            if( lvl != 0)
                applyChanges(current->head,matrice_initiala,N,M);
            lvl--;
        }
         

    }
}
*/  
void writeOutput4(FILE *output,int n,const graph* g,const int* bestpath ){
    int i;
    fprintf(output,"%d\n",n-1);
    for( i = 0; i < n-1; i++)
       fprintf(output,"(%d,%d) ",g->v[bestpath[i]].l,g->v[bestpath[i]].c);
    fprintf(output , "(%d,%d)",g->v[bestpath[n-1]].l,g->v[bestpath[n-1]].c);
    fprintf(output,"\n");
}

void MatrixGraph(TreeNode* root, char* matrice, int N, int M,FILE* text1, int lvl)
{
    int i;
    if (root == NULL)
        return;

	if( lvl != 0) // avoiding root because otherwise all the cells are DEAD
    	applyChanges(root->head, matrice, N, M); 

    graph *g;
	g = creategraph(matrice,N,M);
    int** adj =adjency_matrix(g);
    int *comp=(int*)malloc( g->V * sizeof(int) );
    if( comp == NULL )
    {
        printf("\n alocare esuata");
        exit(1);
    }
    int comp_conexe;
    comp_conexe = DFS(adj,g->V,comp);
    /*printf("\n !!! comp_connexe = %d\n",comp_conexe);
    for( i = 0; i < comp_conexe; i++ )
        printf("\n comp conex %d = %d",i,comp[i]);*/
    if(comp_conexe == 1)
        g->conex = 1;
    else
        g->conex = 0;
    
    g = graf_grade(g,adj);
    getLongestPath(adj,g->V,g,comp_conexe,comp,text1,N,M);
    free(comp);
    for( i = 0; i < g->V; i++ )
        free(adj[i]);
    free(adj);
    deleteGraph(&g);


    // the matrix for left side
    char* mat_st = (char*)malloc(N * M * sizeof(char));
    if (mat_st == NULL)
    {
        printf("\n Alocare dinamica esuata pentru mat_st");
        exit(1);
    }
    memcpy(mat_st, matrice, N * M * sizeof(char));
    MatrixGraph(root->left, mat_st, N, M,text1, lvl + 1);
    free(mat_st);
    mat_st = NULL;

    // matrix for right side
    char* mat_dr = (char*)malloc(N * M * sizeof(char));
    if (mat_dr == NULL)
    {
        printf("\n Alocare dinamica esuata pentru mat_dr");
        exit(1);
    }
    memcpy(mat_dr, matrice, N * M * sizeof(char));
    MatrixGraph(root->right, mat_dr, N, M,text1, lvl + 1);
    free(mat_dr);
    mat_dr = NULL;
}

void deleteGraph(graph** g)
{
    free((*g)->v);
    (*g)->v = NULL;
    free(*g);
    *g = NULL;
};

int* copyINTarray(int* copy,const int* original,int V){
    for(int i = 0; i < V; i++)
        {
            copy[i]=original[i];
        }
    return copy; 
}

void getLongestPath(int** m, int V, graph* g,int comp_conexe,const int* comp,
                    FILE *output,int N,int M) {
    
    int i;
    int bestnglobal = -1;
    int* bestpathglobal = (int*)calloc( V , sizeof(int));

    int* visited=(int*)calloc( V, sizeof(int) );
    if( visited == NULL ){
        printf("\n alocare esuata");
        exit(1);
    }

    int* path = (int*)malloc ( V *sizeof(int));
    int* bestpath= (int*)malloc ( N*M*sizeof(int));
    if( path == NULL || bestpath == NULL){
        printf("\n alocare esuata");
        exit(1);
    }
    int bestnlocal;
    int* passed = (int*)calloc( V ,sizeof(int));
        if( passed == NULL){
            printf("\n alocare esuata");
            exit(1);
        }
    for (int start = 0; start < comp_conexe; start++) {
        
        for( i = 0; i < V; i++){
            passed[i] = 0;
            bestpath[i] = 0;
        }
        int comp_size = mark_component(m, V, comp[start],passed);
        bestnlocal = -1;
        int count = 0;
        for( i = 0; i < g->V; i++){
            if( passed[i] == 1 && g->v[i].grad == 1)
                count++;
               
        }
        if( count >= 3);
        else{
            for( i = 0; i < V; i++){
                if( passed[i] == 1)
                {
                    for(int j = 0; j < V; j++){
                        visited[j] = 0;
                        path[j] = 0;
                    }
                    printf("plec sa caut drumul \n");
                    dfsPath(m,V,i,visited,path,0,&bestnlocal,bestpath,g,comp_size);
                
                if(bestnlocal < comp_size)
                    printf("gresit -1 \n");
                if(bestnlocal == comp_size){
                    if( bestnglobal < bestnlocal)
                    {
                    bestnglobal = bestnlocal;
                    printf(" updatez global = %d\n",bestnglobal);
                    copyINTarray( bestpathglobal,bestpath,bestnglobal);
                   
                    break;
                    }
                    else if( bestnglobal == bestnlocal && is_best(bestpath,bestpathglobal,bestnlocal,g) == 1 ){
                     copyINTarray( bestpathglobal,bestpath,bestnlocal);
                
                    break;
                    }
                }
                }
            }
        }
    }             
    if( bestnglobal != -1 ){
        printf("%d\n", bestnglobal);
        for ( i = 0; i < bestnglobal; i++)
            printf("(%d,%d) ", g->v[bestpathglobal[i]].l, g->v[bestpathglobal[i]].c);
        printf("\n");
        writeOutput4(output,bestnglobal,g,bestpathglobal);
    }
    else
        fprintf(output,"-1\n");

    free(bestpath);
    free(visited);
    free(path);
    free(passed);
    passed = NULL;
    free(bestpathglobal);
}

int mark_component(int** m, int V, int node, int* passed) { //likely with dfs_scan
    int count = 1;
    passed[node] = 1;
    for (int i = 0; i < V; i++) {
        if (m[node][i] == 1 && passed[i] == 0) {
            count += mark_component(m, V, i, passed);
        }
    }
   // printf("\n count = %d",count);
    return count;
};

void dfsPath(int** m, int V, int node, int* visited, int* path, int n, //basicly the dfs_scan code 
             int* bestn, int* bestpath,graph* g,int comp_size)                        // but saving the path and backtracking
{   
    visited[node] = 1;
    path[n] = node;
    n++;
    if ( n > *bestn || ( n == *bestn && (is_best(path, bestpath, n, g) == 1))) 
    {
        *bestn = n;
        printf(" bestn = %d\n",*bestn);
        copyINTarray(bestpath,path,V);
    }
    if( *bestn == comp_size)
        return;

    for (int i = 0; i < V; i++) {
        if (m[node][i] == 1 && visited[i] == 0) {
            dfsPath(m, V, i, visited, path, n, bestn, bestpath, g,comp_size);
        }
    }

    visited[node] = 0; //backtrack 

}

int is_best(const int path[],const int bestpath[], int n,const graph* g) {
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
    return 1;
}

graph* creategraph(const char* m,int N,int M)
{   
    graph *g=(graph*)malloc( sizeof(graph) );
    if( g == NULL)
    {
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
                index++;
            }
        }
    }
    g->V = index;
    g->v= (Nodegraph*)malloc( index * sizeof(Nodegraph));
    if( g->v == NULL )
    {
        printf("\n alocare esuata\n");
        exit(1);
    }
    index = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++ )
        {
            if( m[ i * M + j ] == VIE)
            {
                g->v[index].l = i;
                g->v[index].c = j;
                index++;
            }
        }
    }
    return g;
    
}

int isconnected(Nodegraph a, Nodegraph b) {
    int dl = abs(a.l - b.l);
    int dc = abs(a.c - b.c);
    return (dl <= 1 && dc <= 1) && !(dl == 0 && dc == 0);
}

int**  adjency_matrix(const graph *g)
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
        m[i]=(int*)calloc( V , sizeof(int));
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

graph* graf_grade(graph* g,int** adj){
    
    int i,j;
    for(  i = 0; i < g->V; i++)
        g->v[i].grad = 0;
    for( i = 0; i < g->V; i++ )
    {
        for( j = 0; j < g->V; j++)
            if(adj[i][j] == 1)
                (g->v[i].grad)++;
    }
    return g;
}


void DFS_scan(int**m,int V,int* visited,int i)
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
    int i, comp_conexe;
    int* visited=(int*)calloc(V,sizeof(int));
    comp_conexe = 0;
    for( i = 0; i < V; i++)
    {
        if(visited[i] == 0){ // the nodes are in increasing order
            DFS_scan(m,V,visited,i);
            comp[comp_conexe] = i;
            (comp_conexe)++;
        }
    }
    free(visited);
    return comp_conexe;
}
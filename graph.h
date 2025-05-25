/*typedef struct stack{
    TreeNode *root;
    int reverse; // 1 for yes, 0 for no
    struct stack* next;
}NodeM;
*/
typedef struct Ngraph{
    int l,c;
    int grad;
}Nodegraph;

typedef struct graphs{
    Nodegraph *v;
    int V; //nr of nodes
    int conex; //0 or 1
}graph;

//void push2(NodeM** top,TreeNode* root,int reverse);

//TreeNode* pop2(NodeM** top);

//int isEmpty(NodeM* top);

//void Matrix_Graph_iterative(TreeNode* root,char* matrice_initiala,int N,int M,FILE* output,int lvl);

void writeOutput4(FILE *output,int n,const graph* g,const int* bestpath );

void MatrixGraph(TreeNode* root, char* matrice, int N, int M,FILE* text1, int lvl);

void deleteGraph(graph** g);

int* copyINTarray(int* copy,const int* original,int V);

void getLongestPath(int** m, int V, graph* g,int comp_conexe,const int* comp,
                    FILE *output,int N,int M);

int mark_component(int** m, int V, int node, int* passed);

void dfsPath(int** m, int V, int node, int* visited, int* path, int n, 
             int* bestn, int* bestpath,graph* g,int comp_size);

int is_best(const int path[],const int bestpath[], int n,const graph* g);

graph* creategraph(const char* m,int N,int M);

int isconnected(Nodegraph a, Nodegraph b);

int**  adjency_matrix(const graph *g);

graph* graf_grade(graph* g,int** adj);

void DFS_scan(int**m,int V,int* visited,int i);

int DFS(int**m,int V,int* comp);
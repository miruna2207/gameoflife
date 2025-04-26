#include "gamelib.h"

void main(int argc, const char* argv[])
{
    for( int i = 0; i < argc; i++)
    {
        printf("argv[%d]= %s \n",i,argv[i]);
    }
	FILE *input = fopen(argv[1],"rt");
	FILE *output = fopen(argv[2],"w+t");
	if( input==NULL || output==NULL)
	{
		printf("\n Fisierul nu poate fi deschis");
		exit(1);
	}

	int task,i,j,N,M,nr_gen;
	char *matrice=NULL;

	//reading input data
	fscanf(input,"%d",&task); 
	fscanf(input, "\n");
	printf("\n task=%d",task);

	fscanf(input,"%d %d",&N,&M);
	fscanf(input, "\n");
	printf("\n N=%d M=%d",N,M);

	matrice=(char*)malloc(N*M*sizeof(char));
	if(matrice==NULL)
	{
		printf("\n Alocare dinamica esuata");
		exit(1);
	}
	fscanf(input,"%d",&nr_gen);
	printf("\n nr_gen=%d\n",nr_gen);
	fscanf(input, "\n");
	for( i = 0; i < N; i++ )
	{
		for( j = 0; j < M; j++ )
		{
			fscanf(input,"%c", ( matrice + i * M + j ) );
		}
		fscanf(input, "\n");
	}
	for( i = 0; i < N; i++ )
	{
		for( j = 0; j < M; j++ )
		{
			printf("%c",*( matrice + i * M + j ) );
		}
		printf("\n");
	}

	switch(task)
	{
		case 1: // simulatte generations
		{
			write_in_file_matrice( output, matrice, N, M ); //initial matrix
			for( i = 0 ; i < nr_gen; i++ )
			{
			next_matrice( output, matrice, N, M );  
			}
			break;
		}
		case 2: // creating a stack which saves the differences between generations
		{
			Stack *top = NULL;
			top = (Stack*)malloc(sizeof(Stack));
  			Node *head_gen = NULL; // dynamic allocation adds an unwanted pair of (0,0)


   			if( top == NULL)
			{
			printf("\n alocare esuata");
			exit(1);
			}
			top->nr_gen = 0;
			top->headList = NULL;
			top->next = NULL;

			for( i = 0; i < nr_gen; i++ )
			{
				writeChanges( &head_gen, matrice, N, M); // write changes for each gen
				printList(head_gen); // print list on console(debuggin tool)
				push(&top, head_gen, i+1); //pushing list and the corresponding gen
                fprintStack(top, output); // printing stack per level
                printStackInstant(top); // debbuging tool
				head_gen = NULL;
			}
			deleteStack(&top);
			break;

		}

		case 3: // adding a new rule named ruleB and creating a binary tree to observe the difference
		{
			//creating root
			Node *head = NULL; 
			TreeNode *root=(TreeNode*)malloc( sizeof(TreeNode) ); 
			if( root == NULL)
			{
				printf("\n alocare esuata");
				exit(1);
			}
			root->head = NULL;
			root->left = NULL;
			root->right = NULL;
			for( i = 0;i < N; i++)
			{
				for( j = 0; j < M; j++)
				{
					if( *(matrice + i * M + j) == VIE )
						insertNewNode(&head, i, j);// root contains the coords of alive cells
				}
			}
			root->head = head;

			parcurgere(root, matrice, N, M, 0, nr_gen); // creating tree
			parcurgereCopac(root); //debugging tool(prints the tree on console)
			Matrix(matrice, N, M); //debugging tool printing matrix
			listingTreeM(root, matrice, N, M, output, 0); // writes in output file
			deleteTree(&root);

		}
		default:
		{
			printf("\n taskul nu e bun");
		}
	}
	free(matrice);
	fclose(input);
	fclose(output);
}




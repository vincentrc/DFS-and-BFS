/*
Program Name: Honors Project
Authour's Name: Vincent Crabtree
Class Day & Time: T/Th 3:00pm
This program allows the user to input a nodal graph and then displays the graph 
in matrix form. The program then performs and displays both depth and breadth 
first searches on the graph by first using arrays and loops, and then by using
a linked list and pointers. Finally, the program outputs the reults to a 
text file.
*/
#include <stdio.h>
#include <stdlib.h>

struct node
{
	int row1;
	int column1;
	int path;
	struct node *next;
};

void dfs(int num, int arr[50][50], int check[50], FILE *point1);
void bfs(int num, int arr[50][50], int check[50], FILE *point1);
void linkedListDFS(int num, struct node *head, int check[50], FILE *point1);
void linkedListBFS(int num, struct node *head, int check[50], FILE *point1);
int compareChecklist(int x, int check[50]);



int main()
{
	//Declarations
	int numNodes, a, x, y, val, i, j;
	int matrix[50][50], checklist[50], checklist2[50];
	int row, column;
	struct node *newNode, *prev, *head;
	FILE *point;
	char ch1=10;

	


	printf("Please enter the number of nodes in the graph:\n");
	scanf("%d", &numNodes);
	printf("\n\nPlease input the graph according to the following:\n\n");
	printf("If there is a path from the first node to the second, enter 1.\n\n");
	printf("If there is a path from the second node to the first, enter -1.\n\n");
	printf("If there is no path between the nodes, enter 0\n\n");

	//Take input for graph
	for(i=1;i<=numNodes;i++)
	{
		for(j=1;j<=numNodes;j++)
		{
			printf("Node %d and Node %d: ", i, j);
			scanf("%d", &val);
			if(val!=1&&val!=0&&val!=-1)
			{
				printf("\n\nInvalid input, try again:\n\n");
				j--;
				continue;
			}
			else 
				matrix[i][j] = val;
		}
	}

	//Display matrix
	printf("\n");
	printf("   ");
	for(a=1;a<=numNodes;a++)
	{
		printf("%d  ", a);
	}
	printf("\n\n");	
	for(x=1;x<=numNodes;x++)
	{
		printf("%d",x);
		for(y=1;y<=numNodes;y++)
		{
			printf("%3d", matrix[x][y]);
		}
		printf("\n\n");				
	}

	//Create Linked List of Matrix
	head=(struct node*)malloc(sizeof(struct node));
	prev=head;
	for(row=1;row<=numNodes;row++)
	{
		for(column=1;column<=numNodes;column++)
		{
			
			newNode=(struct node*)malloc(sizeof(struct node));
			if(row==1&&column==1)
				head=newNode;
			newNode->row1=row;
			newNode->column1=column;
			newNode->path=matrix[row][column];
			newNode->next=NULL;
			prev->next=newNode;
			prev=newNode;
			
		}
	}

	point=fopen("searches.txt","w");

	//Depth First Searches 
	fprintf(point,"Array Depth First Search:\n");
	dfs(numNodes, matrix, checklist, point);
	for(x=0;x<50;x++)
	{
		checklist[x] = 0;
	}
	fprintf(point,"\n\n");
	
	fprintf(point,"Linked List Depth First Search:\n");
	linkedListDFS(numNodes, head, checklist2, point);
	for(x=0;x<50;x++)
	{
		checklist2[x] = 0;
	}
	fprintf(point,"\n\n");

	//Breadth First Searches
	fprintf(point,"Array Breadth First Search:\n");
	bfs(numNodes, matrix, checklist, point);
	fprintf(point,"\n\n");
	
	fprintf(point,"Linked List Breadth First Search:\n");
	linkedListBFS(numNodes, head, checklist2, point);
	fprintf(point,"\n\n");

	fclose(point);
		
}

		


void dfs(int num, int arr[50][50], int check[50], FILE *point1)
{
	int i, j, start, k, c=0;
	
	
	while(1)
	{
		printf("Please enter a node to start the DFS on:\n");
		scanf("%d", &start);
		if(start<1||start>num)
		{
			printf("\n\nInvalid entry, please try again:\n\n");
			continue;
		}
		else
			break;
	}

	printf("\n\nSearch:\n\n");
	printf("%d->", start);
	fprintf(point1,"%d->",start);
	check[c]=start;
	c++;
	k = start;

	for(i=1;i<=num;i++)
	{
		for(j=1;j<=num;j++)
		{
			if(arr[k][j]==1&&compareChecklist(j,check)==1)
			{
				printf("%d->", j);
				fprintf(point1,"%d->", j);
				k=j;
				check[c]=j;
				c++;
				j=0;
				continue;
			}
	
		}
		k=start;
	}
	printf("End\n\n");
	fprintf(point1,"END");

}

void bfs(int num, int arr[50][50], int check[50], FILE *point1)
{
	int start, i, j, k, c=0;
	int  a=0;
	
	while(1)
	{
		printf("Please enter a node to start the BFS on:\n");
		scanf("%d", &start);
		if(start<1||start>num)
		{
			printf("\n\nInvalid entry, please try again:\n\n");
			continue;
		}
		else
			break;
	}

	printf("\n\nSearch:\n\n");
	printf("%d->", start);
	fprintf(point1,"%d->",start);
	k = start;
	check[c] = start;
	c++;

	for(i=1;i<=num;i++)
	{
		for(j=1;j<=num;j++)
		{
			if(arr[k][j]==1&&compareChecklist(j,check)==1)
			{
				printf("%d->", j);
				fprintf(point1,"%d->", j);
				check[c]=j;
				c++;
			}
		}
	k=check[a];
	a++;
	}
	printf("End\n\n");
	fprintf(point1,"END");
}

void linkedListDFS(int num, struct node *head, int check[50], FILE *point1)
{
	int i, k, c=0;
	int start;
	struct node *ptr;
	
	while(1)
	{
		printf("Please enter a node to start the linked list DFS on:\n");
		scanf("%d", &start);
		if(start<1||start>num)
		{
			printf("\n\nInvalid entry, please try again:\n\n");
			continue;

		}
		else 
			break;
	}
	
	k=start;
	check[c]=start;
	c++;
	printf("\n\nSearch:\n\n");
	printf("%d->", start);
	fprintf(point1,"%d->",start);
	for(i=1;i<=num;i++)
	{
		for(ptr=head;ptr!=NULL;ptr=ptr->next)
		{
			if(ptr->row1==k&&ptr->path==1
				&&compareChecklist(ptr->column1,check)==1)
			{
				printf("%d->", ptr->column1);
				fprintf(point1,"%d->",ptr->column1);
				check[c]=ptr->column1;
				c++;
				k=ptr->column1;
				ptr=head;
			}
		}
		k=start;
	}
	printf("END\n\n");
	fprintf(point1,"END");
}

void linkedListBFS(int num, struct node *head, int check[50], FILE *point1)
{
	int i, k, c=0, a=0;
	int start;
	struct node *ptr;

	while(1)
	{
		printf("Please enter a node to start the linked list BFS on:\n");
		scanf("%d", &start);
		if(start<1||start>num)
		{
			printf("\n\nInvalid entry, please try again:\n\n");
			continue;
		}
		else
			break;
	}

		k=start;
		check[c]=start;
		c++;
		printf("\n\nSearch:\n\n");
		printf("%d->", start);
		fprintf(point1,"%d->",start);
		for(i=1;i<=num;i++)
		{
			for(ptr=head;ptr!=NULL;ptr=ptr->next)
			{
				if(ptr->row1==k&&ptr->path==1
					&&compareChecklist(ptr->column1,check)==1)
				{
					printf("%d->", ptr->column1);
					fprintf(point1,"%d->",ptr->column1);
					check[c]=ptr->column1;
					c++;
				}
			}
			k=check[a];
			a++;
		}
	printf("END\n\n");
	fprintf(point1,"END");
}

int compareChecklist(int x, int check[50])
{
	int i;
	for(i=0;i<50;i++)
	{
		if(x==check[i])
			return 0;
	}
	return 1;
}
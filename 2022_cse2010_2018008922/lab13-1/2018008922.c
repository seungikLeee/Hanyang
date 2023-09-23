#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fin;
FILE *fout;

typedef struct _Queue{
	int* key;
	int first, rear, qsize, max_queue_size;
}Queue;

typedef struct _Graph{
	int size;
	int* node;
	int** matrix;
}Graph;

Graph* CreateGraph(int* nodes, int n);
void InsertEdge(Graph* G, int a, int b);
void PrintGraph(Graph* G);
void DeleteGraph(Graph* G);
void Topsort(Graph* G);
Queue* MakeNewQueue(int X);
int IsEmpty(Queue* Q);
int Dequeue(Queue* Q);
void Enqueue(Queue* Q, int X);
void DeleteQueue(Queue* Q);
void countInput(int* n, char* str);
void parseInput(int* arr, char* str, int n);

int main(int argc, char* agrv[]){
	fin = fopen(agrv[1], "r");
	fout = fopen(agrv[2], "w");

	char numbers[100], inputs[150];
	fgets(numbers, 100, fin);

	int n=0;
	countInput(&n, numbers);

	int* nodes = (int*)malloc(sizeof(int)*n);
	parseInput(nodes, numbers, n);

	Graph* G = CreateGraph(nodes, n);

	fgets(inputs, 100, fin);
	int len = strlen(inputs), i;

	for(i=0; i<len; i += 4){
		int a = inputs[i] - '0', b = inputs[i+2]-'0';
		
		InsertEdge(G, a, b);
	}

	PrintGraph(G);
	Topsort(G);
	DeleteGraph(G);

	fclose(fin);
	fclose(fout);

	return 0;
}

void countInput(int* n, char* str){
	int len = strlen(str), i;
	for(i=0; i<len; i++)
		if(0 <= str[i] - '0' && str[i] - '0'< 10) (*n)++;
}

void parseInput(int* arr, char* str, int n){
	int len = strlen(str), i;
	int cnt = 0;

	for(i=0; i<len; i++)
		if(0 <= str[i] - '0' && str[i] - '0' < 10) arr[cnt++] = str[i] - '0';
	

}

Graph* CreateGraph(int* nodes, int n){
	Graph* newG = (Graph*)malloc(sizeof(struct _Graph));
	newG->size = n;
	newG->node = nodes;
	newG->matrix = (int**)malloc(sizeof(int*)*n);

	for(int i=0; i<n; i++){
		newG->matrix[i] = (int*)malloc(sizeof(int)*n);
		memset(newG->matrix[i],0,sizeof(int)*n);
	}
	return newG;
}

void InsertEdge(Graph* G, int a, int b){
	int i,j,temp;
	for(int k=0; k<G->size; k++){
		for(int l=0; l<(G->size-1)-k; l++){
			if (G->node[l] > G->node[l + 1]) {
				temp = G->node[l];
				G->node[l] = G->node[l + 1];
				G->node[l + 1] = temp;		
			}
		}
	}
	for(i=0; i<G->size; i++){
		if(G->node[i]==a){
			break;
		}
	}
	for(j=0; j<G->size; j++){
		if(G->node[j]==b){
			break;
		}
	}
	G->matrix[i][j] = 1;
}

void PrintGraph(Graph* G){
	fprintf(fout, "   ");
	
	for(int i=0; i<G->size; i++){
		fprintf(fout, "%d  ", G->node[i]);
	}
	fprintf(fout, "\n");
	for(int i=0; i<G->size; i++){
		fprintf(fout, "%d  ", G->node[i]);
		for(int j=0; j<G->size; j++){
			fprintf(fout, "%d  " ,G->matrix[i][j]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
}

void DeleteGraph(Graph* G){
	for(int i=0; i<G->size; i++){
		free(G->matrix[i]);
	}
	free(G->matrix);
	free(G);
}

void Topsort(Graph* G){
	Queue* Q = MakeNewQueue(G->size);
	int result[G->size];
	for(int i=0; i<G->size; i++){
		int flag=0;
		for(int j=0; j<G->size; j++){
			if(G->matrix[j][i]==1){
				flag=1;
			}
		}
		if(flag==0){
			Enqueue(Q,G->node[i]);		
		}
	}

	for(int i=0; i<G->size; i++){
		if(IsEmpty(Q)){
			fprintf(fout, "sorting error : cycle!\n");
			return;
		}

		result[i] = Dequeue(Q);
		int cur=0;
		for(int l=0; l<G->size; l++){
			if(result[i]==G->node[l]){
				cur = l;
				break;
			}
		}
		for(int j=0; j<G->size; j++){
			G->matrix[cur][j]=0;
		}		

		for(int i=0; i<G->size; i++){
			int flag=0;
			for(int j=0; j<G->size; j++){
				if(G->matrix[j][i]==1){
					flag=1;
				}
			}
			if(flag==0){
				int check_flag = 0;
				for(int j = 0; j < Q->max_queue_size; j++)
				{
					if(G->node[i] == Q->key[j]){
						check_flag = 1;
					}
				}
				if(check_flag==0){
					Enqueue(Q,G->node[i]);
				}	
			}
		}
	}

	for(int i=0; i<G->size; i++){
		fprintf(fout,"%d " , result[i]);
	}
	fprintf(fout, "\n");
}

Queue* MakeNewQueue(int X){
	Queue* newQ = (Queue*)malloc(sizeof(struct _Queue));
	newQ->key = (int*)malloc(sizeof(int)*X);
	for(int i=0; i<X; i++){
		newQ->key[i] = 0;
	}
	newQ->first = 0;
	newQ->rear = -1;
	newQ->max_queue_size = X;
	newQ->qsize=0;
	
	return newQ;
}

int IsEmpty(Queue* Q){
	if(Q->qsize==0){
		return 1;
	}
	else{
		return 0;
	}
}

int Dequeue(Queue* Q){
	if(IsEmpty(Q)){
		fprintf(fout, "queue is empty!\n");
	}
	else{
		Q->qsize--;
		return Q->key[Q->first++];
	}
}

void Enqueue(Queue* Q, int X){
	if(Q->qsize>=Q->max_queue_size){
		fprintf(fout, "queue is full!\n");
	}
	else
	{
		Q->qsize++;
		Q->rear++;
		Q->key[Q->rear] = X;
	}
}

void DeleteQueue(Queue* Q){
	free(Q);
}

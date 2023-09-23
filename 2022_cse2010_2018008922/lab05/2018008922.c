#include<stdio.h>
#include<stdlib.h>

#define MAX_NODE_NUM 100
#define MAX_KEY_NUM 10000

FILE *fin;
FILE *fout;

typedef struct ThreadedTree* ThreadedPtr;
typedef int ElementType;
int level=0;
struct ThreadedTree {
	int left_thread;
	ThreadedPtr left_child;
	ElementType data;
	ThreadedPtr right_child;
	int right_thread;
}ThreadedTree;

ThreadedPtr ta[MAX_NODE_NUM+1];

ThreadedPtr CreateTree();
ThreadedPtr InPred(ThreadedPtr root);
ThreadedPtr InSucc(ThreadedPtr root);
int Insert(ThreadedPtr root, int root_idx, ElementType data, int idx);
void printInorder(ThreadedPtr root);
void DeleteTree(ThreadedPtr root);

int ppow(int a, int b){
	int c=1;
	for(int i=0; i<b; i++){
		c=c*a;
	}
	return c;
}

ThreadedPtr CreateTree(){
	ThreadedPtr tree = NULL;
	tree = (ThreadedPtr)malloc(sizeof(ThreadedTree));
	if(tree==NULL){
		fprintf(fout, "Out of Space!\n");
		return NULL;
	}
	tree->data = -1;
	tree->left_thread = 1;
	tree->left_child = tree;
	tree->right_thread = 1;
	tree->right_child = tree;
	
	return tree;
}

int Insert(ThreadedPtr root, int root_idx, ElementType data, int idx){
 	int i = idx;

	ThreadedPtr tmp;
	tmp = (ThreadedPtr)malloc(sizeof(ThreadedTree));
	if(tmp==NULL){
		fprintf(fout, "Out of Space!\n");
		return 0;
	}
	

	if(i==1){
		level++;
	
		root->right_thread=0;
		root->right_child=tmp;
		tmp->left_thread=1;
		tmp->left_child=root;
		tmp->right_thread=1;
		tmp->right_child=root;
	}
	
	else{	
		if(i%2==0){
			ta[i/2]->left_thread=0;
			ta[i/2]->left_child=tmp;
			
			tmp->left_thread=1;
			if(idx==ppow(2,level-1)){
				tmp->left_child=root;
			}
			else{
				tmp->left_child=ta[i/2/2];
			}
			
			tmp->right_thread=1;
			tmp->right_child=ta[i/2];
		}
		else{
			ta[i/2]->right_thread=0;
			ta[i/2]->right_child=tmp;

			tmp->left_thread=1;
			tmp->left_child=ta[i/2];
			
			tmp->right_thread=1;
			if(idx==(ppow(2,level)-1)){
				tmp->right_child=root;
			}
			else{
				tmp->right_child=ta[i/2/2];
			}	
		}
	}
	
	tmp->data=data;
	ta[i]=tmp;
	
	if(idx==ppow(2,level)-1){
		level++;
	}

	return idx;
	
}

void printInorder(ThreadedPtr root){
	fprintf(fout, "inorder traversal : ");
		
	ThreadedPtr tmp = root;
	while(1){
		tmp = InSucc(tmp);
		if(tmp==root){
			break;
		}
		fprintf(fout, "%d ",tmp->data);

	}
	fprintf(fout, "\n");
}

void DeleteTree(ThreadedPtr root){
	ThreadedPtr tmp = InSucc(root);
	while(1){
		ThreadedPtr tmp1=InSucc(tmp);
		free(tmp);
		tmp=tmp1;

		if(tmp==root){
			free(tmp);
			break;
		}
	}
}

ThreadedPtr InPred(ThreadedPtr root){
	ThreadedPtr tmp;
	tmp = root->left_child;
	if(!(root->left_thread)){
		while(!(tmp->right_thread)){
			tmp=tmp->right_child;
		}
	}
	return tmp;
}


ThreadedPtr InSucc(ThreadedPtr root){
	ThreadedPtr tmp;
	tmp = root->right_child;
	if(!(root->right_thread)){
		while(!(tmp->left_thread)){
			tmp=tmp->left_child;
		}
	}
	return tmp;
}

int main(int argc, char *argv[]){
	fin=fopen(argv[1], "r");
	fout=fopen(argv[2], "w");

	ThreadedPtr root = CreateTree();
	int NUM_NODES;
	fscanf(fin, "%d", &NUM_NODES);
	if(NUM_NODES>MAX_NODE_NUM){
		fprintf(fout,"error: max node num is %d!\n",MAX_NODE_NUM);
		return 0;
	}
	int root_idx=0, idx=0;

	while(++idx <= NUM_NODES){
		ElementType data;
		fscanf(fin, "%d", &data);
		if(data>MAX_KEY_NUM){
			fprintf(fout, "error: max key num is %d!\n",MAX_KEY_NUM);
			return 0;
		}
		if(Insert(root, root_idx, data, idx) == 0){
			return 0;
		}
	}

	printInorder(root);
	DeleteTree(root);

	fclose(fin);
	fclose(fout);

	return 0;
}

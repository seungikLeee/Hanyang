#include<stdio.h>
#include<stdlib.h>

FILE *fin;
FILE *fout;

typedef struct BNode* BNodePtr;

struct BNode{ 
	int order;
        int size;		/*number of keys*/
        BNodePtr *child;	/*children pointers*/
	int *key;		/*keys*/ 
	int is_leaf;		/*is_leaf is not 0 -> number of children is size+1*/
	int is_root;
}BNode;

BNodePtr CreateTree(int order);
void Insert(BNodePtr *root, int key);
int Find(BNodePtr root, int key);
int DeleteTree(BNodePtr root);
void PrintTree(BNodePtr root);

int main(int argc, char* argv[]){
        fin = fopen(argv[1], "r");
        fout = fopen(argv[2], "w");

        int order;
        fscanf(fin, "%d", &order);
	BNodePtr root = CreateTree(order);
	root->is_root=1;
        char cv;
	int key;

        while(!feof(fin)){
                fscanf(fin, "%c", &cv);
                switch(cv){
                        case 'i':
                                fscanf(fin, "%d", &key);
                                if(Find(root,key))
					fprintf(fout, "insert error : key %d is already in the tree!\n", key);
				else
					Insert(&root, key);
                                break;
                        case 'f':
                                fscanf(fin, "%d", &key);
                                if(Find(root,key))
					fprintf(fout, "key %d found\n", key);
				else
					fprintf(fout, "finding error : key %d is not in the tree!\n", key);
                                break;
                        case 'p':
                                if(root->size==0)
					fprintf(fout, "print error : tree is empty!");
				else
					PrintTree(root);
				fprintf(fout, "\n");
				break;
                }
        }

	DeleteTree(root);
	fclose(fin);
	fclose(fout);

        return 0;
}

BNodePtr CreateTree(int order){
	BNodePtr c_root;
	c_root = (BNodePtr)malloc(sizeof(struct BNode));
	c_root->order = order;
	c_root->size = 0;
	
	c_root->child = (BNodePtr*)malloc((order+1)*sizeof(BNodePtr));
	
	for(int i=0; i<order+1; i++){
		c_root->child[i] = NULL;
	}
	
	c_root->key = (int*)malloc(order*sizeof(int));
	
	for(int j=0; j<order; j++){
		c_root->key[j] = 0;
	}
	c_root->is_leaf = 1;
	c_root->is_root = 0;	
	return c_root;
}

BNodePtr splitChild(BNodePtr root)
{
	int i, mid;

	BNodePtr newParent;
	BNodePtr newSibling;

	newParent = CreateTree(root->order);
	newParent->is_leaf=0;

	if(root->is_root){
		newParent->is_root=1;
	}
	root->is_root=0;

	newSibling = CreateTree(root->order);
	newSibling->is_leaf= root->is_leaf;

	mid=(root->order-1)/2;
	for(i=mid+1; i<root->order; i++){
		newSibling->child[i-(mid+1)] = root->child[i];
		newSibling->key[i-(mid+1)] = root->key[i];
		newSibling->size++;

		root->child[i]=NULL;
		root->key[i]=0;
		root->size--;
	}
	
	newSibling->child[i-(mid+1)] = root->child[i];
	root->child[i]=NULL;

	newParent->key[0] = root->key[mid];
	newParent->size++;
	root->key[mid]=0;
	root->size--;

	newParent->child[0] = root;
	newParent->child[1] = newSibling;

	return newParent;
}


void Insert(BNodePtr *root, int key){
	int i,pos,mid;
	BNodePtr split;

	if((*root)->is_leaf){
		for(pos=0; pos<(*root)->size; pos++){
			if((*root)->key[pos] > key){
				break;
			}
		}
		for(i=(*root)->size; i>pos; i--){
			(*root)->key[i] = (*root)->key[i-1];
		}
		(*root)->key[pos]=key;
		(*root)->size++;

		if((*root)->size==(*root)->order&&(*root)->is_root){
			*root = splitChild(*root);
		}
	}
	else{
		for(pos=0; pos<(*root)->size; pos++){
			if((*root)->key[pos] >key){
				break;
			}
		}
		Insert(&((*root)->child[pos]),key);

		if(((*root)->child[pos])->size==(*root)->order){
			split = splitChild((*root)->child[pos]);
			for(i=(*root)->size; i>pos; i--){
				(*root)->key[i] = (*root)->key[i-1];
				(*root)->child[i+1] = (*root)->child[i];
			}
				
			(*root)->key[pos] = split->key[0];
			(*root)->size++;
			(*root)->child[pos] = split->child[0];	
			(*root)->child[pos+1] = split->child[1];
		}
		if((*root)->size==(*root)->order&&(*root)->is_root){
			*root = splitChild(*root);
		}
	}
}

int Find(BNodePtr root, int key){
	BNodePtr level = root;

	while(1){
        	int i;
		for(i=0; i<level->size; i++){
                	if(level->key[i]==key){
				return 1;
			}
			else if(level->key[i]>key){
				break;
			}
		}
		if(level->is_leaf){
			break;
		}
		level = level->child[i];
	}
	return 0;
}

int DeleteTree(BNodePtr root){
	free(root);
}

void PrintTree(BNodePtr root){
	int i;
	for(i=0; i<root->size; i++){
		if(!(root->is_leaf)){
			PrintTree(root->child[i]);
		}

		fprintf(fout, "%d ", root->key[i]);
	}
 	if(!(root->is_leaf)){        
		PrintTree(root->child[i]);    
	}
}



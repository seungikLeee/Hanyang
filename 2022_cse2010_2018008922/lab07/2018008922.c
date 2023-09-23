#include<stdio.h>
#include<stdlib.h>

FILE *fin;
FILE *fout;

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

typedef struct AVLNode{
	ElementType element;
	AVLTree left, right;
	int height;
}AVLNode;

AVLTree Insert(ElementType X, AVLTree T);
AVLTree Delete(ElementType X, AVLTree T);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
void PrintInorder(AVLTree T);
void DeleteTree(AVLTree T);

int max(int a, int b){
	if(a>=b){
		return a;
	}
	else{
		return b;
	}
}

int Height(Position node){
	if(node==NULL){
		return -1;
	}
	return node->height;
}

AVLTree findMin(AVLTree T){
        if(T==NULL){
                return NULL;
        }
        if(T->left==NULL){
                return T;
        }
        return findMin(T->left);
}

Position SingleRotateWithLeft(Position node){
 	Position tmp;
	tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;

	node->height = max(Height(node->left), Height(node->right))+1;
	tmp->height = max(Height(tmp->left), node->height) +1;

	return tmp;
}

Position SingleRotateWithRight(Position node){
	Position tmp;
	tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;

	node->height = max(Height(node->left), Height(node->right))+1;
        tmp->height = max(Height(tmp->right), node->height) +1;
	
	return tmp;
}

Position DoubleRotateWithLeft(Position node){
	node->left = SingleRotateWithRight(node->left);

	return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node){
	node->right = SingleRotateWithLeft(node->right);

	return SingleRotateWithRight(node);
}

AVLTree Insert(ElementType X, AVLTree T){
	if(T==NULL){
		T = malloc(sizeof(struct AVLNode));
		T->element=X;
		T->height=0;
		T->left=T->right=NULL;
	}
	else if(X<T->element){
		T->left = Insert(X,T->left);
		if(Height(T->left)-Height(T->right)>=2){
			if(X<T->left->element){
				T=SingleRotateWithLeft(T);
			}
			else{
				T=DoubleRotateWithLeft(T);
			}
		}
	}
	else if(X>T->element){
		T->right = Insert(X,T->right);
		if(Height(T->right)-Height(T->left)>=2){
			if(X>T->right->element){
				T=SingleRotateWithRight(T);
                        }
                        else{
				T=DoubleRotateWithRight(T);
			}
        	}
	}
	else if(X==T->element){
		fprintf(fout,"insertion error : %d is already in the tree!\n", X);
		return T;
	}
	T->height = max(Height(T->left), Height(T->right))+1;
	return T;
}

AVLTree Delete(ElementType X, AVLTree T){
	if(T==NULL){
        	fprintf(fout,"deletion error : %d is not in the tree!\n", X);
		return T;
        }
        else if(X<T->element){
                T->left = Delete(X,T->left);
        }
        else if(X>T->element){
                T->right = Delete(X,T->right);
        }
        else{
	       	AVLTree tmp;
                if(T->left==NULL){
                        tmp=T->right;
			free(T);
			return tmp;
                }
                else if(T->right==NULL){
                        tmp=T->left;
			free(T);
			return tmp;
                }
		tmp = findMin(T->right);
		T->element=tmp->element;
		T->right = Delete(T->element, T->right);
        }
	if(T==NULL){
		return T;
	}

	T->height = max(Height(T->left), Height(T->right))+1;
        
	if(Height(T->left)-Height(T->right)>=2){
                if(X>T->left->element){
                        T=SingleRotateWithLeft(T);
                }
                else{
                        T=DoubleRotateWithLeft(T);
                }
        }
	
	if(Height(T->right)-Height(T->left)>=2){
		if(X>T->right->element){
             		T=SingleRotateWithRight(T);
		}
          	else{
                       	T=DoubleRotateWithRight(T);       
		}        
	}

        return T;
}

void PrintInorder(AVLTree T){
	if(T){
		PrintInorder(T->left);
		fprintf(fout,"%d(%d) ", T->element, T->height);
		PrintInorder(T->right);
	}
}

void DeleteTree(AVLTree T){
        if(T==NULL){

        }
        else if(T->right==NULL&&T->left==NULL){
                free(T);
        }
        else if(T->left){
                DeleteTree(T->left);
        }
        else if(T->right){
                DeleteTree(T->right);
        }
}



int main(int argc, char *argv[]){
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	AVLTree Tree = NULL;
	char cv;
	int key;
	
	while(!feof(fin)){
		fscanf(fin, "%c", &cv);
		switch(cv){
			case 'i':
				fscanf(fin, "%d\n", &key);
				Tree = Insert(key, Tree);
				break;
			case 'd':	
				fscanf(fin, "%d\n", &key);
				Tree = Delete(key, Tree);
				break;
		}
		PrintInorder(Tree);
		fprintf(fout, "\n");
	}
	DeleteTree(Tree);
	fclose(fin);
	fclose(fout);

	return 0;
}

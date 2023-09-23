#include<stdio.h>
#include<stdlib.h>

FILE *fin;
FILE *fout;

typedef struct BST* Tree;
typedef struct BST{
	int value;
	struct BST* left;
	struct BST* right;
}BST;

Tree maxNode;
Tree insertNode(Tree root, int key);
Tree deleteNode(Tree root, int key);
Tree findMin(Tree root);
Tree findMax(Tree root);
int findNode(Tree root, int key);
void printInorder(Tree root);
void deleteTree(Tree root);

Tree findMin(Tree root){
	if(root==NULL){
		return NULL;
	}	
	if(root->left==NULL){
		return root;
	}
	return findMin(root->left);
}

Tree findMax(Tree root){
	if(root==NULL){
		return NULL;
	}
	if(root->right==NULL){
		return root;
	}
	return findMax(root->right);
}


Tree insertNode(Tree root, int key){
	if(root==NULL){
		root = (Tree)malloc(sizeof(struct BST));
		if(root==NULL){
			fprintf(fout, "out of space!!\n");
			return NULL;
		}
		root->value = key;
		fprintf(fout,"insert %d\n",root->value);
		root->right=root->left=NULL;
	}
	else if(root->value>key){
		root->left = insertNode(root->left,key);
	}
	else if(root->value<key){
		root->right = insertNode(root->right,key);
	}
	else{
		fprintf(fout, "insertion error: %d is already in the tree\n",key);
	}
	return root;
}

Tree deleteNode(Tree root, int key){
	Tree tmp = (Tree)malloc(sizeof(struct BST));
	if(tmp==NULL){
		fprintf(fout, "out of space!!\n");
		return NULL;
	}
	if(root->value<key){
		root->right=deleteNode(root->right, key);
	}
	else if(root->value>key){
		root->left=deleteNode(root->left, key);
	}
	else if(root->left&&root->right){
		tmp = findMin(root->right);
		root->value=tmp->value;
		root->right=deleteNode(root->right,root->value);
	}
	else{
		tmp=root;
		if(root->left==NULL){
			root=root->right;
		}
		else{
			root=root->left;
		}
		free(tmp);
	}
	return root;
}

int findNode(Tree root, int key){
	if(root->value>key&&root->left!=NULL){
		findNode(root->left, key);
	}
	else if(root->value<key&&root->right!=NULL){
		findNode(root->right, key);
	}
	else if(root->value==key){
		return 1;
	}
	else{
		return 0;
	}
}

void printInorder(Tree root){
	if(root){
		printInorder(root->left);	
		if(root==maxNode){
			fprintf(fout, "%d", root->value);
		}
		else{
			fprintf(fout, "%d ", root->value);
		}
		printInorder(root->right);
	}
}

void deleteTree(Tree root){
	if(root==NULL){
	
	}
	else if(root->right==NULL&&root->left==NULL){
		free(root);
	}
	else if(root->left){
		deleteTree(root->left);
	}
	else if(root->right){
		deleteTree(root->right);
	}
}

void main(int argc, char* argv[]){
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	char cv;
	int key;

	Tree root = NULL;
   
	while(!feof(fin)){
		maxNode=findMax(root);
		fscanf(fin, "%c",&cv);
		switch(cv){
			case 'i':
				fscanf(fin, "%d", &key);
				root = insertNode(root, key);
				break;
			case 'f':
				fscanf(fin, "%d", &key);
				if(findNode(root, key)){
					fprintf(fout, "%d is in the tree\n", key);
				}
				else
					fprintf(fout, "finding error: %d is not in the tree\n", key);
				break;
			case 'd':
				fscanf(fin, "%d", &key);
				if(findNode(root, key)){
					root = deleteNode(root, key);
					fprintf(fout, "delete %d\n", key);
				}
				else{
					fprintf(fout, "deletion error: %d is not in the tree\n", key);
				}
				break;
			case 'p':
				fscanf(fin, "%c", &cv);
				if(cv == 'i'){
					if(root == NULL){
						fprintf(fout, "tree is empty");
					}
					else{
						printInorder(root);
					}
				}
				fprintf(fout, "\n");
				break;
		}
	}
	deleteTree(root);
}

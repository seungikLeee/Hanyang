#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define ISFULL 1
#define ISEMPTY 2
#define DIVIDZERO 3

#define EMPTY_TOS (-1)

FILE *fin;
FILE *fout;

typedef struct Stack{
	int *key;
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack* S, int X);
int Pop(Stack* S);
int Top(Stack* S);

void DeleteStack(Stack* S);
int IsEmpty(Stack* S);
int IsFull(Stack* S);

int error_flag=0;

Stack* CreateStack(int max){
	Stack* s;
	
	s=malloc(sizeof(struct Stack));

	s->key=malloc(sizeof(int)*max);
	s->max_stack_size=max;
	s->top=EMPTY_TOS;

	return s;
}

void Push(Stack* S, int X){
	if(IsFull(S)){
		error_flag=ISFULL;
	}
	else{
		S->key[++(S->top)]=X;
	}
}

int Pop(Stack* S){
	if(IsEmpty(S)){
		error_flag=ISEMPTY;
	}
	else{
		return S->key[S->top--];
	}
}

int Top(Stack* S){
	if(IsEmpty(S)){
		error_flag=ISEMPTY;
	}
	else{
		return S->key[S->top];
	}
}

void DeleteStack(Stack* S){
	free(S->key);
	free(S);
}

int IsEmpty(Stack* S){
	return S->top==EMPTY_TOS;
}

int IsFull(Stack* S){
	return S->top==S->max_stack_size;
}

void main(int argc, char *argv[]){
	fin=fopen(argv[1], "r");
	fout=fopen(argv[2], "w");

	Stack* stack;
	char input_str[101];
	int max=20, i=0, a=0, b=0, result;

	fgets(input_str,101,fin);
	stack=CreateStack(max);

	fprintf(fout, "top numbers : ");
	while(input_str[i]!='#'){
		char ch=input_str[i];
		int c=0;
		if(isdigit(ch)){
			Push(stack,ch-'0');
		}
		else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'){
			a=Pop(stack);
			b=Pop(stack);

			switch(ch)
			{
				case '+':
					c=b+a;
					break;
				case '-':
					c=b-a;
					break;
				case '*':
					c=b*a;
					break;
				case '/':
					if(a==0){
						error_flag=DIVIDZERO;
					}
					else{
						c=b/a;
					}
					break;
				case '%':
					if(a==0){
						error_flag=DIVIDZERO;
					}
					else{
						c=b%a;
					}
					break;
			}
			Push(stack,c);
		}

		int t = Top(stack);
		fprintf(fout, "%d ",t);
		result = t;

		i++;
	}

	if(error_flag == ISFULL){
		fprintf(fout, "\nerror : invalid postfix expression, stack is full!\n");
	}
	else if(error_flag == ISEMPTY){
		fprintf(fout, "\nerror : invaild postfix expression, stack is empty!\n");
	}
	else if(error_flag == DIVIDZERO){
		fprintf(fout, "\nerror : invaild postfix expression, divide by zero!\n");
	}
	else{
		if(stack->top+1>1){
			fprintf(fout, "\nerror : invalid postfix expression, %d elements are left!\n", stack->top+1);
		}
		else{
			fprintf(fout, "\nevaluation result : %d\n", result);
		}
	}
	
	fclose(fin);
	fclose(fout);
	DeleteStack(stack);
}

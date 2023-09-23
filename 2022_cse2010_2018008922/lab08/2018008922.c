#include<stdio.h>
#include<stdlib.h>
#include<time.h>

FILE *fin;
FILE *fout;

typedef struct _DisjointSet {
	int size_maze;
	int *ptr_arr;
}DisjointSets;

void init(DisjointSets *sets, DisjointSets *maze_print, int num);
void Union(DisjointSets *sets, int i, int j);
int find(DisjointSets *sets, int i);
void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num);
void printMaze(DisjointSets *sets, DisjointSets *maze_print, int num);
void freeMaze(DisjointSets *sets, DisjointSets *maze_print);

void init(DisjointSets *sets, DisjointSets *maze_print, int num){
	int i;
	
	sets->size_maze = num*num;
	sets->ptr_arr = (int*)malloc(sizeof(int)*(sets->size_maze+1));
	
	for(i=1; i<=sets->size_maze; i++) sets->ptr_arr[i] = 0;

	maze_print->size_maze=num*num*2;
	maze_print->ptr_arr = (int*)malloc(sizeof(int)*(maze_print->size_maze+1));

	for(i=1; i<=maze_print->size_maze; i++) maze_print->ptr_arr[i]=1;
	
	//maze_print->ptr_arr[maze_print->size_maze-1]=0;
}

void Union(DisjointSets *sets, int i, int j){
	int pi=find(sets,i);
	int pj=find(sets,j);
	if(sets->ptr_arr[pi]<sets->ptr_arr[pj]){
		sets->ptr_arr[pj] = pi;
	}
	else{
		if(sets->ptr_arr[pi] == sets->ptr_arr[pj]){
			sets->ptr_arr[pj]--;
		}
		sets->ptr_arr[pi]= pj;
	}
}

int find(DisjointSets *sets, int i){
	if(sets->ptr_arr[i]<=0){
		return i;
	}	
	else{
		return (sets->ptr_arr[i] = find(sets,sets->ptr_arr[i]));
	}
}

void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num){
	int c1,c2,w;
	int size = maze_print->size_maze+1;
	int last_bottom_wall = size-num;

	while(find(sets,1)!=find(sets,sets->size_maze)){
		int l=1;
		while(l)
		{
			srand((unsigned int)time(NULL));
			w = rand()%size;

			if(w==0){
				w=1;
			}
			if(maze_print->ptr_arr[w]==0){
				continue;
			}
			else if(w>=last_bottom_wall){
				continue;
			}
			else if(w <= sets->size_maze && w%num==0){
				continue;
			}
			else{
				l=0;
			}
		}
		
		if(w <= sets->size_maze){
			c1=w;
			c2=w+1;
		}
		else{
			c1=w-sets->size_maze;
			c2=c1+num;
		}

		if(find(sets,c1)!=find(sets,c2)){
			if(find(sets,c1)==find(sets,1)||find(sets,c2)==find(sets,1)||find(sets,c1)==find(sets,sets->size_maze)||find(sets,c2)==find(sets,sets->size_maze)){
				Union(sets,c1,c2);
				maze_print->ptr_arr[w]=0;
			}
		}
	}
}

void printMaze(DisjointSets *sets,DisjointSets *maze_print, int num){
	fprintf(fout,"+");	
	for(int i=1; i<=num; i++){
		fprintf(fout,"---+");
	}
	fprintf(fout,"\n");
 
	int size=sets->size_maze+1;
	fprintf(fout," ");
	for(int i=1; i<=sets->size_maze; i++){
		if(maze_print->ptr_arr[i]>0){
			if(i==sets->size_maze){
				fprintf(fout, "    ");
			}
			else{
				fprintf(fout, "   |");
			}
			if(i%num==0){
				int j=1;
				fprintf(fout, "\n");
				fprintf(fout, "+");
				for(; j<=num; j++){
					if(maze_print->ptr_arr[size]>0){
						fprintf(fout,"---+");
					}
					else{
						fprintf(fout,"   +");
					}
					size++;
				}
				if(i<sets->size_maze){
					fprintf(fout,"\n|");
				}
				else{
					fprintf(fout,"\n");
				}
			}
		}
		else{
			if(i%num==0){
				fprintf(fout,"    \n");
			}
			else{
				fprintf(fout,"    ");
			}
		}
	}
}

void freeMaze(DisjointSets *sets, DisjointSets *maze_print){
	free(sets);
	free(maze_print);
}

int main(int argc, char* agrv[]){
	srand((unsigned int)time(NULL));
	int num, i;
	fin = fopen(agrv[1], "r");
	fout = fopen(agrv[2], "w");

	DisjointSets *sets, *maze_print;
	fscanf(fin, "%d", &num);

	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
	maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));

	init(sets, maze_print, num);
	createMaze(sets, maze_print, num);
	printMaze(sets, maze_print, num);
	freeMaze(sets, maze_print);

	fclose(fin);
	fclose(fout);

	return 0;
}

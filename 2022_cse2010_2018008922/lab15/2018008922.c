#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fin;
FILE *fout;

typedef int ElementType;
typedef ElementType List;
typedef struct HashTbl* HashTable;

typedef struct HashTbl{
	int TableSize;
	List *TheLists;
}HashTbl;

HashTable createTable(int TableSize);
void Insert(HashTable H, ElementType Key, int solution);
void Delete(HashTable H, ElementType Key, int solution);
int Find(HashTable H, ElementType Key, int solution);
void printTable(HashTable H);
void deleteTable(HashTable H);

int main(int argc, char *argv[]){
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	char solution_str[20];
	int solution, TableSize;

	fscanf(fin, "%s", solution_str);
	if(!strcmp(solution_str, "linear"))
		solution = 1;
	else if(!strcmp(solution_str, "quadratic"))
		solution = 2;
	else{
		fprintf(fout, "error: invalid hashing solution!\n");
		return 0;
	}

	fscanf(fin, "%d", &TableSize);

	HashTable H = createTable(TableSize);

	char cv;
	int key;
	while(!feof(fin)){
		fscanf(fin, "%c", &cv);
		switch(cv){
			case 'i':
				fscanf(fin, "%d", &key);
				Insert(H, key, solution);
				break;
			
			case 'f':
				fscanf(fin, "%d", &key);
				int result = Find(H, key, solution);
				if(result)
					fprintf(fout, "%d is in the table\n", key);
				else
					fprintf(fout, "%d is not in the table\n", key);
				break;

			case 'd':
				fscanf(fin, "%d", &key);
				Delete(H, key, solution);
				break;

			case 'p':
				printTable(H);
				break;
		}
	}
	
	deleteTable(H);

	return 0;
}


HashTable createTable(int TableSize){
	HashTable newT = (HashTable)malloc(sizeof(HashTbl));
	
	newT->TableSize = TableSize;
	newT->TheLists = (List*)malloc(sizeof(List)*TableSize);
	for(int i=0; i<TableSize; i++){
		newT->TheLists[i] = 0;
	}
	return newT;
}

void Insert(HashTable H, ElementType Key, int solution){
	if(Find(H,Key,solution)){
		int i;
		for(i=0; i<H->TableSize; i++){
			if(H->TheLists[i] == Key){
				break;
			}
		}
		fprintf(fout, "insertion error : %d already exists at address %d\n", Key, i);
	}
	else{
		int flag=0;
		for(int i=0; i<H->TableSize; i++){
			if(H->TheLists[i] == 0){
				flag = 1;
			}
		}

		if(flag==0){
			fprintf(fout, "insertion error : table is full\n");

		}
		else{
			int hValue = Key%(H->TableSize);
			if(solution==1){
				while(H->TheLists[hValue] != 0){
					hValue = (hValue+1)%(H->TableSize);
				}
				H->TheLists[hValue] = Key;
				fprintf(fout, "insert %d into address %d\n", Key, hValue);
			}
			else{
                                int i=1;
				int tmp = hValue;
				while(H->TheLists[tmp] != 0){
					tmp = (hValue+(i*i))%(H->TableSize);
					i++;
                                }
                                H->TheLists[tmp] = Key;
                                fprintf(fout, "insert %d into address %d\n", Key, hValue);

			}
		}
	}	
}

void Delete(HashTable H, ElementType Key, int solution){
	if(Find(H,Key,solution)){
		int i;
		for(i=0; i<H->TableSize; i++){
			if(H->TheLists[i] == Key){
				H->TheLists[i] = 0;
				break;
			}
		}
		fprintf(fout, "delete %d\n" , Key);
	}
	else{
		fprintf(fout, "deletion error : %d is not in the table\n", Key);
	}
}

int Find(HashTable H, ElementType Key, int solution){
	for(int i=0; i<H->TableSize; i++){
		if(H->TheLists[i] == Key){
			return 1;
		}
	}
	return 0;
}

void printTable(HashTable H){
	for(int i=0; i<H->TableSize; i++){
		fprintf(fout,"%d ", H->TheLists[i]);
	}
	fprintf(fout, "\n");	
}

void deleteTable(HashTable H){
	free(H->TheLists);
	free(H);
}

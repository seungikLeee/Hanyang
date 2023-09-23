#include<stdio.h>
#include<stdlib.h>

#define INF 1e9

FILE *fin;
FILE *fout;

typedef struct HeapStruct{
	int Capacity;
	int Size;
	int *Elements;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap *heap, int value);
int Find(Heap *heap, int value);
int DeleteMax(Heap* heap);
void PrintHeap(Heap* heap);
int IsFull(Heap *heap);

int main(int argc, char* argv[]){
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	char cv;
	Heap* maxHeap;
	int heapSize, key, max_element;

	while(!feof(fin)){
		fscanf(fin, "%c", &cv);
		switch(cv){
			case 'n':
				fscanf(fin, "%d", &heapSize);
				maxHeap = CreateHeap(heapSize);
				break;
			case 'i':
				fscanf(fin, "%d", &key);
				Insert(maxHeap, key);
				break;
			case 'd':
				max_element = DeleteMax(maxHeap);
				if(max_element != -INF){
					fprintf(fout, "max element : %d deleted\n", max_element);
				}
				break;
			case 'p':
				PrintHeap(maxHeap);
				break;
			case 'f':
				fscanf(fin, "%d", &key);
				if(Find(maxHeap, key)) fprintf(fout, "%d is in the heap\n", key);
				else fprintf(fout, "finding error : %d is not in the heap\n", key);
				break;
		}
	}	
	return 0;
}

Heap* CreateHeap(int heapSize){
	Heap* newHeap = (Heap*)malloc(sizeof(Heap));
	if(newHeap==NULL){
		fprintf(fout,"out of space!\n");
		return NULL;
	}
	newHeap->Capacity = heapSize;
	newHeap->Size=0;
	newHeap->Elements = (int*)malloc((heapSize+1)*sizeof(int));
	if(newHeap->Elements==NULL){
		fprintf(fout, "out of space!\n");
	}
	for(int i=0; i<=heapSize; i++){
		newHeap->Elements[i] = 0;
	}
	return newHeap;
}

void Insert(Heap *heap, int value){
	int i=++heap->Size;
	if(IsFull(heap)){
		fprintf(fout, "insert error : heap is full\n");
		heap->Size--;
		return;
	}
	else{
		for(; heap->Elements[i/2]<=value; i/=2){
			if(heap->Elements[i] == value){
                                fprintf(fout, "insert error : %d is already in the heap\n", value);
				heap->Size--;
				return;
                        }
			
			if(i==1){
				break;
			}
			heap->Elements[i] = heap->Elements[i/2];
		}	
		
		heap->Elements[i] = value;
		fprintf(fout, "insert %d\n", value);
	}	
}

int Find(Heap *heap, int value){
	int flag=0;
	for(int i=1; i<=heap->Size; i++){
		if(heap->Elements[i]==value){
			flag=1;
			break;
		}
	}
	return flag;	
}

int DeleteMax(Heap* heap){
	if(heap->Size<1){
                fprintf(fout, "delete error : heap is empty\n");
        	return -INF;
	}
	
	int i, child;
	int max_element,last_element;
	
	max_element = heap->Elements[1];
	last_element = heap->Elements[heap->Size--];

	for(i=1; i*2<=heap->Size; i=child){
		child = i*2;
		if(child<heap->Size&&heap->Elements[child+1] > heap->Elements[child]){
			child++;
		}
		if(last_element < heap->Elements[child]){
			heap->Elements[i] = heap->Elements[child];
		}
		else{
			break;
		}
	}
	heap->Elements[i]=last_element;
	return max_element;
}

void PrintHeap(Heap* heap){
	if(heap->Size<1){
		fprintf(fout, "print error : heap is empty\n");
	}
	else{
		for(int i=1; i<=heap->Size; i++){
			fprintf(fout, "%d ",heap->Elements[i]);
		}
		fprintf(fout,"\n");
	}
}

int IsFull(Heap *heap){
	if(heap->Capacity<heap->Size){
		return 1;
	}
	else{
		return 0;
	}
}


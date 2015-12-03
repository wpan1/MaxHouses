#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

#define HEAP_SUCCESS 1
#define HEAP_FAIL 0

//returns a pointer to a new, empty heap
Heap *CreateHeap(int small_large){
	// Mallocs size of heap
	Heap *h = (Heap*)malloc(sizeof(Heap));
	h->H = (HeapItem*)malloc(sizeof(HeapItem));
	h->map = (int*)malloc(sizeof(int));

	//Sets initial values
	h->n = 0;
	h->size = 1;
	h->small_large = small_large;

	return h;
}

void HeapPrint(Heap *h){
	for (int i=0;i<h->n;i++){
		if (h->H[i].key == INT_MAX){
			printf("inf,");
		}
		else{
			printf("%d,",h->H[i].key);
		}
	}
	printf("\n");
}

void HeapPointerSwap(Heap *h, int loc1, int loc2){
	HeapItem temp;
	
	h->map[h->H[loc1].dataIndex] = loc2;
	h->map[h->H[loc2].dataIndex] = loc1;

	temp = h->H[loc1];
	h->H[loc1] = h->H[loc2];
	h->H[loc2] = temp;
}


void siftup(Heap *h, int location){
	int parent = (location-1)/2;
	while (location > 0){
		if (h->small_large == 1 && h->H[location].key > h->H[parent].key){
			return;
		}
		if (h->small_large == 0 && h->H[location].key < h->H[parent].key){
			return;
		}
		HeapPointerSwap(h,location,parent);
		location = parent;
		parent = (location-1)/2;
	}
	return;
}

//inserts dataIndex into h. Returns
//HEAP SUCCESS if it has inserted, or HEAP FAIL otherwise.
int HeapInsert(Heap *h, int dataIndex, int key){
	int n = h->n;
	// If heap is full, size is doubled
	if (h->n == h->size){
		h->size *= 2;
		h->H = (HeapItem*)realloc(h->H,sizeof(HeapItem)*h->size+1);
	}
	// Heap is updated with insertion values
	h->map = (int*)realloc(h->map,sizeof(int)*dataIndex+1);
	h->map[dataIndex] = n;
	h->H[n].key = key;
	h->H[n].dataIndex = dataIndex;

	siftup(h,h->n);
	h->n ++;

	return (HEAP_SUCCESS);
}

//returns the data index of the root.
int HeapPeek(Heap *h){
	return h->H[0].dataIndex;
}

//returns the key of the root.
int HeapPeekKey(Heap *h){
	return h->H[0].key;
}

int HeapPeekKey_val(Heap *h, int n){
	return h->H[n].key;
}


void siftdown(Heap *h, int location, int size){
	int root = location, child;
	while(root*2 + 1 <= size){
		child = root*2+1;
		if (h->small_large == 0 && child + 1 <= size && h->H[child].key < h->H[child+1].key){
			child = child + 1;
		}
		else if (h->small_large == 1 && child + 1 <= size && h->H[child].key > h->H[child+1].key){
			child = child + 1;
		}
		if (h->small_large == 0 && h->H[root].key < h->H[child].key){
			HeapPointerSwap(h,root,child);
			root = child;
		}
		else if (h->small_large == 1 && h->H[root].key > h->H[child].key){
			HeapPointerSwap(h,root,child);
			root = child;
		}
		else{
			return;
		}
	}
}

//removes the root, returns the data index to it, and re-heapifies
//(possibly changing other items map values)
int HeapRemoveMin(Heap *h){
	HeapPointerSwap(h,0,h->n-1);
	siftdown(h,0,h->n-2);

	h->n --;
	return h->H[h->n].dataIndex;
}

//adds delta to the key of dataIndex
//and then re-heapifies.
void HeapChangeKeyValue(Heap *h, int dataIndex, int new_val){
	int position = h->map[dataIndex];
	h->H[position].key = new_val;
	if (position < h->n){
		siftup(h,position);
		siftdown(h,position,h->n-1);
	}
}

//adds delta to the key of dataIndex
//and then re-heapifies.
void HeapChangeKeyDelta(Heap *h, int dataIndex, int delta){
	int position = h->map[dataIndex];
	h->H[position].key += delta;
	if (position < h->n){
		siftup(h,position);
		siftdown(h,position,h->n-1);
	}
}

//free any memory you might of alloced in heap creation.
void HeapDestroyHeap(Heap *h){
	free(h->H);
	free(h->map);
	free(h);
} 
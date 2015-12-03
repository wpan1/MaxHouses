typedef struct {
	int key; // the key for deciding position in heap
	int dataIndex; // the payload index provided by the calling program
} HeapItem;

typedef struct {
	HeapItem *H; // the underlying array
	int small_large; // smallest val on top
	int *map; // map[i] is index into H of location of payload with dataIndex == i
	int n; // the number of items currently in the heap
	int size; // the maximum number of items allowed in the heap
} Heap;

// returns a pointer to a new, empty heap
Heap *CreateHeap(int small_large);

void HeapPrint(Heap *h);

//inserts dataIndex into h. Returns
//HEAP SUCCESS if it has inserted, or HEAP FAIL otherwise.
int HeapInsert(Heap *h, int dataIndex, int key);

//returns the data index of the root.
int HeapPeek(Heap *h);

//returns the key of the root.
int HeapPeekKey(Heap *h);

//removes the root, returns the data index to it, and re-heapifies
//(possibly changing other items map values)
int HeapRemoveMin(Heap *h);

//adds delta to the key of dataIndex
//and then re-heapifies.
void HeapChangeKeyValue(Heap *h, int dataIndex, int new_val); 

//adds delta to the key of dataIndex
//and then re-heapifies.
void HeapChangeKeyDelta(Heap *h, int dataIndex, int delta); 

//free any memory you might of alloced in heap creation.
void HeapDestroyHeap(Heap *h); 

int HeapPeekKey_val(Heap *h, int n);
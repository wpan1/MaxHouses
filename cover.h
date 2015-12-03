typedef struct {
	int n;
	int size;
	Set **sets;
} Houses;

typedef struct {
	Houses *houses;
	int *add_values;
	int n;
} Cover;

Cover *CreateCover(int number_of_vertices, int num_houses);
void CoverInsertSet(Cover *c, Set *s, int num_houses);
void HeapCoverUpdateVal(Cover *c, Heap *h, Set *s, int num_houses);
void SetAddUnique(Set *s, Set *u, Cover *c);
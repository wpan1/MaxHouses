typedef struct {
    int n;
    int n_2;
    int size;
    int set_number;
    int *houses;
} Set;

Set *CreateSet();
void SetInsert(Set *s, int house, int set_number);
int SetPeekKey_val(Set *s, int n);
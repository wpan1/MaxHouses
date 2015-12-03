#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "set.h"
#include "heap.h"
#include "cover.h"

Set *CreateSet(){
    Set *s = (Set*)malloc(sizeof(Set));
    assert(s);
    s->houses = (int*)malloc(sizeof(int));
    assert(s->houses);
    s->set_number = -1;
    s->n = 0;
    s->n_2 = 0;
    s->size = 1;
    return s;
}

void SetInsert(Set *s, int house, int set_number){
    // If set is full, size is doubled
    if (s->n == s->size){
        s->size *= 2;
        s->houses = (int*)realloc(s->houses,sizeof(int)*s->size+1);
        assert(s->houses);
    }
    s->houses[s->n] = house;
    s->set_number = set_number;
    s->n ++;
    s->n_2 ++;
}

int SetPeekKey_val(Set *s, int n){
    return s->houses[n];
}
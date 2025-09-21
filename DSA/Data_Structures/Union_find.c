#include <stdlib.h>
#include <stdio.h>

typedef struct Union_Find {
    
    int* arr;
    int size;

} Union_Find;

Union_Find* create_union_find(int size) {

    Union_Find* self = (Union_Find*)malloc(sizeof(Union_Find));

    if (self == NULL) {
        perror("Sike");
        return NULL;
    }

    self->arr = (int*)malloc(size * sizeof(int));
    
    if (self->arr == NULL) {
        perror("Sike");
        return NULL;
    }
    
    for (int i = 0; i < size; i++) { 
        self->arr[i] = i;
    }

    self->size = size;
    
    return self;
}

int find(Union_Find* self, int x) {
    
    if (self == NULL || x >= self->size) {
        perror("Sike");
        return -1;
    }
    
    
    if (self->arr[x] == x) {
        return x;
    }
    else {
        
        return find(self, self->arr[self->arr[x]]);
    } 
}

void unite(Union_Find* self, int x, int y) {

    int x_rep = find(self, x);

    int y_rep = find(self, y);

    self->arr[x_rep] = y_rep;
}

int main() {

    return 0;
}

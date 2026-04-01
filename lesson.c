#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
        unsigned char size;
        int *element;
    }SETOFINT;

SETOFINT* create_set(int *arr, int n){
    SETOFINT *set = malloc(sizeof(SETOFINT));
    set->size = n;
    set->element = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        set->element[i] = arr[i];
    }
    return set;
}

void free_set(SETOFINT *set) {
    free(set->element);
    free(set);
}

void print_set(SETOFINT *set) {
    printf("{ ");
    for (int i = 0; i < set->size; i++) {
        printf("%d ", set->element[i]);
    }
    printf("}\n");
}

SETOFINT* set_union(SETOFINT *a, SETOFINT *b) {
    int i = 0, j = 0, k = 0;
    int *res = malloc((a->size + b->size) * sizeof(int));

    while (i < a->size && j < b->size) {
        if (a->element[i] < b->element[j])
            res[k++] = a->element[i++];
        else if (a->element[i] > b->element[j])
            res[k++] = b->element[j++];
        else {
            res[k++] = a->element[i];
            i++; j++;
        }
    }

    while (i < a->size) res[k++] = a->element[i++];
    while (j < b->size) res[k++] = b->element[j++];

    SETOFINT *result = malloc(sizeof(SETOFINT));
    result->size = k;
    result->element = res;
    return result;
}

SETOFINT* set_intersection(SETOFINT *a, SETOFINT *b) {
    int i = 0, j = 0, k = 0;
    int *res = malloc((a->size < b->size ? a->size : b->size) * sizeof(int));

    while (i < a->size && j < b->size) {
        if (a->element[i] < b->element[j])
            i++;
        else if (a->element[i] > b->element[j])
            j++;
        else {
            res[k++] = a->element[i];
            i++; j++;
        }
    }

    SETOFINT *result = malloc(sizeof(SETOFINT));
    result->size = k;
    result->element = res;
    return result;
}

SETOFINT* set_difference(SETOFINT *a, SETOFINT *b) {
    int i = 0, j = 0, k = 0;
    int *res = malloc(a->size * sizeof(int));

    while (i < a->size && j < b->size) {
        if (a->element[i] < b->element[j])
            res[k++] = a->element[i++];
        else if (a->element[i] > b->element[j])
            j++;
        else {
            i++; j++;
        }
    }

    while (i < a->size)
        res[k++] = a->element[i++];

    SETOFINT *result = malloc(sizeof(SETOFINT));
    result->size = k;
    result->element = res;
    return result;
}

SETOFINT* set_sym_diff(SETOFINT *a, SETOFINT *b) {
    int i = 0, j = 0, k = 0;
    int *res = malloc((a->size + b->size) * sizeof(int));

    while (i < a->size && j < b->size) {
        if (a->element[i] < b->element[j])
            res[k++] = a->element[i++];
        else if (a->element[i] > b->element[j])
            res[k++] = b->element[j++];
        else {
            i++; j++; // пропускаем одинаковые
        }
    }

    while (i < a->size)
        res[k++] = a->element[i++];
    while (j < b->size)
        res[k++] = b->element[j++];

    SETOFINT *result = malloc(sizeof(SETOFINT));
    result->size = k;
    result->element = res;
    return result;
}


int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main(){
    int a_arr[] = {-4, 15, 7, 0, 9};
    int b_arr[] = {-6, 20, -4, 15, 0, 1, 2, 3};

    SETOFINT *A = create_set(a_arr, 5);
    SETOFINT *B = create_set(b_arr, 8);
    SETOFINT *inter = set_intersection(A, B);
    SETOFINT *diff = set_difference(A, B);
    SETOFINT *sym = set_sym_diff(A, B);

    qsort(A->element, A->size, sizeof(int), cmp);
    qsort(B->element, B->size, sizeof(int), cmp);

    SETOFINT *uni = set_union(A, B);
    print_set(uni);

    print_set(inter);

    print_set(diff);

    print_set(sym);


    free_set(A);
    free_set(B);
    free_set(uni);
    free_set(inter);
    free_set(diff);
    free_set(sym);      

    return 0;
}

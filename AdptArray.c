#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

struct AdptArray_ {
    PElement* arr;
    int size;
    int capacity;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
};

PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func) {
    PAdptArray p_adpt = (PAdptArray) malloc(sizeof(struct AdptArray_));
    if (!p_adpt) {
        return NULL;
    }

    p_adpt->arr = (PElement*) malloc(sizeof(PElement));
    if (!p_adpt->arr) {
        free(p_adpt);
        return NULL;
    }
    p_adpt->arr[0] = NULL;
    p_adpt->size = 1;
    p_adpt->capacity = 1;
    p_adpt->copy_func = copy_func;
    p_adpt->del_func = del_func;
    p_adpt->print_func = print_func;
    
    return p_adpt;
}

void DeleteAdptArray(PAdptArray p_adpt) {
    if(p_adpt == NULL) return;
    for (int i = 0; i < p_adpt->size; i++) {
        if (p_adpt->arr[i]) {
            p_adpt->del_func(p_adpt->arr[i]);
        }
    }
    free(p_adpt->arr);
    free(p_adpt);
    return;
}

Result SetAdptArrayAt(PAdptArray p_adpt, int index, PElement elem) {
    if (index < 0) {
       
            return FAIL;
        }
        
    else if (index >= p_adpt->size) {
        // Expand array to accommodate positive index
        int new_size = index + 1;
        PElement* new_arr = (PElement*) realloc(p_adpt->arr, new_size * sizeof(PElement));
        if (!new_arr) {
            return FAIL;
        }

        p_adpt->arr = new_arr;
        for (int i = p_adpt->size ; i < index; i++) {
            p_adpt->arr[i] = NULL;
        }
        p_adpt->size = new_size;
    }
    // Copy element into array
    p_adpt->arr[index] = p_adpt->copy_func(elem);
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray p_adpt, int index)
 {
    if (p_adpt == NULL || index < 0 || index >= p_adpt->size || p_adpt->arr[index] == NULL) {
    return NULL;
}
return p_adpt->copy_func(p_adpt->arr[index]);
;
}

int GetAdptArraySize(PAdptArray p_adpt)
{
    if(p_adpt == NULL) return 0;
    return p_adpt->size;
}

void PrintDB(PAdptArray p_adpt) {
    for (int i = 0; i < p_adpt->size; i++) {
        if (p_adpt->arr[i])
        {
            p_adpt->print_func(p_adpt->arr[i]);
        }
    }
    return;
}

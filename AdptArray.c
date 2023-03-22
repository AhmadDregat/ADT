#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

struct AdptArray_
{
    PElement *array;    // Pointer to the array.
    DEL_FUNC del_f;     // Delete function of the PElement.
    COPY_FUNC copy_f;   // Copy function of the PElement.
    PRINT_FUNC print_f; // Print function of the PElement.
    int size;           // Size of the array.
};

// Initializes an empty PAdptArray.
PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func)
{
    PAdptArray ADP_arr = (PAdptArray)malloc(sizeof(struct AdptArray_));
    if (ADP_arr == NULL)
        return NULL;

    ADP_arr->size = 0;
    ADP_arr->array = NULL;
    ADP_arr->copy_f = copy_func;
    ADP_arr->del_f = del_func;
    ADP_arr->print_f = print_func;
    return ADP_arr;
}

void DeleteAdptArray(PAdptArray arr)
{
    if (arr == NULL)
        return;

    // free the elemwnts in the array
    for (int i = 0; i < arr->size; ++i)
    {
        if (arr->array[i] != NULL)
            arr->del_f(arr->array[i]);
    }
    free(arr->array);
    free(arr);
}

int GetAdptArraySize(PAdptArray arr)
{
    if (arr == NULL)
        return FAIL;
    return arr->size;
}

Result SetAdptArrayAt(PAdptArray arr, int index, PElement element)
{
    // Return FAIL if i is less than zero
    if (index < 0 || arr == NULL)
    {
        return FAIL;
    }
    if (index >= arr->size)
    {
        arr->array = realloc(arr->array, (index + 1) * sizeof(void *));
        if (arr->array == NULL)
            return FAIL;
        for (int i = arr->size; i < (index + 1); i++)
        {
            arr->array[i] = NULL;
        }

        arr->size = (index + 1);
    }
    else if (arr->array[index] != NULL)
        arr->del_f(arr->array[index]);
    arr->array[index] = arr->copy_f(element);
    if (arr->array[index] == NULL)
        return FAIL;
    return SUCCESS;
}
void PrintDB(PAdptArray arr)
{
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->array[i] != NULL)
            arr->print_f(arr->array[i]);
    }
}

PElement GetAdptArrayAt(PAdptArray arr, int index)
{
    if (arr == NULL || index < 0 || arr->array[index] == NULL || arr->size == 0 || index >= arr->size)
        return NULL;
    PElement element = arr->copy_f(arr->array[index]);
    arr->copy_f(element);
    return arr->array[index];
}

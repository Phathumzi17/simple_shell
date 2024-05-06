#include "shell.h"

/**
 * bfree - deallocates memory and sets the pointer to NULL
 * @ptr: address of the pointer to deallocate
 *
 * Return: 1 if memory was deallocated, otherwise 0.
 */
int bfree(void **ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
        return (1);
    }
    return (0);
}

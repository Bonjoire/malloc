#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
    // ft_printf("\n=================== REALLOC ===================\n");

    // same as free
    if (size == 0 && ptr != NULL)
    {
        free(ptr);
        return (NULL);
    }

    // same as malloc
    if (!ptr) 
        return (malloc(size));

    // find ptr in heap or large_heap
    t_block *parent_block       = NULL;
    t_chunk *chunk              = find_address_heap(ptr, &parent_block);
    t_large_heap *large_heap    = find_address_large_heap(ptr);
    if (!chunk && !large_heap)
        return (NULL);

    void *new_ptr = malloc(size);

    // malloc failed
    if (!new_ptr)
        return (NULL);

    size_t old_size;
    if (chunk)
        old_size = ((t_chunk*)(ptr - ALIGNED_CHUNK))->size;
    else // if (large_heap)
        old_size = ((t_large_heap*)(ptr - ALIGNED_LARGE_HEAP))->size;

    // copy data from old ptr to new ptr
    ft_memcpy(new_ptr, ptr, old_size < (size ? old_size : size));
    free(ptr);

    return (new_ptr);
}
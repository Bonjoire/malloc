#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	pthread_mutex_lock(&g_mutex);
	
    // same as free
    if (size == 0 && ptr != NULL)
    {
		pthread_mutex_unlock(&g_mutex);
        free(ptr);
        return (NULL);
    }

    // same as malloc
    if (!ptr) 
	{
		pthread_mutex_unlock(&g_mutex);
        return (malloc(size));
	}

    // find ptr in heap or large_heap
    t_block *parent_block       = NULL;
    t_chunk *chunk              = find_address_heap(ptr, &parent_block, NULL);
    t_large_heap *large_heap    = find_address_large_heap(ptr);
    if (!chunk && !large_heap)
	{
		pthread_mutex_unlock(&g_mutex);
        return (NULL);
	}

	pthread_mutex_unlock(&g_mutex);
    void *new_ptr = malloc(size);
	pthread_mutex_lock(&g_mutex);

    // malloc failed
    if (!new_ptr)
	{
		pthread_mutex_unlock(&g_mutex);
        return (NULL);
	}


    size_t old_size;
    if (chunk)
        old_size = ((t_chunk*)(ptr - ALIGNED_CHUNK))->size;
    else // if (large_heap)
        old_size = ((t_large_heap*)(ptr - ALIGNED_LARGE_HEAP))->size;

    // copy data from old ptr to new ptr
    ft_memcpy(new_ptr, ptr, old_size < size ? old_size : size);
	pthread_mutex_unlock(&g_mutex);
    free(ptr);
    return (new_ptr);
}
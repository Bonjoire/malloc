/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:40:16 by hubourge          #+#    #+#             */
/*   Updated: 2024/12/27 11:59:29 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_data *g_data = NULL;

void *malloc(size_t size)
{
    printf("-> Size = %zu (%lu)bytes\n", size, sizeof(size)); /// debug
    if (size == 0)
        return (NULL);

    if (g_data == NULL)
    {
        if (!data_init(&g_data))
            return (NULL);
    }

    if (size <= TINY_S_MAX_ALLOC)
        heap_alloc(g_data->tiny_heap, TINY_S, size);
    else if (size <= SMALL_S_MAX_ALLOC)
        heap_alloc(g_data->small_heap, SMALL_S, size);
    // else
    //     allocate_large(&g_data->large_heap, size);

    printf("\n");
    if (g_data->failed == false)
        return (g_data->addr_return);
    
    return (NULL);
}

void *align(void *ptr_to_align)
{
    uintptr_t new_ptr = (uintptr_t)ptr_to_align;

    if ((new_ptr % ALIGNMENT) != 0)
        new_ptr += ALIGNMENT - (new_ptr % ALIGNMENT);

    return ((void *)new_ptr);
}

void heap_alloc(t_heap *heap, size_t heap_pagesize, size_t size)
{
    t_block *block_tmp = NULL;
    t_block *block = heap->first_block;

    if ((size_t)heap_pagesize == (size_t)TINY_S)
        printf("-> TINY HEAP\n"); /// debug
    else
        printf("-> SMALL HEAP\n"); /// debug
        
    while (block != NULL)
    {
        block_tmp = block;
        block = block->next;
    }

    block = (t_block *)mmap(NULL, heap_pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (block == MAP_FAILED)
    {
        g_data->failed = true;        
        return ;
    }

    if (block_tmp != NULL)
        block_tmp->next = block;
    else
        heap->first_block = block;
    block->next = NULL;
    block->free_size = heap_pagesize - ALIGNED_BLOCK;

    chunk_alloc(block, size);
}

void    chunk_alloc(t_block *block, size_t size)
{
    block->first_chunk = (t_chunk *)((void *)block + ALIGNED_BLOCK);
    
    block->first_chunk->chunk = (t_chunk *)((void *)block->first_chunk + ALIGNED_CHUNK);
    block->first_chunk->prev = NULL;
    block->first_chunk->next = NULL;
    
    block->first_chunk->size = size;
    block->free_size -= (size_t)align((void *)ALIGNED_CHUNK + size);
}
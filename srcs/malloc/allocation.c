/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:55:35 by hubourge          #+#    #+#             */
/*   Updated: 2024/12/30 19:05:58 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void heap_alloc(t_heap *heap, size_t heap_pagesize, size_t size)
{
    t_block *block_tmp  = NULL;
    t_block *block      = heap->first_block;

    if ((size_t)heap_pagesize == (size_t)TINY_S)
        printf("-> TINY HEAP\n"); /// debug
    else
        printf("-> SMALL HEAP\n"); /// debug

    printf("-> Heap pagesize = %zu\n", heap_pagesize); /// debug
    while (block != NULL)
    {
        // If there is enough space in the block, 
        // create a new chunk and return true, else return false
        if (try_alloc_new_chunk_if_space_in_block(block, size))
            return ;
        block_tmp = block;
        block = block->next;
    }
    printf("--> Block avant = %p\n", block); /// debug

    block = (t_block *)mmap(NULL, heap_pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (block == MAP_FAILED)
    {
        g_data->failed = true;        
        return ;
    }
    printf("--> Block apres = %p, %zu\n", block, (size_t)block - (size_t)g_data); /// debug
    printf("--> Block size = %zu\n", heap_pagesize); /// debug
    printf("--> Block deep = %zu\n", (size_t)block - (size_t)g_data); 
    
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
    block->first_chunk          = (t_chunk *)((size_t)block + ALIGNED_BLOCK);
    block->first_chunk->chunk   = (t_chunk *)((size_t)block->first_chunk + ALIGNED_CHUNK);
    
    block->first_chunk->prev = NULL;
    block->first_chunk->next = NULL;
    
    block->first_chunk->size = size;
    block->free_size -= (size_t)align((void *)ALIGNED_CHUNK + block->first_chunk->size);
    
    g_data->addr_return = block->first_chunk;
}

bool    try_alloc_new_chunk_if_space_in_block(t_block *block, size_t size)
{
    t_chunk *chunk_tmp = NULL;
    t_chunk *chunk = block->first_chunk;

    if (block && block->free_size < (size_t)align((void *)ALIGNED_CHUNK + size))
        return (false);

    printf("-> Free size = %zu, size = %zu\n", block->free_size, size); /// debug
    while (chunk != NULL)
    {
        chunk_tmp = chunk;
        chunk = chunk->next;
    }

    chunk = (t_chunk*)((size_t)chunk_tmp->chunk + (size_t)align((void*)(size_t)chunk_tmp + chunk_tmp->size) - (size_t)chunk_tmp);
    chunk->chunk = (t_chunk *)((size_t)chunk + ALIGNED_CHUNK);
    
    chunk_tmp->next = chunk;
    chunk->prev = chunk_tmp;
    chunk->next = NULL;
    chunk->size = size;
    
    block->free_size -= (size_t)align((void *)ALIGNED_CHUNK + chunk->size);

    g_data->addr_return = chunk;
    return (true);
}

void    large_alloc(t_large_heap *heap, size_t size)
{
    t_large_heap *heap_tmp = NULL;
    t_large_heap *new_heap = NULL;

    while (heap != NULL)
    {
        heap_tmp = heap;
        heap = heap->next;
    }

    new_heap = (t_large_heap *)mmap(NULL, (size_t)align((void*)size + ALIGNED_LARGE_HEAP), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_heap == MAP_FAILED)
    {
        g_data->failed = true;
        return ;
    }

    if (heap_tmp != NULL)
        heap_tmp->next = new_heap;
    else
        g_data->large_heap = new_heap;
    new_heap->prev = heap_tmp;
    new_heap->next = NULL;
    
    new_heap->start = (void *)((size_t)new_heap + ALIGNED_LARGE_HEAP);
    new_heap->size = size;
    
    g_data->addr_return = new_heap->start;
}
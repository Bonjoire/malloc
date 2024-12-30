/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_debug.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:44:59 by hubourge          #+#    #+#             */
/*   Updated: 2024/12/30 18:45:04 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void show_heap(size_t base, t_heap *heap);
static void show_large_heap(size_t base, t_large_heap *heap);

void show_alloc_debug()
{
    if (g_data == NULL)
        return ;

    size_t base = (size_t)g_data;
    printf("DATA :      %p (%zu)\n", g_data, (size_t)g_data - base);

    printf("| - Tiny :      %p meta(%zu) deep(%zu)\n", g_data->tiny_heap, (size_t)g_data->tiny_heap - (size_t)g_data, (size_t)g_data->tiny_heap - base);
    show_heap(base, g_data->tiny_heap);
    
    printf("| - Small :      %p meta(%zu) deep(%zu)\n", g_data->small_heap, (size_t)g_data->small_heap - (size_t)g_data->tiny_heap,  (size_t)g_data->small_heap - base);
    show_heap(base, g_data->small_heap);
   
    printf("| - Large :      %p meta(%zu) deep(%zu)\n", g_data->large_heap, (size_t)g_data->large_heap - (size_t)g_data,  (size_t)g_data->large_heap - base);
    show_large_heap(base, g_data->large_heap);
}

static void show_heap(size_t base, t_heap *heap)
{
    t_block *block = heap->first_block;
    
    while (block)
    {
        printf("  | - BLOCK :      %p meta(%zu) deep(%zu)\n", block, ALIGNED_BLOCK, (size_t)block - base);
        t_chunk *chunk = block->first_chunk;
        while (chunk)
        {
            printf("     | - CHUNK :      %p meta(%zu) deep(%zu) size(%zu) align(%zu)\n", chunk, (size_t)chunk->chunk - (size_t)chunk, (size_t)chunk - base, chunk->size, (size_t)align((void*)chunk->size));
            chunk = chunk->next;
        }
        printf("\n");
        block = block->next;
    }
}

static void show_large_heap(size_t base, t_large_heap *heap)
{
    t_large_heap* large_heap = heap;

    while (large_heap)
    {
        printf("  | - CHUNK :      %p meta(%zu) deep(%zu) size(%zu) align(%zu)\n", large_heap, ALIGNED_LARGE_HEAP, (size_t)large_heap - base, large_heap->size, (size_t)align((void*)large_heap->size));
        large_heap = large_heap->next;
    }
}

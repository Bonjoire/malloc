/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_debug.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:44:59 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/03 16:54:55 by hubourge         ###   ########.fr       */
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
    ft_printf("DATA :      %p (%d)\n", g_data, (int)(size_t)g_data - (int)base);

    ft_printf("| - Tiny :      %p meta(%d) deep(%d)\n", g_data->tiny_heap, (int)((size_t)g_data->tiny_heap - (size_t)g_data), (int)((size_t)g_data->tiny_heap - base));
    show_heap(base, g_data->tiny_heap);
    
    ft_printf("| - Small :      %p meta(%d) deep(%d)\n", g_data->small_heap, (int)((size_t)g_data->small_heap - (size_t)g_data->tiny_heap),  (int)((size_t)g_data->small_heap - base));
    show_heap(base, g_data->small_heap);
   
    ft_printf("| - Large :      %p meta(%d) deep(%d)\n", g_data->large_heap, (int)((size_t)g_data->large_heap - (size_t)g_data),  (int)((size_t)g_data->large_heap - base));
    show_large_heap(base, g_data->large_heap);
}

static void show_heap(size_t base, t_heap *heap)
{
    t_block *block = heap->first_block;
    
    (void)base;
    (void)heap;
    while (block)
    {
        ft_printf("  | - BLOCK :      %p meta(%d) deep(%d)\n", block, (int)ALIGNED_BLOCK, (int)((size_t)block - base));
        t_chunk *chunk = block->first_chunk;
        while (chunk)
        {
            ft_printf("     | - CHUNK :      %p meta(%d) deep(%d) size(%d) align(%d)\n", chunk, (int)((size_t)chunk->chunk - (size_t)chunk), (int)((size_t)chunk - base), (int)(chunk->size), (int)((size_t)align((void*)chunk->size)));
            chunk = chunk->next;
        }
        ft_printf("\n");
        block = block->next;
    }
}

static void show_large_heap(size_t base, t_large_heap *heap)
{
    t_large_heap* large_heap = heap;

    
    while (large_heap)
    {
        ft_printf("  | - CHUNK :      %p meta(%d) deep(%d) size(%d) align(%d)\n", large_heap, (int)ALIGNED_LARGE_HEAP, (int)((size_t)large_heap - base), (int)large_heap->size, (int)((size_t)align((void*)large_heap->size)));
        large_heap = large_heap->next;
    }
}

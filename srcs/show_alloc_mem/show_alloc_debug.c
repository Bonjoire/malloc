/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_debug.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:44:59 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/03 19:21:30 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void show_heap(t_heap *heap);
static void show_large_heap(t_large_heap *heap);

void show_alloc_debug()
{
	if (g_data == NULL)
		return ;

	long long base = (size_t)g_data;
	ft_printf("DATA :      %p (%T)\n", g_data, (size_t)g_data - (size_t)base);

	ft_printf("| - Tiny :      %p meta(%T) deep(%T)\n", g_data->tiny_heap, (size_t)g_data->tiny_heap - (size_t)g_data, (size_t)g_data->tiny_heap - base);
	show_heap(g_data->tiny_heap);

	ft_printf("| - Small :      %p meta(%T) deep(%T)\n", g_data->small_heap, (size_t)g_data->small_heap - (size_t)g_data->tiny_heap,  (size_t)g_data->small_heap - base);
	show_heap(g_data->small_heap);

	ft_printf("| - Large :      (16)%p, (10)%T\n", g_data->large_heap, (size_t)g_data->large_heap);
	show_large_heap(g_data->large_heap);
}

static void show_heap(t_heap *heap)
{
	t_block	*block	= heap->first_block;
	size_t	base	= (size_t)block;
	
	while (block)
	{
		ft_printf("  | - BLOCK :      %p meta(%T) deep(%T)\n", block, (size_t)ALIGNED_BLOCK, (size_t)block - (size_t)base);
		t_chunk *chunk = block->first_chunk;
		
		while (chunk)
		{
			ft_printf("     | - CHUNK :      %p meta(%T) deep(%T) size(%T) align(%T)\n", chunk, (size_t)ALIGNED_CHUNK, (size_t)chunk - (size_t)base, chunk->size, (size_t)align((void*)chunk->size));
			chunk = chunk->next;
		}
		
		ft_printf("\n");
		block = block->next;
	}
}

static void show_large_heap(t_large_heap *heap)
{
	t_large_heap* large_heap = heap;
	t_large_heap* tmp = large_heap;
	
	while (large_heap)
	{
		
		ft_printf("  | - BLOCK :      (16)%p, (10)%T ", large_heap, (size_t)large_heap);
		if ((size_t)tmp < (size_t)large_heap)
			ft_printf("diff(%T)", (size_t)large_heap - (size_t)tmp);
		else
			ft_printf("diff(%T)", (size_t)tmp - (size_t)large_heap);
		ft_printf(" meta(%T) size(%T) align(%T)\n", (size_t)ALIGNED_LARGE_HEAP, large_heap->size, (size_t)align((void*)large_heap->size));

		tmp = large_heap;
		large_heap = large_heap->next;
	}
}

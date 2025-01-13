/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_debug.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:44:59 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/13 14:27:09 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	show_heap(t_heap *heap);
static void	show_large_heap(t_large_heap *heap);

void	show_alloc_debug()
{
	if (g_data == NULL)
	{
		ft_printf("show_alloc_debug : No memory allocated\n");
		return ;
	}

	ft_printf("\n============== SHOW ALLOC DEBUG ==============\n|\n");

	long long base = (size_t)g_data;
	ft_printf("| DATA :      %p (%T)\n", g_data, (size_t)g_data - (size_t)base);

	ft_printf("| - Tiny :      %p meta(%T) deep(%T)\n", g_data->tiny_heap, (size_t)g_data->tiny_heap - (size_t)g_data, (size_t)g_data->tiny_heap - base);
	show_heap(g_data->tiny_heap);

	ft_printf("| - Small :      %p meta(%T) deep(%T)\n", g_data->small_heap, (size_t)g_data->small_heap - (size_t)g_data->tiny_heap,  (size_t)g_data->small_heap - base);
	show_heap(g_data->small_heap);

	ft_printf("| - Large :      (16)%p, (10)%T\n", g_data->large_heap, (size_t)g_data->large_heap);
	show_large_heap(g_data->large_heap);

	ft_printf("|\n==============================================\n");
}

static void	show_heap(t_heap *heap)
{
	t_block	*block	= heap->first_block;
	
	while (block)
	{
		size_t	base	= (size_t)block;
		t_chunk	*chunk	= block->first_chunk;
		ft_printf("|   - BLOCK :      %p meta(%T) pos(%T) after(%T)\n", block, (size_t)ALIGNED_BLOCK, (size_t)block, (size_t)block->size_next);

		while (chunk)
		{
			ft_printf("|            / ->prev %p\n", chunk->prev ? (chunk->prev->chunk ? chunk->prev->chunk : NULL) : NULL);
			ft_printf("|      - CHUNK :      %p meta(%T) deep(%T) size(%T) align(%T) after(%T)\n", chunk->chunk, (size_t)ALIGNED_CHUNK, (size_t)chunk - (size_t)base, chunk->size, (size_t)align((void*)chunk->size), (size_t)chunk->size_next);
			ft_printf("|            \\ ->next %p\n", chunk->next ? (chunk->next->chunk ? chunk->next->chunk : NULL) : NULL);
			chunk = chunk->next;
		}
		
		ft_printf("|\n");
		block = block->next;
	}
}

static void	show_large_heap(t_large_heap *heap)
{
	t_large_heap* large_heap = heap;
	t_large_heap* tmp = large_heap;
	
	while (large_heap)
	{
		ft_printf("              / ->prev %p\n", large_heap->prev ? (large_heap->prev->start ? large_heap->prev->start : NULL) : NULL);
		
		ft_printf("  | - BLOCK :      (16)%p, (10)%T ", large_heap->start, (size_t)large_heap->start);
		if ((size_t)tmp < (size_t)large_heap)
			ft_printf("diff(%T)", (size_t)large_heap - (size_t)tmp);
		else
			ft_printf("diff(%T)", (size_t)tmp - (size_t)large_heap);
		ft_printf(" meta(%T) size(%T) align(%T)\n", (size_t)ALIGNED_LARGE_HEAP, large_heap->size, (size_t)align((void*)large_heap->size));

		ft_printf("              \\ ->next %p\n", large_heap->next ? (large_heap->next->start ? large_heap->next->start : NULL) : NULL);

		tmp = large_heap;
		large_heap = large_heap->next;
	}
}

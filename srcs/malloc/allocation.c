/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:55:35 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/09 18:33:19 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void heap_alloc(t_heap *heap, size_t heap_pagesize, size_t size)
{
	t_block *block_prev  = NULL;
	t_block *block      = heap->first_block;

	while (block != NULL)
	{
		// If there is enough space in the block, 
		// create a new chunk and return true, else return false
		if (try_alloc_new_chunk_if_space_in_block(block, size))
			return ;
		block_prev = block;
		block = block->next;
	}

	block = (t_block *)mmap(NULL, (size_t)heap_pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (block == MAP_FAILED)
	{
		g_data->failed = true;        
		return ;
	}

	// Set start position of the block
	if (block_prev != NULL)
		block_prev->next = block;
	else
		heap->first_block = block;

	block->free_size = heap_pagesize - ALIGNED_BLOCK;
	block->size_next = 0;
	block->next = NULL;

	chunk_alloc(block, size, NULL);
}

void    chunk_alloc(t_block *block, size_t size, t_chunk *chunk_next)
{
	block->first_chunk          = (t_chunk *)((size_t)block + ALIGNED_BLOCK);
	block->first_chunk->chunk   = (t_chunk *)((size_t)block->first_chunk + ALIGNED_CHUNK);
	
	block->first_chunk->prev = NULL;
	block->first_chunk->next = chunk_next;
	
	block->first_chunk->size = size;
	block->free_size -= (size_t)align((void *)ALIGNED_CHUNK + block->first_chunk->size);
	if (chunk_next)
	{
		block->first_chunk->size_next = block->size_next - (size_t)align((void *)ALIGNED_CHUNK + block->first_chunk->size);
	}
	else
		block->first_chunk->size_next = block->free_size;
	block->size_next = 0;
	
	g_data->addr_return = block->first_chunk->chunk;
	g_data->total_size += size;
}

bool    try_alloc_new_chunk_if_space_in_block(t_block *block, size_t size)
{
	t_chunk *chunk_tmp = NULL;
	t_chunk *chunk = block->first_chunk;

	// Check if there is enough space in the block
	if (block && block->free_size < (size_t)align((void *)ALIGNED_CHUNK + size))
		return (false);

	// Allocate a new chunk at the beginning of the block
	if ((size_t)align((void*)ALIGNED_CHUNK + size) <= block->size_next)
	{
		chunk_alloc(block, size, chunk);
		return (true);
	}

	while (chunk)
	{
		if (try_alloc_new_chunk_if_space_in_chunk(block, chunk, size))
			return (true);
		chunk_tmp = chunk;
		chunk = chunk->next;
	}

	// Check if there is enough space before the end of the block
	if (chunk && chunk->size_next < (size_t)align((void*)ALIGNED_CHUNK + size))
		return (false);

	chunk = (t_chunk*)((size_t)chunk_tmp->chunk + (size_t)align((void*)(size_t)chunk_tmp + chunk_tmp->size) - (size_t)chunk_tmp);
	chunk->chunk = (t_chunk *)((size_t)chunk + ALIGNED_CHUNK);

	chunk_tmp->next = chunk;
	chunk->prev = chunk_tmp;
	chunk->next = NULL;

	chunk->size = size;
	block->free_size -= (size_t)align((void*)ALIGNED_CHUNK + chunk->size);
	chunk->size_next = block->free_size;

	g_data->addr_return = chunk->chunk;
	g_data->total_size += size;

	return (true);
}

bool    try_alloc_new_chunk_if_space_in_chunk(t_block* block, t_chunk *prev_chunk, size_t size)
{
	// ft_printf("prev_chunk->size_next %T\n", prev_chunk->size_next);
	// ft_printf("size %T\n", (size_t)align((void*)size));
	if (prev_chunk && prev_chunk->size_next < (size_t)align((void*)ALIGNED_CHUNK + size))
		return (false);
	// printf("alloc after chunk\n\n");

	t_chunk *new_chunk = NULL;
	t_chunk *next_chunk = prev_chunk->next ? prev_chunk->next : NULL;

	// ft_printf("------ BEFORE -------\n");
	// if (prev_chunk)
	// 	ft_printf("prev_chunk->prev       %p, %T\n", prev_chunk->prev, (size_t)prev_chunk->prev);
	// ft_printf("prev_chunk             %p, %T\n", prev_chunk, (size_t)prev_chunk);
	// ft_printf("prev_chunk->next       %p, %T\n", prev_chunk->next, (size_t)prev_chunk->next);

	// ft_printf("-----------------------\n");
	// if (new_chunk)
	// 	ft_printf("new_chunk->prev       %p, %T\n", new_chunk->prev, (size_t)new_chunk->prev);
	// ft_printf("new_chunk             %p, %T\n", new_chunk, (size_t)new_chunk);
	// ft_printf("new_chunk->next       %p, %T\n", new_chunk->next, (size_t)new_chunk->next);

	// ft_printf("-----------------------\n");
	// if (next_chunk)
	// 	ft_printf("next_chunk->prev       %p, %T\n", next_chunk->prev, (size_t)next_chunk->prev);
	// ft_printf("next_chunk             %p, %T\n", next_chunk, (size_t)next_chunk);
	// if (next_chunk)
		// ft_printf("next_chunk->next       %p, %T\n", next_chunk->next, (size_t)next_chunk->next);

	// ft_printf("prev_chunk->size_next %p, %T\n", prev_chunk->size_next, (size_t)prev_chunk->size_next);
	// if (prev_chunk->next)
	// 	ft_printf("prev_chunk->next->prev %p, %T\n", prev_chunk->next->prev, (size_t)prev_chunk->next->prev);
	// ft_printf("\n");

	new_chunk = (t_chunk *)((size_t)prev_chunk->chunk + (size_t)align((void*)(size_t)prev_chunk + prev_chunk->size) - (size_t)prev_chunk);
	new_chunk->chunk = (t_chunk *)((size_t)new_chunk + ALIGNED_CHUNK);

	// if (next_chunk) ///
	// 	ft_printf("1 next_chunk->next       %p, %T\n", next_chunk->next, (size_t)next_chunk->next);

	prev_chunk->next = new_chunk;

	// if (next_chunk) ///
	// 	ft_printf("2 next_chunk->next       %p, %T\n", next_chunk->next, (size_t)next_chunk->next);

    if (next_chunk)
		next_chunk->prev = new_chunk;

	// if (next_chunk) ///
	// 	ft_printf("3 next_chunk->next       %p, %T\n", next_chunk->next, (size_t)next_chunk->next);

	// if (next_chunk && new_chunk->size == 0)
    	// new_chunk->next = next_chunk->next;
	// else
    	new_chunk->next = next_chunk;

	// if (next_chunk) ///
	// 	ft_printf("4 next_chunk->next       %p, %T\n", next_chunk->next, (size_t)next_chunk->next);

	new_chunk->prev = prev_chunk;

	// if (next_chunk) ///
	// 	ft_printf("5 next_chunk->next       %p, %T\n", next_chunk->next, (size_t)next_chunk->next);

	// ft_printf("\n------ AFTER -------\n");
	// if (prev_chunk)
	// 	ft_printf("prev_chunk->prev       %p, %T\n", prev_chunk->prev, (size_t)prev_chunk->prev);
	// ft_printf("prev_chunk             %p, %T\n", prev_chunk, (size_t)prev_chunk);
	// ft_printf("prev_chunk->next       %p, %T\n", prev_chunk->next, (size_t)prev_chunk->next);

	// ft_printf("-----------------------\n");
	// if (new_chunk)
	// 	ft_printf("new_chunk->prev       %p, %T\n", new_chunk->prev, (size_t)new_chunk->prev);
	// ft_printf("new_chunk             %p, %T\n", new_chunk, (size_t)new_chunk);
	// ft_printf("new_chunk->next       %p, %T\n", new_chunk->next, (size_t)new_chunk->next);

	// ft_printf("-----------------------\n");
	// if (next_chunk && next_chunk->next)
	// 	ft_printf("next_chunk->next->prev       %p, %T\n", next_chunk->next->prev, (size_t)next_chunk->next->prev);
	// if (next_chunk && next_chunk->next)
	// ft_printf("next_chunk->next             %p, %T\n", next_chunk->next, (size_t)next_chunk->next);
	// if (next_chunk && next_chunk->next)
	// 	ft_printf("next_chunk->next->next       %p, %T\n", next_chunk->next->next, (size_t)next_chunk->next->next);

	
	new_chunk->size = size;

	// ft_printf("======= BEFORE =======\n");
	// ft_printf("prev_chunk->size_next %T - %T\n", prev_chunk->size_next, (size_t)align((void*)ALIGNED_CHUNK + new_chunk->size));
	// ft_printf("new_chunk->size_next %T\n", new_chunk->size_next);

	if (prev_chunk->size_next && prev_chunk->size)
		new_chunk->size_next = prev_chunk->size_next - (size_t)align((void*)ALIGNED_CHUNK + new_chunk->size);
	else
		new_chunk->size_next = block->free_size - (size_t)align((void*)ALIGNED_CHUNK + new_chunk->size);
	block->free_size -= (size_t)align((void*)ALIGNED_CHUNK + new_chunk->size);

	if (prev_chunk->next)
		prev_chunk->size_next = 0;

	// ft_printf("======= AFTER =======\n");
	// ft_printf("prev_chunk->size_next %T\n", prev_chunk->size_next);
	// ft_printf("new_chunk->size_next %T\n", new_chunk->size_next);

	g_data->addr_return = new_chunk->chunk;
	g_data->total_size += size;

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

	new_heap = (t_large_heap *)mmap(NULL, (size_t)align(ALIGNED_LARGE_HEAP + (void*)size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
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
	g_data->total_size += size;

}

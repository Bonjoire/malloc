/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:55:35 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/03 19:23:52 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void heap_alloc(t_heap *heap, size_t heap_pagesize, size_t size)
{
	t_block *block_tmp  = NULL;
	t_block *block      = heap->first_block;

	while (block != NULL)
	{
		// If there is enough space in the block, 
		// create a new chunk and return true, else return false
		if (try_alloc_new_chunk_if_space_in_block(block, size))
			return ;
		block_tmp = block;
		block = block->next;
	}

	// ft_putstr_fd("heap_pagesize ", 1);
	// ft_putnbr_base_fd((size_t)heap_pagesize, "0123456789", 1);
	// ft_putstr_fd(" sizeof(size_t) ", 1);
	// ft_putnbr_base_fd(sizeof(size_t), "0123456789", 1);
	// ft_putstr_fd("\n", 1);

	// ft_putstr_fd("heap_pagesize ", 1);
	// ft_putnbr_base_fd((unsigned long)heap_pagesize, "0123456789", 1);
	// ft_putstr_fd(" sizeof(unsigned long) ", 1);
	// ft_putnbr_base_fd(sizeof(unsigned long), "0123456789", 1);
	// ft_putstr_fd("\n", 1);
	
	// ft_printf("block tmp %p, %T, ", block_tmp, (size_t)block_tmp);
	// ft_putnbr_base_fd((size_t)block_tmp, "0123456789", 1);
	// ft_printf("\n");
	
	// ft_printf("block bef %p, %T, ", block, (size_t)block);
	// ft_putnbr_base_fd((size_t)block, "0123456789", 1);
	// ft_printf("\n");
	
	// ft_printf("heap_pagesize %T, ", (size_t)heap_pagesize);
	// ft_putnbr_base_fd((size_t)heap_pagesize, "0123456789", 1);
	// ft_printf("\n");

	// ft_printf("g_data      %p, %T, ", g_data,  (size_t)g_data);
	// ft_putnbr_base_fd((size_t)g_data, "0123456789", 1);
	// ft_printf("\n");

	// heap_pagesize
	block = (t_block *)mmap(NULL, (size_t)heap_pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (block == MAP_FAILED)
	{
		g_data->failed = true;        
		return ;
	}

	// ft_printf("block after %p, %T, ", block, (size_t)block);
	// ft_putnbr_base_fd((size_t)block, "0123456789", 1);
	// ft_printf("\n");

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
	block->first_chunk->size_next = block->free_size;
	
	g_data->addr_return = block->first_chunk->chunk;
}

bool    try_alloc_new_chunk_if_space_in_block(t_block *block, size_t size)
{
	t_chunk *chunk_tmp = NULL;
	t_chunk *chunk = block->first_chunk;

	if (block && block->free_size < (size_t)align((void *)ALIGNED_CHUNK + size))
		return (false);

	while (chunk != NULL)
	{
		if (try_alloc_new_chunk_if_space_in_chunk(block, chunk, size))
			return (true);
		chunk_tmp = chunk;
		chunk = chunk->next;
	}

	chunk = (t_chunk*)((size_t)chunk_tmp->chunk + (size_t)align((void*)(size_t)chunk_tmp + chunk_tmp->size) - (size_t)chunk_tmp);
	chunk->chunk = (t_chunk *)((size_t)chunk + ALIGNED_CHUNK);
	
	chunk_tmp->next = chunk;
	chunk->prev = chunk_tmp;
	chunk->next = NULL;

	chunk->size = size;
	block->free_size -= (size_t)align((void*)ALIGNED_CHUNK + chunk->size);
	chunk->size_next = block->free_size;

	g_data->addr_return = chunk->chunk;
	return (true);
}

bool    try_alloc_new_chunk_if_space_in_chunk(t_block* block, t_chunk *prev_chunk, size_t size)
{
	if (prev_chunk && prev_chunk->size_next < (size_t)align((void*)ALIGNED_CHUNK + size))
		return (false);

	t_chunk *new_chunk;
	t_chunk *next_chunk = prev_chunk->next ? prev_chunk->next : NULL;

	// ft_printf("! prev_chunk             %p, %T\n", prev_chunk, (size_t)prev_chunk);
	// ft_printf("! prev_chunk->next       %p, %T\n", prev_chunk->next, (size_t)prev_chunk->next);
	// ft_printf("! prev_chunk->size_next %p, %T\n", prev_chunk->size_next, (size_t)prev_chunk->size_next);
	// if (prev_chunk->next)
	// 	ft_printf("! prev_chunk->next->prev %p, %T\n", prev_chunk->next->prev, (size_t)prev_chunk->next->prev);
	// ft_printf("\n");

	new_chunk = (t_chunk *)((size_t)prev_chunk->chunk + (size_t)align((void*)(size_t)prev_chunk + prev_chunk->size) - (size_t)prev_chunk);
	new_chunk->chunk = (t_chunk *)((size_t)new_chunk + ALIGNED_CHUNK);

	prev_chunk->next = new_chunk;

    if (next_chunk)
		next_chunk->prev = new_chunk;
    new_chunk->next = next_chunk;
	new_chunk->prev = prev_chunk;

	// ft_printf("prev_chunk       %p, %T\n", prev_chunk, (size_t)prev_chunk);
	// ft_printf("prev_chunk->next %p, %T\n", prev_chunk->next, (size_t)prev_chunk->next);
	// ft_printf("prev_chunk->size_next %p, %T\n", prev_chunk->size_next, (size_t)prev_chunk->size_next);

	// ft_printf("new_chunk        %p, %T\n", new_chunk, (size_t)new_chunk);
	// ft_printf("new_chunk->prev  %p, %T\n", new_chunk->prev, (size_t)new_chunk->prev);
	// ft_printf("new_chunk->next  %p, %T\n", new_chunk->next, (size_t)new_chunk->next);

	// if (next_chunk)
	// {
	// 	ft_printf("next_chunk       %p, %T\n", next_chunk, (size_t)next_chunk);
	// 	ft_printf("next_chunk->prev %p, %T\n", next_chunk->prev, (size_t)next_chunk->prev);
	// }
	// ft_printf("\n");

	prev_chunk->size_next = 0;
	new_chunk->size = size;
	
	block->free_size -= (size_t)align((void*)ALIGNED_CHUNK + new_chunk->size);
	new_chunk->size_next = prev_chunk->size_next - (size_t)align((void*)ALIGNED_CHUNK + new_chunk->size);

	g_data->addr_return = new_chunk->chunk;
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
}

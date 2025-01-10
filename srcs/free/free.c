/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:40:16 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/09 18:36:04 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// typedef struct chunk
// {
// 	struct chunk		*chunk;
// 	struct chunk		*next;
// 	struct chunk		*prev;
// 	size_t				size;
// 	size_t				size_next;
// }					t_chunk;

void free(void *ptr)
{
    // ft_printf("\n========== FREE ==========\n");

    t_block *parent_block       = NULL;
    t_chunk *chunk              = find_address_heap(ptr, &parent_block);
    t_large_heap *large_heap    = find_address_large_heap(ptr);

    if (chunk)
    {
        t_chunk *prev_chunk = chunk->prev;
        t_chunk *next_chunk = chunk->next;

		// Set next chunk
        if (next_chunk)
            next_chunk->prev = prev_chunk;

		// Free size and set size_next to future allocation
        if (prev_chunk)
            prev_chunk->size_next += (size_t)align((void*)ALIGNED_CHUNK + chunk->size) + chunk->size_next;
		else if (chunk->chunk == parent_block->first_chunk->chunk)
			parent_block->size_next += (size_t)align((void*)ALIGNED_CHUNK + chunk->size) + chunk->size_next;
		parent_block->free_size += (size_t)align((void*)ALIGNED_CHUNK + chunk->size);
		g_data->total_size -= chunk->size;

	   	// Set prev chunk (or prev block)
        if (prev_chunk)
            prev_chunk->next = next_chunk;
		else if (chunk->chunk == parent_block->first_chunk->chunk)
			parent_block->first_chunk = next_chunk;
	   
		// Empty the chunk
		chunk->size_next = 0;
		chunk->size = 0;
        chunk->chunk = NULL;
        chunk->next = NULL;
        chunk->prev = NULL;
        chunk = NULL;

        free_block_if_empty(parent_block); // Est ce que on throw une erreur si munmap == NULL ?
    }
    else if (large_heap)
    {
        // struct	large_heap	*prev;
        // struct	large_heap	*next;
        // void				*start;
        // size_t				size;

        // Set prev and next
        if (large_heap->prev)
            large_heap->prev->next = large_heap->next;
        else
            g_data->large_heap = large_heap->next;
        if (large_heap->next)
            large_heap->next->prev = large_heap->prev;

        g_data->total_size -= large_heap->size;

        munmap(large_heap, large_heap->size);
    }
    else
        ft_printf("free(): invalid pointer\n", ptr);
}

void    free_block_if_empty(t_block* block)
{
    if (block && block->first_chunk == NULL)
    {
        if (block->prev)
            block->prev->next = block->next;
        else   
            block->heap->first_block = block->next;
        if (block->next)
            block->next->prev = block->prev;
        munmap(block, block->heap->pagesize);
    }
}
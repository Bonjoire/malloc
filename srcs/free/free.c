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

        // ft_printf("chunk addr(%p), block(%p)\n", chunk->chunk, parent_block);
        // ft_printf("------ BEFORE -------\n");
        // if (prev_chunk)
        // 	ft_printf("prev_chunk->prev       %p, %T\n", prev_chunk->prev, (size_t)prev_chunk->prev);
        // ft_printf("prev_chunk             %p, %T\n", prev_chunk, (size_t)prev_chunk);
        // ft_printf("prev_chunk->next       %p, %T\n", prev_chunk->next, (size_t)prev_chunk->next);

        // ft_printf("-----------------------\n");
        // if (chunk)
        // 	ft_printf("chunk->prev       %p, %T\n", chunk->prev, (size_t)chunk->prev);
        // ft_printf("chunk             %p, %T\n", chunk, (size_t)chunk);
        // ft_printf("chunk->next       %p, %T\n", chunk->next, (size_t)chunk->next);

        // ft_printf("-----------------------\n");
        // if (next_chunk)
        // 	ft_printf("next_chunk->prev       %p, %T\n", next_chunk->prev, (size_t)next_chunk->prev);
        // ft_printf("next_chunk             %p, %T\n", next_chunk, (size_t)next_chunk);
        // if (next_chunk)
        //     ft_printf("next_chunk->next       %p, %T\n", next_chunk->next, (size_t)next_chunk->next);

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
	   
		// Empty chunk
		chunk->size_next = 0;
		chunk->size = 0;
        chunk->chunk = NULL;
        chunk->next = NULL;
        chunk->prev = NULL;
        chunk = NULL;

        // ft_printf("\n------ AFTER -------\n");
        // if (prev_chunk)
        // 	ft_printf("prev_chunk->prev       %p, %T\n", prev_chunk->prev, (size_t)prev_chunk->prev);
        // ft_printf("prev_chunk             %p, %T\n", prev_chunk, (size_t)prev_chunk);
        // ft_printf("prev_chunk->next       %p, %T\n", prev_chunk->next, (size_t)prev_chunk->next);

        // ft_printf("-----------------------\n");
        // if (chunk)
        // {
        // 	ft_printf("chunk->prev       %p, %T\n", chunk->prev, (size_t)chunk->prev);
        //     ft_printf("chunk             %p, %T\n", chunk, (size_t)chunk);
        //     ft_printf("chunk->next       %p, %T\n", chunk->next, (size_t)chunk->next);
        // }

        // ft_printf("-----------------------\n");
        // if (next_chunk)
        // 	ft_printf("next_chunk->prev       %p, %T\n", next_chunk->prev, (size_t)next_chunk->prev);
        // ft_printf("next_chunk             %p, %T\n", next_chunk, (size_t)next_chunk);
        // if (next_chunk)
        //     ft_printf("next_chunk->next       %p, %T\n", next_chunk->next, (size_t)next_chunk->next);
    }
    else if (large_heap)
    {
        ft_printf("large_heap addr = %p\n", large_heap->start);
    }
}

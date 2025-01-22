/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_address_heap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:40:46 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/22 17:04:11 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_chunk	*find_addr_heap(t_heap *heap, void *addr, t_block **parent_block, t_heap **parent_heap);

t_chunk	*find_address_heap(void *addr, t_block **parent_block, t_heap **parent_heap)
{
    t_chunk *addr_found;
	
    if (!addr || !g_data)
        return (NULL);

    addr_found = find_addr_heap(g_data->tiny_heap, addr, parent_block, parent_heap);
    if (addr_found)
        return (addr_found);

    addr_found = find_addr_heap(g_data->small_heap, addr, parent_block, parent_heap);
    if (addr_found)
        return (addr_found);
    return (NULL);
}

static t_chunk	*find_addr_heap(t_heap *heap, void *addr, t_block **parent_block, t_heap **parent_heap)
{
    if (g_data && !heap)
        return (NULL);
		
    t_block *block = heap->first_block;

    while (block)
    {
        t_chunk *chunk = block->first_chunk;
        while (chunk)
        {
            if (chunk->chunk == addr)
            {
				*parent_block = block;
				if (parent_heap)
					*parent_heap = heap;
                return (chunk);
            }
            chunk = chunk->next;
        }
        block = block->next;
    }
    return (NULL);
}
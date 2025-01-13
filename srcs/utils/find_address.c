/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_address.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:40:46 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/13 14:29:42 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_chunk	*find_addr_heap(t_heap *heap, void *addr, t_block **parent_block);

t_large_heap	*find_address_large_heap(void *addr)
{
    if (!addr || !g_data)
        return (NULL);

    t_large_heap *heap = g_data->large_heap;
    while (heap)
    {
        if (heap->start == addr)
            return (heap);
        heap = heap->next;
    }
    return (NULL);
}

t_chunk	*find_address_heap(void *addr, t_block **parent_block)
{
    t_chunk *addr_found;
	
    if (!addr || !g_data)
        return (NULL);

    addr_found = find_addr_heap(g_data->tiny_heap, addr, parent_block);
    if (addr_found)
        return (addr_found);

    addr_found = find_addr_heap(g_data->small_heap, addr, parent_block);
    if (addr_found)
        return (addr_found);
    return (NULL);
}

static t_chunk	*find_addr_heap(t_heap *heap, void *addr, t_block **parent_block)
{
    t_block *block = heap->first_block;
	
    if (g_data && heap)
        (void)NULL;

    while (block)
    {
        t_chunk *chunk = block->first_chunk;
        while (chunk)
        {
            if (chunk->chunk == addr)
            {
                *parent_block = block;
                return (chunk);
            }
            chunk = chunk->next;
        }
        block = block->next;
    }
    return (NULL);
}
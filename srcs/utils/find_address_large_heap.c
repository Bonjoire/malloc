/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_address_large_heap.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:40:46 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/22 15:00:50 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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

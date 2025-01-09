/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:40:16 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/09 18:36:40 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_data *g_data = NULL;

void *malloc(size_t size)
{
	// ft_printf("\n========= MALLOC ========\n");
    // ft_printf("size %T bytes\n", size);
	
    if (g_data == NULL)
    {
        if (!data_init(&g_data))
            return (NULL);
    }

    if (size <= TINY_S_MAX_ALLOC)
        heap_alloc(g_data->tiny_heap, TINY_S, size);
    else if (size <= SMALL_S_MAX_ALLOC)
        heap_alloc(g_data->small_heap, SMALL_S, size);
    else
        large_alloc(g_data->large_heap, size);
    
    if (g_data->failed == false)
        return (g_data->addr_return);
    
    return (NULL);
}

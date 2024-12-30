/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:40:16 by hubourge          #+#    #+#             */
/*   Updated: 2024/12/30 19:05:10 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_data *g_data = NULL;

void *malloc(size_t size)
{
    printf("-------------------\n");
    printf("-> Size = %zu (%lu)bytes\n", size, sizeof(size)); /// debug
    if (size == 0)
        return (NULL);

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

    printf("-------------------\n\n");
    if (g_data->failed == false)
        return (g_data->addr_return);
    
    return (NULL);
}

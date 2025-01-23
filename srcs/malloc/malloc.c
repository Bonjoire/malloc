/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:40:16 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/23 14:51:39 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_data 	*g_data			= NULL;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void *malloc(size_t size)
{
	pthread_mutex_lock(&g_mutex);
    if (g_data == NULL)
    {
        if (!data_init(&g_data))
		{
			pthread_mutex_unlock(&g_mutex);
            return (NULL);
		}
    }

    if (size <= TINY_S_MAX_ALLOC)
        heap_alloc(g_data->tiny_heap, TINY_S, size);
    else if (size <= SMALL_S_MAX_ALLOC)
        heap_alloc(g_data->small_heap, SMALL_S, size);
    else
        large_alloc(g_data->large_heap, size);
    
    if (g_data->failed == false)
	{
		pthread_mutex_unlock(&g_mutex);
        return (g_data->addr_return);
	}
	pthread_mutex_unlock(&g_mutex);
    return (NULL);
}

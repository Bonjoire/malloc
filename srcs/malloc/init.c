/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:42:39 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/23 15:07:43 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int data_init(t_data **data)
{
    struct rlimit limit;
    
    if (getrlimit(RLIMIT_AS, &limit) == -1)
        return (false);
    if (ALIGNED_DATA + ALIGNED_HEAP * 2 >= limit.rlim_max)
		return (false);

    (*data) = (t_data *)mmap(NULL, ALIGNED_DATA + ALIGNED_HEAP * 2, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if ((*data) == MAP_FAILED)
        return (false);

    tiny_init(data);
    small_init(data);
    (*data)->large_heap = NULL;

    (*data)->failed = false;
    (*data)->addr_return = NULL;
	(*data)->total_size = 0;

    return (true);
}

void    tiny_init(t_data **data)
{
    (*data)->tiny_heap = (t_heap *)((size_t)*data + ALIGNED_DATA);
    (*data)->tiny_heap->pagesize = TINY_S;
    (*data)->tiny_heap->first_block = NULL;
}

void    small_init(t_data **data)
{
    (*data)->small_heap = (t_heap *)((size_t)(*data)->tiny_heap + ALIGNED_HEAP);
    (*data)->small_heap->pagesize = SMALL_S;
    (*data)->small_heap->first_block = NULL;
}

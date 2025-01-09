/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:40:46 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/06 16:44:12 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *align(void *ptr_to_align)
{
    uintptr_t new_ptr = (uintptr_t)ptr_to_align;

    if ((new_ptr % ALIGNMENT) != 0)
        new_ptr += ALIGNMENT - (new_ptr % ALIGNMENT);

    return ((void *)new_ptr);
}

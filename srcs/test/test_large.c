/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:11:22 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/22 15:11:29 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	test_large(int *error, int to_free)
{
    void	*addr[10];
    size_t	nb_addr = 0;
    size_t	len = 0;
    size_t	sizes[] = {5185, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};

    ft_printf("--> TEST : large heap alloc\n");

    for (int i = 0; i < 8; i++)
    {
        size_t len_tmp = sizes[i] * sizeof(char);
        len += len_tmp;
        addr[nb_addr++] = malloc(len_tmp);
        if (addr[nb_addr - 1] && g_data && (g_data->total_size != len))
            ft_printf("ERROR : malloc(%u) = %p\n", (unsigned)len_tmp, addr[nb_addr - 1]), (*error)++;
    }
	for (int i = 0; to_free && i < 8; i++)
		free(addr[--nb_addr]);
}

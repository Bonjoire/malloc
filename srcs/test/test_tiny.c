/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tiny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:10:56 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/22 15:11:02 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	test_tiny(int *error, int to_free)
{
	void	*addr[5000];
	size_t	len_tmp	= 0;
	size_t	nb_addr	= 0;

	ft_printf("--> TEST : tiny heap alloc\n");

	// malloc(0), check if 0 bytes alloc in tiny heap
	{
		len_tmp = 0;
		addr[nb_addr++] = malloc(len_tmp);
		if (!addr[nb_addr - 1])
			ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);
		if (to_free)
			free(addr[--nb_addr]);
	}


	// malloc(16), fill completely a block
	// check there is no more space in the block
	{
		// (size  + metadata chunk) * 255 * sizeof(char) + metadata block
		// (16    + 48)             * 255 * 1            + 48             = 16368 bytes
		// 16368/16384 is the max memory allocatable in tiny
		for (int i = 0; i != 255; i++)
		{
			len_tmp = 16 * sizeof(char);
			addr[nb_addr++] = malloc(len_tmp);
			if (!addr[nb_addr - 1])
				ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);
		}
		for (int i = 0; to_free && i != 255; i++)
			free(addr[--nb_addr]);
	}

	// malloc(112), check if 112 bytes alloc in tiny heap
	// need minimum 100 alloc
	{
		for (int i = 0; i != 100; i++)
		{
			len_tmp = 112 * sizeof(char);
			addr[nb_addr++] = malloc(len_tmp);
			if (!addr[nb_addr - 1])
				ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);
		}
		for (int i = 0; to_free &&  i != 100; i++)
			free(addr[--nb_addr]);
	}

	{
		// malloc(2), write "1", result : "1"
		len_tmp = 2 * sizeof(char);
		addr[nb_addr++] = malloc(len_tmp);
		if (addr[nb_addr - 1])
			ft_strlcpy(addr[nb_addr - 1], "1", len_tmp);
		if (!addr[nb_addr - 1] || (addr[nb_addr - 1] && ft_strncmp(addr[nb_addr - 1], "1", len_tmp)))
			ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);

		// malloc(2), overwrite "Hello", result : "H"
		if (addr[nb_addr - 1])
			ft_strlcpy(addr[nb_addr - 1], "Hello", len_tmp);
		if (!addr[nb_addr - 1] || (addr[nb_addr - 1] && ft_strncmp(addr[nb_addr - 1], "H", len_tmp)))
			ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);

		if (to_free)
			free(addr[--nb_addr]);
	}
}

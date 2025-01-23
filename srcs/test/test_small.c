/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:11:11 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/22 15:11:13 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	test_small(int *error, int to_free)
{
	void	*addr[5000];
	int		len_tmp	= 0;
	int		nb_addr	= 0;
	char	*str;

	ft_printf("--> TEST : small heap alloc\n");

	// malloc(16), fill completely a block
	// check there is no more space in the block
	
	// (size  + metadata chunk) * 127 * sizeof(char) + size + metadata block
	// (4048  + 48)             * 127 * 1            + 4000 + 48             = 524288 bytes
	// 524288/524288 is the max memory allocatable in small heap
	{
		for (int i = 0; i < 127; i++)
		{
			len_tmp = 4048;
			addr[nb_addr++] = malloc(len_tmp);
			if (!addr[nb_addr - 1])
				ft_printf("ERROR : malloc(%d) = %p\n", (int)len_tmp, addr[nb_addr - 1]), (*error)++;
		}
		for (int i = 0; i < 1; i++)
		{
			len_tmp = 4000;
			addr[nb_addr++] = malloc(len_tmp);
			if (!addr[nb_addr - 1])
				ft_printf("ERROR : malloc(%d) = %p\n", (int)len_tmp, addr[nb_addr - 1]), (*error)++;
		}
		for (int i = 0; to_free && i < 127 + 1; i++)
			free(addr[--nb_addr]);
	}

	// malloc(112), check if 5148 bytes alloc in small 
	// need minimum 100 alloc
	{
		for (int i = 0; i < 100; i++)
    	{
			len_tmp = 5184;
			addr[nb_addr++] = malloc(len_tmp);
			if (!addr[nb_addr - 1])
				ft_printf("ERROR : malloc(%d) = %p\n", (int)len_tmp, addr[nb_addr - 1]), (*error)++;
   		}
		for (int i = 0; to_free && i < 100; i++)
			free(addr[--nb_addr]);
	}

	// malloc(128), write "1111"... , result : "1111"...
	{
		len_tmp = 128;
		str = malloc(len_tmp);
		addr[nb_addr++] = str;
		if (!str)
			ft_printf("ERROR : malloc(%d) = %p\n", (int)len_tmp, str), (*error)++;
		else
		{
			for (int i = 0; i < (int)len_tmp - 1; i++)
				str[i] = '1';
			str[len_tmp - 1] = '\0';
			for (int i = 0; i < (int)len_tmp - 1; i++)
				if (str[i] != '1')
					ft_printf("ERROR : bad write in str[%d]\n", i), (*error)++;
		}
		if (to_free)
			free(addr[--nb_addr]);
	}

    // malloc(128) and write "H"
	{
		len_tmp = 128;
		str = malloc(len_tmp);
		addr[nb_addr++] = str;
		if (!str)
			ft_printf("ERROR : malloc(%d) = %p\n", (int)len_tmp, str), (*error)++;
		else
		{
			ft_strlcpy(str, "H", len_tmp);
			if (ft_strncmp(str, "H", len_tmp))
				ft_printf("ERROR : malloc(%d) content != H\n", (int)len_tmp), (*error)++;
		}
		if (to_free)
			free(addr[--nb_addr]);
	}
}

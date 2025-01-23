/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:11:59 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/22 16:54:20 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	test_free(int *error)
{
	ft_printf("--> TEST : free\n");

	// Free first chunk next to block
	{	
		char *str1 = malloc(500 * sizeof(char));
		char *str2 = malloc(1000 * sizeof(char));

		free(str1);
		char *str3 = malloc(128 * sizeof(char));
		char *str4 = malloc(128 * sizeof(char));
		if (g_data && g_data->total_size != (128 * 2 + 1000))
			ft_printf("ERROR : total_size = %d\n", g_data->total_size,(*error)++);
		
		free(str2);
		free(str3);
		free(str4);
		if (g_data && g_data->total_size != 0)
			ft_printf("ERROR : total_size = %d\n", g_data->total_size,(*error)++);
	}

	// Free chunk between chunks
	{
		char *str1 = malloc(128 * sizeof(char));
		char *str2 = malloc(2500 * sizeof(char));
		char *str3 = malloc(128 * sizeof(char));
		
		free(str2);
		char *str4 = malloc(500 * sizeof(char));
		char *str5 = malloc(1000 * sizeof(char));
		if (g_data && g_data->total_size != (128 * 2 + 500 + 1000))
			ft_printf("ERROR : total_size = %d\n", g_data->total_size,(*error)++);

		free(str1);
		free(str3);
		free(str4);
		free(str5);
		if (g_data && g_data->total_size != 0)
			ft_printf("ERROR : total_size = %d\n", g_data->total_size,(*error)++);
	}

	// Free last chunk of a block
	{
		char *str1 = malloc(128 * sizeof(char));
		char *str2 = malloc(2500 * sizeof(char));
		char *str3 = malloc(128 * sizeof(char));

		free(str3);
		char *str4 = malloc(500 * sizeof(char));
		char *str5 = malloc(3000 * sizeof(char));
		if (g_data && g_data->total_size != (128 + 2500 + 3000 + 500))
			ft_printf("ERROR : total_size = %d\n", g_data->total_size,(*error)++);

		free(str1);
		free(str2);
		free(str4);
		free(str5);
		if (g_data && g_data->total_size != 0)
			ft_printf("ERROR : total_size = %d\n", g_data->total_size,(*error)++);
	}

	// Fill 3 block, and free all chunks of it to see munmap call
	{
		size_t	nb_chunk = 102;
		size_t  nb_block = 3; // Depend of the nb_chunk value to fill pagesize
		void	*addr_block[nb_block][nb_chunk];
	
		for (size_t i = 0; i < nb_block; i++)
		{
			for (size_t j = 0; j < nb_chunk; j++)
				addr_block[i][j] = malloc(112 * sizeof(char));
		}

		// Empty the block, check if munmap is called
		size_t	block_to_free = rand() % nb_block;
		for (size_t i = 0; i < nb_chunk; i++)
			free(addr_block[block_to_free][i]);

		// Free allocated memory
		for (size_t i = 0; i < nb_chunk; i++)
		{
			free(addr_block[(block_to_free + 1) % nb_block][i]);
			free(addr_block[(block_to_free + 2) % nb_block][i]);
		}
	}

	// Free in large_heap
	{
		char *str1 = malloc(10000 * sizeof(char));
		char *str2 = malloc(10000 * sizeof(char));
		char *str3 = malloc(20000 * sizeof(char));
		(void)str1;
		(void)str2;
		(void)str3;

		free(str1);
		free(str2);
		free(str3);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:26:59 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/09 18:37:46 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	malloc_test();
void	test_error();
void	test_tiny(size_t *error);
void	test_small(size_t *error);
void	test_free(size_t *error);
void	test_realloc(size_t *error);

int main()
{   
    ft_printf("\n==================== MAIN ====================\n\n");
	
    ft_printf("PAGESIZE = %d\n", (int)PAGESIZE);
    ft_printf("TINY_S = %d\n", (int)TINY_S);
    ft_printf("SMALL_S = %d\n", (int)SMALL_S);
    ft_printf("TINY_S_MAX_ALLOC = %d\n", (int)TINY_S_MAX_ALLOC);
    ft_printf("SMALL_S_MAX_ALLOC = %d\n", (int)SMALL_S_MAX_ALLOC);
    ft_printf("ALIGNED_DATA = %d\n", (int)ALIGNED_DATA);
    ft_printf("ALIGNED_HEAP = %d\n", (int)ALIGNED_HEAP);
    ft_printf("ALIGNED_LARGE_HEAP = %d\n", (int)ALIGNED_LARGE_HEAP);
    ft_printf("ALIGNED_BLOCK = %d\n", (int)ALIGNED_BLOCK);
    ft_printf("ALIGNED_CHUNK = %d\n", (int)ALIGNED_CHUNK);

    ft_printf("\n==================== TEST ====================\n\n");
	malloc_test();
}

// =================================== TEST ====================================

void	malloc_test()
{
	// return ;
	
	size_t	error	= 0;
	
	// test_free(&error);
	// test_realloc(&error);
	// test_error(&error);
	// test_tiny(&error);
	// test_small(&error);
	
	ft_printf("TOTAL ERROR : %d\n", error);

	ft_printf("\n================== SHOW DEBUG ================\n\n");
    show_alloc_debug();
    
    ft_printf("\n===================== SHOW ===================\n\n");
    show_alloc_mem();
}

void	test_error(size_t *error)
{
	size_t	len			= 0;
	size_t	len_tmp		= 0;
	size_t	len_init	= g_data ? g_data->total_size : 0;
	void	*addr;
	(void)error;

	ft_printf("--> TEST : error handling\n");

	len_tmp = 0;
	len += len_tmp;
	addr = malloc(len_tmp);
	if (addr && g_data && (g_data->total_size - len_init) != len)
		ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);

	// free(addr);

	// test avec rlimit
}

void	test_tiny(size_t *error)
{
	size_t	len			= 0;
	size_t	len_tmp		= 0;
	size_t	len_init	= g_data ? g_data->total_size : 0;
	void	*addr;
	(void)error;

	ft_printf("--> TEST : tiny heap alloc\n");

	// malloc(16), fill completely a block
	// check there is no more space in the block

	// (size  + metadata chunk) * 255 * sizeof(char) + metadata block
	// (16    + 48)             * 255 * 1            + 48             = 16368 bytes
	// 16368/16384 is the max memory allocatable in tiny
	for (int i = 0; i != 255; i++)
	{
		len_tmp = 16 * sizeof(char);
		len += len_tmp;
		addr = malloc(len_tmp);
		if (addr && g_data && (g_data->total_size - len_init) != len)
			ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);
	}

	// malloc(112), check if 112 bytes alloc in tiny heap
	// need minimum 100 alloc
	for (int i = 0; i != 100; i++)
	{
		len_tmp = 112 * sizeof(char);
		len += len_tmp;
		addr = malloc(len_tmp);
		if (addr && g_data && (g_data->total_size - len_init) != len)
			ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);
	}

	// malloc(2), write "1", result : "1"
	len_tmp = 2 * sizeof(char);
	len += len_tmp;
	addr = malloc(len_tmp);
	ft_strlcpy(addr, "1", len_tmp);
	if (addr && g_data && (g_data->total_size - len_init) != len && ft_strncmp(addr, "1", len_tmp))
		ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);
		
	// malloc(5), write "Hello", result : "Hello"
	len_tmp = 5 * sizeof(char);
	len += len_tmp;
	addr = malloc(len_tmp);
	ft_strlcpy(addr, "Hello", len_tmp);
	if (addr && g_data && (g_data->total_size - len_init) != len && ft_strncmp(addr, "Hello", len_tmp))
		ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);

	// malloc(2), overwrite "Hello", result : "H"
	len_tmp = 2 * sizeof(char);
	len += len_tmp;
	addr = malloc(len_tmp);
	ft_strlcpy(addr, "Hello", len_tmp);
	if (addr && g_data && (g_data->total_size - len_init) != len && ft_strncmp(addr, "H", len_tmp))
		ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);
}

void	test_small(size_t *error)
{
	size_t	len			= 0;
	size_t	len_tmp		= 0;
	size_t	len_init	= g_data ? g_data->total_size : 0;
	void	*addr;
	char	*str;
	(void)error;

	ft_printf("--> TEST : small heap alloc\n");

	// malloc(16), fill completely a block
	// check there is no more space in the block
	
	// (size  + metadata chunk) * 127 * sizeof(char) + size + metadata block
	// (4048  + 48)             * 127 * 1            + 4000 + 48             = 524288 bytes
	// 524288/524288 is the max memory allocatable in small heap
	for (int i = 0; i != 127; i++)
	{
		len_tmp = 4048 * sizeof(char);
		len += len_tmp;
		addr = malloc(len_tmp);
		if (addr && g_data && (g_data->total_size - len_init) != len)
			ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);
	}
	for (int i = 1; i != 2; i++)
	{
		len_tmp = 4000 * sizeof(char);
		len += len_tmp;
		addr = malloc(len_tmp);
		if (addr && g_data && (g_data->total_size - len_init) != len)
			ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);
	}

	// malloc(112), check if 5148 bytes alloc in small 
	// need minimum 100 alloc
	for (int i = 1; i != 100; i++)
	{
		len_tmp = 5148 * sizeof(char);
		len += len_tmp;
		addr = malloc(len_tmp);
		if (addr && g_data && (g_data->total_size - len_init) != len)
			ft_printf("ERROR : malloc(%d) = %p\n", len_tmp, addr,(*error)++);
	}

	// malloc(128), write "1111"... , result : "1111"...
	len_tmp = 128 * sizeof(char);
	len += len_tmp;
	str = malloc(len_tmp);
	if (str && g_data && (g_data->total_size - len_init) != len)
		ft_printf("ERROR : malloc(%d) = %s\n", len_tmp, str,(*error)++);
	for (int i = 0; i != 127; i++)
		str[i] = '1';
	str[len_tmp - 1] = '\0';
	for (int i = 0; i != 127; i++)
		if (str[i] != '1')
			ft_printf("ERROR : malloc(%d) str[%d] = %s,\n", len_tmp, i, str, (*error)++);
			
	// malloc(128), write "H", result : "H"
	len_tmp = 128 * sizeof(char);
	len += len_tmp;
	str = malloc(len_tmp);
	ft_strlcpy(str, "H", len_tmp);
	if (str && g_data && (g_data->total_size - len_init) != len && ft_strncmp(str, "H", len_tmp))
		ft_printf("ERROR : malloc(%d) = %s\n", len_tmp, str,(*error)++);
}

void	test_free(size_t *error)
{
	(void)error;	
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

void	test_realloc(size_t *error)
{
	(void)error;
	ft_printf("--> TEST : realloc\n");

	// Realloc input
	{
		// Simple free
		char *str1 = malloc(5 * sizeof(char));
		str1 = realloc(str1, 0);

		// Simple malloc
		char *str2 = realloc(NULL, 0);
		(void)str2;

		// Simple malloc
		char *str3 = realloc(NULL, 128);
		(void)str3;

		free(str2);
		free(str3);
	}
	// Realloc to a smaller size
	{
		char *str1 = malloc(128 * sizeof(char));
		char *str2 = malloc(2500 * sizeof(char));
		char *str3 = malloc(128 * sizeof(char));
		(void)str1;
		(void)str2;
		(void)str3;

		str1 = realloc(str1, 64 * sizeof(char));
		str2 = realloc(str2, 1000 * sizeof(char));
		str3 = realloc(str3, 64 * sizeof(char));

		free(str1);
		free(str2);
		free(str3);
	}
	// Realloc to a bigger size
	{
		char *str1 = malloc(128 * sizeof(char));
		char *str2 = malloc(2500 * sizeof(char));
		char *str3 = malloc(128 * sizeof(char));
		(void)str1;
		(void)str2;
		(void)str3;

		str1 = realloc(str1, 128 + 100 * sizeof(char));
		str2 = realloc(str2, 2500 + 100 * sizeof(char));
		str3 = realloc(str3, 128 + 100 * sizeof(char));

		free(str1);
		free(str2);
		free(str3);
	}
	// Realloc same size
	{
		char *str1 = malloc(5 * sizeof(char));
		ft_strlcpy(str1, "Hello", ft_strlen("Hello") + 1);

		str1 = realloc(str1, ft_strlen(str1) * sizeof(char));

		free(str1);
	}

	// Realloc in large heap
	{
		char *str1 = malloc(10000 * sizeof(char));
		char *str2 = malloc(10000 * sizeof(char));
		char *str3 = malloc(10000 * sizeof(char));
		(void)str1;
		(void)str2;
		(void)str3;

		str1 = realloc(str1, 10000 * sizeof(char));
		str2 = realloc(str2, 20000 * sizeof(char));
		str3 = realloc(str3, 6000 * sizeof(char));

		free(str1);
		free(str2);
		free(str3);
	}
}
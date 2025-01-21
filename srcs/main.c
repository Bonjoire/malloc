/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:26:59 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/13 14:28:34 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	malloc_test();
void	test_tiny(int *error, int to_free);
void	test_small(int *error, int to_free);
void	test_large(int *error, int to_free);
void	test_free(int *error);
void	test_realloc();

int main()
{   
    ft_printf("\n==================== TEST ====================\n\n");
	malloc_test();
}

// =================================== TEST ====================================

void	malloc_test()
{
	int	error	= 0;
	
	test_tiny(&error, DO_FREE_AFTER_MALLOC);
	test_small(&error, DO_FREE_AFTER_MALLOC);
	test_large(&error, DO_FREE_AFTER_MALLOC);
	test_free(&error);
	test_realloc();

	ft_printf("TOTAL ERROR : %d\n", error);
    show_alloc_debug();
    show_alloc_mem();
}

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

void	test_realloc()
{
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
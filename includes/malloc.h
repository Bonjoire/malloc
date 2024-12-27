/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:23:51 by hubourge          #+#    #+#             */
/*   Updated: 2024/12/26 22:26:35 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/mman.h>
# include <stdbool.h>

# define PAGESIZE 				getpagesize() // 16384 bytes
# define TINY_S					PAGESIZE * 2  // 32768 bytes
# define SMALL_S				PAGESIZE * 64 // 1048576 bytes
# define LARGE_S				1

# define ALIGNMENT 				16
# define ALIGNED_DATA			(size_t)align((void*)sizeof(t_data))
# define ALIGNED_HEAP			(size_t)align((void*)sizeof(t_heap))
# define ALIGNED_LARGE_HEAP		(size_t)align((void*)sizeof(t_large_heap))
# define ALIGNED_BLOCK			(size_t)align((void*)sizeof(t_block))
# define ALIGNED_CHUNK			(size_t)align((void*)sizeof(t_chunk))

// ALIGNED_DATA = 48
// ALIGNED_HEAP = 32
// ALIGNED_LARGE_HEAP = 32
// ALIGNED_BLOCK = 32
// ALIGNED_CHUNK = 48

# define TINY_S_MAX_ALLOC		(size_t)((TINY_S - ALIGNED_BLOCK) / 100) - ALIGNED_CHUNK - ALIGNMENT
# define SMALL_S_MAX_ALLOC		(size_t)((SMALL_S - ALIGNED_BLOCK) / 100) - ALIGNED_CHUNK - ALIGNMENT
// 279 bytes
// 10437 bytes

typedef struct data
{
	struct	heap		*tiny_heap;
	struct	heap		*small_heap;
	struct	large_heap	*large_heap;
	void				*addr_return;
	bool				failed;
}					t_data;

extern t_data *g_data;

typedef struct heap
{
	struct block		*first_block;
	size_t				pagesize;
	int					nb_blocks; /////// A SUPPRIMER ?
}					t_heap;

typedef struct large_heap
{
	struct	large_heap	*prev;
	struct	large_heap	*next;
	void				*start;
	size_t				size_allocated;
}					t_large_heap;

typedef struct block
{
	struct block		*prev;
	struct block		*next;
	struct chunk		*first_chunk;
	int					num;
	size_t				free_size;
}					t_block;

typedef struct chunk
{
	struct chunk		*chunk;
	struct chunk		*next;
	struct chunk		*prev;
	size_t				size;
	size_t				size_allocated;
}					t_chunk;

// malloc.c
void	*malloc(size_t size);
void	*align(void *ptr_to_align);
void	heap_alloc(t_heap *heap, size_t heap_pagesize, size_t size);
void    chunk_alloc(t_block *block, size_t size);

// init.c
int		data_init(t_data **data);
void    tiny_init(t_data **data);
void    small_init(t_data **data);

// show_alloc_mem.c
void	show_alloc_mem();
void	show_alloc_debug();

#endif
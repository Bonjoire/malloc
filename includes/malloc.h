/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:23:51 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/03 18:12:28 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "../libft/libft.h"

# include <stdio.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/time.h>
# include <sys/resource.h>

# define PAGESIZE 				(size_t)sysconf(_SC_PAGESIZE)	// 4096 bytes
# define TINY_S					(size_t)PAGESIZE * 4			// 16384 bytes
# define SMALL_S				(size_t)PAGESIZE * 128			// 524288 bytes
# define LARGE_S				1

# define ALIGNMENT 				16
# define ALIGNED_DATA			(size_t)align((void*)sizeof(t_data))
# define ALIGNED_HEAP			(size_t)align((void*)sizeof(t_heap))
# define ALIGNED_LARGE_HEAP		(size_t)align((void*)sizeof(t_large_heap))
# define ALIGNED_BLOCK			(size_t)align((void*)sizeof(t_block))
# define ALIGNED_CHUNK			(size_t)align((void*)sizeof(t_chunk))

// ALIGNED_DATA			= 48 bytes
// ALIGNED_HEAP			= 16 bytes
// ALIGNED_LARGE_HEAP	= 32 bytes
// ALIGNED_BLOCK		= 32 bytes
// ALIGNED_CHUNK		= 48 bytes 

# define TINY_S_MAX_ALLOC		(size_t)((TINY_S - ALIGNED_BLOCK) / 100) - ALIGNED_CHUNK - ALIGNMENT
# define SMALL_S_MAX_ALLOC		(size_t)((SMALL_S - ALIGNED_BLOCK) / 100) - ALIGNED_CHUNK - ALIGNMENT

// TINY_S_MAX_ALLOC		= 115 bytes
// SMALL_S_MAX_ALLOC	= 5194 bytes

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
}					t_heap;

typedef struct large_heap
{
	struct	large_heap	*prev;
	struct	large_heap	*next;
	void				*start;
	size_t				size;
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
	size_t				size_next;
}					t_chunk;

//	malloc.c
void	*malloc(size_t size);

// allocatoin.c
void	*align(void *ptr_to_align);
void	heap_alloc(t_heap *heap, size_t heap_pagesize, size_t size);
void	chunk_alloc(t_block *block, size_t size);
bool	try_alloc_new_chunk_if_space_in_block(t_block *block, size_t size);
bool    try_alloc_new_chunk_if_space_in_chunk(t_block* block, t_chunk *chunk, size_t size);
void	large_alloc(t_large_heap *heap, size_t size);

//	init.c
int		data_init(t_data **data);
void	tiny_init(t_data **data);
void	small_init(t_data **data);

//	show_alloc_mem.c
void	show_alloc_mem();

//	show_alloc_debug.c 
void	show_alloc_debug(); ////// remove from makefile berofe pushing ?

#endif
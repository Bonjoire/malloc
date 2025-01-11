/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:23:51 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/09 15:29:37 by hubourge         ###   ########.fr       */
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

# define ALIGNMENT 				16
# define ALIGNED_DATA			(size_t)align((void*)sizeof(t_data))
# define ALIGNED_HEAP			(size_t)align((void*)sizeof(t_heap))
# define ALIGNED_LARGE_HEAP		(size_t)align((void*)sizeof(t_large_heap))
# define ALIGNED_BLOCK			(size_t)align((void*)sizeof(t_block))
# define ALIGNED_CHUNK			(size_t)align((void*)sizeof(t_chunk))

// ALIGNED_DATA			= 48 bytes
// ALIGNED_HEAP			= 16 bytes
// ALIGNED_LARGE_HEAP	= 32 bytes
// ALIGNED_BLOCK		= 48 bytes
// ALIGNED_CHUNK		= 48 bytes 

# define TINY_S_MAX_ALLOC		(size_t)align((void*)((TINY_S - ALIGNED_BLOCK) / 100) - ALIGNED_CHUNK - ALIGNMENT)
# define SMALL_S_MAX_ALLOC		(size_t)align((void*)((SMALL_S - ALIGNED_BLOCK) / 100) - ALIGNED_CHUNK - ALIGNMENT)

// TINY_S_MAX_ALLOC		= 112 bytes
// SMALL_S_MAX_ALLOC	= 5148 bytes

typedef struct data
{
	struct	heap		*tiny_heap;
	struct	heap		*small_heap;
	struct	large_heap	*large_heap;
	void				*addr_return;
	bool				failed;
	size_t				total_size;
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
	struct heap			*heap;
	struct block		*prev;
	struct block		*next;
	struct chunk		*first_chunk;
	size_t				free_size;
	size_t				size_next;
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

//	free.c
void	free(void *ptr);
void    free_block_if_empty(t_block* block);

// realloc.c
void	*realloc(void *ptr, size_t size);

// allocation.c
void*	align(void *ptr_to_align);
void	heap_alloc(t_heap *heap, size_t heap_pagesize, size_t size);
void	large_alloc(t_large_heap *heap, size_t size);
void    chunk_alloc(t_block *block, size_t size, t_chunk *chunk_next);
bool	try_alloc_new_chunk_if_space_in_block(t_block *block, size_t size);
bool    try_alloc_new_chunk_if_space_after_chunk(t_block* block, t_chunk *chunk, size_t size);

//	init.c
int		data_init(t_data **data);
void	tiny_init(t_data **data);
void	small_init(t_data **data);

// utils/*.c
void			*align(void *ptr_to_align);
t_chunk			*find_address_heap(void *addr, t_block **parent_block);
t_large_heap    *find_address_large_heap(void *addr);

//	show_alloc_mem/*.c
void	show_alloc_mem();
void	show_alloc_debug();

#endif
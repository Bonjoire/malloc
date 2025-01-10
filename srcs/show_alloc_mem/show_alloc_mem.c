/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:35:53 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/06 18:41:00 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// TINY : 0xA0000
// 0xA0020 - 0xA004A : 42 bytes
// 0xA006A - 0xA00BE : 84 bytes
// SMALL : 0xAD000
// 0xAD020 - 0xADEAD : 3725 bytes
// LARGE : 0xB0000
// 0xB0020 - 0xBBEEF : 48847 bytes
// Total : 52698 bytes

static void show_tiny(size_t *total);
static void show_small(size_t *total);
static void show_large(size_t *total);
static void show_heap(t_heap *heap, size_t *total);
static void show_large_heap(t_large_heap *heap, size_t *total);

void show_alloc_mem()
{
    size_t total = 0;
    
    if (g_data == NULL)
        return ;
    
    ft_putstr_fd("| ===== SHOW ALLOC MEM =====\n|\n", 1);
    
    show_tiny(&total);
    show_small(&total);
    show_large(&total);
    
    ft_putstr_fd("| Total : ", 1);
    ft_putnbr_fd(total, 1);
    ft_putstr_fd(" bytes\n", 1);
	
	if (g_data->total_size != total) ////////////// DEBUG
		ft_printf("| ERROR : total_size != total, %T, %T\n", g_data->total_size, total); //////////////// DEBUG

	ft_putstr_fd("|\n", 1);
    ft_putstr_fd("| ==========================\n\n", 1);
}

static void show_tiny(size_t *total)
{
    ft_putstr_fd("| TINY : 0x", 1);
    ft_putnbr_base_fd((unsigned long)(g_data->tiny_heap->first_block), "0123456789ABCDEF", 1);
    ft_putstr_fd("\n", 1);

    show_heap(g_data->tiny_heap, total);
}

static void show_small(size_t *total)
{
    ft_putstr_fd("| SMALL : 0x", 1);
    ft_putnbr_base_fd((unsigned long)(g_data->small_heap->first_block), "0123456789ABCDEF",  1);
    ft_putstr_fd("\n", 1);

    show_heap(g_data->small_heap, total);
}

static void show_large(size_t *total)
{
    ft_putstr_fd("| LARGE : 0x", 1);
    ft_putnbr_base_fd((unsigned long)(g_data->large_heap), "0123456789ABCDEF", 1);
    ft_putstr_fd("\n", 1);


    show_large_heap(g_data->large_heap, total);
}

static void show_heap(t_heap *heap, size_t *total)
{
    t_block *block = heap->first_block;
    t_chunk *chunk = NULL;
    
    while (block)
    {
        if (block->first_chunk)
        {
            chunk = block->first_chunk;
            // t_chunk *chunk_bef = NULL;
            while (chunk)
            {
                ft_putstr_fd("| 0x", 1);
                ft_putnbr_base_fd((unsigned long)(chunk->chunk), "0123456789ABCDEF", 1);
                ft_putstr_fd(" - 0x", 1);
                ft_putnbr_base_fd((unsigned long)((size_t)align((void *)chunk->chunk + chunk->size)), "0123456789ABCDEF", 1);
                ft_putstr_fd(" : ", 1);
                ft_putnbr_fd(chunk->size, 1);
                ft_putstr_fd(" bytes\n", 1);
                *total += chunk->size;

                // if (chunk_bef)
                // {
                //     printf("diffout %Td\n", (size_t)((size_t)chunk->chunk - (size_t)align((void*)chunk_bef->chunk + chunk_bef->size)));
                //     printf("%p - %p\n", (void*)align((void *)chunk_bef->chunk + chunk_bef->size), (void*)chunk->chunk);
                // }
                // printf("diff in %zu\n", (unsigned long)((size_t)align((void *)chunk->chunk + chunk->size) - (unsigned long)(chunk->chunk)));
                // printf("%p - %p\n", (void*)align((void *)chunk->chunk + chunk->size, (void*)chunk->chunk));
                // chunk_bef = chunk;
                
                // if (chunk == chunk->next) ////////////////////
				//     break ;
                chunk = chunk->next;
            }
        }
        block = block->next;
    }
    ft_putstr_fd("|\n", 1);
}

static void show_large_heap(t_large_heap *heap, size_t *total)
{
    t_large_heap* large_heap = heap;

    while (large_heap)
    {
        ft_putstr_fd("| 0x", 1);
        ft_putnbr_base_fd((unsigned long)(large_heap->start), "0123456789ABCDEF", 1);
        ft_putstr_fd(" - 0x", 1);
        ft_putnbr_base_fd((unsigned long)((size_t)align((void *)large_heap->start + large_heap->size)), "0123456789ABCDEF", 1);
        ft_putstr_fd(" : ", 1);
        ft_putnbr_fd(large_heap->size, 1);
        ft_putstr_fd(" bytes\n", 1);
        
        *total += large_heap->size;
        large_heap = large_heap->next;
    }
}
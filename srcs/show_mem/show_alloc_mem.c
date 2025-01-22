/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:35:53 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/13 14:28:26 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	show_tiny(size_t *total);
static void	show_small(size_t *total);
static void	show_large(size_t *total);
static void	show_heap(t_heap *heap, size_t *total);
static void	show_large_heap(t_large_heap *heap, size_t *total);

void	show_alloc_mem()
{
    size_t total = 0;
    
    if (g_data == NULL)
	{
		ft_putstr_fd("show_alloc_mem : No memory allocated\n", 1);
        return ;
	}
    
    ft_putstr_fd("\n======== SHOW ALLOC MEM ========\n|\n", 1);
    
    show_tiny(&total);
    show_small(&total);
    show_large(&total);
    
    ft_putstr_fd("|\n| Total : ", 1);
    ft_putnbr_fd(total, 1);
    ft_putstr_fd(" bytes\n", 1);

    if (g_data->total_size != total) // Should never happen
    {
        ft_putstr_fd("| ERROR : Total size is not correct\n", 1);
        ft_putstr_fd("| g_data->total_size : ", 1);
        ft_putnbr_fd(g_data->total_size, 1);
        ft_putstr_fd(" bytes\n", 1);
    }

	ft_putstr_fd("|\n", 1);
    ft_putstr_fd("================================\n\n", 1);
}

static void	show_tiny(size_t *total)
{
    ft_putstr_fd("| TINY : 0x", 1);
    ft_putnbr_base_fd((unsigned long)(g_data->tiny_heap->first_block), "0123456789ABCDEF", 1);
    ft_putstr_fd("\n", 1);

    show_heap(g_data->tiny_heap, total);
}

static void	show_small(size_t *total)
{
    ft_putstr_fd("| SMALL : 0x", 1);
    ft_putnbr_base_fd((unsigned long)(g_data->small_heap->first_block), "0123456789ABCDEF",  1);
    ft_putstr_fd("\n", 1);

    show_heap(g_data->small_heap, total);
}

static void	show_large(size_t *total)
{
    ft_putstr_fd("| LARGE : 0x", 1);
    ft_putnbr_base_fd((unsigned long)(g_data->large_heap), "0123456789ABCDEF", 1);
    ft_putstr_fd("\n", 1);

    show_large_heap(g_data->large_heap, total);
}

static void	show_heap(t_heap *heap, size_t *total)
{
    t_block *block = heap->first_block;
    t_chunk *chunk = NULL;
    
    while (block)
    {
        if (block->first_chunk)
        {
            chunk = block->first_chunk;
			ft_putstr_fd("|   Block : 0x", 1);
			ft_putnbr_base_fd((unsigned long)(block), "0123456789ABCDEF", 1);
			ft_putstr_fd("\n", 1);
			
            while (chunk)
            {
                ft_putstr_fd("|     0x", 1);
                ft_putnbr_base_fd((unsigned long)(chunk->chunk), "0123456789ABCDEF", 1);
                ft_putstr_fd(" - 0x", 1);
                ft_putnbr_base_fd((unsigned long)((size_t)align((void *)chunk->chunk + chunk->size)), "0123456789ABCDEF", 1);
                ft_putstr_fd(" : ", 1);
                ft_putnbr_fd(chunk->size, 1);
                ft_putstr_fd(" bytes\n", 1);

                *total += chunk->size;
                chunk = chunk->next;
            }
        }
        block = block->next;
    }
    ft_putstr_fd("|\n", 1);
}

static void	show_large_heap(t_large_heap *heap, size_t *total)
{
    t_large_heap*	large_heap = heap;

    while (large_heap)
    {
        ft_putstr_fd("|     0x", 1);
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

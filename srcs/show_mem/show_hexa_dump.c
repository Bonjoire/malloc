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

void print_memory_hexa(void *addr, size_t size)
{
    unsigned char *mem = (unsigned char *)addr;
    size_t i, j;

    for (i = 0; i < size; i += 16)
    {
        // ft_printf("i = %T\n", i);

        // Show the address
        ft_putnbr_base_fd((size_t)(mem + i), "0123456789ABCDEF", 1);
        ft_putstr_fd("  ", 1);

        // Show the hexa
        for (j = 0; j < 16 && i + j < size; j++)
        {
            ft_putnbr_base_fd(mem[i + j], "0123456789ABCDEF", 1);
            if (!mem[i + j] || mem[i + j] < 16)
                ft_putchar_fd('0', 1);
            ft_putchar_fd(' ', 1);
            if (j == 7)
                ft_putchar_fd(' ', 1);
        }
        for (; j < 16; j++)
        {
            if (j == 7)
                ft_putchar_fd(' ', 1);
            ft_putstr_fd("   ", 1);
        }

        // Show the ascii
        ft_putstr_fd(" |", 1);
        for (j = 0; j < 16 && i + j < size; j++)
        {
            char c = mem[i + j];
            ft_printf("%c %T, %T\n",c , i ,j);
            ft_putchar_fd(((c >= 32 && c < 127) ? c : '.'), 1);
        }
        ft_putchar_fd('|', 1);
        ft_putchar_fd('\n', 1);
    }
}

static void show_heap(t_heap *heap)
{
    t_block *block;
    t_chunk *chunk;

    if (!heap)
        return;
    block = heap->first_block;
    while (block)
    {
        chunk = block->first_chunk;
        while (chunk)
        {
            print_memory_hexa((void *)(chunk), ALIGNED_CHUNK + chunk->size);
            chunk = chunk->next;
            if (chunk)
                ft_putstr_fd("*\n", 1);
        }
        block = block->next;
        if (block)
            ft_putstr_fd("*\n", 1);
    }
    ft_putstr_fd("*\n", 1);
}

static void show_large(t_large_heap *large)
{
    while (large)
    {
        print_memory_hexa(large->start, large->size);
        large = large->next;
    }
}

void show_hexa_dump(void)
{
    if (!g_data)
    {
        ft_putstr_fd("show_hexa_dump : No memory allocated\n", 1);
        return ;
    }

    ft_putstr_fd("\n================================= SHOW HEXA DUMP =================================\n*\n", 1);

    show_heap(g_data->tiny_heap);
    show_heap(g_data->small_heap);
    show_large(g_data->large_heap);

    ft_putstr_fd("==================================================================================\n\n", 1);

}
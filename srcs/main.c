/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:26:59 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/03 18:16:38 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main()
{
    char *str = (char *)malloc(279);
    char *str1 = (char *)malloc(279);
    int *str2 = (int *)malloc(280);
    int *str3 = (int *)malloc(280);

    char *str4 = (char *)malloc(10437);
    char *str5 = (char *)malloc(10438);
    char *str6 = (char *)malloc(20000);

    ft_printf("\n==================== MAIN ====================\n\n");

    str[0] = 'a';
    str[1] = 'b';
    str[2] = 'c';
    str[3] = 'd';
    str[3] = '\0';

    ft_printf("str  = %p, '%s'\n", str, str);
    ft_printf("str1 = %p, '%s'\n", str1, str1);
    ft_printf("str2 = %p\n", str2);
    ft_printf("str3 = %p\n", str3);
    ft_printf("str4  = %p, '%s'\n", str4, str4);
    ft_printf("str5 = %p, '%s'\n", str5, str5);
    ft_printf("str6  = %p, '%s'\n", str6, str6);

    // struct rlimit limit;
    // if (getrlimit(RLIMIT_AS, &limit) == -1)
    //     return (1);
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

    ft_printf("align 32 = %d\n", (int)((size_t)align((void*)32)));
    
    ft_printf("\n================== SHOW DEBUG ================\n\n");
    show_alloc_debug();
    
    ft_printf("\n===================== SHOW ===================\n\n");
    show_alloc_mem();
}
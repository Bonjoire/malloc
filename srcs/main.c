/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:26:59 by hubourge          #+#    #+#             */
/*   Updated: 2024/12/30 18:35:34 by hubourge         ###   ########.fr       */
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

    printf("\n==================== MAIN ====================\n\n");

    // str1[0] = 'a';
    // str[1] = 'b';
    // str[2] = 'c';
    // str[3] = 'd';
    // str[3] = '\0';

    printf("str  = %p, '%s'\n", str, str);
    printf("str1 = %p, '%s'\n", str1, str1);
    printf("str2 = %p\n", str2);
    printf("str3 = %p\n", str3);
    printf("str4  = %p, '%s'\n", str4, str4);
    printf("str5 = %p, '%s'\n", str5, str5);
    printf("str6  = %p, '%s'\n", str6, str6);

    // struct rlimit limit;
    // if (getrlimit(RLIMIT_AS, &limit) == -1)
    //     return (1);
    printf("PAGESIZE = %zu\n", PAGESIZE);
    printf("TINY_S = %zu\n", TINY_S);
    printf("SMALL_S = %zu\n", SMALL_S);
    // printf("TINY_S_MAX_ALLOC = %zu\n", TINY_S_MAX_ALLOC);
    // printf("SMALL_S_MAX_ALLOC = %zu\n", SMALL_S_MAX_ALLOC);
    
    printf("ALIGNED_DATA = %zu\n", ALIGNED_DATA);
    printf("ALIGNED_HEAP = %zu\n", ALIGNED_HEAP);
    printf("ALIGNED_LARGE_HEAP = %zu\n", ALIGNED_LARGE_HEAP);
    printf("ALIGNED_BLOCK = %zu\n", ALIGNED_BLOCK);
    printf("ALIGNED_CHUNK = %zu\n", ALIGNED_CHUNK);

    printf("align 32 = %zu\n", (size_t)align((void*)32));
    
    printf("\n================== SHOW DEBUG ================\n\n");
    show_alloc_debug();
    
    printf("\n===================== SHOW ===================\n\n");
    show_alloc_mem();
}
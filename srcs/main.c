/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:26:59 by hubourge          #+#    #+#             */
/*   Updated: 2024/12/26 22:43:41 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main()
{
    char *str = (char *)malloc(434);
    char *str1 = (char *)malloc(10000);
    int *str2 = (int *)malloc(1000);
    int *str3 = (int *)malloc(304);

    (void)str;
    (void)str1;
    (void)str2;
    (void)str3;

    printf("\n==================== MAIN ====================\n\n");

    printf("str  = %p, %s\n", str, str);
    printf("str1 = %p, %s\n", str1, str1);
    printf("str2 = %p\n", str2);
    printf("str3 = %p\n", str3);


    // struct rlimit limit;
    // if (getrlimit(RLIMIT_AS, &limit) == -1)
    //     return (1);
    // printf("PAGESIZE = %d\n", PAGESIZE);
    // printf("TINY_S = %d\n", TINY_S);
    // printf("SMALL_S = %d\n", SMALL_S);
    // printf("TINY_S_MAX_ALLOC = %zu\n", TINY_S_MAX_ALLOC);
    // printf("SMALL_S_MAX_ALLOC = %zu\n", SMALL_S_MAX_ALLOC);
    printf("ALIGNED_DATA = %zu\n", ALIGNED_DATA);
    printf("ALIGNED_HEAP = %zu\n", ALIGNED_HEAP);
    printf("ALIGNED_LARGE_HEAP = %zu\n", ALIGNED_LARGE_HEAP);
    printf("ALIGNED_BLOCK = %zu\n", ALIGNED_BLOCK);
    printf("ALIGNED_CHUNK = %zu\n", ALIGNED_CHUNK);
    
    printf("\n===================== SHOW ===================\n\n");
    show_alloc_debug();
    printf("\n==================== DEBUG ===================\n\n");
    show_alloc_mem();

    printf("diff addr = %lu\n", (void*)0xA00BE - (void*)0xA006A);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:26:59 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/23 15:14:43 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	malloc_test();

int main()
{   
    ft_printf("\n==================== TEST ====================\n\n");
	malloc_test();
}

void	malloc_test()
{
	int error = 0;

	test_tiny(&error, DO_FREE_AFTER_MALLOC);
	test_small(&error, DO_FREE_AFTER_MALLOC);
	test_large(&error, DO_FREE_AFTER_MALLOC);
	test_free(&error);
	test_realloc();
	test_thread();
	// test_hexa_dump(DO_FREE_AFTER_MALLOC);

	ft_printf("\n--> TEST : TOTAL ERROR : %d\n", error);
    show_alloc_debug();
    show_alloc_mem();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hexa_dump.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:12:26 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/22 17:23:57 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	test_hexa_dump(int to_free)
{
    ft_printf("--> TEST : show_hexa_dump\n");

    char *ptr1 = malloc(5 + 1);
    if(ptr1)
	    ft_strlcpy(ptr1, "12345", 5 + 1);
		
	char *ptr2 = malloc(40);
	if(ptr2)
		ft_strlcpy(ptr2, "H_E_X__D_U_M_P_? FOR SURE ?", 27 + 1);

    char *ptr3 = malloc(183 + 1);
    if(ptr3)
        ft_strlcpy(ptr3, "In computing, a hex dump is a textual hexadecimal view (on screen or paper)\
of (often, but not necessarily binary) computer data, from memory or from a computer file or storage device", 183 + 1);

	char *ptr4 = malloc(5208);
	if(ptr4)
	{
		for(int i = 0; i < 5207; i += 41)
			ft_strlcpy(&ptr4[i], "This is a test for a big chunk of memory!", 41 + 1);
	}

    show_hexa_dump();

	if (to_free)
	{
		free(ptr1);
		free(ptr2);
		free(ptr3);
		free(ptr4);
	}
}

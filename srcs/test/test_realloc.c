/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:12:13 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/22 15:12:19 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	test_realloc()
{
	ft_printf("--> TEST : realloc\n");

	// Realloc input
	{
		// Simple free
		char *str1 = malloc(5 * sizeof(char));
		str1 = realloc(str1, 0);

		// Simple malloc
		char *str2 = realloc(NULL, 0);
		(void)str2;

		// Simple malloc
		char *str3 = realloc(NULL, 128);
		(void)str3;

		free(str2);
		free(str3);
	}
	// Realloc to a smaller size
	{
		char *str1 = malloc(128 * sizeof(char));
		char *str2 = malloc(2500 * sizeof(char));
		char *str3 = malloc(128 * sizeof(char));
		(void)str1;
		(void)str2;
		(void)str3;

		str1 = realloc(str1, 64 * sizeof(char));
		str2 = realloc(str2, 1000 * sizeof(char));
		str3 = realloc(str3, 64 * sizeof(char));

		free(str1);
		free(str2);
		free(str3);
	}
	// Realloc to a bigger size
	{
		char *str1 = malloc(128 * sizeof(char));
		char *str2 = malloc(2500 * sizeof(char));
		char *str3 = malloc(128 * sizeof(char));
		(void)str1;
		(void)str2;
		(void)str3;

		str1 = realloc(str1, 128 + 100 * sizeof(char));
		str2 = realloc(str2, 2500 + 100 * sizeof(char));
		str3 = realloc(str3, 128 + 100 * sizeof(char));

		free(str1);
		free(str2);
		free(str3);
	}
	// Realloc same size
	{
		char *str1 = malloc(5 * sizeof(char));
		ft_strlcpy(str1, "Hello", ft_strlen("Hello") + 1);

		str1 = realloc(str1, ft_strlen(str1) * sizeof(char));

		free(str1);
	}

	// Realloc in large heap
	{
		char *str1 = malloc(10000 * sizeof(char));
		char *str2 = malloc(10000 * sizeof(char));
		char *str3 = malloc(10000 * sizeof(char));
		(void)str1;
		(void)str2;
		(void)str3;

		str1 = realloc(str1, 10000 * sizeof(char));
		str2 = realloc(str2, 20000 * sizeof(char));
		str3 = realloc(str3, 6000 * sizeof(char));

		free(str1);
		free(str2);
		free(str3);
	}
}

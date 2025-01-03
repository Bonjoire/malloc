/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:43:34 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/03 15:34:57 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_check_int(long n, int cpt)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (cpt + 11);
	}
	else if (n == 2147483647)
	{
		write(1, "2147483647", 10);
		return (cpt + 10);
	}
	return (cpt);
}

int	ft_printf_check(long n, int cpt)
{
	cpt = ft_printf_check_int(n, cpt);
	return (cpt);
}

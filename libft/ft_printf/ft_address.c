/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_address.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:05:55 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/03 15:34:42 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_putnbr_adr_base(unsigned long n, char *base, unsigned int len, int cpt)
{
	char	c;

	c = base[n % len];
	if ((n / len) > 0)
		cpt = ft_printf_putnbr_adr_base(n / len, base, len, cpt);
	cpt += ft_printf_putchar_fd(c, 1);
	return (cpt);
}

int	ft_printf_address(unsigned long ptr, int cpt)
{
	char	*base;

	if (ptr == 0)
		return (ft_printf_putstr_fd("(nil)", 1) + cpt);
	base = "0123456789abcdef";
	cpt += ft_printf_putstr_fd("0x", 1);
	return (ft_printf_putnbr_adr_base(ptr, base, ft_printf_strlen(base), cpt));
}

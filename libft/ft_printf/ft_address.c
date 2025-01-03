/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_address.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:05:55 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/03 19:28:15 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_putnbr_adr(unsigned long n, char *base, unsigned int len, int cpt)
{
	char	c;

	c = base[n % len];
	if ((n / len) > 0)
		cpt = ft_pf_putnbr_adr(n / len, base, len, cpt);
	cpt += ft_pf_putchar_fd(c, 1);
	return (cpt);
}

int	ft_pf_address(unsigned long ptr, int cpt)
{
	char	*base;

	if (ptr == 0)
		return (ft_pf_putstr_fd("(nil)", 1) + cpt);
	base = "0123456789abcdef";
	cpt += ft_pf_putstr_fd("0x", 1);
	return (ft_pf_putnbr_adr(ptr, base, ft_pf_strlen(base), cpt));
}

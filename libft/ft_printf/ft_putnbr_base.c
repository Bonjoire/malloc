/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:43:34 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/03 15:35:48 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_putnbr_base(int nbr, char *base, unsigned int len, int cpt)
{
	char	c;

	c = base[nbr % len];
	if ((nbr / len) > 0)
		cpt = ft_printf_putnbr_adr_base(nbr / len, base, len, cpt);
	cpt += ft_printf_putchar_fd(c, 1);
	return (cpt);
}

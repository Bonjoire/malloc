/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:27:32 by hubourge          #+#    #+#             */
/*   Updated: 2024/12/25 19:37:43 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_base_fd(unsigned long int nbr, char *base, int fd)
{
	char	c;
    int		len;

    len = 0;
    while (base && base[len])
        len++;

	c = base[nbr % len];
	if ((nbr / len) > 0)
		ft_putnbr_base_fd(nbr / len, base, fd);
	ft_putchar_fd(c, fd);
}
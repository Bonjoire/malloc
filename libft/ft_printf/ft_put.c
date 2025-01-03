/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:21:56 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/03 19:29:37 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_pf_putstr_fd(char *s, int fd)
{
	if (s == NULL)
	{
		write (fd, "(null)", 6);
		return (6);
	}
	if (s != NULL && fd != 0)
		write (fd, s, ft_pf_strlen(s));
	return (ft_pf_strlen(s));
}

int	ft_pf_putnbr_fd(long long int n, int fd, int cpt)
{
	int	tmp;

	tmp = ft_pf_check(n, cpt);
	if (cpt != tmp)
		return (tmp);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(1, "-2147483648", 11);
			return (cpt + 11);
		}
		write(fd, "-", 1);
		n *= -1;
		cpt++;
	}
	if (n < 10)
		cpt += ft_pf_putchar_fd(n + '0', fd);
	else
	{
		cpt = ft_pf_putnbr_fd(n / 10, fd, cpt);
		cpt += ft_pf_putchar_fd(n % 10 + '0', fd);
	}
	return (cpt);
}

int	ft_pf_putnbr_st_fd(size_t n, int fd, int cpt)
{
	if (n < 10)
		cpt += ft_pf_putchar_fd(n + '0', fd);
	else
	{
		cpt = ft_pf_putnbr_st_fd(n / 10, fd, cpt);
		cpt += ft_pf_putchar_fd(n % 10 + '0', fd);
	}
	return (cpt);
}

int	ft_pf_putnbr_uns_fd(unsigned int n, int fd, int cpt)
{
	if (n < 10)
		cpt += ft_pf_putchar_fd(n + '0', fd);
	else
	{
		cpt = ft_pf_putnbr_fd(n / 10, fd, cpt);
		cpt += ft_pf_putchar_fd(n % 10 + '0', fd);
	}
	return (cpt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:27:47 by hubourge          #+#    #+#             */
/*   Updated: 2023/12/07 20:06:22 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	nbr_len(int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		i++;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static char	*ft_putitoa(char *str, int sign, int n, int i)
{
	str[i] = '\0';
	while (--i >= 0)
	{
		if (i == 0 && sign)
			break ;
		str[i] = n % 10 + 48;
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		sign;

	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648");
		return (str);
	}
	i = nbr_len(n);
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (0);
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= -1;
		str[0] = '-';
	}
	str = ft_putitoa(str, sign, n, i);
	return (str);
}

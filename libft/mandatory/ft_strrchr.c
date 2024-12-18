/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:47:46 by hubourge          #+#    #+#             */
/*   Updated: 2024/12/09 20:11:30 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = -1;
	while (s[i])
	{
		if (s[i] == (char)c)
			tmp = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	if (tmp != -1)
		return ((char *)(s + tmp));
	return (NULL);
}

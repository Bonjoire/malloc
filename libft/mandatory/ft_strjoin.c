/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:20:53 by hubourge          #+#    #+#             */
/*   Updated: 2023/12/07 20:08:26 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		lens1;
	int		lens2;

	if (s1 == NULL || s2 == NULL)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	dest = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (dest == NULL)
		return (0);
	ft_strlcpy(dest, s1, lens1 + 1);
	ft_strlcat(dest, s2, lens1 + lens2 + 1);
	return (dest);
}

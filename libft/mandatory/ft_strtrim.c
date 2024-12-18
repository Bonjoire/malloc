/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:58:29 by hubourge          #+#    #+#             */
/*   Updated: 2023/12/07 20:08:55 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	verif(char c, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*str;
	int		start;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && verif(s1[start], set))
		start++;
	if (!s1[start])
		return (ft_calloc(1, 1));
	i = ft_strlen(s1) - 1;
	while (i > 0 && verif(s1[i], set))
		i--;
	str = ft_calloc((i - start) + 2, sizeof(char));
	if (str == NULL)
		return (NULL);
	j = 0;
	while (s1[j] && j <= i - start)
	{
		str[j] = s1[start + j];
		j++;
	}
	return (str);
}

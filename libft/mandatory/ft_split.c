/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:01:48 by hubourge          #+#    #+#             */
/*   Updated: 2023/12/07 20:06:56 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static int	len_word_malloc(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static void	ft_freetab(char **s)
{
	int		i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return ;
}

static char	**ft_split_in_tab(char const *str, char c, char **tab)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	while (++k < count_words(str, c))
	{
		j = 0;
		while (str[i] && str[i] == c)
			i++;
		tab[k] = malloc(sizeof(char) * (len_word_malloc(&str[i], c) + 1));
		if (tab[k] == NULL)
		{
			ft_freetab(tab);
			return (NULL);
		}
		while (str[i] && str[i] != c)
			tab[k][j++] = str[i++];
		tab[k][j] = '\0';
	}
	tab[k] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	if (s == NULL)
	{
		tab = malloc(sizeof(char *));
		tab[0] = NULL;
		return (tab);
	}
	i = 0;
	tab = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	if (s[i] == 0)
	{
		tab[0] = NULL;
		return (tab);
	}
	tab = ft_split_in_tab(s, c, tab);
	return (tab);
}

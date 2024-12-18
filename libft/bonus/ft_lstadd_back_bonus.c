/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:40:19 by hubourge          #+#    #+#             */
/*   Updated: 2023/12/07 20:04:18 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*buffer;

	if (!new || !lst)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	buffer = *lst;
	buffer = (ft_lstlast(buffer));
	buffer->next = new;
}

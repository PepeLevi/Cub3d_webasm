/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:29:20 by cestevez          #+#    #+#             */
/*   Updated: 2023/01/09 14:29:26 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*save_next;

	if (lst == 0 || del == 0)
		return ;
	while (*lst)
	{
		save_next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = save_next;
	}
}
/*line23: save the pointer to the next element before deleting it
to be able to access*/
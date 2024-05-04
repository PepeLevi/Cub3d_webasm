/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:30:02 by cestevez          #+#    #+#             */
/*   Updated: 2023/01/09 17:49:42 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;

	new_lst = 0;
	if (lst == 0 || f == 0 || del == 0)
		return (0);
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (new_node == 0)
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		lst = lst->next;
		ft_lstadd_back(&new_lst, new_node);
	}
	return (new_lst);
}
/*line23: create a node for the new lst that is = to the 1st node of
the given lst after having the given func applied to it
line25: if the funct returned an empty node, delete it and break??*/
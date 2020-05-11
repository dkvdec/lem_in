/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:23:59 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/30 15:23:11 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_lstmapdel(t_list *current)
{
	t_list *next;

	while (current)
	{
		next = current->next;
		if (current->content)
		{
			free(current->content);
			current->content = NULL;
		}
		free(current);
		current = NULL;
		current = next;
	}
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*p_lst;
	t_list	*begin;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	p_lst = f(lst);
	if (!(new = ft_lstnew(p_lst->content, p_lst->content_size)))
		return (NULL);
	begin = new;
	lst = lst->next;
	while (lst)
	{
		p_lst = f(lst);
		if (!(new->next = ft_lstnew(p_lst->content, p_lst->content_size)))
		{
			ft_lstmapdel(begin);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (begin);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 21:09:41 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:14:00 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *p_next;

	if (alst && del)
	{
		while ((*alst) != NULL)
		{
			p_next = (*alst)->next;
			ft_lstdelone(alst, del);
			*alst = p_next;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 21:09:41 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/23 21:09:44 by dheredat         ###   ########.fr       */
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

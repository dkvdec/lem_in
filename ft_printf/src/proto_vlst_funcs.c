/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_vlst_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:13:21 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 17:17:11 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

t_vlst			*vlst_new(int nbr)
{
	t_vlst *newlst;

	if (!(newlst = (t_vlst*)malloc(sizeof(t_vlst))))
		return (NULL);
	newlst->nbr = nbr;
	newlst->type = 0;
	newlst->value = NULL;
	newlst->next = NULL;
	newlst->prev = NULL;
	return (newlst);
}

t_vlst			*vlst_make(int nbr)
{
	int		i;
	t_vlst	*strt;
	t_vlst	*prev;
	t_vlst	*curr;

	i = 1;
	curr = vlst_new(i);
	prev = NULL;
	strt = curr;
	while (++i <= nbr)
	{
		curr->next = vlst_new(i);
		prev = curr;
		curr = curr->next;
		curr->prev = prev;
	}
	return (strt);
}

void			vlst_walk(int nbr)
{
	int dif;

	if (!t_connect.current)
		return ;
	if (nbr == t_connect.current->nbr)
		return ;
	dif = nbr - t_connect.current->nbr;
	while (dif < 0 && t_connect.current->prev != NULL)
	{
		t_connect.current = t_connect.current->prev;
		dif++;
	}
	while (dif > 0 && t_connect.current->next != NULL)
	{
		t_connect.current = t_connect.current->next;
		dif--;
	}
}

void			vlst_starbucks(int nbr)
{
	t_vlst	*savepos;

	savepos = t_connect.current;
	vlst_walk(nbr);
	t_connect.current->type = 1;
	t_connect.current = savepos;
}

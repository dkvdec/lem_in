/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_coll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 07:38:16 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 07:39:40 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_link		*way_next_coll_entr_frcd(t_room *room)
{
	t_link	*link;
	t_link	*next;
	int		min;

	link = room->links;
	next = NULL;
	min = 2147483647;
	while (link)
	{
		if (link->room->home->mark == room->mark
		&& link->room->home->status > 0
		&& link->status == 1 && link->room->status == 1
		&& link->room->home->price < min)
		{
			min = link->room->home->price;
			next = link;
		}
		link = link->next;
	}
	t_col.col_flg++;
	t_col.col_stp++;
	return (next);
}

t_link		*way_next_coll_entr(t_room *room)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->room->home->mark == room->mark
		&& link->room->home->status > 0
		&& link->status == 1 && link->room->status == 1
		&& link->room->home->price == room->price - 1)
			next = link;
		link = link->next;
	}
	if (next == NULL)
		next = way_next_coll_entr_frcd(room);
	else
	{
		t_col.col_flg++;
		t_col.col_stp++;
	}
	return (next);
}

t_link		*way_next_coll_cont(t_room *room)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->room->home->mark == room->mark
		&& link->room->home->status == room->status
		&& link->status == 0 && link->room->status == -1)
			next = link;
		link = link->next;
	}
	t_col.col_stp++;
	return (next);
}

t_link		*way_next_coll_escp(t_room *room)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->room->home->mark == room->mark
		&& link->room->home->status == 0
		&& link->status == 1 && link->room->status == 1
		&& link->room->home->price <= room->price - 1)
			next = link;
		link = link->next;
	}
	if (next == NULL)
		next = way_next_coll_cont(room);
	else
		t_col.col_stp = 0;
	return (next);
}

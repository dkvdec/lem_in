/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 16:38:51 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/25 08:20:34 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_link	*next_room_coll_frcd_entr(t_room *room)
{
	t_link	*link;
	t_link	*next;
	int		min;

	min = 2147483647;
	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 1
		&& link->room->home->status > 0
		&& link->room->home->price < min)
		{
			min = link->room->home->price;
			next = link;
		}
		link = link->next;
	}
	if (next == NULL)
		error_func("Build Path Error! Forced collision enter failed.");
	t_col.col_flg++;
	t_col.col_stp++;
	t_col.col_sts = next->room->home->status;
	return (next);
}

t_link	*next_room_coll_entr(t_room *room)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 1
		&& link->room->home->status > 0
		&& link->room->home->price == room->price - 1)
			next = link;
		link = link->next;
	}
	if (next == NULL)
		next = next_room_coll_frcd_entr(room);
	else
	{
		t_col.col_flg++;
		t_col.col_stp++;
		t_col.col_sts = next->room->home->status;
	}
	return (next);
}

t_link	*next_room_norm_case(t_room *room)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 1
		&& link->room->home->status == 0
		&& link->room->home->price == room->price - 1)
			next = link;
		link = link->next;
	}
	if (next == NULL && room->room_nbr == t_map.end->room_nbr)
		error_func("Build Path Error! Can't escape end_room.");
	else if (next == NULL)
		next = next_room_coll_entr(room);
	return (next);
}

t_link	*next_room_coll_fllw_frcd(t_room *room)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 0
		&& link->room->status == -1
		&& link->room->home->status == t_col.col_sts)
			next = link;
		link = link->next;
	}
	if (next == NULL)
		error_func("Build Path Error! Forced collision follow failed.");
	t_col.col_stp++;
	return (next);
}

t_link	*next_room_coll_fllw(t_room *room)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 0
		&& link->room->status == -1
		&& link->room->home->status == t_col.col_sts
		&& link->room->home->price == room->price + 1)
			next = link;
		link = link->next;
	}
	if (next == NULL)
		next = next_room_coll_fllw_frcd(room);
	else
		t_col.col_stp++;
	return (next);
}

t_link	*next_room_coll_escp(t_room *room)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 1
		&& link->room->home->status == 0
		&& link->room->home->price <= room->price)
			next = link;
		link = link->next;
	}
	if (next == NULL)
		next = next_room_coll_fllw(room);
	else
	{
		t_col.col_sts = 0;
		t_col.col_stp = 0;
	}
	return (next);
}


t_link	*next_room_decider(t_room *room)
{
	t_link	*next;

	if (t_col.col_stp == 0)
		next = next_room_norm_case(room);
	else if (t_col.col_stp == 1)
		next = next_room_coll_fllw(room);
	else
		next = next_room_coll_escp(room);
	return (next);
}

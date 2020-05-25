/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 13:20:31 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 00:48:29 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_link  *way_first_room(t_room *room)
{
	t_link  *link;
	t_link  *next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 1
		&& link->room->status == 1
		&& link->room->home->status == 0
		&& link->room->home->mark == room->mark
		&& link->room->home->price < room->price)
		{
			if (next != NULL)
				error_func("Double link at way_first_room.");
			next = link;
		}
		link = link->next;

	}
	return (next);
}

t_link  *way_next_coll_entr_frcd(t_room *room)
{
	t_link  *link;
	t_link  *next;
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

t_link  *way_next_coll_entr(t_room *room)
{
	t_link  *link;
	t_link  *next;

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

t_link  *way_next_norm(t_room *room)
{
	t_link  *link;
	t_link  *next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->room->home->mark == room->mark
		&& link->room->home->status == 0
		&& link->status == 1 && link->room->status == 1
		&& link->room->home->price == room->price - 1)
			next = link;
		link = link->next;
	}
	if (next == NULL)
		next = way_next_coll_entr(room);
	return (next);
}

t_link  *way_next_coll_cont(t_room *room)
{
	t_link  *link;
	t_link  *next;

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

t_link  *way_next_coll_escp(t_room *room)
{
	t_link  *link;
	t_link  *next;

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

t_link  *way_next_room(t_room *room)
{
	t_link  *next;

	next = NULL;
	if (t_col.col_stp == 0)
		next = way_next_norm(room);
	else if (t_col.col_stp == 1)
		next = way_next_coll_cont(room);
	else
		next = way_next_coll_escp(room);
	return (next);
}

t_w		*make_new_coll_path(t_w** end, t_wh* home)
{
	t_room* room;
	t_link* link;
	t_w*	curr;

	curr = make_w(t_map.end, NULL, home);
	*(end) = curr;
	link = way_first_room(t_map.end);
	link->status = 0;
	link->room->status = 0;
	while(link->room->home->room_nbr != t_map.start->room_nbr)
	{
		room = link->room->home;
		curr->prev = make_w(room, curr, home);
		curr = curr->prev;
		if (room->status == 0)
			room->status = home->way_nbr;
		link = way_next_room(room);
		link->status = 0;
		link->room->status = 0;
	}
	link->status = 0;
	link->room->status = 0;
	return (curr);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 02:17:47 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 09:06:17 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		map_reset(void)
{
	t_room	*room;

	room = t_map.rooms;
	t_map.mark_sts = 0;
	t_map.coll_lvl = 0;
	while (room)
	{
		room->mark = 0;
		room->price = 2147483647;
		room = room->next;
	}
}

void		full_map_reset(void)
{
	t_room	*room;
	t_link	*link;

	room = t_map.rooms;
	t_map.coll_lvl = 0;
	t_map.mark_sts = 0;
	while (room)
	{
		room->status = 0;
		room->mark = 0;
		room->price = 2147483647;
		link = room->links;
		while (link)
		{
			link->status = 1;
			link = link->next;
		}
		room = room->next;
	}
}

void		full_reset(void)
{
	t_valid.ants_flag = 0;
	t_valid.room_flag = 0;
	t_valid.start_flag = 0;
	t_valid.end_flag = 0;
	t_valid.room_counter = 0;
	t_valid.link_counter = 0;
	t_map.ants_nbr = 0;
	t_map.mark_sts = 0;
	t_map.coll_lvl = 0;
	t_map.rooms = NULL;
	t_map.start = NULL;
	t_map.end = NULL;
}

void		find_reset_link(t_room *prev, t_room *curr, int p_nbr, int c_nbr)
{
	t_link	*link;

	link = prev->links;
	while (link && link->room->home->room_nbr != curr->room_nbr)
		link = link->next;
	link->status = p_nbr;
	link->room->status = c_nbr;
}

void		map_reclaim(t_ws *wcs)
{
	t_w		*curr;
	t_wh	*head;

	head = wcs->ways;
	while (head)
	{
		if (head->end->prev)
		{
			curr = head->end->prev;
			curr->room->status = curr->home->way_nbr;
			find_reset_link(t_map.end, curr->room, 0, 0);
			while (curr->prev)
			{
				curr->room->status = curr->home->way_nbr;
				find_reset_link(curr->room, curr->prev->room, -1, 0);
				curr = curr->prev;
			}
			curr->room->status = curr->home->way_nbr;
			find_reset_link(curr->room, t_map.start, 0, 0);
		}
		else
			find_reset_link(t_map.end, t_map.start, 0, 0);
		head = head->next;
	}
}

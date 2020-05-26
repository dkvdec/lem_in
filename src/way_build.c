/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 20:24:54 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 04:52:23 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_w			*make_w(t_room *room, t_w *next, t_wh *home)
{
	t_w		*curr;

	if (!(curr = (t_w*)malloc(sizeof(t_w))))
		error_func("Malloc Error!");
	curr->home = home;
	curr->room = room;
	curr->ant_nbr = 0;
	curr->prev = NULL;
	curr->next = next;
	return (curr);
}

t_wh		*make_wh(int way_nbr, t_wh *orig)
{
	t_wh	*curr;

	if (!(curr = (t_wh*)malloc(sizeof(t_wh))))
		error_func("Malloc Error!");
	if (orig == NULL)
	{
		curr->way_nbr = way_nbr;
		curr->way_len = 0;
		curr->ants_in_rooms = 0;
	}
	else
	{
		curr->way_nbr = orig->way_nbr;
		curr->way_len = orig->way_len;
		curr->ants_in_rooms = orig->ants_in_rooms;
	}
	curr->next = NULL;
	curr->start = NULL;
	curr->end = NULL;
	return (curr);
}

t_ws		*make_ws(t_ws *orig)
{
	t_ws	*curr;

	if (!(curr = (t_ws*)malloc(sizeof(t_ws))))
		error_func("Malloc Error!");
	if (orig == NULL)
	{
		curr->turn_nbr = 0;
		curr->ways_nbr = 0;
		curr->ants_in_rooms = 0;
		curr->ant_nbr = 1;
	}
	else
	{
		curr->turn_nbr = orig->turn_nbr;
		curr->ways_nbr = orig->ways_nbr;
		curr->ants_in_rooms = orig->ants_in_rooms;
		curr->ant_nbr = orig->ant_nbr;
	}
	curr->ways = NULL;
	return (curr);
}

t_w			*make_new_coll_path(t_w **end, t_wh *home)
{
	t_room	*room;
	t_link	*link;
	t_w		*curr;

	curr = make_w(t_map.end, NULL, home);
	*(end) = curr;
	link = way_first_room(t_map.end);
	link->status = 0;
	link->room->status = 0;
	while (link->room->home->room_nbr != t_map.start->room_nbr)
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

void		add_new_path(t_ws *wcs)
{
	t_wh	*path;

	if (wcs->ways == NULL)
	{
		wcs->ways = make_wh(++wcs->ways_nbr, NULL);
		path = wcs->ways;
	}
	else
	{
		path = wcs->ways;
		while (path->next != NULL)
			path = path->next;
		path->next = make_wh(++wcs->ways_nbr, NULL);
		path = path->next;
	}
	way_collision_reset();
	path->start = make_new_coll_path(&(path->end), path);
	open_ways_links(path);
	if (t_col.col_flg > 0)
		way_collision_handler(wcs, path);
	recount_ways_len(wcs);
	resort_ways_by_len(wcs);
	get_turn_nbr(wcs);
}

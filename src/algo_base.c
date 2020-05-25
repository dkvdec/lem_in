/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 00:12:43 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/25 19:54:11 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int			base_deixtra(t_room *room, int price)
{
	t_link	*link;
	int		flag;

	flag = 0;
	link = room->links;
	room->price = price++;
	if (room->room_nbr == t_map.end->room_nbr)
		return (1);
	while (link)
	{
		if (link->status == 1
		&& link->room->home->status == 0
		&& link->room->home->price > price
		&& (base_deixtra(link->room->home, price) == 1))
			flag = 1;
		link = link->next;
	}
	return (flag);
}

t_link		*min_price_next_room(t_room *room)
{
	t_link	*min_link;
	t_link	*link;
	int		min;

	min = 2147483647;
	min_link = NULL;
	link = room->links;
	while (link)
	{
		if (link->status == 1
		&& link->room->home->price < min)
		{
			min = link->room->home->price;
			min_link = link;
		}
		link = link->next;
	}
	return (min_link);
}

t_w			*make_new_path(t_w **end, t_wh *home)
{
	t_room	*room;
	t_link	*link;
	t_w		*curr;

	curr = make_w(t_map.end, NULL, home);
	*end = curr;
	link = min_price_next_room(t_map.end);
	room = link->room->home;
	link->status = 0;
	link->room->status = 0;
	while (link->room->home->room_nbr != t_map.start->room_nbr)
	{
		room = link->room->home;
		room->status = 1;
		curr->prev = make_w(room, curr, home);
		curr = curr->prev;
		link = min_price_next_room(room);
		link->status = 0;
		link->room->status = 0;
		room->status = 1;
	}
	return (curr);
}

void		new_base_path(void)
{
	t_ws	*home;
	t_wh	*path;

	home = t_wcs.base_min;
	if (home->ways == NULL)
	{
		home->ways = make_wh(1, NULL);
		path = home->ways;
	}
	else
	{
		path = home->ways;
		while (path->next != NULL)
			path = path->next;
		path->next = make_wh(path->way_nbr + 1, NULL);
		path = path->next;
	}
	path->start = make_new_path(&(path->end), path);
	get_way_len(path);
	t_wcs.base_min->ways_nbr++;
}

void		algo_base(void)
{
	if ((base_deixtra(t_map.start, 0)) < 1)
		error_func("Map Error! No conection between ##start and ##end.");
	t_wcs.base_min = make_ws(NULL);
	new_base_path();
	map_reset();
	while (base_deixtra(t_map.start, 0))
	{
		new_base_path();
		map_reset();
	}
	get_turn_nbr(t_wcs.base_min);
}

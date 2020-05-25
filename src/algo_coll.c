/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_coll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:21:33 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/25 20:10:06 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int			coll_deixtra_coll(t_room *room, int price, int lvl, int step)
{
	t_link	*link;
	int		flag;
	int		best;

	flag = 0;
	best = 0;
	link = room->links;
	room->price = price++;
	while (link)
	{
		if (step > 0
		&& link->status == 1
		&& link->room->home->status == 0
		&& link->room->home->price > price)
		{
			if ((flag = coll_deixtra_base(link->room->home, price, lvl)))
			{
				best = (flag > best) ? flag : best;
			}
		}
		else if (step >= 0
		&& link->status == -1
		&& link->room->home->status == room->status
		&& link->room->home->price > price)
		{
			link->status = 0;
			if ((flag = coll_deixtra_coll(link->room->home, price, lvl + 1, step + 1)))
			{
				best = (flag > best) ? flag : best;
			}
			link->status = -1;
		}
		link = link->next;
	}
	room->mark = (best > room->mark) ? best : room->mark;
	return (best);
}

int			coll_deixtra_base(t_room *room, int price, int lvl)
{
	t_link	*link;
	int		flag;
	int		best;

	flag = 0;
	best = 0;
	link = room->links;
	room->price = price++;
	if (room->room_nbr == t_map.end->room_nbr)
	{
		t_map.coll_lvl = lvl;
		room->mark = ++t_map.mark_sts;
		return (room->mark);
	}
	while (link)
	{
		if (link->status == 1
		&& link->room->home->status == 0
		&& link->room->home->price > price)
		{
			if ((flag = coll_deixtra_base(link->room->home, price, lvl)))
				best = (flag > best) ? flag : best;
		}
		else if (price > 0
		&& link->status == 1
		&& link->room->home->status > 0
		&& link->room->home->price > price + lvl * 2)
		{
			if ((flag = coll_deixtra_coll(link->room->home, price, lvl, 0)))
				best = (flag > best) ? flag : best;
		}
		link = link->next;
	}
	room->mark = (best > room->mark) ? best : room->mark;
	return (best);
}

void		algo_coll()
{
	t_wcs.coll_cur = make_ws(NULL);
	while (coll_deixtra_base(t_map.start, 0, 0) > 0)
	{
		add_new_path(t_wcs.coll_cur);
		if (way_status_resulter(&t_wcs.coll_min, t_wcs.coll_cur))
			break ;
		map_reset();
	}
}

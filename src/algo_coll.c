/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_coll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:21:33 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 09:50:19 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int			coll_deixtra_coll_dcd(t_link *link, int price, int lvl, int step)
{
	int		flag;

	flag = 0;
	if (step > 0
	&& link->status == 1
	&& link->room->home->status == 0
	&& link->room->home->price > price)
		flag = coll_deixtra_base(link->room->home, price, lvl);
	else if (step >= 0
	&& link->status == -1
	&& link->room->home->status == link->home->status
	&& link->room->home->price > price)
	{
		link->status = 0;
		flag = coll_deixtra_coll(link->room->home, price, lvl + 1, step + 1);
		link->status = -1;
	}
	return (flag);
}

int			coll_deixtra_coll(t_room *room, int price, int lvl, int step)
{
	t_link	*link;
	int		flag;
	int		best;

	best = 0;
	link = room->links;
	room->price = price++;
	while (link)
	{
		flag = coll_deixtra_coll_dcd(link, price, lvl, step);
		best = (flag > best) ? flag : best;
		link = link->next;
	}
	room->mark = (best > room->mark) ? best : room->mark;
	return (best);
}

int			coll_deixtra_base_dcd(t_link *link, int price, int lvl)
{
	int		flag;

	flag = 0;
	if (link->status == 1
	&& link->room->home->status == 0
	&& link->room->home->price > price)
		flag = coll_deixtra_base(link->room->home, price, lvl);
	else if (price > 0
	&& link->status == 1
	&& link->room->home->status > 0
	&& link->room->home->price > price)
		flag = coll_deixtra_coll(link->room->home, price, lvl, 0);
	return (flag);
}

int			coll_deixtra_base(t_room *room, int price, int lvl)
{
	t_link	*link;
	int		flag;
	int		best;

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
		flag = coll_deixtra_base_dcd(link, price, lvl);
		best = (flag > best) ? flag : best;
		link = link->next;
	}
	room->mark = (best > room->mark) ? best : room->mark;
	return (best);
}

void		algo_coll(void)
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

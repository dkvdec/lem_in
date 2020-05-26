/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_deep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 00:14:20 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 09:47:48 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int			deep_deixtra_coll_dcd(t_link *link, int price, int lvl, int step)
{
	int		flag;

	flag = 0;
	if (step > 0
	&& link->status == 1
	&& link->room->home->status == 0
	&& link->room->home->price > price)
		flag = deep_deixtra_base(link->room->home, price + 1, lvl);
	else if (step >= 0
	&& link->status == -1
	&& link->room->home->status == link->home->status
	&& link->room->home->price > price)
	{
		link->status = 0;
		flag = deep_deixtra_coll(link->room->home,
		price + 1, lvl + 1, step + 1);
		link->status = -1;
	}
	return (flag);
}

int			deep_deixtra_coll(t_room *room, int price, int lvl, int step)
{
	t_link	*link;
	int		flag;
	int		best;

	best = 0;
	link = room->links;
	while (link)
	{
		flag = deep_deixtra_coll_dcd(link, price, lvl, step);
		if (flag > 0)
			room->price = price;
		best = (flag > best) ? flag : best;
		if (best > t_wcs.stop)
			break ;
		link = link->next;
	}
	room->mark = (best > room->mark) ? best : room->mark;
	return (best);
}

int			deep_deixtra_base_dcd(t_link *link, int price, int lvl)
{
	int		flag;

	flag = 0;
	if (link->status == 1
	&& link->room->home->status == 0
	&& link->room->home->price > price)
		flag = deep_deixtra_base(link->room->home, price, lvl);
	else if (price > 0
	&& link->status == 1
	&& link->room->home->status > 0
	&& link->room->home->price > price)
		flag = deep_deixtra_coll(link->room->home, price, lvl, 0);
	return (flag);
}

int			deep_deixtra_base(t_room *room, int price, int lvl)
{
	t_link	*link;
	int		flag;
	int		best;

	best = 0;
	link = room->links;
	room->price = price++;
	if (room->room_nbr == t_map.end->room_nbr)
	{
		if (room->price > t_wcs.deep_min->turn_nbr)
			return (0);
		t_map.coll_lvl = lvl;
		room->mark = ++t_map.mark_sts;
		return (room->mark);
	}
	while (link)
	{
		flag = deep_deixtra_base_dcd(link, price, lvl);
		best = (flag > best) ? flag : best;
		if (best > t_wcs.stop)
			break ;
		link = link->next;
	}
	room->mark = (best > room->mark) ? best : room->mark;
	return (best);
}

void		way_deep_select(void)
{
	if (t_wcs.deep_smp)
		dstr_way(&(t_wcs.deep_smp));
	full_map_reset();
	map_reclaim(t_wcs.deep_min);
	t_wcs.stop = 0;
	while (deep_deixtra_base(t_map.start, 0, 0) > t_wcs.stop)
	{
		add_new_path(t_wcs.deep_cur);
		if (t_wcs.deep_smp == NULL
		|| t_wcs.deep_cur->turn_nbr <= t_wcs.deep_smp->turn_nbr)
			copy_way(&(t_wcs.deep_smp), t_wcs.deep_cur);
		full_map_reset();
		map_reclaim(t_wcs.deep_min);
		copy_way(&(t_wcs.deep_cur), t_wcs.deep_min);
		t_wcs.stop++;
	}
}

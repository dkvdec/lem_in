/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_deep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 19:39:22 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/25 08:43:00 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void find_reset_link(t_room *prev, t_room *curr, int p_nbr, int c_nbr)
{
	t_link *link;

	link = prev->links;
	while (link && link->room->home->room_nbr != curr->room_nbr)
		link = link->next;
	link->status = p_nbr;
	link->room->status = c_nbr;
}

void map_reclaim(t_ws *wcs)
{
	t_w*	curr;
	t_wh*	head;

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

int deep_deixtra_coll(t_room *room, int price, int lvl, int step)
{
    t_link *link;
    int flag;
    int best;

    flag = 0;
    best = 0;
    link = room->links;
    while (link)
    {
        if (best > t_wcs.stop)
            break ;
        if (step > 0
        && link->status == 1
        && link->room->home->status == 0
        && link->room->home->price > price)
        {
            if ((flag = deep_deixtra_base(link->room->home, price + 1, lvl)))
            {
                room->price = price;
                best = (flag > best) ? flag : best;
            }
        }
        else if (step >= 0
        && link->status == -1
        && link->room->home->status == room->status
        && link->room->home->price > price)
        {
            link->status = 0;
            if ((flag = deep_deixtra_coll(link->room->home, price + 1, lvl + 1, step + 1)))
            {
                room->price = price;
                best = (flag > best) ? flag : best;
            }
            link->status = -1;
        }
        link = link->next;
    }
    room->mark = (best > room->mark) ? best : room->mark;
    return (best);
}

int deep_deixtra_base(t_room *room, int price, int lvl)
{
    t_link *link;
    int flag;
    int best;

    flag = 0;
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
        if (best > t_wcs.stop)
            break ;
        if (link->status == 1
        && link->room->home->status == 0
        && link->room->home->price > price)
        {
            if ((flag = deep_deixtra_base(link->room->home, price, lvl)))
                best = (flag > best) ? flag : best;
        }
        else if (price > 0
        && link->status == 1
        && link->room->home->status > 0
        && link->room->home->price > price)
        {
            if ((flag = deep_deixtra_coll(link->room->home, price, lvl, 0)))
                best = (flag > best) ? flag : best;
        }
        link = link->next;
    }
    room->mark = (best > room->mark) ? best : room->mark;
    return (best);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 13:56:54 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/11 14:59:40 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int coll_deixtra_rec(t_room *room, int price, int lvl, int step)
{
    t_link *link;
    int flag;
    int best;

    flag = 0;
    best = 0;
    link = room->links;
    while (link)
    {
        if (step > 0
        && link->status == 1
        && link->room->home->status == 0
        && link->room->home->price > price + 1 + lvl * 2)
        {
            // link->status = 0;
            // link->room->status = 0;
            if ((flag = base_deixtra_rec(link->room->home, price + 1, lvl)))
            {
                room->price = price + lvl * 2;
                best = (flag > best) ? flag : best;
            }
            // link->status = 1;
            // link->room->status = 1;
        }
        else if (step >= 0
        && link->status == -1
        && link->room->home->status == room->status
        && link->room->home->price > price - 1 + lvl * 2)
        {
            link->status = 0;
            if ((flag = coll_deixtra_rec(link->room->home, price - 1, lvl + 1, step + 1)))
            {
                room->price = price + lvl * 2;
                best = (flag > best) ? flag : best;
            }
            link->status = -1;
        }
        link = link->next;
    }
    room->mark = (best > room->mark) ? best : room->mark;
    return (best);
}

int base_deixtra_rec(t_room *room, int price, int lvl)
{
    t_link *link;
    int flag;
    int best;

    flag = 0;
    best = 0;
    link = room->links;
    room->price = price + lvl * 2;
    if (room->room_nbr == t_map.end->room_nbr)
    {
        // if (t_wcs.min && price < t_wcs.min->turn_nbr)
            // printf("price = %d, lvl = %d, mark = %d\n", price, lvl, t_map.mark_sts + 1);
        room->mark = ++t_map.mark_sts;
        return (room->mark);
    }
    while (link)
    {
        if (link->status == 1
        && link->room->home->status == 0
        && link->room->home->price > price + lvl * 2)
        {
            // link->status = 0;
            // link->room->status = 0;
            if ((flag = base_deixtra_rec(link->room->home, price + 1, lvl)))
                best = (flag > best) ? flag : best;
            // link->status = 1;
            // link->room->status = 1;
        }
        else if (price > 0
        && link->status == 1
        && link->room->home->status > 0
        && link->room->home->price > price + lvl * 2)
        {
            // link->status = 0;
            // link->room->status = 0;
            if ((flag = coll_deixtra_rec(link->room->home, price + 1, lvl, 0)))
                best = (flag > best) ? flag : best;
            // link->status = 1;
            // link->room->status = 1;
        }
        link = link->next;
    }
    room->mark = (best > room->mark) ? best : room->mark;
    return (best);
}
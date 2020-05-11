/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 13:20:31 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/09 16:20:25 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int base_deixtra(t_room *room, int price)
{
    t_link *link;
    int flag;

    flag = 0;
    link = room->links;
    room->price = price++;
    if (room->room_nbr == t_map.end->room_nbr)
    {
        room->mark = ++t_map.mark_sts;
        return (room->mark);
    }
    while (link)
    {
        if (link->status == 1
        && link->room->home->status == 0
        && link->room->home->price > price)
        {
            if ((flag = base_deixtra(link->room->home, price)))
                room->mark = (flag > room->mark) ? flag : room->mark;
        }
        link = link->next;
    }
    return (room->mark);
}

/////////////////////////////////////////////////////////////////////////////

// int coll_deixtra_rec(t_room *room, int price, int lvl, int step)
// {
//     t_link *link;
//     int flag;

//     flag = 0;
//     link = room->links;
//     while (link)
//     {
//         if (step > 0
//         && link->status == 1
//         && link->room->home->status == 0
//         && link->room->home->price > price + 1)
//         {
//             // link->status = 0;
//             // link->room->status = 0;
//             if ((flag = base_deixtra_rec(link->room->home, price + 1, lvl)))
//             {
//                 room->price = price;
//                 room->mark = (flag > room->mark) ? flag : room->mark;
//             }
//             // link->status = 1;
//             // link->room->status = 1;
//         }
//         else if (step >= 0
//         && link->status == -1
//         && link->room->home->status == room->status
//         && link->room->home->price > price - 1)
//         {
//             link->status = 0;
//             if ((flag = coll_deixtra_rec(link->room->home, price - 1, lvl + 1, step + 1)))
//             {
//                 room->price = price;
//                 room->mark = (flag > room->mark) ? flag : room->mark;
//             }
//             link->status = -1;
//         }
//         link = link->next;
//     }
//     return (room->mark);
// }

// int base_deixtra_rec(t_room *room, int price, int lvl)
// {
//     t_link *link;
//     int flag;

//     flag = 0;
//     link = room->links;
//     room->price = price;
//     if (room->room_nbr == t_map.end->room_nbr)
//     {
//         if (t_wcs.min && price < t_wcs.min->turn_nbr)
//         {
//             //ft_putendl("WAY FOUND");
//             printf("price = %d, lvl = %d, mark = %d\n", price, lvl, t_map.mark_sts + 1);
//         }
//         room->mark = ++t_map.mark_sts;
//         return (room->mark);
//     }
//     while (link)
//     {
//         if (link->status == 1
//         && link->room->home->status == 0
//         && link->room->home->price > price)
//         {
//             // link->status = 0;
//             // link->room->status = 0;
//             if ((flag = base_deixtra_rec(link->room->home, price + 1, lvl)))
//             {
//                 room->mark = (flag > room->mark) ? flag : room->mark;
//             }
//             // link->status = 1;
//             // link->room->status = 1;
//         }
//         else if (price > 0
//         && link->status == 1
//         && link->room->home->status > 0
//         && link->room->home->price > price)
//         {
//             // link->status = 0;
//             // link->room->status = 0;
//             if ((flag = coll_deixtra_rec(link->room->home, price + 1, lvl, 0)))
//             {
//                 room->mark = (flag > room->mark) ? flag : room->mark;
//             }
//             // link->status = 1;
//             // link->room->status = 1;
//         }
//         link = link->next;
//     }
//     return (room->mark);
// }

/////////////////////////////////////////////////////////////////////////////

t_link  *way_first_room(t_room *room, t_wh *home)
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

t_link  *way_next_coll_entr(t_room *room, t_wh *home)
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
        && link->room->home->price < room->price)
            next = link;
        link = link->next;
    }
    t_col.col_flg++;
    t_col.col_stp++;
    return (next);
}

t_link  *way_next_norm(t_room *room, t_wh *home)
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
        next = way_next_coll_entr(room, home);
    return (next);
}

t_link  *way_next_coll_cont(t_room *room, t_wh *home)
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
        // && link->room->home->price >= room->price)
            next = link;
        link = link->next;
    }
    t_col.col_stp++;
    return (next);
}

t_link  *way_next_coll_escp(t_room *room, t_wh *home)
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
        next = way_next_coll_cont(room, home);
    else
        t_col.col_stp = 0;
    return (next);
}

t_link  *way_next_room(t_room *room, t_wh *home)
{
    t_link  *next;

    next = NULL;
    if (t_col.col_stp == 0)
        next = way_next_norm(room, home);
    else if (t_col.col_stp == 1)
        next = way_next_coll_cont(room, home);
    else
        next = way_next_coll_escp(room, home);
    return (next);
}

t_w		*make_new_coll_path(t_w** end, t_wh* home)
{
	t_room* room;
    t_link* link;
	t_w*	curr;

	curr = make_w(t_map.end, NULL, home);
	*(end) = curr;
    link = way_first_room(t_map.end, home);
	link->status = 0;
    link->room->status = 0;
	while(link->room->home->room_nbr != t_map.start->room_nbr)
	{
        room = link->room->home;
		curr->prev = make_w(room, curr, home);
		curr = curr->prev;
        if (room->status == 0)
            room->status = home->way_nbr;
        link = way_next_room(room, home);
        if (link == NULL)
            current_status(room, home);
		link->status = 0;
        link->room->status = 0;
	}
    printf("\n t_col.col_flg = %d\n", t_col.col_flg);
	link->status = 0;
    link->room->status = 0;
	return (curr);
}
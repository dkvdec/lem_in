/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 13:20:31 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/18 18:08:00 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int base_deixtra_rec(t_room *room, int price)
{
    t_link *link;
    int flag;

    flag = 0;
    link = room->links;
    room->price = price++;
    if (room->room_nbr == t_map.end->room_nbr)
        return (1);
    while (link)
    {
        if (link->status != 0 && link->room->home->price > price
        && (base_deixtra_rec(link->room->home, price) == 1))
            flag = 1;
        // else if (link->room->home->room_nbr == t_map.end->room_nbr)
        //     flag = 1;
        link = link->next;
    }
    return (flag);
}

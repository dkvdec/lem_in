/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 23:57:44 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/25 08:03:26 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void map_reset()
{
    t_room *room;

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

void full_map_reset()
{
	t_room *room;
	t_link *link;

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

void wcs_reset()
{
    t_wcs.base_min = NULL;
    t_wcs.coll_cur = NULL;
    t_wcs.coll_min = NULL;
    t_wcs.deep_cur = NULL;
    t_wcs.deep_min = NULL;
    t_wcs.deep_smp = NULL;
}

void algo_core()
{
    wcs_reset();
    algo_base();
    full_map_reset();
    algo_coll();
    full_map_reset();
    algo_deep();
}
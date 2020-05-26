/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 02:17:47 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 06:00:54 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		map_reset(void)
{
	t_room	*room;

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

void		full_map_reset(void)
{
	t_room	*room;
	t_link	*link;

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

void		wcs_reset(void)
{
	t_wcs.base_min = NULL;
	t_wcs.coll_cur = NULL;
	t_wcs.coll_min = NULL;
	t_wcs.deep_cur = NULL;
	t_wcs.deep_min = NULL;
	t_wcs.deep_smp = NULL;
}

void		full_reset(void)
{
	t_valid.ants_flag = 0;
	t_valid.room_flag = 0;
	t_valid.start_flag = 0;
	t_valid.end_flag = 0;
	t_valid.room_counter = 0;
	t_valid.link_counter = 0;
	t_map.ants_nbr = 0;
	t_map.mark_sts = 0;
	t_map.coll_lvl = 0;
	t_map.rooms = NULL;
	t_map.start = NULL;
	t_map.end = NULL;
}

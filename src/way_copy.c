/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:27:57 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 01:19:22 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		copy_path(t_wh *dst, t_wh *src)
{
	t_w		*dst_room;
	t_w		*src_room;

	dst_room = make_w(t_map.end, NULL, dst);
	dst->end = dst_room;
	src_room = src->end;
	while (src_room->prev != NULL)
	{
		src_room = src_room->prev;
		dst_room->prev = make_w(src_room->room, dst_room, dst);
		dst_room = dst_room->prev;
	}
	dst->start = dst_room;
}

void		copy_way(t_ws **dst, t_ws *src)
{
	t_wh	*ds_ws;
	t_wh	*sr_ws;

	if (*(dst) != NULL)
		dstr_way(dst);
	*(dst) = make_ws(src);
	(*dst)->ways = make_wh(src->ways->way_nbr, src->ways);
	ds_ws = (*dst)->ways;
	sr_ws = src->ways;
	copy_path(ds_ws, sr_ws);
	while (sr_ws->next != NULL)
	{
		sr_ws = sr_ws->next;
		ds_ws->next = make_wh(sr_ws->way_nbr, sr_ws);
		ds_ws = ds_ws->next;
		copy_path(ds_ws, sr_ws);
	}
}

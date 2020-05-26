/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 06:51:32 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 09:58:39 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		find_coll_way1(t_wh *way)
{
	t_w		*curr;

	t_col.wh1 = way;
	t_col.w1_col_s = NULL;
	t_col.w1_col_e = NULL;
	curr = way->end->prev;
	while (curr && curr->room->status == way->way_nbr)
		curr = curr->prev;
	t_col.w1_col_s = curr;
	while (curr && curr->prev->room->status != way->way_nbr)
		curr = curr->prev;
	t_col.w1_col_e = curr;
	if (t_col.w1_col_s == NULL || t_col.w1_col_e == NULL)
		error_func("Collision Error! w1 collision not allocated.");
}

void		find_coll_way2(t_ws *wcs)
{
	t_wh	*way2;
	t_w		*curr;

	if (t_col.w1_col_s->room->status != t_col.w1_col_e->room->status)
		error_func("Collision Error! w1_s doesn't match w1_e.");
	way2 = wcs->ways;
	while (way2 && way2->way_nbr != t_col.w1_col_s->room->status)
		way2 = way2->next;
	if (!(way2))
		error_func("Collision Error! w2 not found.");
	t_col.wh2 = way2;
	t_col.w2_col_s = NULL;
	t_col.w2_col_e = NULL;
	curr = way2->end->prev;
	while (curr && curr->room->room_nbr != t_col.w1_col_e->room->room_nbr)
		curr = curr->prev;
	t_col.w2_col_s = curr;
	while (curr && curr->room->room_nbr != t_col.w1_col_s->room->room_nbr)
		curr = curr->prev;
	t_col.w2_col_e = curr;
	if (t_col.w2_col_s == NULL || t_col.w2_col_e == NULL)
		error_func("Collision Error! w2 collision not allocated.");
}

void		handle_collision(void)
{
	reconnect_ways(t_col.w1_col_s, t_col.w2_col_e, t_col.w1_col_e);
	reconnect_ways(t_col.w2_col_s, t_col.w1_col_e, t_col.w2_col_e);
	reconnect_home(t_col.wh1);
	reconnect_home(t_col.wh2);
	claim_rooms(t_col.wh2);
	claim_tail(t_col.w1_col_e);
	t_col.wh1 = NULL;
	t_col.w1_col_s = NULL;
	t_col.w1_col_e = NULL;
	t_col.wh2 = NULL;
	t_col.w2_col_s = NULL;
	t_col.w2_col_e = NULL;
}

void		claim_rooms(t_wh *home)
{
	t_w		*curr;

	curr = home->start;
	while (curr->next)
	{
		curr->room->status = curr->home->way_nbr;
		curr = curr->next;
	}
}

void		way_collision_handler(t_ws *wcs, t_wh *way)
{
	while (t_col.col_flg > 0)
	{
		find_coll_way1(way);
		find_coll_way2(wcs);
		handle_collision();
		t_col.col_flg--;
	}
	claim_rooms(way);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_coll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 20:31:46 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 00:49:27 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	find_coll_way1(t_wh *way)
{
	t_w	*curr;

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
	{
		// test_show_way(way);
		error_func("Collision Error! w1 collision not allocated.");
	}
	// printf("way 1 sollision s = |%s| e = |%s|\n", t_col.w1_col_s->room->name, t_col.w1_col_e->room->name);
}

void	find_coll_way2(t_ws *wcs)
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
	{
		// test_show_trouble_situation(t_map.end, 2);
		// test_show_way(t_col.wh1);
		printf("collision |%s|->...->|%s|\n", t_col.w1_col_e->room->name, t_col.w1_col_s->room->name);
		// test_show_way(t_col.wh2);
		error_func("Collision Error! w2 collision not allocated.");
	}
}

void	open_links(t_room *room)
{
	t_link *link;

	link = room->links;
	while (link)
	{
		if ((link->status == 0 && link->room->status == -1)
		|| (link->status == -1 && link->room->status == 0))
		{
			link->status = 1;
			link->room->status = 1;
		}
		link = link->next;
	}
}

void	reconnect_ways(t_w *start, t_w *end, t_w *stop)
{
	t_w	*tmp;
	t_w *prev;

	tmp = start;
	prev = tmp->prev;
	start = start->next;
	end->next = start;
	start->prev = end;
	free(tmp);
	tmp = NULL;
	while (prev && prev->room->room_nbr != stop->room->room_nbr)
	{
		prev->room->status = 0;
		open_links(prev->room);
		tmp = prev;
		prev = prev->prev;
		free(tmp);
		tmp = NULL;
	}
}

void	reconnect_home(t_wh *home)
{
	t_w	*curr;

	curr = home->start;
	home->end = NULL;
	while (curr)
	{
		curr->home = home;
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	home->end = curr;
}

void	claim_rooms(t_wh *home)
{
	t_w* curr;

	curr = home->start;
	while (curr->next)
	{
		curr->room->status = curr->home->way_nbr;
		curr = curr->next;
	}
}

void	claim_tail(t_w* curr)
{
	while (curr->next)
	{
		curr->room->status = curr->home->way_nbr;
		curr = curr->next;
	}
}

void	handle_collision()
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

void	test_claim(t_ws *wcs)
{
	t_wh*	head;
	t_w*	curr;

	head = wcs->ways;
	while (head)
	{
		curr = head->start;
		while (curr && curr->room->room_nbr != t_map.end->room_nbr)
		{
			if (curr->room->status != curr->home->way_nbr)
			{
				// test_show_paths();
				error_func("Collision Error! Claim test failed.");
			}
			curr = curr->next;
		}
		head = head->next;
	}
}

void	recount_ways_len(t_ws *wcs)
{
	t_wh	*head;

	head = wcs->ways;
	while (head)
	{
		get_way_len(head);
		head = head->next;
	}
}

void	get_ways_nbr(t_ws *wcs)
{
	t_wh	*curr;

	curr = wcs->ways;
	wcs->ways_nbr = 1;
	while (curr->next)
	{
		wcs->ways_nbr++;
		curr = curr->next;
	}
}

int		check_ways_sort(t_ws *wcs)
{
	t_wh	*curr;

	curr = wcs->ways;
	while (curr->next)
	{
		if (curr->way_len > curr->next->way_len)
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	sort_operation(t_ws *wcs)
{
	t_wh	*prev;
	t_wh	*curr;
	t_wh	*next;

	prev = wcs->ways;
	curr = wcs->ways->next;
	next = wcs->ways->next->next;
	if (prev->way_len > curr->way_len)
	{
		prev->next = curr->next;
		curr->next = prev;
		wcs->ways = curr;
	}
	else
		while (next)
		{
			if (curr->way_len > next->way_len)
			{
				curr->next = next->next;
				next->next = curr;
				prev->next = next;
				break ;
			}
			next = next->next;
			curr = curr->next;
			prev = prev->next;
		}
}

void	resort_ways_by_len(t_ws *wcs)
{
	t_wh	*curr;

	get_ways_nbr(wcs);
	if (wcs->ways_nbr == 2
	&& wcs->ways->way_len > wcs->ways->next->way_len)
	{
		curr = wcs->ways;
		wcs->ways = wcs->ways->next;
		wcs->ways->next = curr;
		wcs->ways->next->next = NULL;
	}
	else if (wcs->ways_nbr > 2)
		while (check_ways_sort(wcs))
			sort_operation(wcs);			
}

void	way_collision_handler(t_ws *wcs, t_wh *way)
{
	while (t_col.col_flg > 0)
	{
		find_coll_way1(way);
		find_coll_way2(wcs);
		handle_collision();
		t_col.col_flg--;
	}
	claim_rooms(way);
	test_claim(wcs); // test
}
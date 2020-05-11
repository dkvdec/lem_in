/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_way.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 20:24:54 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/09 13:55:10 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_w*    make_w(t_room *room, t_w *next, t_wh* home)
{
	t_w		*curr;

	if (!(curr = (t_w*)malloc(sizeof(t_w))))
		error_func("Malloc Error!");
	curr->home = home; //mb delete later
	curr->room = room;
	curr->ant_nbr = 0;
	curr->prev = NULL;
	curr->next = next;
	return (curr);
}

t_wh*   make_wh(int way_nbr, t_wh *orig)
{
	t_wh	*curr;

	if (!(curr = (t_wh*)malloc(sizeof(t_wh))))
		error_func("Malloc Error!");
	if (orig == NULL)
	{
		curr->way_nbr = way_nbr;
		curr->way_len = 0;
		curr->ants_in_rooms = 0;
	}
	else
	{
		curr->way_nbr = orig->way_nbr;
		curr->way_len = orig->way_len;
		curr->ants_in_rooms = orig->ants_in_rooms;
	}
	curr->next = NULL;
	curr->start = NULL;
	curr->end = NULL;
	return (curr);
}

t_ws*   make_ws(t_ws* orig)
{
	t_ws	*curr;

	if (!(curr = (t_ws*)malloc(sizeof(t_ws))))
		error_func("Malloc Error!");
	if (orig == NULL)
	{
		curr->turn_nbr = 0;
		curr->ways_nbr = 0;
		curr->ants_in_rooms = 0;
		curr->ant_nbr = 1;
	}
	else
	{
		curr->turn_nbr = orig->turn_nbr;
		curr->ways_nbr = orig->ways_nbr;
		curr->ants_in_rooms = orig->ants_in_rooms;
		curr->ant_nbr = orig->ant_nbr;
	}
	curr->ways = NULL;
	return (curr);
}

// t_w		*make_new_path(t_w** end, t_wh* home)
// {
// 	t_room* room;
//     t_link* link;
// 	t_w*	curr;

// 	curr = make_w(t_map.end, NULL, home);
// 	*(end) = curr;
// 	link = min_price_next_room(t_map.end, home);
// 	room = link->room->home;
// 	link->status = 0;
//     link->room->status = 0;
// 	while(link->room->home->room_nbr != t_map.start->room_nbr)
// 	{
//         room = link->room->home;
// 		room->status = 1;
// 		curr->prev = make_w(room, curr, home);
// 		curr = curr->prev;
// 		link = min_price_next_room(room, home);
// 		link->status = 0;
//         link->room->status = 0;
// 		room->status = home->way_nbr;
// 	}
// 	link->status = 0;
//     link->room->status = 0;
// 	return (curr);
// }

void	way_collision_reset()
{
	t_col.col_flg = 0;
	t_col.col_stp = 0;
	t_col.col_sts = 0;
}

void	open_ways_links(t_wh *way)
{
	t_w		*curr;
	t_link	*link;

	curr = way->start;
	while (curr->next)
	{
		link = curr->room->links;
		if (curr->next->room->room_nbr == t_map.end->room_nbr)
			break ;
		while (curr->next->room->room_nbr != link->room->home->room_nbr)
			link = link->next;
		link->status = 0;
		link->room->status = -1;
		curr = curr->next;
	}
}

void	add_new_path(void)
{
	t_wh	*path;

	if (t_wcs.cur->ways == NULL)
	{
		t_wcs.cur->ways = make_wh(++t_wcs.cur->ways_nbr, NULL);
		path = t_wcs.cur->ways;
	}
	else
	{
		path = t_wcs.cur->ways;
		while (path->next != NULL)
			path = path->next;
		path->next = make_wh(++t_wcs.cur->ways_nbr, NULL);
		path = path->next;
	}
	way_collision_reset();
	//path->start = make_new_path(&(path->end), path);
	path->start = make_new_coll_path(&(path->end), path);
	// test_show_paths();
	open_ways_links(path);
	if (t_col.col_flg > 0)
		way_collision_handler(path);
	recount_ways_len();
	resort_ways_by_len();
	get_turn_nbr(t_wcs.cur);
}

//			WCS_FUCS

void make_wcs()
{
	t_wcs.min = NULL;
	t_wcs.cur = make_ws(NULL);
}

void get_way_len(t_wh *way)
{
	t_w	*curr;

	way->way_len = 1;
	curr = way->start;
	while (curr->next != NULL)
	{
		curr = curr->next;
		way->way_len++;
	}
}

void get_turn_nbr(t_ws *head)
{
	t_wh	*cur;
	int		ant_nbr;
	int		big_len;

	ant_nbr = t_map.ants_nbr;
	big_len = 0;
	head->turn_nbr = 0;
	while (ant_nbr > 0)
	{
		cur = head->ways;
		while (cur != NULL && ant_nbr > 0)
		{
			if (acess_giver(head, cur, ant_nbr))
			{
				ant_nbr--;
				if (big_len < cur->way_len)
					 big_len = cur->way_len;
			}
			cur = cur->next;
		}
		head->turn_nbr++;
		big_len--;
	}
	head->turn_nbr += big_len;
}
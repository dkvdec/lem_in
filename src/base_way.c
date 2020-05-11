/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 16:38:51 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/11 14:59:25 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_link	*next_room_coll_frcd_entr(t_room *room, t_wh *home)
{
	t_link	*link;
	t_link	*next;
	int		min;

	min = 2147483647;
	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 1
		&& link->room->home->status > 0
		&& link->room->home->price < min)
		{
			min = link->room->home->price;
			next = link;
		}
		link = link->next;
	}
	if (next == NULL)
		error_func("Build Path Error! Forced collision enter failed.");
	t_col.col_flg++;
	t_col.col_stp++;
	t_col.col_sts = next->room->home->status;
	return (next);
}

t_link	*next_room_coll_entr(t_room *room, t_wh *home)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 1
		&& link->room->home->status > 0
		&& link->room->home->price == room->price - 1)
			next = link;
		link = link->next;
	}
	if (next == NULL)
		next = next_room_coll_frcd_entr(room, home);
	else
	{
		t_col.col_flg++;
		t_col.col_stp++;
		t_col.col_sts = next->room->home->status;
	}
	return (next);
}
t_link	*next_room_norm_case(t_room *room, t_wh *home)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 1
		&& link->room->home->status == 0
		&& link->room->home->price == room->price - 1)
			next = link;
		link = link->next;
	}
	if (next == NULL && room->room_nbr == t_map.end->room_nbr)
		error_func("Build Path Error! Can't escape end_room.");
	else if (next == NULL)
		next = next_room_coll_entr(room, home);
	printf("(%s)", next->room->home->name);
	return (next);
}

t_link	*next_room_coll_fllw_frcd(t_room *room, t_wh *home)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 0
		&& link->room->status == -1
		&& link->room->home->status == t_col.col_sts)
			next = link;
		link = link->next;
	}
	if (next == NULL)
	{
		test_show_trouble_situation(room, 3);
		error_func("Build Path Error! Forced collision follow failed.");
	}
	t_col.col_stp++;
	return (next);
}

t_link	*next_room_coll_fllw(t_room *room, t_wh *home)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 0
		&& link->room->status == -1
		&& link->room->home->status == t_col.col_sts
		&& link->room->home->price == room->price + 1)
			next = link;
		link = link->next;
	}
	if (next == NULL)
		next = next_room_coll_fllw_frcd(room, home);
	else
		t_col.col_stp++;
	return (next);
}

t_link	*next_room_coll_escp(t_room *room, t_wh *home)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 1
		&& link->room->home->status == 0
		&& link->room->home->price <= room->price)
			next = link;
		link = link->next;
	}
	if (next == NULL)
		next = next_room_coll_fllw(room, home);
	else
	{
		t_col.col_sts = 0;
		t_col.col_stp = 0;
	}
	return (next);
}


t_link	*next_room_decider(t_room *room, t_wh *home)
{
	t_link	*next;

	if (t_col.col_stp == 0)
		next = next_room_norm_case(room, home);
	else if (t_col.col_stp == 1)
		next = next_room_coll_fllw(room, home);
	else
		next = next_room_coll_escp(room, home);
	return (next);
}

t_link *min_price_next_room(t_room *room, t_wh *home)
{
	t_link  *min_link;
    t_link  *link;
	int min;
	
	min = 2147483647;
	min_link = NULL;
    link = room->links;
	while (link)
	{
		if ((room->status == home->way_nbr || room->room_nbr == t_map.end->room_nbr)
		&& link->status == 1
		&& link->room->home->price < min)
		{
			min = link->room->home->price;
			min_link = link;
		}
		else if (room->status != home->way_nbr
		&& t_col.col_stp > 1
		&& link->status == 1)
		//&& link->room->home->price == room->price - 1)
		{
			t_col.col_stp = 0;
			min = link->room->home->price;
			min_link = link;
		}
		else if (room->status != home->way_nbr
		&& t_col.col_stp >= 0
		&& link->status == 0 && link->room->status == -1)
		//&& link->room->home->price == room->price + 1)
		{
			if (t_col.col_stp == 0)
				t_col.col_flg++;
			t_col.col_stp++;
			min = link->room->home->price;
			min_link = link;
		}
		link = link->next;
	}
	return (min_link);
}

t_wroom  *make_wroom(t_room *room, t_wroom *prev)
{
	t_wroom *curr;
	
	if (!(curr = (t_wroom*)malloc(sizeof(t_wroom))))
		error_func("Malloc Error!");
	curr->room_nbr = room->room_nbr;
    curr->name = room->name;
	curr->ant_nbr = 0;
	curr->prev_room = NULL;
	curr->next_room = prev;
	return (curr);
}

// t_wroom *make_path(t_wroom **end_room, int *length)
// {
// 	t_wroom *curr;
//     t_room* room;
//     t_link* link;

// 	curr = make_wroom(t_map.end, NULL);
// 	*(end_room) = curr;
// 	link = min_price_next_room(t_map.end, home);
//     room = link->room->home;
//     link->status = 0;//-1
//     link->room->status = 0;
// 	while(link->room->home->room_nbr != t_map.start->room_nbr)
// 	{
//         room = link->room->home;
// 		room->status = 1;
// 		curr->prev_room = make_wroom(room, curr);
// 		curr = curr->prev_room;
// 		link = min_price_next_room(room);
//         //room = link->room->home;
// 		room->status = 1;
// 		link->status = 0;//-1
//         link->room->status = 0;
// 	}
// 	return (curr);
// }

// t_way *make_way(int way_nbr)
// {
// 	t_way*  curr;

// 	if (!(curr = (t_way*)malloc(sizeof(t_way))))
// 		error_func("Malloc Error!");
// 	curr->lenght = 0;
// 	curr->way_nbr = way_nbr;
// 	curr->start = make_path(&(curr->end), &(curr->lenght));
// 	curr->next = NULL;
// }

void change_value()
{
    t_room *room;

    room = t_map.rooms;
	t_map.mark_sts = 0;
    while (room)
    {
		room->mark = 0;
        room->price = 2147483647;
        room = room->next;
    }
}

void get_ways_len()
{
	t_way*	curr;
	int		i;

	if (!(t_move.ways_len = (int*)malloc(sizeof(int) * t_move.ways)))
		error_func("Malloc Error!");
	curr = t_move.head;
	i = 0;
	while (curr != NULL && i < t_move.ways)
	{
		t_move.ways_len[i] = curr->lenght;
		i++;
		curr = curr->next;
	}
	//
	// i = 0;
	// ft_printf("_______________\nLEN_WAYS\n");
	// while (i < t_move.ways)
	// {
	// 	ft_printf("way_nbr = %d len = %d\n", i, t_move.ways_len[i++]);
	// }
	// ft_printf("\n\n\n");
	//
}

int way_status_resulter()
{
	if (t_wcs.min == NULL
	|| t_wcs.min->turn_nbr > t_wcs.cur->turn_nbr)
		copy_way(&(t_wcs.min), t_wcs.cur);
	else
		return (1);
	return (0);
}

void full_map_reset()
{
	t_room *room;
	t_link *link;

    room = t_map.rooms;
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

void find_reset_link(t_room *prev, t_room *curr, int p_nbr, int c_nbr)
{
	t_link *link;

	link = prev->links;
	while (link && link->room->home->room_nbr != curr->room_nbr)
		link = link->next;
	link->status = p_nbr;
	link->room->status = c_nbr;
}

void map_reclaim()
{
	t_w*	curr;
	t_wh*	head;

	head = t_wcs.min->ways;
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

void base_way_former()
{
    t_way *curr;
	// int i;

	/* BASE ALGO HERE */
    if ((base_deixtra(t_map.start, 0)) < 1)
        error_func("Map Error! No conection between ##start and ##end.");
    // i = 0;
	// curr = make_way(i++);
	// t_move.head = curr;
	// test_show_room_status();
	make_wcs();
	add_new_path();//
    change_value();
	// test_show_paths();
	way_status_resulter();
    // while (base_deixtra(t_map.start, 0) > 0)
    // {
    //     // curr->next = make_way(i++);
	// 	// curr = curr->next;
	// 	// test_show_room_status();
	// 	printf("end room mark = %d\n", t_map.end->mark);
	// 	add_new_path();//
    // 	printf("\ncur turn_nbr = %d\n", t_wcs.cur->turn_nbr);
	// 	printf("min turn_nbr = %d\n\n", t_wcs.min->turn_nbr);
	// 	change_value();
	// 	if (way_status_resulter())
	// 		break ;
	// 	test_show_paths();
	// 	printf("====================================================================================================================================================================\n\n\n\n");
    // }
	// /* RECURSION ALGO HERE */
	// // test_show_room_status();
	// printf("******************************************************************************************************************\n");
	// printf("cur turn_nbr = %d ways_nbr = %d\n", t_wcs.cur->turn_nbr, t_wcs.cur->ways_nbr);
	// printf("min turn_nbr = %d ways_nbr = %d\n", t_wcs.min->turn_nbr, t_wcs.min->ways_nbr);
	// full_map_reset();
	// map_reclaim();
	// copy_way(&(t_wcs.cur), t_wcs.min);
	// printf("cur turn_nbr = %d ways_nbr = %d\n", t_wcs.cur->turn_nbr, t_wcs.cur->ways_nbr);
	// printf("min turn_nbr = %d ways_nbr = %d\n", t_wcs.min->turn_nbr, t_wcs.min->ways_nbr);
	// printf("******************************************************************************************************************\n");
	// // test_show_room_status();
	while (base_deixtra_rec(t_map.start, 0, 0) > 0)
    {
        // curr->next = make_way(i++);
		// curr = curr->next;
		// test_show_room_status();
		// printf("end room mark = %d\n", t_map.end->mark);
		add_new_path();//
    	// printf("\ncur turn_nbr = %d\n", t_wcs.cur->turn_nbr);
		// printf("min turn_nbr = %d\n\n", t_wcs.min->turn_nbr);
		change_value();
		way_status_resulter();
		// 	break ;
		// test_show_paths();
		// printf("====================================================================================================================================================================\n\n\n\n");
    }
	// test_show_room_status();
	// test_show_paths();
    // printf("result cur turn_nbr = %d\n", t_wcs.cur->turn_nbr);
	// printf("result min turn_nbr = %d\n", t_wcs.min->turn_nbr);
    // t_move.ways = i;
    // get_ways_len();
}
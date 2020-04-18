/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 16:38:51 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/18 18:01:09 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_link *min_price_next_room(t_room *room, int **length)
{
	t_link  *min_link;
    t_link  *link;
	int min;
	
	min = 2147483647;
	min_link = NULL;
    link = room->links;
	while (link)
	{
		if (link->status == 1
		&& link->room->home->price < min)
		{
			min = link->room->home->price;
			min_link = link;
		}
		link = link->next;
	}
	if (**(length) == 0)
		**(length) = min;
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

t_wroom *make_path(t_wroom **end_room, int *length)
{
	t_wroom *curr;
    t_room* room;
    t_link* link;

	curr = make_wroom(t_map.end, NULL);
	*(end_room) = curr;
	link = min_price_next_room(t_map.end, &length);
    room = link->room->home;
    link->status = 0;//-1
    link->room->status = 0;
	while(link->room->home->room_nbr != t_map.start->room_nbr)
	{
        room = link->room->home;
		curr->prev_room = make_wroom(room, curr);
		curr = curr->prev_room;
		link = min_price_next_room(room, &length);
        room = link->room->home;
		link->status = 0;//-1
        link->room->status = 0;
	}
	return (curr);
}

t_way *make_way(int way_nbr)
{
	t_way*  curr;

	if (!(curr = (t_way*)malloc(sizeof(t_way))))
		error_func("Malloc Error!");
	curr->lenght = 0;
	curr->way_nbr = way_nbr;
	curr->start = make_path(&(curr->end), &(curr->lenght));
	curr->next = NULL;
}

void change_value()
{
    t_room *room;

    room = t_map.rooms;
    while (room)
    {
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

void base_way_former()
{
    t_way *curr;
	int i;

    if ((base_deixtra_rec(t_map.start, 0)) < 1)
        error_func("Map Error! No conection between ##start and ##end.");
    i = 0;
	curr = make_way(i++);
	t_move.head = curr;
    change_value();
    while ((base_deixtra_rec(t_map.start, 0)) == 1)
    {
        curr->next = make_way(i++);
		curr = curr->next;
		change_value();
    }
    t_move.ways = i;
    get_ways_len();
}
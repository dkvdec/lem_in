/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transport.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:16:26 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/10 20:22:59 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
**	map_mark
**
**	functions:
**		-valuation of ways cost
**	return options:
**		1 - if end reached
**		0 - if blocked by cost
**		-1 - if end's unreached
*/

void remove_link(int i)
{
	int j;

	j = 0;
	while(j < t_links.max_size)
	{
		t_links.room_links[i][j] = 0;
		t_links.room_links[j][i] = 0;
		j++;
	}
}

int min_price_next_room(int i, int **length)
{
	int j;
	int min;
	int min_nbr;

	j = 0;
	min = 2147483647;
	min_nbr = -1;
	while (j < t_links.max_size)
	{
		if (t_links.room_links[i][j] > 0
		&& t_links.room_links[i][j] < min)
		{
			min = t_links.room_links[i][j];
			min_nbr = j;
		}
		j++;
	}
	if (**(length) == 0)
		**(length) = min;
	return (min_nbr);
}


t_room  *make_room(int room_nbr, t_room *prev)
{
	t_room *curr;
	
	if (!(curr = (t_room*)malloc(sizeof(t_room))))
		error_func("Malloc Error!");
	curr->room_nbr = room_nbr;
	curr->ant_nbr = 0;
	curr->prev_room = NULL;
	curr->next_room = prev;
	return (curr);
}

t_room *make_path(int room_nbr, t_room *end_room, int *length)
{
	t_room *curr;
	int room_old;

	curr = make_room(room_nbr, NULL);
	end_room = curr;
	room_nbr = min_price_next_room(room_nbr, &length);
	t_links.room_links[room_nbr][t_rooms.end_room_nbr] = 0;
	t_links.room_links[t_rooms.end_room_nbr][room_nbr] = 0;
	while(room_nbr != t_rooms.start_room_nbr)
	{
		curr->prev_room = make_room(room_nbr, curr);
		curr = curr->prev_room;
		room_old = room_nbr;
		room_nbr = min_price_next_room(room_nbr, &length);
		remove_link(room_old);
	}
	t_links.room_links[room_nbr][t_rooms.end_room_nbr] = 0;
	return (curr);
}

t_way *make_way(int way_nbr)
{
	t_way*  curr;

	if (!(curr = (t_way*)malloc(sizeof(t_way))))
		error_func("Malloc Error!");
	curr->lenght = 0;
	curr->way_nbr = way_nbr;
	curr->start_room = make_path(t_rooms.end_room_nbr, curr->end_room, &curr->lenght);
	curr->next = NULL;
}

void form_ways()
{
	t_way *curr;
	int i;

	change_value();
	if (map_mark(t_rooms.start_room_nbr, 0) < 1)
		ft_printf("Map Error! No conection between ##start and ##end.");
	i = 0;
	curr = make_way(i++);
	t_move.head = curr;
	change_value();
	while (map_mark(t_rooms.start_room_nbr, 0) == 1)
	{
		curr->next = make_way(i++);
		curr = curr->next;
		change_value();        
	}
	t_move.ways = i;
	ft_printf("WAYS FORMED = %d\n", i);////////////
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
	i = 0;
	ft_printf("_______________\nLEN_WAYS\n");
	while (i < t_move.ways)
	{
		ft_printf("way_nbr = %d len = %d\n", i, t_move.ways_len[i++]);
	}
	//
}

void ants_mover()
{
}

int acess_giver(int way_nbr)
{
	int i;

	
}

void ants_launcher()
{
	t_way	*curr;

	curr = t_move.head;
	while (curr != NULL)
	{
		if (t_valid.ants_nbr < 1)
			break;
		if (acess_giver(curr->way_nbr))
			curr->start_room->ant_nbr = t_valid.ants_nbr--;
		curr = curr->next;
	}
}

void display_status()
{
}

void transport_core()
{
}

//версия с рекурсией
// t_room *make_way(int room_nbr, t_room *prev)
// {
//     t_room *curr;
//     int min_nbr;

//     // if (!(curr = (t_room*)malloc(sizeof(t_room))))
// 	// 	error_func("Malloc Error!");
//     curr->room_nbr = room_nbr;
//     curr->ant_nbr = 0;
//     min_nbr = min_price_next_room(room_nbr);
//     if (min_nbr == t_rooms.start_room_nbr)
//         curr->next_room = NULL;
//     else
//         curr->next_room = make_way(min_nbr, &curr);
//     if (room_nbr != t_rooms.end_room_nbr)
//         remove_link(room_nbr);
//     return (&curr);
// }
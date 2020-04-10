/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transport.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:16:26 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/11 00:13:53 by dheredat         ###   ########.fr       */
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

t_room *make_path(int room_nbr, t_room **end_room, int *length)
{
	t_room *curr;
	int room_old;

	curr = make_room(room_nbr, NULL);
	*(end_room) = curr;
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
	curr->start_room = make_path(t_rooms.end_room_nbr, &(curr->end_room), &curr->lenght);
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

int acess_giver(int way_nbr)
{
	int i;
	int sum;

	i = way_nbr - 1;
	sum = 0;
	while (i >= 0)
	{
		sum += t_move.ways_len[way_nbr] - t_move.ways_len[i];
		i--;
	}
	if (t_valid.ants_nbr <= t_valid.ants_nbr)
		return (1);
	return (0);
}

void ants_launcher()
{
	t_way	*curr;

	curr = t_move.head;
	while (curr != NULL && t_valid.ants_nbr > 0)
	{
		if (acess_giver(curr->way_nbr))
		{
			curr->start_room->ant_nbr = t_move.ant_nbr++;
			t_move.ants_in_rooms++;
			t_valid.ants_nbr--;
		}
		curr = curr->next;
	}
}

void ants_mover()
{
	t_way	*curr;
	t_room	*room;

	curr = t_move.head;
	while (curr != NULL)
	{
		room = curr->end_room;
		if (room->ant_nbr > 0)
		{
			room->ant_nbr = 0;
			t_move.ants_in_rooms--;
		}
		while (room->prev_room != NULL)
		{
			if (room->prev_room->ant_nbr != 0)
			{
				room->ant_nbr = room->prev_room->ant_nbr;
				room->prev_room->ant_nbr = 0;
			}
			room = room->prev_room;
		}
		curr = curr->next;
	}
}

void display_status()
{
	t_way	*curr;
	t_room	*room;
	int 	i;

	curr = t_move.head;
	i = 0;
	while (curr != NULL)
	{
		room = curr->end_room;
		while (room != NULL)
		{
			if (room->ant_nbr != 0)
			{
				if (i == 0)
					ft_printf("L%d-%s", room->ant_nbr, t_rooms.room_list[room->room_nbr]);
				else
					ft_printf(" L%d-%s", room->ant_nbr, t_rooms.room_list[room->room_nbr]);
				i++;
			}
			room = room->prev_room;
		}
		curr = curr->next;
	}
	ft_printf("\n");
}

void transport_core()
{
	t_move.ant_nbr = 1;
	while (t_move.ants_in_rooms > 0 || t_valid.ants_nbr > 0)
	{
		if (t_move.ants_in_rooms > 0)
			ants_mover();
		if (t_valid.ants_nbr > 0)
			ants_launcher();
		if (t_move.ants_in_rooms > 0)
			display_status();
	}
	ft_printf(">>>>>>>>>END<<<<<<<<<\n");
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
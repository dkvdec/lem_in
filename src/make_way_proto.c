/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_way_proto.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 11:09:41 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/16 11:56:48 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

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

	//change_value();
	kill_tails();
	//make_room_tail();
	ft_putendl("tails killed");//visu//remove
	//if (map_mark(t_rooms.start_room_nbr, 0) < 1)
	// if (deixtra_linear_2() < 1)
		error_func("Map Error! No conection between ##start and ##end.");
	//test_links_matrix();
	//ft_putendl("   map_marked");//visu//remove
	i = 0;
	curr = make_way(i++);
	t_move.head = curr;
	change_value();
	ft_putendl("   value_changed");//visu//remove
	ft_putendl("first_way done");//visu//remove
	while (map_mark(t_rooms.start_room_nbr, 0) == 1)
	// while (deixtra_linear_2() > 0)
	{
		ft_putendl("   map_marked");//visu//remove
		curr->next = make_way(i++);
		curr = curr->next;
		change_value();
		ft_putendl("   value_changed");//visu//remove
		ft_putendl("additional_way done");//visu//remove
		//test_links_matrix();
	}
	t_move.ways = i;
	//ft_printf("WAYS FORMED = %d\n", i);////////////
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

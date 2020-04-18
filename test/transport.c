/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transport.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:16:26 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/18 17:57:27 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
	if (t_map.ants_nbr <= t_map.ants_nbr)
		return (1);
	return (0);
}

void ants_launcher()
{
	t_way	*curr;

	curr = t_move.head;
	while (curr != NULL && t_map.ants_nbr > 0)
	{
		if (acess_giver(curr->way_nbr))
		{
			curr->start->ant_nbr = t_move.ant_nbr++;
			t_move.ants_in_rooms++;
			t_map.ants_nbr--;
		}
		curr = curr->next;
	}
}

void ants_mover()
{
	t_way	*curr;
	t_wroom	*room;

	curr = t_move.head;
	while (curr != NULL)
	{
		room = curr->end;
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

void writer(int i, t_wroom* room)
{
	if (i != 0)
		ft_putchar(' ');
	ft_putchar('L');
	ft_putnbr(room->ant_nbr);
	ft_putchar('-');
	ft_putstr(room->name);
}

void display_status()
{
	t_way	*curr;
	t_wroom	*room;
	int 	i;

	curr = t_move.head;
	i = 0;
	while (curr != NULL)
	{
		room = curr->end;
		while (room != NULL)
		{
			if (room->ant_nbr != 0)
				writer(i++, room);
			room = room->prev_room;
		}
		curr = curr->next;
	}
	ft_putchar('\n');
}

void transport_core(char *buff)
{
	t_move.ant_nbr = 1;
	//ft_putendl(buff);
	ft_putchar('\n');
	while (t_move.ants_in_rooms > 0 || t_map.ants_nbr > 0)
	{
		if (t_move.ants_in_rooms > 0)
			ants_mover();
		if (t_map.ants_nbr > 0)
			ants_launcher();
		if (t_move.ants_in_rooms > 0)
			display_status();
	}
}

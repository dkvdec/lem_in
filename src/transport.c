/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transport.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:16:26 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/12 11:34:17 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

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

void writer(int i, t_room* room)
{
	if (i != 0)
		ft_putchar(' ');
	ft_putchar('L');
	ft_putnbr(room->ant_nbr);
	ft_putchar('-');
	ft_putstr(t_rooms.room_list[room->room_nbr]);
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
	while (t_move.ants_in_rooms > 0 || t_valid.ants_nbr > 0)
	{
		if (t_move.ants_in_rooms > 0)
			ants_mover();
		if (t_valid.ants_nbr > 0)
			ants_launcher();
		if (t_move.ants_in_rooms > 0)
			display_status();
	}
}

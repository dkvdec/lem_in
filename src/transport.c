/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transport.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:16:26 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 05:31:38 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int			acess_giver(t_ws *wcs, t_wh *cur, int ants_nbr)
{
	int		sum;
	t_wh	*way;

	sum = 0;
	way = wcs->ways;
	while (way && way->way_nbr < cur->way_nbr)
	{
		sum += cur->way_len - way->way_len;
		way = way->next;
	}
	if (sum < ants_nbr)
		return (1);
	return (0);
}

void		ants_launcher(t_ws *wcs)
{
	t_wh	*curr;

	curr = wcs->ways;
	while (curr != NULL && t_map.ants_nbr > 0)
	{
		if (acess_giver(wcs, curr, t_map.ants_nbr))
		{
			curr->start->ant_nbr = wcs->ant_nbr++;
			curr->ants_in_rooms++;
			wcs->ants_in_rooms++;
			t_map.ants_nbr--;
		}
		curr = curr->next;
	}
}

void		ants_mover(t_ws *wcs)
{
	t_wh	*curr;
	t_w		*room;

	curr = wcs->ways;
	while (curr != NULL)
	{
		room = curr->end;
		if (room->ant_nbr > 0)
		{
			room->ant_nbr = 0;
			curr->ants_in_rooms--;
			wcs->ants_in_rooms--;
		}
		while (room->prev != NULL)
		{
			if (room->prev->ant_nbr != 0)
			{
				room->ant_nbr = room->prev->ant_nbr;
				room->prev->ant_nbr = 0;
			}
			room = room->prev;
		}
		curr = curr->next;
	}
}

void		writer(int i, t_w *room)
{
	if (i != 0)
		ft_putchar(' ');
	ft_putchar('L');
	ft_putnbr(room->ant_nbr);
	ft_putchar('-');
	ft_putstr(room->room->name);
}

void		display_status(t_ws *wcs)
{
	t_wh	*curr;
	t_w		*room;
	int		i;

	curr = wcs->ways;
	i = 0;
	while (curr != NULL)
	{
		room = curr->end;
		while (room != NULL)
		{
			if (room->ant_nbr != 0)
				writer(i++, room);
			room = room->prev;
		}
		curr = curr->next;
	}
	ft_putchar('\n');
}

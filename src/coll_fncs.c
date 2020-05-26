/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_fncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 20:31:46 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 09:58:58 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		open_links(t_room *room)
{
	t_link	*link;

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

void		reconnect_ways(t_w *start, t_w *end, t_w *stop)
{
	t_w		*tmp;
	t_w		*prev;

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

void		reconnect_home(t_wh *home)
{
	t_w		*curr;

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

void		claim_tail(t_w *curr)
{
	while (curr->next)
	{
		curr->room->status = curr->home->way_nbr;
		curr = curr->next;
	}
}

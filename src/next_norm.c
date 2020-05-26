/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 13:20:31 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 07:39:45 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_link		*way_first_room(t_room *room)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->status == 1
		&& link->room->status == 1
		&& link->room->home->status == 0
		&& link->room->home->mark == room->mark
		&& link->room->home->price < room->price)
		{
			if (next != NULL)
				error_func("Double link at way_first_room.");
			next = link;
		}
		link = link->next;
	}
	return (next);
}

t_link		*way_next_norm(t_room *room)
{
	t_link	*link;
	t_link	*next;

	link = room->links;
	next = NULL;
	while (link)
	{
		if (link->room->home->mark == room->mark
		&& link->room->home->status == 0
		&& link->status == 1 && link->room->status == 1
		&& link->room->home->price == room->price - 1)
			next = link;
		link = link->next;
	}
	if (next == NULL)
		next = way_next_coll_entr(room);
	return (next);
}

t_link		*way_next_room(t_room *room)
{
	t_link	*next;

	next = NULL;
	if (t_col.col_stp == 0)
		next = way_next_norm(room);
	else if (t_col.col_stp == 1)
		next = way_next_coll_cont(room);
	else
		next = way_next_coll_escp(room);
	return (next);
}

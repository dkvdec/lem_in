/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 11:58:36 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/18 20:11:07 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_room		*make_room(char *name, int nbr)
{
	t_room	*room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		error_func("Malloc  error!");
	room->next = NULL;
	room->room_nbr = nbr;
	room->status = 0;
	room->price = 2147483647;
	room->name = name;
	room->links = NULL;
	return (room);
}

t_room		*add_room(char *name)
{
	t_room	*room;
	int		nbr;

	nbr = 0;
	if (t_map.rooms == NULL)
	{
		room = make_room(name, nbr);
		t_map.rooms = room;
		return (room);
	}
	room = t_map.rooms;
	while (room)
	{
		if (!(ft_strcmp(room->name, name)))
			error_func("Map Error! Map contains room duplicates.");
		nbr++;
		if (room->next == NULL)
			break ;
		room = room->next;
	}
	room->next = make_room(name, nbr);
	room = room->next;
	return (room);
}

t_link		*make_link(t_room *home)
{
	t_link	*link;

	if (!(link = (t_link*)malloc(sizeof(t_link))))
		error_func("Malloc  error!");
	link->next = NULL;
	link->home = home;
	link->room = NULL;
	link->status = 0;
	return (link);
}

t_link		*add_link(t_room *room, int check_nbr)
{
	t_link	*curr;

	if (room->links == NULL)
	{
		curr = make_link(room);
		room->links = curr;
		return (curr);
	}
	curr = room->links;
	while (curr)
	{
		if (check_nbr == curr->room->home->room_nbr)
			error_func("Map Error! Map contains room relinks.");
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	curr->next = make_link(room);
	curr = curr->next;
	return (curr);
}

void		link_connector(t_room *room1, t_room *room2)
{
	t_link	*link1;
	t_link	*link2;

	link1 = add_link(room1, room2->room_nbr);
	link2 = add_link(room2, room1->room_nbr);
	link1->room = link2;
	link2->room = link1;
	link1->status = 1;
	link2->status = 1;
}

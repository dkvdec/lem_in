/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 11:58:36 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 05:44:00 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_room		*make_room(char *name, int nbr)
{
	t_room	*room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		error_func("Malloc  error!");
	room->next = NULL;
	room->room_nbr = nbr;
	room->mark = 0;
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
	while (room && ++nbr)
	{
		if (!(ft_strcmp(room->name, name)))
		{
			free(name);
			error_func("Map Error! Map contains room duplicates.");
		}
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
	link->status = 1;
	return (link);
}

t_link		*add_link(t_room *room, int check_nbr, char **names)
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
		if (check_nbr == curr->room->home->room_nbr && free_strsplit(names))
			error_func("Map Error! Map contains room relinks.");
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	curr->next = make_link(room);
	curr = curr->next;
	return (curr);
}

void		link_connector(t_room *room1, t_room *room2, char **names)
{
	t_link	*link1;
	t_link	*link2;

	link1 = add_link(room1, room2->room_nbr, names);
	link2 = add_link(room2, room1->room_nbr, names);
	link1->room = link2;
	link2->room = link1;
	link1->status = 1;
	link2->status = 1;
}

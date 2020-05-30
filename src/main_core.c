/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:44:14 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/27 22:39:20 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		room_connector(char *name1, char *name2, char **names)
{
	t_room	*room1;
	t_room	*room2;
	t_room	*curr;

	if (!(ft_strcmp(name1, name2)) && free_strsplit(names))
		error_func("Map Error! Same room relinks not allowed.");
	room1 = NULL;
	room2 = NULL;
	curr = t_map.rooms;
	while (curr)
	{
		if (room1 == NULL && (!(ft_strcmp(name1, curr->name))))
			room1 = curr;
		else if (room2 == NULL && (!(ft_strcmp(name2, curr->name))))
			room2 = curr;
		if ((room1 != NULL && room2 != NULL) || curr->next == NULL)
			break ;
		curr = curr->next;
	}
	if ((room1 == NULL || room2 == NULL) && free_strsplit(names))
		error_func("Map Error! Link contains unknown room.");
	link_connector(room1, room2, names);
}

void		transport_core(char *buff, t_ws *wcs)
{
	ft_putendl(buff);
	while (wcs->ants_in_rooms > 0 || t_map.ants_nbr > 0)
	{
		if (wcs->ants_in_rooms > 0)
			ants_mover(wcs);
		if (t_map.ants_nbr > 0)
			ants_launcher(wcs);
		if (wcs->ants_in_rooms > 0)
			display_status(wcs);
	}
}

void		best_way_selector(char *buff)
{
	if (t_wcs.base_min->turn_nbr <= t_wcs.coll_min->turn_nbr
	&& t_wcs.base_min->turn_nbr <= t_wcs.deep_min->turn_nbr)
		transport_core(buff, t_wcs.base_min);
	else if (t_wcs.coll_min->turn_nbr <= t_wcs.base_min->turn_nbr
	&& t_wcs.coll_min->turn_nbr <= t_wcs.deep_min->turn_nbr)
		transport_core(buff, t_wcs.coll_min);
	else
		transport_core(buff, t_wcs.deep_min);
}

void		lem_in_core(int fd)
{
	int		data;
	char	buff[BUFFSIZE + 1];

	if ((data = read(fd, buff, BUFFSIZE)) < 32)
		error_func("Map Error!");
	buff[data] = '\0';
	empty_lines_check(buff);
	t_map.lines = NULL;
	if (!(t_map.lines = ft_strsplit(buff, '\n')))
		error_func("Split malloc error!");
	get_map(t_map.lines);
	free_strsplit(t_map.lines);
	t_map.lines = NULL;
	algo_core();
	best_way_selector(buff);
}

int			main(int argc, char **argv)
{
	int fd;
	char	pnt;

	if (argc == 2)
	{
		if (((fd = open(argv[1], O_RDONLY))>0) && (read(fd, &pnt, 0) == 0))
		{
			lem_in_core(fd);
			free_map();
			free_ways();
		}
		else
			error_func("Incorrect format or unreadable file!");
	}
	else
		error_func("Unknown arguments!");
	return (0);
}

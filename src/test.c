/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:44:14 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 00:46:45 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	free_links(t_room *room)
{
	t_link *curr;
	t_link *next;

	next = room->links;
	room->links = NULL;
	while (next)
	{
		curr = next;
		next = next->next;
		free(curr);
		curr = NULL;
	}
}

void	free_map()
{
	t_room *curr;
	t_room *next;

	next = t_map.rooms;
	t_map.rooms = NULL;
	t_map.start = NULL;
	t_map.end = NULL;
	while (next)
	{
		curr = next;
		next = next->next;
		ft_strdel(&(curr->name));
		free_links(curr);
		free(curr);
		curr = NULL;
	}
}

void	free_ways()
{
	if (t_wcs.base_min)
		dstr_way(&(t_wcs.base_min));
	if (t_wcs.coll_min)
		dstr_way(&(t_wcs.coll_min));
	if (t_wcs.coll_cur)
		dstr_way(&(t_wcs.coll_cur));
	if (t_wcs.deep_min)
		dstr_way(&(t_wcs.deep_min));
	if (t_wcs.deep_cur)
		dstr_way(&(t_wcs.deep_cur));
	if (t_wcs.deep_smp)
		dstr_way(&(t_wcs.deep_smp));
}

void error_func(char *str)
{
	if (t_map.lines)
		free_strsplit(t_map.lines);
	free_map();
	ft_putendl(str);
	exit(0);
}

int free_strsplit(char **str)
{
	unsigned int i;

	i = 0;
	if (str == NULL || str[0] == NULL)
		return(0);
	while (str[i])
		ft_strdel(&str[i++]);
	free(str);
	str = NULL;
	return (1);
}

void full_reset()
{
	t_valid.ants_flag = 0;
	t_valid.room_flag = 0;
	t_valid.start_flag = 0;
	t_valid.end_flag = 0;
	t_valid.room_counter = 0;
	t_valid.link_counter = 0;
	t_map.ants_nbr = 0;
	t_map.mark_sts = 0;
	t_map.coll_lvl = 0;
	t_map.rooms = NULL;
	t_map.start = NULL;
	t_map.end = NULL;
}

void    room_connector(char *name1, char *name2, char **names)
{
	t_room  *room1;
	t_room  *room2;
	t_room  *curr;

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
			break;
		curr = curr->next;
	}
	if ((room1 == NULL || room2 == NULL) && free_strsplit(names))
		error_func("Map Error! Link contains unknown room.");
	link_connector(room1, room2, names);
}

t_room* get_next_room(t_link *curr, int price)
{
	while (curr)
	{
		if (curr->room->status == 1
		&& curr->room->home->price > price)
			return (curr->room->home);
		curr = curr->next;
	}
	return (NULL);
}

void best_way_selector(char *buff)
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

void lem_in_core(void)
{
	int data;
	char buff[BUFFSIZE + 1];

	if ((data = read(0, buff, BUFFSIZE)) < 32)
		error_func("Map Error!");
	buff[data] = '\0';
	empty_lines_check(buff);
	t_map.lines = NULL;
	if (!(t_map.lines = ft_strsplit(buff, '\n')))
		error_func("Split malloc error!");
	get_map(t_map.lines);
	free_strsplit(t_map.lines);
	algo_core();
	best_way_selector(buff);
}

int main(int argc, char **argv)
{    
	char pnt;

	if (argc == 1)
	{
		if ((read(0, &pnt,0) == 0))
		{
			argv[1] = '\0';
			lem_in_core();
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

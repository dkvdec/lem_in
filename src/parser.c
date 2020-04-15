/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:11:47 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/15 10:39:21 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int name_len(char *line)
{
	int i;

	i = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if (i < 1)
		error_func("Map Error! Room name error.");
	return (i);
}

int	get_room_nbr(char *room_name)
{
	int i;

	i = 0;
	while (t_rooms.room_list[i])
	{
		if (!(ft_strcmp(t_rooms.room_list[i], room_name)))
			return (i);
		i++;
	}
	error_func("Map Error! Link contains unknown room.");
	return (0);
}

void make_link_matrix()
{
	int i;
	int j;

	t_links.max_size = t_valid.rooms_counter;
	if (!(t_links.room_links =
	(int**)malloc(sizeof(int*) * t_links.max_size)))
		error_func("Malloc Error!");
	i = 0;
	while (i < t_links.max_size)
	{
		if (!(t_links.room_links[i] =
		(int*)malloc(sizeof(int) * t_links.max_size)))
			error_func("Malloc Error!");
		j = 0;
		while (j < t_links.max_size)
			t_links.room_links[i][j++] = 0;
		i++;
	}
}

void free_strsplit(char **str)
{
	unsigned int i;

	i = 0;
	while (str[i])
		ft_strdel(&str[i++]);
	free(str);
	str = NULL;
}

void link_to_matrix(char *line)
{
	int room1;
	int room2;
	char **rooms;

	if (!(rooms = ft_strsplit(line, '-')))
		error_func("Malloc Error!");
	room1 = get_room_nbr(rooms[0]);
	room2 = get_room_nbr(rooms[1]);
	free_strsplit(rooms);
	if (t_links.room_links[room1][room2] == 0)
		t_links.room_links[room1][room2] = 2147483647;
	else
		error_func("Map Error! Map contains room relinks.");
	if (t_links.room_links[room2][room1] == 0)
		t_links.room_links[room2][room1] = 2147483647;
	else
		error_func("Map Error! Map contains room relinks.");
}

void parse_links(char **lines)
{
	int i;

	make_link_matrix();
	i = t_valid.links_begin;
	while (lines[i])
	{
		if (lines[i][0] == '#')
			i++;
		else
		{
			link_to_matrix(lines[i]);
			i++;
		}
	}
}

void check_room_duplicates()
{
	int i;
	int j;

	i = 0;
	while (i + 1 < t_valid.rooms_counter)
	{
		j = i + 1;
		while (j < t_valid.rooms_counter)
		{
			if (!(ft_strcmp(t_rooms.room_list[i], t_rooms.room_list[j])))
				error_func("Map Error! Map contains room duplicates.");
			j++;
		}
		i++;
	}
	//ft_printf(">>>NO ROOM DUPLICATES\n");
}

void parse_rooms(char **lines)
{
	// malloc space for rooms
	// numerise rooms
	// check for duplicates
	int i;
	int j;
	int len;

	if (!(t_rooms.room_list =
	(char**)malloc(sizeof(char*) * (t_valid.rooms_counter + 1))))
		error_func("Malloc Error!");
	t_rooms.room_list[t_valid.rooms_counter] = NULL;
	i = t_valid.rooms_begin;
	j = 0;
	while (i < t_valid.links_begin && j < t_valid.rooms_counter)
	{
		if (lines[i][0] != '#')
		{
			len = name_len(lines[i]);
			if (!(t_rooms.room_list[j] = ft_strsub(lines[i], 0, len)))
				error_func("Malloc Error!");
			if (i == t_valid.start_line)
				t_rooms.start_room_nbr = j;
			if (i == t_valid.end_line)
				t_rooms.end_room_nbr = j;
			j++;
		}
		i++;
	}
}

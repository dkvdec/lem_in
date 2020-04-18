/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:25:03 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/18 13:09:15 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void		get_ants_nbr(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (ft_isdigit(line[i]))
			i++;
		else
			error_func("Map Error! Invalid ants number.");		
	}
	if (i > 10 || (i == 10 && exception_check(line)))
		error_func("Map Error! Invalid ants number.");
	if ((t_map.ants_nbr = ft_atoi(line)) < 1)
		error_func("Map Error! Invalid ants number.");
	t_valid.ants_flag = 1;
}

void get_command(char *line)
{
	if (line[1] != '#')
		return ;
	if (!(ft_strcmp("##start", line)))
	{
		if (t_valid.start_flag == 0)
			t_valid.start_flag = -1;
		else
			error_func("Map Error! Multiple ##start commands.");
	}
	if (!(ft_strcmp("##end", line)))
	{
		if (t_valid.end_flag == 0)
			t_valid.end_flag = -1;
		else
			error_func("Map Error! Multiple ##end commands.");
	}
}

void get_room(char *line)
{
	char	*name;
	int		i;

	i = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if (i < 1)
		error_func("Map Error! Room name error.");
	if (!(name = ft_strsub(line, 0, i)))
		error_func("Malloc Error!");
	if (t_valid.start_flag == -1 && t_map.start == NULL)
	{
		t_map.start = add_room(name);
		t_valid.start_flag = 1;
	}
	else if (t_valid.end_flag == -1 && t_map.end == NULL)
	{
		t_map.end = add_room(name);
		t_valid.end_flag = 1;
	}
	else if (t_valid.start_flag == -1 || t_valid.end_flag == -1)
		error_func("Map Error! Multiple ##start or ##end commnads.");
	else
		add_room(name);
}

void get_link(char *line)
{
	char **names;

	if (!(is_link(line)))
		error_func("Map Error! Map contains invalid lines.");
	if (t_valid.start_flag != 1 || t_valid.end_flag != 1)
		error_func("Map Error! Missing ##start or ##end or both.");
	if (t_valid.room_counter < 2)
		error_func("Map Error! Invalid room number.");
	if (t_valid.room_flag == 0)
		t_valid.room_flag == 1;
	t_valid.link_counter++;
	if (!(names = ft_strsplit(line, '-')))
		error_func("Malloc Error!");
	room_connector(names[0], names[1]);
	free_strsplit(names);
}

void get_map(char **lines)
{
	int i;

	i = 0;
	full_reset();
	while (lines[i])
	{
		if (t_valid.ants_flag == 0)
			get_ants_nbr(lines[i++]);
		else if (lines[i][0] == '#')
			get_command(lines[i++]);
		else if (t_valid.room_flag == 0 && is_room(lines[i]))
			get_room(lines[i++]);
		else
			get_link(lines[i++]);
	}
	if (t_valid.ants_flag != 1 || t_map.ants_nbr < 1
	|| t_valid.start_flag != 1 || t_valid.end_flag != 1
	|| t_valid.room_counter < 2 || t_valid.link_counter < 1)
		error_func("Map Error! Invalid map condition.");
}

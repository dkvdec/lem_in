/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:25:03 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/18 01:08:23 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void full_reset()
{
	//s_valid && s_map reset
}
////////////////////////////////////////////////////////
int		exception_check(char *line)
{
	int		i;
	char	*int_exc;

	int_exc = "2147483647";
	i = 0;
	while (line[i])
	{
		if (line[i] > int_exc[i])
			return (1);
		i++;
	}
	return (0);
}

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
//////////////////////////////////////////////////////////
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
			t_valid.start_flag = -1;
		else
			error_func("Map Error! Multiple ##end commands.");
	}
}
////////////////////////////////////////////////////////////
int		room_check(char *line)
{
	int i;
	int j;

	i = 0;
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	if (i == 0 || line[i++] != ' ')
		return (0);
	j = i;
	while (ft_isdigit(line[j]))
		j++;
	if (i == j || line[j++] != ' ')
		return (0);
	i = j;
	while (ft_isdigit(line[i]))
		i++;
	if (i > j && line[i] == '\0')
		return (1);
	return (0);
}

int		is_room(char *line, int i)
{
	if (t_valid.ants_flag != 1)
		error_func("Map Error! Invalid or absent ant number.");
	if (line[0] == 'L')
		error_func("Map Error! Room name begins with L.");
	if (line[0] == '#' || !(room_check(line)))
		return (0);
	if (t_valid.start_flag == -1 && t_valid.end_flag == -1)
		error_func("Map Error! No room after ##start or ##end command.");
	t_valid.room_counter++;
	return (1);
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
		t_valid.start_flag == 1;
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
//////////////////////////////////////////////////////////
int		is_link(char *line)
{
	int i;
	int j;

	i = 0;
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	if (i > 0 && line[i] == '-')
		j = i + 1;
	else
		return (0);
	while (ft_isalnum(line[j]) || line[j] == '_')
		j++;
	if (i + 1 < j && line[j] == '\0')
	{
	 	t_valid.link_counter++;
	 	return (1);
	}
	return (0);
}

void get_link(char *line)
{
	if (!(is_link(line)))
		error_func("Map Error! Map contains invalid lines.");
	if (t_valid.start_flag != 1 || t_valid.end_flag != 1)
		error_func("Map Error! Missing ##start or ##end or both.");
	if (t_valid.room_counter < 2)
		error_func("Map Error! Invalid room number.");
	if (t_valid.room_flag == 0)
		t_valid.room_flag == 1;
	t_valid.link_counter++;
	//room searcher + checker
}

void get_map(char **lines)
{
	int i;

	i = 0;
	reset_struct();
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
}

void	empty_lines_check(char *buff)
{
	int i;

	i = 0;
	while(buff[i])
	{
		if (buff[i] == '\n' && buff[i + 1] == '\n')
			error_func("Map Error! Empty lines.");
		i++;
	}
}

void parser_core(int fd)
{
	int data;
	int i;
	char **lines;
	char buff[BUFFSIZE + 1];

	if ((data = read(fd, buff, BUFFSIZE)) < 32)
		error_func("Map Error!");
	buff[data] = '\0';
	empty_lines_check(buff);
	if (!(lines = ft_strsplit(buff, '\n')))
		error_func("Split malloc error!");
	get_map(lines);
	free_strsplit(lines);
}

int main(int argc, char **argv)
{    
	int fd;
	char pnt;

	if (argc < 2)
		error_func("No arguments!");
	else if (argc == 2)
	{
		if (((fd = open(argv[1], O_RDONLY)) > 0) && ((read(fd, &pnt,0) == 0)))
		{
			valid_core(fd);
			close(fd);
		}
		else
			error_func("Incorrect format or unreadable file!");
	}
	else
		error_func("Too many arguments!");
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:12:12 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/11 23:47:08 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ant_mask
** 0 < ant < max_int
**
** room_mask
** str_int_int where str shouldn't start with 'L'
**
** link_mask
** str-str both str should be known
**
** command_mask
** ##...
**
** comment_mask
** #...
*/

#include "../inc/lem_in.h"

void error_func(char *str)
{
    ft_putendl(str);
    exit(0);
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

int		is_comment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (1);
	return (0);
}

int		is_ants_nbr(char *line)
{
	// check is nbr
	// check is positive
	// check is < max_int
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
	if ((t_valid.ants_nbr = ft_atoi(line)) < 1)
		error_func("Map Error! Invalid ants number.");
	t_valid.ants_flg = 1;
	return (1);
}

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
	if (t_valid.ants_flg == 0 || line[0] == 'L')
		error_func("Map Error! Room name begins with L.");
	if (line[0] == '#' || !(room_check(line)))
		return (0);
	if (t_valid.rooms_begin == 0)
		t_valid.rooms_begin = i;
	t_valid.rooms_counter++;
	return (1);
}

int		is_se_command(char *comm_line, char *room_line, int i)
{
	if (!(ft_strcmp("##start", comm_line)))
	{
		if (is_room(room_line, i + 1))
		{
			t_valid.start_line = i + 1;
			t_valid.start_counter++;
			return (1);
		}
		else
			error_func("Map Error! Invalid start room!");
	}
	else if (!(ft_strcmp("##end", comm_line)))
	{
		if (is_room(room_line, i + 1))
		{
			t_valid.end_line = i + 1;
			t_valid.end_counter++;
			return (1);
		}
		else
			error_func("Map Error! Invalid end room!");
	}
	return (0);
}

int		is_command(char *line)
{
	if (line[0] == '#' && line[1] == '#')
		return (1);
	return (0);
}

int		is_link(char *line, int l_nbr)
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
		if (t_valid.links_begin == 0)
	 		t_valid.links_begin = l_nbr;
	 	t_valid.links_counter++;
	 	return (1);
	}
	return (0);
}

void	base_valid_result()
{
	if (!(t_valid.ants_nbr > 0
	&& t_valid.rooms_counter > 1
	&& t_valid.links_counter > 0
	&& t_valid.start_counter == 1
	&& t_valid.end_counter == 1))
		error_func("Map Error! Base validation error.");
}

void base_valid(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
	{
		if (is_comment(lines[i]))
			i++;
		else if (t_valid.ants_flg == 0 && is_ants_nbr(lines[i]))
			i++;
		else if (t_valid.links_counter == 0 && is_room(lines[i], i))
			i++;
		else if (is_se_command(lines[i], lines[i + 1], i))
			i += 2;
		else if (is_command(lines[i]))
			i++;
		else if (is_link(lines[i], i))
			i++;
		else
			error_func("Map Error!");			
	}
	base_valid_result();
	ft_putendl("base_valid done");
	parse_rooms(lines);
	ft_putendl("room_valid done");
	//test_room_list(); // tester
	check_room_duplicates();
	parse_links(lines);
	ft_putendl("parse_links done");
	//test_links_matrix(); // tester
}

void s_valid_reset()
{
	t_valid.ants_nbr = 0;
	t_valid.ants_flg = 0;
	t_valid.rooms_begin = 0;
	t_valid.rooms_counter = 0;
	t_valid.links_begin = 0;
	t_valid.links_counter = 0;
	t_valid.start_line = 0;
	t_valid.start_counter = 0;
	t_valid.end_line = 0;
	t_valid.end_counter = 0;
}

void valid_core(int fd)
{
	int data;
	int i;
	char **lines;
	char buff[BUFFSIZE + 1];

	data = read(fd, buff, BUFFSIZE);
	if (data < 30)
		error_func("Map Error!");
	buff[data] = '\0';
	empty_lines_check(buff);
	if (!(lines = ft_strsplit(buff, '\n')))
		error_func("Split malloc error!");
	s_valid_reset();
	base_valid(lines);
	ft_putendl("->base_valid done");
	test_deixtra_alg();
	ft_putendl("ways_formed done");
	transport_core(buff);
}

int main(int argc, char **argv)
{    
    int fd;
    char *pnt;

    if (argc < 2)
        error_func("No arguments!");
    else if (argc == 2)
    {
        if (((fd = open(argv[1], O_RDONLY)) > 0) && ((read(fd, pnt,0) == 0)))
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 12:14:38 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/25 08:58:40 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

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

int		is_room(char *line)
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
	if (i > 0 && buff[i - 1] != '\n')
		error_func("Map Error! Map should end with \\n.");
}

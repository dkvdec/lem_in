/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 01:23:43 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 01:29:51 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		free_links(t_room *room)
{
	t_link	*curr;
	t_link	*next;

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

void		free_map(void)
{
	t_room	*curr;
	t_room	*next;

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

void		free_ways(void)
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

int			free_strsplit(char **str)
{
	unsigned int	i;

	i = 0;
	if (str == NULL || str[0] == NULL)
		return (0);
	while (str[i])
		ft_strdel(&str[i++]);
	free(str);
	str = NULL;
	return (1);
}

void		error_func(char *str)
{
	if (t_map.lines)
		free_strsplit(t_map.lines);
	free_map();
	ft_putendl(str);
	exit(0);
}

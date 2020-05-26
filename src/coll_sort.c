/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 07:06:38 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 07:18:59 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int			check_ways_sort(t_ws *wcs)
{
	t_wh	*curr;

	curr = wcs->ways;
	while (curr->next)
	{
		if (curr->way_len > curr->next->way_len)
			return (1);
		curr = curr->next;
	}
	return (0);
}

void		sort_swap(t_wh *prev, t_wh *curr, t_wh *next)
{
	curr->next = next->next;
	next->next = curr;
	prev->next = next;
}

void		sort_operation(t_ws *wcs)
{
	t_wh	*prev;
	t_wh	*curr;
	t_wh	*next;

	prev = wcs->ways;
	curr = wcs->ways->next;
	next = wcs->ways->next->next;
	if (prev->way_len > curr->way_len)
	{
		prev->next = curr->next;
		curr->next = prev;
		wcs->ways = curr;
	}
	else
		while (next)
		{
			if (curr->way_len > next->way_len)
			{
				sort_swap(prev, curr, next);
				break ;
			}
			next = next->next;
			curr = curr->next;
			prev = prev->next;
		}
}

void		get_ways_nbr(t_ws *wcs)
{
	t_wh	*curr;

	curr = wcs->ways;
	wcs->ways_nbr = 1;
	while (curr->next)
	{
		wcs->ways_nbr++;
		curr = curr->next;
	}
}

void		resort_ways_by_len(t_ws *wcs)
{
	t_wh	*curr;

	get_ways_nbr(wcs);
	if (wcs->ways_nbr == 2
	&& wcs->ways->way_len > wcs->ways->next->way_len)
	{
		curr = wcs->ways;
		wcs->ways = wcs->ways->next;
		wcs->ways->next = curr;
		wcs->ways->next->next = NULL;
	}
	else if (wcs->ways_nbr > 2)
		while (check_ways_sort(wcs))
			sort_operation(wcs);
}

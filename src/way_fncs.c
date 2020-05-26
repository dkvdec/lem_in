/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_fncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 01:47:07 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 05:27:47 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		way_collision_reset(void)
{
	t_col.col_flg = 0;
	t_col.col_stp = 0;
	t_col.col_sts = 0;
}

void		open_ways_links(t_wh *way)
{
	t_w		*curr;
	t_link	*link;

	curr = way->start;
	while (curr->next)
	{
		link = curr->room->links;
		if (curr->next->room->room_nbr == t_map.end->room_nbr)
			break ;
		while (curr->next->room->room_nbr != link->room->home->room_nbr)
			link = link->next;
		link->status = 0;
		link->room->status = -1;
		curr = curr->next;
	}
}

void		get_way_len(t_wh *way)
{
	t_w		*curr;

	way->way_len = 1;
	curr = way->start;
	while (curr->next != NULL)
	{
		curr = curr->next;
		way->way_len++;
	}
}

void		recount_ways_len(t_ws *wcs)
{
	t_wh	*head;

	head = wcs->ways;
	while (head)
	{
		get_way_len(head);
		head = head->next;
	}
}

void		get_turn_nbr(t_ws *head)
{
	t_wh	*cur;
	int		ant_nbr;
	int		big_len;

	ant_nbr = t_map.ants_nbr;
	big_len = 0;
	head->turn_nbr = 0;
	while (ant_nbr > 0)
	{
		cur = head->ways;
		while (cur != NULL && ant_nbr > 0)
		{
			if (acess_giver(head, cur, ant_nbr))
			{
				ant_nbr--;
				if (big_len < cur->way_len)
					big_len = cur->way_len;
			}
			cur = cur->next;
		}
		head->turn_nbr++;
		big_len--;
	}
	head->turn_nbr += big_len;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_deep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 00:14:20 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/25 20:09:51 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int			way_control_system(t_ws **min, t_ws *cur, t_ws *org)
{
	if (*(min) == NULL
	|| (*min)->turn_nbr > cur->turn_nbr)
		copy_way(min, cur);
	if (cur->turn_nbr > org->turn_nbr)
		return (1);
	return (0);
}

void	way_deep_select()
{
	if (t_wcs.deep_smp)
		dstr_way(&(t_wcs.deep_smp));
	full_map_reset();
	map_reclaim(t_wcs.deep_min);
	t_wcs.stop = 0;
	while(deep_deixtra_base(t_map.start, 0, 0) > t_wcs.stop)
	{
		add_new_path(t_wcs.deep_cur);
		if (t_wcs.deep_smp == NULL
		|| t_wcs.deep_cur->turn_nbr <= t_wcs.deep_smp->turn_nbr)
			copy_way(&(t_wcs.deep_smp), t_wcs.deep_cur);
		full_map_reset();
		map_reclaim(t_wcs.deep_min);
		copy_way(&(t_wcs.deep_cur), t_wcs.deep_min);
		t_wcs.stop++;
	}
}

void algo_deep()
{
	t_wcs.deep_cur = make_ws(NULL);
	while (coll_deixtra_base(t_map.start, 0, 0) > 0)
	{
		if (t_map.coll_lvl > 0)
		{
			way_deep_select();
			if (t_wcs.deep_smp == NULL
			|| t_wcs.deep_min->turn_nbr < t_wcs.deep_smp->turn_nbr)
				break ;
			copy_way(&(t_wcs.deep_min), t_wcs.deep_smp);
    		copy_way(&(t_wcs.deep_cur), t_wcs.deep_smp);
    		full_map_reset();
			map_reclaim(t_wcs.deep_min);
		}
		else
		{
			add_new_path(t_wcs.deep_cur);
			if (t_wcs.deep_min
			&& t_wcs.deep_cur->turn_nbr > t_wcs.deep_min->turn_nbr)
				break;
			copy_way(&(t_wcs.deep_min), t_wcs.deep_cur);
			map_reset();
		}
	}
}